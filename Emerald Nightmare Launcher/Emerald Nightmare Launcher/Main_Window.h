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
// to Share � to copy, distribute and transmit the work                                                                                                     //
//                                                                                                                                                          //
//                                                                                                                                                          //
// Under the following conditions:                                                                                                                          //
//                                                                                                                                                          //
// Attribution � You must attribute the work in the manner specified by the author or licensor                                                              //
//(but not in any way that suggests that they endorse you or your use of the work).                                                                         //
//                                                                                                                                                          //
// Noncommercial � You may not use this work for commercial purposes.                                                                                       //
//(this includes private servers that run for-profit donation operations, like the ones that promise something of electronic value for donations)           //
//                                                                                                                                                          //
// No Derivative Works � You may not alter, transform, or build upon this work.                                                                             //
//                                                                                                                                                          //
//                                                                                                                                                          //
// With the understanding that:                                                                                                                             //
//                                                                                                                                                          //
// Waiver � Any of the above conditions can be waived if you get permission from the copyright holder.                                                      //
// Public Domain � Where the work or any of its elements is in the public domain under applicable law, that status is in no way affected by the license.    //
// Other Rights � In no way are any of the following rights affected by the license:                                                                        //
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



//////////////////////////////////////////////////////////////////////////
// User/Project configure-able code settings                             /
//////////////////////////////////////////////////////////////////////////

// Uncomment these out and use all of them like I have or they will reset to default
// Project name(s) */
//#define PROJECT_NAME "Emerald Nightmare Launcher"
// Developer name(s)
//#define DEVELOPER_NAME "Marforius"
// License summary string
//#define LICENSE "Attribution-NonCommercial-NoDerivs 3.0 Unported"
// Additional copyright rights
//#define CR_RIGHTS "No permission is given to other projects."


// Increase this to prevent new versions from being downloaded when the text file is changed on the server to create an update
#define CURRENT_VERSION 3

// PUT YOUR REALMLIST THAT YOU WANT PLAYERS TO LOGIN TO HERE
// The client will reset to this realmlist ON EVERY LAUNCH

//#define REALMLIST "AnExampleofAProperRealmlist.example"

/* Uncomment it out or IT WILL NOT APPLY

//////////////////////////////////////////////////////////////////////////
// End User/Project configure-able code settings                         /
//////////////////////////////////////////////////////////////////////////
// Modifying anything beyond this point without knowledge of what you are/
// doing... you know already.                                            /
/////////////////////////////////////////////////////////////////////////*/



#include "stdafx.h"

using namespace std;
#pragma once

#pragma warning(disable:4996)

#include "Server_Changer_Window.h"

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
	delete ProcessName;
	}

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
	delete &fileop;
	delete [] pszFrom;
	delete lpszDir;

	}

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

inline void TurnOnDebugging(void)
	{
	ofstream myfile;
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


	myfile.close();

	delete myfile;
	}


// Since Marforius-Client has a ton of these already thrown in these are some that can be set on retail clients without any negative effects
// called via the play button (as to make the wtf file invisible to the end-user)
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

	delete myfile;
	}

namespace EmeraldNightmareLauncher {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;

	/// <summary>
	/// Summary for Main_Window
	/// </summary>
	public ref class Main_Window : public System::Windows::Forms::Form
		{
		public:
			Main_Window(void)
				{
				InitializeComponent();
				}

		protected:
			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~Main_Window()
				{
				if (components)
					{
					delete components;
					}
				}
		private: System::Windows::Forms::WebBrowser^  webBrowser1;
		private: System::Windows::Forms::Button^  button1;

		private: System::Windows::Forms::MenuStrip^  menuStrip1;
		private: System::Windows::Forms::ToolStripMenuItem^  test1ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  forceLauncherUpdateToolStripMenuItem;


		private: System::Windows::Forms::ToolStripMenuItem^  cleanupToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  consolidatePatchesToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  deleteSettingsToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  deleteNonessentialFilesToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  clientSystemChecksToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  mD5CheckArchivesToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^  deleteWarcraftsCacheToolStripMenuItem;




		private: System::Windows::Forms::ToolStripMenuItem^  marforiusClientToolStripMenuItem;

		private: System::Windows::Forms::ToolStripMenuItem^  editSavedServersToolStripMenuItem;

		private: System::Windows::Forms::ToolStripMenuItem^  developerToolStripMenuItem;

		private: System::Windows::Forms::ToolStripMenuItem^  gMToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  toggleDebugToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  downloadAddOnToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  deleteARCHIVEFrameGlueAddOnsToolStripMenuItem;
		private: System::Windows::Forms::LinkLabel^  LauncherAlertBox;
		private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
		private: System::Windows::Forms::CheckBox^  DeleteCacheCheckBox;




		private:
			/// <summary>
			/// Required designer variable.
			/// </summary>
			System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
			/// <summary>
			/// Required method for Designer support - do not modify
			/// the contents of this method with the code editor.
			/// </summary>
			void InitializeComponent(void)
				{
				System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Main_Window::typeid));
				this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
				this->button1 = (gcnew System::Windows::Forms::Button());
				this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
				this->test1ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->forceLauncherUpdateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->cleanupToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->consolidatePatchesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->deleteSettingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->deleteNonessentialFilesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->deleteWarcraftsCacheToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->clientSystemChecksToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->mD5CheckArchivesToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->marforiusClientToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->editSavedServersToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->deleteARCHIVEFrameGlueAddOnsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->developerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toggleDebugToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->gMToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->downloadAddOnToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->LauncherAlertBox = (gcnew System::Windows::Forms::LinkLabel());
				this->DeleteCacheCheckBox = (gcnew System::Windows::Forms::CheckBox());
				this->menuStrip1->SuspendLayout();
				this->SuspendLayout();
				// 
				// webBrowser1
				// 
				this->webBrowser1->AllowWebBrowserDrop = false;
				this->webBrowser1->Anchor = System::Windows::Forms::AnchorStyles::Top;
				this->webBrowser1->Location = System::Drawing::Point(0, 24);
				this->webBrowser1->Margin = System::Windows::Forms::Padding(0);
				this->webBrowser1->MinimumSize = System::Drawing::Size(20, 20);
				this->webBrowser1->Name = L"webBrowser1";
				this->webBrowser1->ScriptErrorsSuppressed = true;
				this->webBrowser1->ScrollBarsEnabled = false;
				this->webBrowser1->Size = System::Drawing::Size(636, 402);
				this->webBrowser1->TabIndex = 0;
				this->webBrowser1->Url = (gcnew System::Uri(L"http://www.assembla.com/code/emerald-nightmare-launcher/subversion/node/blob/inde" 
					L"x.html", 
					System::UriKind::Absolute));
				this->webBrowser1->DocumentCompleted += gcnew System::Windows::Forms::WebBrowserDocumentCompletedEventHandler(this, &Main_Window::webBrowser1_DocumentCompleted);
				// 
				// button1
				// 
				this->button1->AutoSize = true;
				this->button1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				this->button1->BackColor = System::Drawing::Color::Transparent;
				this->button1->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
					static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
				this->button1->FlatAppearance->BorderSize = 10;
				this->button1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Lime;
				this->button1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Green;
				this->button1->ForeColor = System::Drawing::Color::Transparent;
				this->button1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button1.Image")));
				this->button1->Location = System::Drawing::Point(489, 449);
				this->button1->Margin = System::Windows::Forms::Padding(0);
				this->button1->Name = L"button1";
				this->button1->Size = System::Drawing::Size(147, 90);
				this->button1->TabIndex = 1;
				this->button1->UseVisualStyleBackColor = false;
				this->button1->Click += gcnew System::EventHandler(this, &Main_Window::button1_Click);
				// 
				// menuStrip1
				// 
				this->menuStrip1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(44)), 
					static_cast<System::Int32>(static_cast<System::Byte>(67)));
				this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->test1ToolStripMenuItem, 
					this->cleanupToolStripMenuItem, this->clientSystemChecksToolStripMenuItem, this->marforiusClientToolStripMenuItem, this->developerToolStripMenuItem, 
					this->gMToolStripMenuItem, this->aboutToolStripMenuItem});
				this->menuStrip1->Location = System::Drawing::Point(0, 0);
				this->menuStrip1->Name = L"menuStrip1";
				this->menuStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
				this->menuStrip1->Size = System::Drawing::Size(636, 24);
				this->menuStrip1->TabIndex = 3;
				this->menuStrip1->Text = L"menuStrip1";
				// 
				// test1ToolStripMenuItem
				// 
				this->test1ToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(31)), 
					static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(67)));
				this->test1ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->forceLauncherUpdateToolStripMenuItem});
				this->test1ToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->test1ToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), 
					static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(34)));
				this->test1ToolStripMenuItem->Name = L"test1ToolStripMenuItem";
				this->test1ToolStripMenuItem->Size = System::Drawing::Size(59, 20);
				this->test1ToolStripMenuItem->Text = L"General";
				this->test1ToolStripMenuItem->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
				// 
				// forceLauncherUpdateToolStripMenuItem
				// 
				this->forceLauncherUpdateToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(14)), 
					static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(31)));
				this->forceLauncherUpdateToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->forceLauncherUpdateToolStripMenuItem->Name = L"forceLauncherUpdateToolStripMenuItem";
				this->forceLauncherUpdateToolStripMenuItem->Size = System::Drawing::Size(196, 22);
				this->forceLauncherUpdateToolStripMenuItem->Text = L"Force Launcher Update";
				this->forceLauncherUpdateToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main_Window::forceLauncherUpdateToolStripMenuItem_Click);
				// 
				// cleanupToolStripMenuItem
				// 
				this->cleanupToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(31)), 
					static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(67)));
				this->cleanupToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->consolidatePatchesToolStripMenuItem, 
					this->deleteSettingsToolStripMenuItem, this->deleteNonessentialFilesToolStripMenuItem, this->deleteWarcraftsCacheToolStripMenuItem});
				this->cleanupToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->cleanupToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), 
					static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(34)));
				this->cleanupToolStripMenuItem->Name = L"cleanupToolStripMenuItem";
				this->cleanupToolStripMenuItem->Size = System::Drawing::Size(63, 20);
				this->cleanupToolStripMenuItem->Text = L"Cleanup";
				this->cleanupToolStripMenuItem->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
				// 
				// consolidatePatchesToolStripMenuItem
				// 
				this->consolidatePatchesToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(14)), 
					static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(31)));
				this->consolidatePatchesToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->consolidatePatchesToolStripMenuItem->Name = L"consolidatePatchesToolStripMenuItem";
				this->consolidatePatchesToolStripMenuItem->Size = System::Drawing::Size(209, 22);
				this->consolidatePatchesToolStripMenuItem->Text = L"Consolidate Patches";
				this->consolidatePatchesToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main_Window::consolidatePatchesToolStripMenuItem_Click);
				// 
				// deleteSettingsToolStripMenuItem
				// 
				this->deleteSettingsToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(14)), 
					static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(31)));
				this->deleteSettingsToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->deleteSettingsToolStripMenuItem->Name = L"deleteSettingsToolStripMenuItem";
				this->deleteSettingsToolStripMenuItem->Size = System::Drawing::Size(209, 22);
				this->deleteSettingsToolStripMenuItem->Text = L"Delete Settings";
				this->deleteSettingsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main_Window::deleteSettingsToolStripMenuItem_Click);
				// 
				// deleteNonessentialFilesToolStripMenuItem
				// 
				this->deleteNonessentialFilesToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(14)), 
					static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(31)));
				this->deleteNonessentialFilesToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->deleteNonessentialFilesToolStripMenuItem->Name = L"deleteNonessentialFilesToolStripMenuItem";
				this->deleteNonessentialFilesToolStripMenuItem->Size = System::Drawing::Size(209, 22);
				this->deleteNonessentialFilesToolStripMenuItem->Text = L"Delete Non-Essential Files";
				this->deleteNonessentialFilesToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main_Window::deleteNonessentialFilesToolStripMenuItem_Click);
				// 
				// deleteWarcraftsCacheToolStripMenuItem
				// 
				this->deleteWarcraftsCacheToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(14)), 
					static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(31)));
				this->deleteWarcraftsCacheToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->deleteWarcraftsCacheToolStripMenuItem->Name = L"deleteWarcraftsCacheToolStripMenuItem";
				this->deleteWarcraftsCacheToolStripMenuItem->Size = System::Drawing::Size(209, 22);
				this->deleteWarcraftsCacheToolStripMenuItem->Text = L"Delete Warcraft\'s Cache";
				this->deleteWarcraftsCacheToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main_Window::deleteWarcraftsCacheToolStripMenuItem_Click_1);
				// 
				// clientSystemChecksToolStripMenuItem
				// 
				this->clientSystemChecksToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(31)), 
					static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(67)));
				this->clientSystemChecksToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->mD5CheckArchivesToolStripMenuItem1});
				this->clientSystemChecksToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->clientSystemChecksToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), 
					static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(34)));
				this->clientSystemChecksToolStripMenuItem->Name = L"clientSystemChecksToolStripMenuItem";
				this->clientSystemChecksToolStripMenuItem->Size = System::Drawing::Size(129, 20);
				this->clientSystemChecksToolStripMenuItem->Text = L"ClientSystem Checks";
				this->clientSystemChecksToolStripMenuItem->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
				// 
				// mD5CheckArchivesToolStripMenuItem1
				// 
				this->mD5CheckArchivesToolStripMenuItem1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(14)), 
					static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(31)));
				this->mD5CheckArchivesToolStripMenuItem1->ForeColor = System::Drawing::Color::White;
				this->mD5CheckArchivesToolStripMenuItem1->Name = L"mD5CheckArchivesToolStripMenuItem1";
				this->mD5CheckArchivesToolStripMenuItem1->Size = System::Drawing::Size(204, 22);
				this->mD5CheckArchivesToolStripMenuItem1->Text = L"Sig/MD5 Check Archives";
				this->mD5CheckArchivesToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Main_Window::mD5CheckArchivesToolStripMenuItem1_Click);
				// 
				// marforiusClientToolStripMenuItem
				// 
				this->marforiusClientToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(31)), 
					static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(67)));
				this->marforiusClientToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->editSavedServersToolStripMenuItem, 
					this->deleteARCHIVEFrameGlueAddOnsToolStripMenuItem});
				this->marforiusClientToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->marforiusClientToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), 
					static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(34)));
				this->marforiusClientToolStripMenuItem->Name = L"marforiusClientToolStripMenuItem";
				this->marforiusClientToolStripMenuItem->Size = System::Drawing::Size(106, 20);
				this->marforiusClientToolStripMenuItem->Text = L"Marforius-Client";
				this->marforiusClientToolStripMenuItem->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
				// 
				// editSavedServersToolStripMenuItem
				// 
				this->editSavedServersToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(14)), 
					static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(31)));
				this->editSavedServersToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->editSavedServersToolStripMenuItem->Name = L"editSavedServersToolStripMenuItem";
				this->editSavedServersToolStripMenuItem->Size = System::Drawing::Size(271, 22);
				this->editSavedServersToolStripMenuItem->Text = L"Edit Saved Servers";
				this->editSavedServersToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main_Window::editSavedServersToolStripMenuItem_Click);
				// 
				// deleteARCHIVEFrameGlueAddOnsToolStripMenuItem
				// 
				this->deleteARCHIVEFrameGlueAddOnsToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(12)), 
					static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(31)));
				this->deleteARCHIVEFrameGlueAddOnsToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->deleteARCHIVEFrameGlueAddOnsToolStripMenuItem->Name = L"deleteARCHIVEFrameGlueAddOnsToolStripMenuItem";
				this->deleteARCHIVEFrameGlueAddOnsToolStripMenuItem->Size = System::Drawing::Size(271, 22);
				this->deleteARCHIVEFrameGlueAddOnsToolStripMenuItem->Text = L"Delete ARCHIVE Frame/Glue/AddOns";
				this->deleteARCHIVEFrameGlueAddOnsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main_Window::deleteARCHIVEFrameGlueAddOnsToolStripMenuItem_Click);
				// 
				// developerToolStripMenuItem
				// 
				this->developerToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(31)), 
					static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(67)));
				this->developerToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->toggleDebugToolStripMenuItem});
				this->developerToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->developerToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), 
					static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(34)));
				this->developerToolStripMenuItem->Name = L"developerToolStripMenuItem";
				this->developerToolStripMenuItem->Size = System::Drawing::Size(72, 20);
				this->developerToolStripMenuItem->Text = L"Developer";
				this->developerToolStripMenuItem->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
				// 
				// toggleDebugToolStripMenuItem
				// 
				this->toggleDebugToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(12)), 
					static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(31)));
				this->toggleDebugToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->toggleDebugToolStripMenuItem->Name = L"toggleDebugToolStripMenuItem";
				this->toggleDebugToolStripMenuItem->Size = System::Drawing::Size(152, 22);
				this->toggleDebugToolStripMenuItem->Text = L"Toggle Debug";
				this->toggleDebugToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main_Window::toggleDebugToolStripMenuItem_Click);
				// 
				// gMToolStripMenuItem
				// 
				this->gMToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(31)), 
					static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(67)));
				this->gMToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->downloadAddOnToolStripMenuItem});
				this->gMToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->gMToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), 
					static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(34)));
				this->gMToolStripMenuItem->Name = L"gMToolStripMenuItem";
				this->gMToolStripMenuItem->Size = System::Drawing::Size(38, 20);
				this->gMToolStripMenuItem->Text = L"GM";
				this->gMToolStripMenuItem->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
				// 
				// downloadAddOnToolStripMenuItem
				// 
				this->downloadAddOnToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(12)), 
					static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(31)));
				this->downloadAddOnToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->downloadAddOnToolStripMenuItem->Name = L"downloadAddOnToolStripMenuItem";
				this->downloadAddOnToolStripMenuItem->Size = System::Drawing::Size(169, 22);
				this->downloadAddOnToolStripMenuItem->Text = L"Download AddOn";
				this->downloadAddOnToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main_Window::downloadAddOnToolStripMenuItem_Click);
				// 
				// aboutToolStripMenuItem
				// 
				this->aboutToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
				this->aboutToolStripMenuItem->Size = System::Drawing::Size(52, 20);
				this->aboutToolStripMenuItem->Text = L"About";
				this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main_Window::aboutToolStripMenuItem_Click);
				// 
				// LauncherAlertBox
				// 
				this->LauncherAlertBox->ActiveLinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
					static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
				this->LauncherAlertBox->BackColor = System::Drawing::Color::Transparent;
				this->LauncherAlertBox->CausesValidation = false;
				this->LauncherAlertBox->DisabledLinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
					static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
				this->LauncherAlertBox->Font = (gcnew System::Drawing::Font(L"Tahoma", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					static_cast<System::Byte>(0)));
				this->LauncherAlertBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
					static_cast<System::Int32>(static_cast<System::Byte>(0)));
				this->LauncherAlertBox->LinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
					static_cast<System::Int32>(static_cast<System::Byte>(0)));
				this->LauncherAlertBox->Location = System::Drawing::Point(-3, 449);
				this->LauncherAlertBox->Name = L"LauncherAlertBox";
				this->LauncherAlertBox->Size = System::Drawing::Size(497, 90);
				this->LauncherAlertBox->TabIndex = 4;
				// 
				// DeleteCacheCheckBox
				// 
				this->DeleteCacheCheckBox->AutoSize = true;
				this->DeleteCacheCheckBox->BackColor = System::Drawing::Color::Transparent;
				this->DeleteCacheCheckBox->ForeColor = System::Drawing::Color::White;
				this->DeleteCacheCheckBox->Location = System::Drawing::Point(12, 429);
				this->DeleteCacheCheckBox->Name = L"DeleteCacheCheckBox";
				this->DeleteCacheCheckBox->Size = System::Drawing::Size(91, 17);
				this->DeleteCacheCheckBox->TabIndex = 5;
				this->DeleteCacheCheckBox->Text = L"Delete Cache";
				this->DeleteCacheCheckBox->UseVisualStyleBackColor = false;
				this->DeleteCacheCheckBox->CheckedChanged += gcnew System::EventHandler(this, &Main_Window::DeleteCacheCheckBox_CheckedChanged);
				// 
				// Main_Window
				// 
				this->AcceptButton = this->button1;
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->AutoSize = true;
				this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(20)), 
					static_cast<System::Int32>(static_cast<System::Byte>(20)));
				this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
				this->ClientSize = System::Drawing::Size(636, 541);
				this->Controls->Add(this->DeleteCacheCheckBox);
				this->Controls->Add(this->menuStrip1);
				this->Controls->Add(this->button1);
				this->Controls->Add(this->webBrowser1);
				this->Controls->Add(this->LauncherAlertBox);
				this->DoubleBuffered = true;
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
				this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
				this->MainMenuStrip = this->menuStrip1;
				this->MaximizeBox = false;
				this->Name = L"Main_Window";
				this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				this->Text = L"Emerald Nightmare Launcher";
				this->Load += gcnew System::EventHandler(this, &Main_Window::Main_Window_Load);
				this->menuStrip1->ResumeLayout(false);
				this->menuStrip1->PerformLayout();
				this->ResumeLayout(false);
				this->PerformLayout();

				}
#pragma endregion

		private: System::Void webBrowser1_DocumentCompleted(System::Object^  sender, System::Windows::Forms::WebBrowserDocumentCompletedEventArgs^  e) {

					 // The following is a model of the update process:
					 // Download LauncherVersion.ini
					 // Open and store value in string
					 // Compare VersionAtCompile and VersionOfRemoteIni
					 // if remote greater then version at compile, then call autoupdater.exe -RunMain :: Autoupdater will delete this file, and update it with whatever is in the remote /updates/ directory
					 // fin, really simple versioning/update system

					 URLDownloadToFile ( NULL, _T("http://www.assembla.com/code/emerald-nightmare-launcher/subversion/node/blob/updates/LauncherVersion.ini"), _T("LauncherVersion.temp"), 0, NULL );

					 int VersionAtCompile=CURRENT_VERSION;

					 string VerofRemoteBeforeConvert;
					 ifstream infile;
					 infile.open ("LauncherVersion.temp");
					 getline(infile,VerofRemoteBeforeConvert);
					 infile.close();
					 delete infile;
					 remove( "LauncherVersion.temp" );

					 int VersionOfRemoteIni = atoi( VerofRemoteBeforeConvert.c_str() );

					 if(VersionOfRemoteIni > VersionAtCompile)
						 {
						 URLDownloadToFile ( NULL, _T("http://www.assembla.com/code/emerald-nightmare-launcher/subversion/node/blob/updates/AutoUpdater.exe"), _T("AutoUpdater.exe"), 0, NULL );
						 LauncherAlertBox->Text->Empty;

						 if (MessageBox::Show("An updated version is available, update to the latest version?", "Update", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
							 {
							 VerofRemoteBeforeConvert.clear();
							 VersionAtCompile = NULL;
							 VersionOfRemoteIni = NULL;
							 CreateProcessLauncher("AutoUpdater.exe -RunMain");
							 EmeraldNightmareLauncher::Main_Window::Close();
							 }


						 }
					 VerofRemoteBeforeConvert.clear();
					 VersionAtCompile = NULL;
					 VersionOfRemoteIni = NULL;
					 }
		private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
					 SetCompatibleCVARs(); // set here so it seems invisible to the user
					 //PlaySound("%appdata%\\Marforius-Launcher\\launcher-launchbutton.mp3", NULL, SND_FILENAME | SND_ASYNCH); // todo: Marforius
					 CreateProcessLauncher("wow.exe -console");
					 EmeraldNightmareLauncher::Main_Window::Close();
					 }
		private: System::Void forceLauncherUpdateToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

					 URLDownloadToFile ( NULL, _T("http://www.assembla.com/code/emerald-nightmare-launcher/subversion/node/blob/updates/AutoUpdater.exe"), _T("AutoUpdater.exe"), 0, NULL );
					 Sleep(1000);
					 CreateProcessLauncher("AutoUpdater.exe -RunMain");
					 EmeraldNightmareLauncher::Main_Window::Close();
					 }
		private: System::Void mD5CheckArchivesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 CreateProcessLauncher("StormProxy.exe -RunCHECKARCHIVES");
					 EmeraldNightmareLauncher::Main_Window::Close();
					 }
		private: System::Void deleteNonessentialFilesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

					 DeleteNonEssentialFiles();

					 LauncherAlertBox->Text->Empty;
					 LauncherAlertBox->Text = "Deleting Non-Essential files that won't be used in a private server environment(bloat)... \r\n\r\nYou should now relaunch World of Warcraft and close it to generate temporary files it needs. Realmlist.wtf is now integrated into WTF\\Config.wtf";

					 if (MessageBox::Show("Should I delete the Cinematics folder? (About 540MB of data) The game will function without them - however you will not see any opening/expansion cinematics, nor the \"fall of the lich king\" video if you click on the fountain in Dalaran.", "Cinematic Folder", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
						 {
						 DeleteDirectoryLauncher("Data\\enUS\\Interface\\Cinematics");
						 }

					 }
		private: System::Void deleteWarcraftsCacheToolStripMenuItem_Click_1(System::Object^  sender, System::EventArgs^  e) {
					 DeleteDirectoryLauncher("Cache");
					 LauncherAlertBox->Text->Empty;
					 LauncherAlertBox->Text = "Deleted Cache...";
					 }
		private: System::Void editSavedServersToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 Server_Changer_Window^ server_changer_window = gcnew Server_Changer_Window();
					 server_changer_window->Show();
					 }
		private: System::Void clientSystemCheckToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 CreateProcessLauncher("StormProxy.exe -RunCHECKARCHIVES");
					 EmeraldNightmareLauncher::Main_Window::Close();
					 }
		private: System::Void mD5CheckArchivesToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
					 CreateProcessLauncher("StormProxy.exe -RunCHECKARCHIVES");
					 EmeraldNightmareLauncher::Main_Window::Close();
					 }
		private: System::Void consolidatePatchesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 CreateProcessLauncher("StormProxy.exe -Repack");
					 EmeraldNightmareLauncher::Main_Window::Close();
					 }
		private: System::Void deleteSettingsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 DeleteDirectoryLauncher("WTF");
					 DeleteDirectoryLauncher("Cache");
					 LauncherAlertBox->Text->Empty;
					 LauncherAlertBox->Text = "Deleted Cache and Settings...";
					 }
		private: System::Void deleteARCHIVEFrameGlueAddOnsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 CreateProcessLauncher("StormProxy.exe -RunDELETEARCHIVEINTERFACEFILES");
					 EmeraldNightmareLauncher::Main_Window::Close();
					 }
		private: System::Void toggleDebugToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 if (MessageBox::Show("Debugging is obscure and is not recommended for you to turn on unless you are an addon developer, modifying the client, or changing packets.", "Debug", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
						 {

						 char buffer[MAX_PATH];
						 GetCurrentDirectory(sizeof(buffer),buffer);
						 strcat(buffer , "\\EN-Launcher.wtf");
						 int DebugOn = GetPrivateProfileInt("DEBUG", "DebugOn", 0, buffer);


						 if (DebugOn == 1)
							 {
							 WritePrivateProfileString("DEBUG", "DebugOn", "0", buffer);
							 }
						 else
							 {
							 WritePrivateProfileString("DEBUG", "DebugOn", "1", buffer);
							 TurnOnDebugging();
							 }

						 // do stuff in main load event, not here
						 // this item only generates the proper settings

						 }


					 }
		private: System::Void downloadAddOnToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 CreateProcessLauncher("AutoUpdater.exe -DownloadNightmareAdmin");
					 EmeraldNightmareLauncher::Main_Window::Close();
					 }
		private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 LauncherAlertBox->Text->Empty;
#ifndef LICENSE
					 LauncherAlertBox->Text = "Launcher wrote by Marforius for the Emerald Nightmare/Marforius-Client projects. No authorization is given for use of this launcher or related tools in other projects' launchers or toolchains. Emerald Nightmare AND all related tools by Marforius are licensed under a Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License.";
#endif
#ifdef DEVELOPER_NAME
#ifdef PROJECT_NAME
#ifdef CR_RIGHTS
#ifdef LICENSE
					LauncherAlertBox->Text = "Launcher modified by "DEVELOPER_NAME" for the "PROJECT_NAME" project. "CR_RIGHTS" "PROJECT_NAME" by "DEVELOPER_NAME" is licensed under a "LICENSE" License.";
#endif
#endif
#endif
#endif

					 }
		private: System::Void DeleteCacheCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

					 char buffer[MAX_PATH];
					 GetCurrentDirectory(sizeof(buffer),buffer);
					 strcat(buffer , "\\EN-Launcher.wtf");

					 if ( this->DeleteCacheCheckBox->Checked == true )
						 {
						 WritePrivateProfileString("CACHE", "DeleteCache", "1", buffer);
						 DeleteDirectoryLauncher("Cache");
						 LauncherAlertBox->Text->Empty;
						 LauncherAlertBox->Text = "Deleted Cache...";
						 }
					 else if ( this->DeleteCacheCheckBox->Checked == false )
						 {
						 WritePrivateProfileString("CACHE", "DeleteCache", "0", buffer);
						 }

					 }
		private: System::Void Main_Window_Load(System::Object^  sender, System::EventArgs^  e) {

					 char buffer[MAX_PATH];
					 GetCurrentDirectory(sizeof(buffer),buffer);
					 strcat(buffer , "\\EN-Launcher.wtf");
					 int DeleteCache = GetPrivateProfileInt("CACHE", "DeleteCache", 0, buffer);


					 if (DeleteCache == 1)
						 {
						 DeleteCacheCheckBox->Checked = TRUE;
						 DeleteDirectoryLauncher("Cache");
						 LauncherAlertBox->Text->Empty;
						 LauncherAlertBox->Text = "Cache Deleted.";
						 }

					 int DebugOn = GetPrivateProfileInt("DEBUG", "DebugOn", 0, buffer);


					 if (DebugOn == 1)
						 {
						 TurnOnDebugging();
						 LauncherAlertBox->Text->Empty;
						 LauncherAlertBox->Text = "Debugging on.";
						 }

					 if (DebugOn && DeleteCache)
					 {
					 LauncherAlertBox->Text->Empty;
					LauncherAlertBox->Text = "Cache Deleted... Debugging on.";
						 }
					 }
		};
	}



// TODO: edit the contents of Marforius-Client's options file
// TODO: Finish StormProxy work with repacking operations
// TODO: Delete interface/framexml/gluexml archive if Marforius-Client detected
// TODO: Check interface for more buttons without backend