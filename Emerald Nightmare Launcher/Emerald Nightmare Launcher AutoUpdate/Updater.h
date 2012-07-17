#include "boost\filesystem\v2\operations.hpp"
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

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


	URLDownloadToFile ( NULL, "http://www.assembla.com/code/emerald-nightmare-launcher/subversion/node/blob/updates/Emerald%20Nightmare%20Launcher.exe", "Emerald Nightmare Launcher.exe", 0, NULL );
	URLDownloadToFile ( NULL, "http://www.assembla.com/code/emerald-nightmare-launcher/subversion/node/blob/updates/StormProxy.exe", "StormProxy.exe", 0, NULL );
	URLDownloadToFile ( NULL, "http://www.assembla.com/code/emerald-nightmare-launcher/subversion/node/blob/updates/WowError.exe", "WowError.exe", 0, NULL );
	}