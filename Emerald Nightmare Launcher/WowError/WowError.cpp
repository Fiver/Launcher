// WowError.cpp : main project file.

#include "boost\filesystem\path.hpp"
#include "boost\filesystem\operations.hpp"
#include <iostream>

using namespace std;
namespace bfs = boost::filesystem;

//************************************
// Method:    main
// FullName:  main
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: int argc
// Parameter: char * argv[]
// Comment: Called from WoW.exe, prints error text (from command line) and saves it to file under Errors\WowError.exe.log (directory created by wow.exe)
//************************************
bool main(int argc, char *argv[])
	{

#if (!_DEBUG)
	bfs::path wowexe("wow.exe");

	if( !bfs::exists(wowexe) )
		{
		cout << "This program must called from wow.exe!" << endl;
		cin.get();
		return 1;
		}
#endif

#if (_DEBUG)

	OutputDebugString("\nWow.exe check skipped in debug.\n");

#endif

	int i;
	if (argc == 1)
		{
		cout << "This program must called from wow.exe!" << endl;
		return 0;
		}
	else for (i = 0; i < argc; i++)
		{
		cout << ("argv[%d] is %s\n", i, argv[i]) << endl;
		}

	ofstream myfile;
	myfile.open("Errors\\WowError.exe.log");
	int il;
	for (il = 0; il < argc; il++)
		{
		myfile << ("argv[%d] is %s\n", il, argv[il]);
		}
	myfile.close();

	cout << "\n\n" << endl;
	cout << "World of Warcraft has crashed" << endl;
	cout << "\n\n" << endl;
	cout << "A crash report has been saved in \"World of Warcraft\\Errors\"\n\nupload this file (and the related client made dump file) to mediafire if you are able to reproduce this bug\nand make a report,\nlinking this crashdump on our Marforius-Client github \"issues\" section." << endl;
	cout << "\n\n" << endl;
	cout << "This program does nothing but print these lines, as the default\nbugreporter(WowError.exe) carries a risk of reporting private server information to blizzard entertainment." << endl;
	cout << "\n\n" << endl;
	cin.get();
	return(0);
	}
