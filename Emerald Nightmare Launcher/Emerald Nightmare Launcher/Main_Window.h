#include "stdafx.h"
#include "Code.h"
using namespace std;
#pragma once

#pragma warning(disable:4996)

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

		private: System::Windows::Forms::ToolStripMenuItem^  deleteSettingsToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  deleteNonessentialFilesToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  clientSystemChecksToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  mD5CheckArchivesToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^  deleteWarcraftsCacheToolStripMenuItem;








		private: System::Windows::Forms::ToolStripMenuItem^  developerToolStripMenuItem;

		private: System::Windows::Forms::ToolStripMenuItem^  gMToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  toggleDebugToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  downloadAddOnToolStripMenuItem;

		private: System::Windows::Forms::LinkLabel^  LauncherAlertBox;
		private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
		private: System::Windows::Forms::CheckBox^  DeleteCacheCheckBox;
		private: System::Windows::Forms::ToolStripMenuItem^  addonsToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  downloadReccomendedAddonsToolStripMenuItem;
		private: System::Windows::Forms::CheckBox^  IRCModeCheckBox;




		private:
			/// <summary>
			/// Required designer variable.
			/// </summary>
			System::ComponentModel::Container ^components;
			bool IRCMode;

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
				this->deleteSettingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->deleteNonessentialFilesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->deleteWarcraftsCacheToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->clientSystemChecksToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->mD5CheckArchivesToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->developerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toggleDebugToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->addonsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->downloadReccomendedAddonsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->gMToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->downloadAddOnToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->LauncherAlertBox = (gcnew System::Windows::Forms::LinkLabel());
				this->DeleteCacheCheckBox = (gcnew System::Windows::Forms::CheckBox());
				this->IRCModeCheckBox = (gcnew System::Windows::Forms::CheckBox());
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
				this->button1->TabIndex = 0;
				this->button1->UseVisualStyleBackColor = false;
				this->button1->Click += gcnew System::EventHandler(this, &Main_Window::button1_Click);
				// 
				// menuStrip1
				// 
				this->menuStrip1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(44)), 
					static_cast<System::Int32>(static_cast<System::Byte>(67)));
				this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->test1ToolStripMenuItem, 
					this->cleanupToolStripMenuItem, this->clientSystemChecksToolStripMenuItem, this->developerToolStripMenuItem, this->addonsToolStripMenuItem, 
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
				this->cleanupToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->deleteSettingsToolStripMenuItem, 
					this->deleteNonessentialFilesToolStripMenuItem, this->deleteWarcraftsCacheToolStripMenuItem});
				this->cleanupToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->cleanupToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), 
					static_cast<System::Int32>(static_cast<System::Byte>(21)), static_cast<System::Int32>(static_cast<System::Byte>(34)));
				this->cleanupToolStripMenuItem->Name = L"cleanupToolStripMenuItem";
				this->cleanupToolStripMenuItem->Size = System::Drawing::Size(63, 20);
				this->cleanupToolStripMenuItem->Text = L"Cleanup";
				this->cleanupToolStripMenuItem->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
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
				this->toggleDebugToolStripMenuItem->Size = System::Drawing::Size(149, 22);
				this->toggleDebugToolStripMenuItem->Text = L"Toggle Debug";
				this->toggleDebugToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main_Window::toggleDebugToolStripMenuItem_Click);
				// 
				// addonsToolStripMenuItem
				// 
				this->addonsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->downloadReccomendedAddonsToolStripMenuItem});
				this->addonsToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->addonsToolStripMenuItem->Name = L"addonsToolStripMenuItem";
				this->addonsToolStripMenuItem->Size = System::Drawing::Size(60, 20);
				this->addonsToolStripMenuItem->Text = L"Addons";
				// 
				// downloadReccomendedAddonsToolStripMenuItem
				// 
				this->downloadReccomendedAddonsToolStripMenuItem->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(67)));
				this->downloadReccomendedAddonsToolStripMenuItem->ForeColor = System::Drawing::Color::White;
				this->downloadReccomendedAddonsToolStripMenuItem->Name = L"downloadReccomendedAddonsToolStripMenuItem";
				this->downloadReccomendedAddonsToolStripMenuItem->Size = System::Drawing::Size(246, 22);
				this->downloadReccomendedAddonsToolStripMenuItem->Text = L"Download recommended addons";
				this->downloadReccomendedAddonsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Main_Window::downloadReccomendedAddonsToolStripMenuItem_Click);
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
				this->downloadAddOnToolStripMenuItem->Size = System::Drawing::Size(252, 22);
				this->downloadAddOnToolStripMenuItem->Text = L"Download AddOn (for trintiycore)";
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
				// IRCModeCheckBox
				// 
				this->IRCModeCheckBox->AutoSize = true;
				this->IRCModeCheckBox->BackColor = System::Drawing::Color::Transparent;
				this->IRCModeCheckBox->ForeColor = System::Drawing::Color::White;
				this->IRCModeCheckBox->Location = System::Drawing::Point(109, 429);
				this->IRCModeCheckBox->Name = L"IRCModeCheckBox";
				this->IRCModeCheckBox->Size = System::Drawing::Size(74, 17);
				this->IRCModeCheckBox->TabIndex = 6;
				this->IRCModeCheckBox->Text = L"IRC Mode";
				this->IRCModeCheckBox->UseVisualStyleBackColor = false;
				this->IRCModeCheckBox->CheckedChanged += gcnew System::EventHandler(this, &Main_Window::IRCModeCheckBox_CheckedChanged);
				// 
				// Main_Window
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->AutoSize = true;
				this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(20)), 
					static_cast<System::Int32>(static_cast<System::Byte>(20)));
				this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
				this->ClientSize = System::Drawing::Size(636, 541);
				this->Controls->Add(this->IRCModeCheckBox);
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
		private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
					 SetCompatibleCVARs(); // set here so it seems invisible to the user
					 //PlaySound("%appdata%\\Marforius-Launcher\\launcher-launchbutton.mp3", NULL, SND_FILENAME | SND_ASYNCH); // todo: Marforius
					 CreateProcessLauncher("wow.exe -console");
					 if(!IRCMode)
						 {
						 EmeraldNightmareLauncher::Main_Window::Close();
						 }

					 }
		private: System::Void forceLauncherUpdateToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

					 URLDownloadToFile ( NULL, _T("http://www.assembla.com/code/emerald-nightmare-launcher/subversion/node/blob/updates/AutoUpdater.exe"), _T("AutoUpdater.exe"), 0, NULL );
					 Sleep(1000);
					 CreateProcessLauncher("AutoUpdater.exe --RunMain");
					 if(!IRCMode)
						 {
						 EmeraldNightmareLauncher::Main_Window::Close();
						 }

					 }
		private: System::Void mD5CheckArchivesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 CreateProcessLauncher("StormProxy.exe --RunCHECKARCHIVES");
					 if(!IRCMode)
						 {
						 EmeraldNightmareLauncher::Main_Window::Close();
						 }

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
		private: System::Void clientSystemCheckToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 CreateProcessLauncher("StormProxy.exe --RunCHECKARCHIVES");
					 if(!IRCMode)
						 {
						 EmeraldNightmareLauncher::Main_Window::Close();
						 }

					 }
		private: System::Void mD5CheckArchivesToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
					 CreateProcessLauncher("StormProxy.exe --RunCHECKARCHIVES");
					 if(!IRCMode)
						 EmeraldNightmareLauncher::Main_Window::Close();

					 }
		private: System::Void consolidatePatchesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 CreateProcessLauncher("StormProxy.exe --Repack");
					 if(!IRCMode)
						 {
						 EmeraldNightmareLauncher::Main_Window::Close();
						 }

					 }
		private: System::Void deleteSettingsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 DeleteDirectoryLauncher("WTF");
					 DeleteDirectoryLauncher("Cache");
					 LauncherAlertBox->Text->Empty;
					 LauncherAlertBox->Text = "Deleted Cache and Settings...";
					 }
		private: System::Void deleteARCHIVEFrameGlueAddOnsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 CreateProcessLauncher("StormProxy.exe --RunDELETEARCHIVEINTERFACEFILES");
					 if(!IRCMode)
						 {
						 EmeraldNightmareLauncher::Main_Window::Close();
						 }

					 }
		private: System::Void toggleDebugToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
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
		private: System::Void downloadAddOnToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 ShellExecute(NULL, "open", "https://github.com/Emerald-Nightmare/NightmareAdmin/zipball/master", NULL, NULL, SW_SHOWNORMAL);
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

					 }
		private: System::Void downloadReccomendedAddonsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
					 ShellExecute(NULL, "open", "https://github.com/Marforius/Addons/zipball/master", NULL, NULL, SW_SHOWNORMAL);

					 if(!IRCMode)
						 {
						 EmeraldNightmareLauncher::Main_Window::Close();
						 }

					 }
		private: System::Void IRCModeCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
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
		};
	};
// TODO: Finish StormProxy work with repacking operations
// TODO: Delete interface/framexml/gluexml archive if Marforius-Client detected