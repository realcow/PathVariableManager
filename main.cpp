#include "pathmanager.h"
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const std::string kConfigFileName = "config.yml";

int main(int argc, char** argv)
{
    // change current directory to the same location as executable
    namespace filesystem = boost::filesystem;
    filesystem::path execPath(argv[0]);
    filesystem::current_path(filesystem::absolute(execPath).parent_path());
    
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    const char* kRegisterCommand = "reg";
    const char* kSetCommand = "set";
    const char* kListCommand = "list";
    desc.add_options()
        (kRegisterCommand, po::value<vector<string>>()->multitoken(), "register path")
        (kSetCommand, po::value<string>(), "set path to current path variable by name")
        (kListCommand, "list all registered pathes");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    int ret = 0;
    if (vm.count(kRegisterCommand))
    {
        auto args = vm[kRegisterCommand].as<vector<string>>();
        PathManager pathManager;
        pathManager.load(kConfigFileName);
        pathManager.registerPath(args[0], args[1]);
        pathManager.save(kConfigFileName);
    }
    else if (vm.count(kSetCommand))
    {
        string name = vm[kSetCommand].as<string>();
        PathManager pathManager;
        if (pathManager.load(kConfigFileName))
        {
            auto path = pathManager.getPathByName(name);
            if (path)
            {
                char* pathVar = getenv("PATH");
                string newPathVar = pathVar;
                if (newPathVar.back() != ';')
                {
                    newPathVar.push_back(';');
                }
                newPathVar += path.get();

                char* tempFilename = getenv("PVM_TEMPFILE");
                if (tempFilename)
                {
                    ofstream fout(tempFilename);
                    fout << newPathVar;
                    const int kErrorCodeNewPath = 9;
                    ret = kErrorCodeNewPath;
                }
            }
        }
    }
    else if (vm.count(kListCommand))
    {
        PathManager pathManager;
        if (pathManager.load(kConfigFileName))
        {
            pathManager.enumerate([](const std::string& name, const std::vector<std::string>& pathes) {
                string s;
                for (const string& path : pathes)
                {
                    s += path + ";";
                }
                s.pop_back();
                cout << name << " - " << s << endl;
            });
        }
    }
    return ret;
}