
#include <boost/program_options.hpp>
#include "Updater.h"
#include <iostream>
using namespace std;
namespace bpo = boost::program_options;

//************************************
// Method:    main
// FullName:  main
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: int argc
// Parameter: char * argv[]
// Args: --RunMain --help
//************************************
int main(int ac, char* av[])
	{
	if (ac == 1)
		{
		cout << "This program must be called by the launcher." << endl;
		return 0;
		}

	bpo::options_description options("command line options");
	options.add_options() ("help", "Use -h or --help to list all arguments")
		("RunMain", "to be called from launcher, will delete files and update them via the web");
	bpo::variables_map vmap;
	try{
		bpo::store(
			bpo::parse_command_line(ac, av, options), vmap);
		bpo::notify(vmap);



		if (vmap.count("help")) {
			cout << options << endl;
			}

		if (vmap.count("RunMain")) {
			UpdateEverything();
			}

		}catch ( exception e ) // Not a valid arg
		{
		cout << options << endl;
			}
	}