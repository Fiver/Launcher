#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Code.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PlayButton_clicked()
{
    SetCompatibleCVARs(); // set here so it seems invisible to the user
    //PlaySound("%appdata%\\Marforius-Launcher\\launcher-launchbutton.mp3", NULL, SND_FILENAME | SND_ASYNCH); // todo: Marforius
    CreateProcessLauncher("wow.exe -console");
    if(!IRCMode)
    {
        EmeraldNightmareLauncher::Main_Window::Close();
    }
}

void MainWindow::on_IRCModeCheckBox_clicked()
{
    char buffer[MAX_PATH];
    GetCurrentDirectory(sizeof(buffer),buffer);
    strcat(buffer , "\\EN-Launcher.wtf");

    if ( this->IRCModeCheckBox->Checked == true )
    {
        WritePrivateProfileString("General", "IrcMode", "1", buffer);
        LauncherAlertBox->Text->Empty;
        LauncherAlertBox->Text = "Window will now stay open for IRC.";
        IRCMode = true;
    }
    else if ( this->IRCModeCheckBox->Checked == false )
    {
        WritePrivateProfileString("General", "IrcMode", "0", buffer);
        LauncherAlertBox->Text->Empty;
        LauncherAlertBox->Text = "IRC mode is now off.";
        IRCMode = false;
    }
}

void MainWindow::on_DeleteCacheCheckBox_clicked()
{
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

void MainWindow::on_webView_loadFinished(bool arg1)
{
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
         ToggleWarcraftDebug();
         LauncherAlertBox->Text->Empty;
         LauncherAlertBox->Text = "Debugging on.";
     }

     int IRCModeOn = GetPrivateProfileInt("General", "IrcMode", 0, buffer);
     if (IRCModeOn == 1)
     {
         IRCModeCheckBox->Checked = TRUE;
         IRCMode = true;
     }

     if (DebugOn && DeleteCache && IRCModeOn)
     {
         LauncherAlertBox->Text->Empty;
         LauncherAlertBox->Text = "Cache Deleted... Debugging on... Window staying open for IRC";
     }
     else if (DebugOn && DeleteCache && !IRCModeOn)
     {
         LauncherAlertBox->Text->Empty;
         LauncherAlertBox->Text = "Cache Deleted... Debugging on.";
     }
     else if (DeleteCache && IRCModeOn)
     {
         LauncherAlertBox->Text->Empty;
         LauncherAlertBox->Text = "Cache Deleted... Window staying open for IRC";
     }

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
            CreateProcessLauncher("AutoUpdater.exe --RunMain");
            EmeraldNightmareLauncher::Main_Window::Close();
        }
    }
    VerofRemoteBeforeConvert.clear();
    VersionAtCompile = NULL;
    VersionOfRemoteIni = NULL;
}

void MainWindow::on_actionDelete_Non_Essential_Files_triggered()
{
    DeleteNonEssentialFiles();

    LauncherAlertBox->Text->Empty;
    LauncherAlertBox->Text = "Deleting Non-Essential files that won't be used in a private server environment(bloat)... \r\n\r\nYou should now relaunch World of Warcraft and close it to generate temporary files it needs. Realmlist.wtf is now integrated into WTF\\Config.wtf";

    if (MessageBox::Show("Should I delete the Cinematics folder? (About 540MB of data) The game will function without them - however you will not see any opening/expansion cinematics, nor the \"fall of the lich king\" video if you click on the fountain in Dalaran.", "Cinematic Folder", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
    {
        DeleteDirectoryLauncher("Data\\enUS\\Interface\\Cinematics");
    }
}

void MainWindow::on_actionDownload_GM_Addon_triggered()
{
    ShellExecute(NULL, "open", "https://github.com/Emerald-Nightmare/NightmareAdmin/zipball/master", NULL, NULL, SW_SHOWNORMAL);
    EmeraldNightmareLauncher::Main_Window::Close();
}

void MainWindow::on_actionDelete_Settings_triggered()
{
    DeleteDirectoryLauncher("WTF");
    DeleteDirectoryLauncher("Cache");
    LauncherAlertBox->Text->Empty;
    LauncherAlertBox->Text = "Deleted Cache and Settings...";
}

void MainWindow::on_actionDelete_Cache_triggered()
{
    DeleteDirectoryLauncher("Cache");
    LauncherAlertBox->Text->Empty;
    LauncherAlertBox->Text = "Deleted Cache...";
}

void MainWindow::on_actionSig_MD5_Check_Archives_triggered()
{
    CreateProcessLauncher("StormProxy.exe --RunCHECKARCHIVES");
    if(!IRCMode)
    {
        EmeraldNightmareLauncher::Main_Window::Close();
    }

}

void MainWindow::on_actionToggle_Debug_triggered()
{
    char buffer[MAX_PATH];
    GetCurrentDirectory(sizeof(buffer),buffer);
    strcat(buffer , "\\EN-Launcher.wtf");
    int DebugOn = GetPrivateProfileInt("DEBUG", "DebugOn", 0, buffer);

    if (DebugOn == 0)
    {
        if (MessageBox::Show("Debugging is obscure and is not recommended for you to turn on unless you are an addon developer, modifying the client, or changing packets.", "Debug", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
        {
            {
                WritePrivateProfileString("DEBUG", "DebugOn", "1", buffer);
                ToggleWarcraftDebug();
            }
        }
    }
    else if (DebugOn == 1)
    {
        if (MessageBox::Show("Turn off debugging?", "Debug", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
        {
            WritePrivateProfileString("DEBUG", "DebugOn", "0", buffer);
            ToggleWarcraftDebug();
        }
    }
    // do stuff in main load event, not here
    // this item only generates the proper settings
}

void MainWindow::on_actionDownload_Reccomended_Addons_triggered()
{
    ShellExecute(NULL, "open", "https://github.com/Marforius/Addons/zipball/master", NULL, NULL, SW_SHOWNORMAL);

    if(!IRCMode)
    {
        EmeraldNightmareLauncher::Main_Window::Close();
    }
}

void MainWindow::on_actionDownload_Client_triggered()
{
    ShellExecute(NULL, "open", "https://github.com/Marforius/Marforius-Client/zipball/master", NULL, NULL, SW_SHOWNORMAL);
    EmeraldNightmareLauncher::Main_Window::Close();
}

void MainWindow::on_actionDelete_Archive_Interface_Files_triggered()
{
    CreateProcessLauncher("StormProxy.exe --RunDELETEARCHIVEINTERFACEFILES");
    if(!IRCMode)
    {
        EmeraldNightmareLauncher::Main_Window::Close();
    }
}

void MainWindow::on_actionForce_Update_triggered()
{
    URLDownloadToFile ( NULL, _T("http://www.assembla.com/code/emerald-nightmare-launcher/subversion/node/blob/updates/AutoUpdater.exe"), _T("AutoUpdater.exe"), 0, NULL );
    Sleep(1000);
    CreateProcessLauncher("AutoUpdater.exe --RunMain");
    if(!IRCMode)
    {
        EmeraldNightmareLauncher::Main_Window::Close();
    }
}

void MainWindow::on_actionCredits_triggered()
{
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
