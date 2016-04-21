#include "pathmanager.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const std::string kConfigFileName = "config.yml";

int main(int argc, char** argv)
{
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("register", po::value<vector<string>>()->multitoken(), "register path");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("register"))
    {
        auto args = vm["register"].as<vector<string>>();
        PathManager pathManager;
        pathManager.load(kConfigFileName);
        pathManager.registerPath(args[0], args[1]);
        pathManager.save(kConfigFileName);
    }

	return 0;
}