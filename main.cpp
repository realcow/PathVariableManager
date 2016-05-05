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
    const char* kDeregisterCommand = "dereg";
    const char* kSetCommand = "set";
    const char* kResetCommand = "reset";
    const char* kCdCommand = "cd";
    const char* kListCommand = "list";
    const char* kVerbose = "verbose";
    desc.add_options()
        (kRegisterCommand, po::value<vector<string>>()->multitoken(), "register path")
        (kDeregisterCommand, po::value<vector<string>>()->multitoken(), "deregister path")
        (kSetCommand, po::value<string>(), "set path to current path variable by name")
        (kResetCommand, po::value<string>(), "reset path")
        (kCdCommand, po::value<string>(), "change directory")
        (kListCommand, "list all registered pathes")
        (kVerbose, "verbose");

    po::variables_map vm;
    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);
    }
    catch (po::invalid_command_line_syntax&)
    {
        cout << "Invalid arguments";
        return 1;
    }
    catch (po::unknown_option&)
    {
        cout << "Invalid arguments";
        return 1;
    }
    po::notify(vm);

    bool verbose = (vm.count(kVerbose) != 0);
    int ret = 0;
    if (vm.count(kRegisterCommand))
    {
        auto args = vm[kRegisterCommand].as<vector<string>>();
        if (args.size() >= 2)
        {
            PathManager pathManager;
            pathManager.load(kConfigFileName);
            pathManager.registerPath(args[0], args[1]);
            pathManager.save(kConfigFileName);
        }
        else
        {
            cout << "Invalid arguments";
        }
    }
    else if (vm.count(kDeregisterCommand))
    {
        auto args = vm[kDeregisterCommand].as<vector<string>>();
        PathManager pathManager;
        pathManager.load(kConfigFileName);
        pathManager.deregisterPath(args[0]);
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
                    cout << "New path was added successfully!"
                        << " (" << *path << ")" << endl;
                    if (verbose)
                    {
                        cout << "Old path var: " << pathVar << endl
                            << "New path var: " << newPathVar << endl;
                    }
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
    else if (vm.count(kCdCommand))
    {
        string name = vm[kCdCommand].as<string>();
        PathManager pathManager;
        if (pathManager.load(kConfigFileName))
        {
            auto path = pathManager.getPathByName(name);
            if (path)
            {
                char* tempFilename = getenv("PVM_TEMPFILE");
                if (tempFilename)
                {
                    ofstream fout(tempFilename);
                    string dirToChange = *path;
                    auto i = dirToChange.find(';');
                    if (i != string::npos)
                    {
                        dirToChange.erase(i);
                    }
                    fout << "CD /D " << dirToChange;
                    const int kErrorCodeRun = 8;
                    ret = kErrorCodeRun;
                }
            }
        }
    }
    return ret;
}