#include <iostream>
#include <boost/program_options.hpp>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("register", po::value<vector<string>>()->multitoken(), "set compression level");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("register"))
    {
        auto args = vm["register"].as<vector<string>>();
    }

	return 0;
}