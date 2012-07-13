/*//////////////////////////////////////////////////////////////////////////
//        Emerald Nightmare Launcher / Generic Marforius-Client Launcher   /
//                             By Marforius                                /
//                                 Notes                                   /
////////////////////////////////////////////////////////////////////////////
// Before printing to LauncherAlertBox clear the string and the undo cache /
// by passing it "LauncherAlertBox->Text->Empty;" first, this will cause   /
// the "undo cache" to flush, as i'm using a richtextbox designed for user /
// input, it was the only thing that would color my text and give me a     /
// transparent background in windows forms.                                /
////////////////////////////////////////////////////////////////////////////
// Syntax corrections were done by ctrl+a+k+f in visual studio.            /
////////////////////////////////////////////////////////////////////////////
// If you didn't read the github page for my launcher you will need to     /
// download and install the boost library from                             /
// http://www.boostpro.com/download/ for stormproxy                        /
////////////////////////////////////////////////////////////////////////////
// You may notice that much of my code calls on the other executables to   /
// get things done, that's because windows forms need managed code, and    /
// some things are just easier to do with "normal c++", or I just didn't   /
// want to include some code in here for reasons that are obvious like the /
// automated updater that's called via the launcher                        /
////////////////////////////////////////////////////////////////////////////
// irc.rizon.net #Marforius                                                /
// https://github.com/Emerald-Nightmare/Launcher                           /
////////////////////////////////////////////////////////////////////////////
//                                 License                                 ///////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                          //
// You are free:                                                                                                                                            //
//                                                                                                                                                          //
// to Share — to copy, distribute and transmit the work                                                                                                     //
//                                                                                                                                                          //
//                                                                                                                                                          //
// Under the following conditions:                                                                                                                          //
//                                                                                                                                                          //
// Attribution — You must attribute the work in the manner specified by the author or licensor                                                              //
//(but not in any way that suggests that they endorse you or your use of the work).                                                                         //
//                                                                                                                                                          //
// Noncommercial — You may not use this work for commercial purposes.                                                                                       //
//(this includes private servers that run for-profit donation operations, like the ones that promise something of electronic value for donations)           //
//                                                                                                                                                          //
// No Derivative Works — You may not alter, transform, or build upon this work.                                                                             //
//                                                                                                                                                          //
//                                                                                                                                                          //
// With the understanding that:                                                                                                                             //
//                                                                                                                                                          //
// Waiver — Any of the above conditions can be waived if you get permission from the copyright holder.                                                      //
// Public Domain — Where the work or any of its elements is in the public domain under applicable law, that status is in no way affected by the license.    //
// Other Rights — In no way are any of the following rights affected by the license:                                                                        //
// Your fair dealing or fair use rights, or other applicable copyright exceptions and limitations;                                                          //
// The author's moral rights;                                                                                                                               //
// Rights other persons may have either in the work itself or in how the work is used, such as publicity or privacy rights.                                 //
//                                                                                                                                                          //
//                                                                                                                                                          //
// http://creativecommons.org/licenses/by-nc-nd/3.0/                                                                                                        //
// http://creativecommons.org/licenses/by-nc-nd/3.0/legalcode                                                                                               //
// Attribution-NonCommercial-NoDerivs 3.0 Unported                                                                                                          //
// (CC BY-NC-ND 3.0)                                                                                                                                        //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// The following have had this license waived:                           /
// AlterEgo (of Project Skyfire)                                         /
//////////////////////////////////////////////////////////////////////////
// Thanks:                                                               /
// Ladik(Ladislav Zezula)                                                /
// Dfighter                                                              /
// Subv (of TrinityCore)                                                 /
// Nayd (of TrinityCore)                                                 /
//////////////////////////////////////////////////////////////////////////
// As I stated on the Github page this is not complete                   /
// Also this launcher is made for the Emerald Nightmare Project, which   /
// I am working on, I will make a generic version without my logos and   /
// with a much less.. limiting license when I am done coding this version/
//////////////////////////////////////////////////////////////////////////
// I put this in because people are asking questions and forking this ;) /
///////////////////////////////////////////////////////////////////////// 
// Modifying anything beyond this point without knowledge of what you are/
// doing... you know already.                                            /
/////////////////////////////////////////////////////////////////////////*/



#include "stdafx.h"

// NOTE TO PROJECT MANAGERS OR WHOEVER IS USING THIS LAUNCHER
// The config.h file contains configurable defines you should check out before modifying the code to suit your needs!
#include "config.h"

using namespace std;
#pragma once

#pragma warning(disable:4996)

//************************************
// Method:    CreateProcessLauncher
// FullName:  CreateProcessLauncher
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: LPSTR ProcessName (Include call to executable and follow it with command line args like so: ("WoW.exe -console"))
//************************************
inline void CreateProcessLauncher(LPSTR ProcessName)
	{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	int spi=sizeof(pi);
	int ssi= sizeof(si);
	ZeroMemory( &si, sizeof(si) );
	si.cb=sizeof(STARTUPINFO); //sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	CreateProcess( NULL,
		ProcessName,    // Command line.
		NULL,            // Process handle not inheritable.
		NULL,            // Thread handle not inheritable.
		0,          // Set handle inheritance to FALSE.
		ABOVE_NORMAL_PRIORITY_CLASS,               // Do not set Warcraft higher then this, you will cause thread problems
		NULL,            // Use parent's environment block.
		NULL,            // Use parent's starting directory.
		&si,              // Pointer to STARTUPINFO structure.
		&pi );
	}

//************************************
// Method:    DeleteDirectoryLauncher
// FullName:  DeleteDirectoryLauncher
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: LPCTSTR lpszDir (Deletes file or directory, nothing special to do; accepts full path or working directory)
//************************************
inline void DeleteDirectoryLauncher(LPCTSTR lpszDir)
	{
	int len = _tcslen(lpszDir);
	TCHAR *pszFrom = new TCHAR[len+2];
	_tcscpy(pszFrom, lpszDir);
	pszFrom[len] = 0;
	pszFrom[len+1] = 0;

	SHFILEOPSTRUCT fileop;
	fileop.hwnd   = NULL;    // no status display
	fileop.wFunc  = FO_DELETE;  // delete operation
	fileop.pFrom  = pszFrom;  // source file name as double null terminated string
	fileop.pTo    = NULL;    // no destination needed
	fileop.fFlags = FOF_NOCONFIRMATION|FOF_SILENT;  // do not prompt the user

	fileop.fAnyOperationsAborted = FALSE;
	fileop.lpszProgressTitle     = NULL;
	fileop.hNameMappings         = NULL;

	SHFileOperation(&fileop);
	delete [] pszFrom;
	}

//************************************
// Method:    DeleteNonEssentialFiles
// FullName:  DeleteNonEssentialFiles
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
// Comment: Deletes files using DeleteDirectoryLauncher, called by user selecting "Delete Non-Essential Files"
//************************************
inline void DeleteNonEssentialFiles(void)
	{
	// main directory
	DeleteDirectoryLauncher("Cache");
	DeleteDirectoryLauncher("Logger.exe");
	DeleteDirectoryLauncher("Util.dll");
	DeleteDirectoryLauncher("Battle.net.dll");
	DeleteDirectoryLauncher("Changelog.URL");
	DeleteDirectoryLauncher("Create Account.URL");
	//"DivxDecoder.dll"); // see below why this is commented
	DeleteDirectoryLauncher("Features.URL");
	DeleteDirectoryLauncher("Molten Official Website.URL");
	DeleteDirectoryLauncher("Repair.exe");
	DeleteDirectoryLauncher("dbghelp.dll");
	DeleteDirectoryLauncher("ijl15.dll");
	DeleteDirectoryLauncher("msvcr80.dll");
	DeleteDirectoryLauncher("unicows.dll");

	// interface\\addons directory
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_AchievementUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_ArenaUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_AuctionUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_BarbershopUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_BattlefieldMinimap");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_BindingUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_Calendar");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_CombatLog");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_CombatText");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_DebugTools");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_GMChatUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_GMSurveyUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_GlyphUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_GuildBankUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_InspectUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_ItemSocketingUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_MacroUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_RaidUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_TalentUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_TimeManager");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_TokenUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_TradeSkillUI");
	DeleteDirectoryLauncher("Interface\\AddOns\\Blizzard_TrainerUI");

	// under data\\enUS directory
	DeleteDirectoryLauncher("Data\\enUS\\Documentation");

	//"Data\\enUS\\Interface");

	// movies, divx codec - this functionality still exists in Marforius-Client however the client will crash if movies are played WITHOUT
	// divx codec in directory, Marforius-Client just is smart enough to launch without the divx codec needed being there,
	// official client however will not load without the dll

	DeleteDirectoryLauncher("Data\\enUS\\AccountBilling.url");
	DeleteDirectoryLauncher("Data\\enUS\\Credits.html");
	DeleteDirectoryLauncher("Data\\enUS\\Credits_BC.html");
	DeleteDirectoryLauncher("Data\\enUS\\Credits_LK.html");
	DeleteDirectoryLauncher("Data\\enUS\\TechSupport.url");
	DeleteDirectoryLauncher("Data\\enUS\\connection-help.html");
	DeleteDirectoryLauncher("Data\\enUS\\eula.html");
	DeleteDirectoryLauncher("Data\\enUS\\realmlist.wtf");
	DeleteDirectoryLauncher("Data\\enUS\\tos.html");

	// don't think I missed anything as per http://torrentz.eu/35414f8be8348a08a49fc4ccfb29093e22f1d628


	// more junk
	DeleteDirectoryLauncher("Patch");
	DeleteDirectoryLauncher("Patches");
	DeleteDirectoryLauncher("Old");
	DeleteDirectoryLauncher("Logs");
	DeleteDirectoryLauncher("Errors");
	DeleteDirectoryLauncher("pgort100.dll");
	DeleteDirectoryLauncher("Logger.exe");
	DeleteDirectoryLauncher("Util.dll");
	DeleteDirectoryLauncher(".curseclient");
	DeleteDirectoryLauncher("LauncherVersion.ini");
	DeleteDirectoryLauncher("DeveloperStreamingControl.ini");
	DeleteDirectoryLauncher("wow.ini");
	DeleteDirectoryLauncher("Data\\allfiles.md5");
	DeleteDirectoryLauncher("Data\\enUS\\allfiles.md5");

	// should really rig something up to grab dev archive
	DeleteDirectoryLauncher("streamingloc.MPQ");
	DeleteDirectoryLauncher("streaming.MPQ");
	DeleteDirectoryLauncher("development.MPQ");
	DeleteDirectoryLauncher("lichkingloc.MPQ");
	DeleteDirectoryLauncher("expansionloc.MPQ");
	DeleteDirectoryLauncher("dbc.MPQ");
	DeleteDirectoryLauncher("fonts.MPQ");
	DeleteDirectoryLauncher("sound.MPQ");
	DeleteDirectoryLauncher("wmo.MPQ");
	DeleteDirectoryLauncher("terrain.MPQ");
	DeleteDirectoryLauncher("texture.MPQ");
	DeleteDirectoryLauncher("model.MPQ");
	DeleteDirectoryLauncher("misc.MPQ");
	DeleteDirectoryLauncher("interface.MPQ");
	DeleteDirectoryLauncher("alternate.MPQ");
	DeleteDirectoryLauncher("Start.MPQ");
	DeleteDirectoryLauncher("Installer Tome.MPQ");
	DeleteDirectoryLauncher("Movies.MPQ");
	DeleteDirectoryLauncher("agreements.mpq");
	DeleteDirectoryLauncher("wow-patch.mpq");
	DeleteDirectoryLauncher("Data\\base.MPQ");

	DeleteDirectoryLauncher("Data\\streamingloc.MPQ");
	DeleteDirectoryLauncher("Data\\streaming.MPQ");
	DeleteDirectoryLauncher("Data\\development.MPQ");
	DeleteDirectoryLauncher("Data\\lichkingloc.MPQ");
	DeleteDirectoryLauncher("Data\\expansionloc.MPQ");
	DeleteDirectoryLauncher("Data\\dbc.MPQ");
	DeleteDirectoryLauncher("Data\\fonts.MPQ");
	DeleteDirectoryLauncher("Data\\sound.MPQ");
	DeleteDirectoryLauncher("Data\\wmo.MPQ");
	DeleteDirectoryLauncher("Data\\terrain.MPQ");
	DeleteDirectoryLauncher("Data\\texture.MPQ");
	DeleteDirectoryLauncher("Data\\model.MPQ");
	DeleteDirectoryLauncher("Data\\misc.MPQ");
	DeleteDirectoryLauncher("Data\\interface.MPQ");
	DeleteDirectoryLauncher("Data\\alternate.MPQ");
	DeleteDirectoryLauncher("Data\\Start.MPQ");
	DeleteDirectoryLauncher("Data\\Installer Tome.MPQ");
	DeleteDirectoryLauncher("Data\\Movies.MPQ");
	DeleteDirectoryLauncher("Data\\agreements.mpq");
	DeleteDirectoryLauncher("Data\\wow-patch.mpq");
	DeleteDirectoryLauncher("Data\\base.MPQ");
	DeleteDirectoryLauncher("Data\\realmlist.wtf");
	DeleteDirectoryLauncher("Data\\enUS\\realmlist.wtf");

	// some private server stuff that's common and cleanup after myself, so that I can call this function (or a clone of) after downloading my client with the UI

	DeleteDirectoryLauncher("Buildings");
	DeleteDirectoryLauncher("Repacker");
	DeleteDirectoryLauncher("World of Warcraft.app"); // no love for mac
	DeleteDirectoryLauncher("maps");
	DeleteDirectoryLauncher("vmaps");

	}

//************************************
// Method:    ToggleWarcraftDebug
// FullName:  ToggleWarcraftDebug
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
// Comment: Toggles Warcraft's debug CVARs based on setting in EN-Launcher.wtf, can be called at any time but is called on checkbox changed and on mainwindow load
//************************************
inline void ToggleWarcraftDebug(void)
	{
	char buffer[MAX_PATH];
	GetCurrentDirectory(sizeof(buffer),buffer);
	strcat(buffer , "\\EN-Launcher.wtf");
	ofstream myfile;

	int DebugOn = GetPrivateProfileInt("DEBUG", "DebugOn", 0, buffer);



	if (DebugOn)
		{
		myfile.open("WTF\\RunOnce-Development.wtf");

		// http://wow.go-hero.net/framexml/15005/LFGFrame.lua#8 see this as to what lfgDebug does
		myfile << ("SET lfgDebug \"1\"") << endl;


		// note, too that the launcher automatically launches warcraft with the "-console" arg
		myfile << ("SET FrameXML_Debug \"1\"") << endl; // Saves detailed reports under /Logs/Framexml.log (may not be settable via cvar)
		// will code an addon later to make this cvar apply to the LuaAPI equiv, FrameXML_Debug(1);  todo: Marforius
		myfile << ("SET errorlevelmin \"0\"") << endl; // Error level minimum to report (0 = all)
		myfile << ("SET errorlevelmax \"3\"") << endl; // Error level maximum to report (3 = all)
		myfile << ("SET errorfilter \"general world ui animation models objects sound movement\"") << endl; // Types of Errors to show
		//           Filters: general world ui animation models objects sound movement all
		//			 use "except" to invert mask
		//           i.e.: all except objects"  : note that all seems not to generate any report (or see below)
		myfile << ("SET errors \"1\"") << endl; // Show errors         > see below TODO: Marforius
		myfile << ("SET showerrors \"1\"") << endl; // Show errors (may also be 2 or something weird, see disasm)
		}
	else if (!DebugOn)
		{
		myfile << ("SET lfgDebug \"0\"") << endl;
		// note, too that the launcher automatically launches warcraft with the "-console" arg
		myfile << ("SET FrameXML_Debug \"0\"") << endl; // Saves detailed reports under /Logs/Framexml.log (may not be settable via cvar)
		// will code an addon later to make this cvar apply to the LuaAPI equiv, FrameXML_Debug(1);  todo: Marforius
		myfile << ("SET errorlevelmin \"0\"") << endl; // Error level minimum to report (0 = all)
		myfile << ("SET errorlevelmax \"3\"") << endl; // Error level maximum to report (3 = all)
		myfile << ("SET errorfilter \"general\"") << endl; // Types of Errors to show
		//           Filters: general world ui animation models objects sound movement all
		//			 use "except" to invert mask
		//           i.e.: all except objects"  : note that all seems not to generate any report (or see below)
		myfile << ("SET errors \"0\"") << endl; // Show errors         > see below TODO: Marforius
		myfile << ("SET showerrors \"0\"") << endl; // Show errors (may also be 2 or something weird, see disasm)
		}


	myfile.close();
	}


// Since Marforius-Client has a ton of these already thrown in these are some that can be set on retail clients without any negative effects
// called via the play button (as to make the wtf file invisible to the end-user)
//************************************
// Method:    SetCompatibleCVARs
// FullName:  SetCompatibleCVARs
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
inline void SetCompatibleCVARs(void)
	{
	ofstream myfile;
	myfile.open("WTF\\RunOnce-Compatibles.wtf");

	myfile << ("SET expansionMovie \"0\"") << endl; // skips expansion movie on first launch
	myfile << ("SET readEULA \"1\"") << endl; // skips reading eula on first launch
	myfile << ("SET processaffinitymask \"255\"") << endl; // enables wow.exe to use all cores of a multi-processor machine
	myfile << ("SET gxapi \"d3d9ex\"") << endl; // sets graphics API to d3d9 MM2.0 (much better performance)

#ifdef REALMLIST
	// Edit this above
	myfile << ("SET realmlist \""REALMLIST"\"") << endl;
	DeleteDirectoryLauncher("Data\\enUS\\realmlist.wtf");
#endif

	myfile.close();
	}
