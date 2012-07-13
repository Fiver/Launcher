#include "stdafx.h"
using namespace std; 

/*
// The following is a model of the update process:
// Download LauncherVersion.temp
// Open and store value in string
// Compare VersionAtCompile and VersionOfRemoteIni
// if remote greater then version at compile, 
//			then delete current autoupdater and download new version of it (if any)
//				then call autoupdater.exe -RunMain :: Autoupdater will then update with whatever is in the remote /updates/ directory
// fin, really simple update system
*/

//************************************
// Method:    UpdateEverything
// FullName:  UpdateEverything
// Access:    public 
// Returns:   void
// Qualifier:
// Comment: called from program being called by -RunMain
//************************************
inline void UpdateEverything()
	{
	remove( "Emerald Nightmare Launcher.exe" );
	remove( "StormProxy.exe" );
	remove( "WowError.exe" );
	remove( "WardenFix.exe" ); // DND
	remove( "LauncherVersion.ini" ); //DND


	URLDownloadToFile ( NULL, _T("http://www.assembla.com/code/emerald-nightmare-launcher/subversion/node/blob/updates/Emerald%20Nightmare%20Launcher.exe"), _T("Emerald Nightmare Launcher.exe"), 0, NULL );
	URLDownloadToFile ( NULL, _T("http://www.assembla.com/code/emerald-nightmare-launcher/subversion/node/blob/updates/StormProxy.exe"), _T("StormProxy.exe"), 0, NULL );
	URLDownloadToFile ( NULL, _T("http://www.assembla.com/code/emerald-nightmare-launcher/subversion/node/blob/updates/WowError.exe"), _T("WowError.exe"), 0, NULL );
	}

//************************************
// Method:    main
// FullName:  main
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: int argc
// Parameter: char * argv[]
// Args: -RunMain
//************************************
int main(int argc, char *argv[])
	{
	int i;
	if (argc == 1)
		{
		cout << "This program must be called by the launcher." << endl;
		cin.get();
		return 0;
		}
	else for (i = 1; i < argc; i++)
		{
		if (strcmp (argv[i], "-RunMain") == 0)
			{
			UpdateEverything();
			}
		}
	}