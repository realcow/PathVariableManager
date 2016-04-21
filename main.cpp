#include "pathmanager.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const std::string kConfigFileName = "config.yml";

int main(int argc, char** argv)
{
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    const char* kRegisterCommand = "register";
    const char* kSetCommand = "set";
    desc.add_options()
        (kRegisterCommand, po::value<vector<string>>()->multitoken(), "register path")
        (kSetCommand, po::value<string>(), "set path to current path variable by name");

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

    return ret;
}