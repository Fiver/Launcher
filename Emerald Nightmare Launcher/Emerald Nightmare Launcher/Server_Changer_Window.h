#include "stdafx.h"

#pragma once

#include "Main_Window.h"

namespace EmeraldNightmareLauncher {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Server_Changer_Window
	/// </summary>
	public ref class Server_Changer_Window : public System::Windows::Forms::Form
	{
	public:
		Server_Changer_Window(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Server_Changer_Window()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	protected: 

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
		System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Server_Changer_Window::typeid));
		this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
		this->SuspendLayout();
		// 
		// richTextBox1
		// 
		this->richTextBox1->Location = System::Drawing::Point(12, 12);
		this->richTextBox1->Name = L"richTextBox1";
		this->richTextBox1->Size = System::Drawing::Size(445, 478);
		this->richTextBox1->TabIndex = 0;
		this->richTextBox1->Text = L"";
		// 
		// Server_Changer_Window
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->AutoSize = true;
		this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
		this->ClientSize = System::Drawing::Size(469, 542);
		this->Controls->Add(this->richTextBox1);
		this->DoubleBuffered = true;
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
		this->MaximizeBox = false;
		this->Name = L"Server_Changer_Window";
		this->Text = L"Realmlist";
		this->Load += gcnew System::EventHandler(this, &Server_Changer_Window::Server_Changer_Window_Load);
		this->ResumeLayout(false);

			}
#pragma endregion
	private: System::Void Server_Changer_Window_Load(System::Object^  sender, System::EventArgs^  e) {
				 string contents_of_config;

				 // determine existence of realmlist.wtf
				 // else look for entry in config.wtf
				 // else  create entry in config.wtf
				 // load current realm list then
				 // read from LoginUI.lua to make list
				 // 

				 ifstream my_file("wtf\\config.wtf");

				 if( !my_file.is_open() )
					 {
					 getline(my_file, contents_of_config); // saves everything into contents_of_config
					 // todo


					 }

				 my_file.close();
				 delete my_file;
				 }
		};
}
