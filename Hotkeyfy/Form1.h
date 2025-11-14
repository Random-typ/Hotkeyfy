#pragma once

#ifdef _DEBUG
#define _AFXDLL
#endif //!_DEBUG

#include "../Hotkeyfy-api/KeyListener.h"
#include "../Hotkeyfy-api/config.h"
#include <Shlobj.h>
#include <dwmapi.h>

#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include "resource.h"
#include "Rounded.hpp"

#include "toggle.h"
#include "CButton.h"
#include "CNumericUpDown.h"
#include "CTextBox.h"

#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "Gdi32.lib")

#ifdef _DEBUG
#pragma comment(lib, "../x64/Debug/Hotkeyfy-api.lib")
#else
#pragma comment(lib, "../x64/Release/Hotkeyfy-api.lib")
#endif // _DEBUG


namespace Hotkeyfy {

	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			ChangeTitleBarColor();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:


	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ListView^ listView1;


	private: System::Windows::Forms::Label^ label3;


	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Timer^ timer1;



	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label5;

	private: System::Windows::Forms::LinkLabel^ linkLabel1;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label9;

	private: System::ComponentModel::IContainer^ components;










	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::ListViewItem^ listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(1) { L"Play Pause" },
				-1, System::Drawing::SystemColors::ControlLight, System::Drawing::Color::Empty, nullptr));
			System::Windows::Forms::ListViewItem^ listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(1) { L"Previous Track" },
				-1, System::Drawing::SystemColors::ControlLight, System::Drawing::Color::Empty, nullptr));
			System::Windows::Forms::ListViewItem^ listViewItem3 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(1) { L"Next Track" },
				-1, System::Drawing::SystemColors::ControlLight, System::Drawing::Color::Empty, nullptr));
			System::Windows::Forms::ListViewItem^ listViewItem4 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(1) { L"Volume Up" },
				-1, System::Drawing::SystemColors::ControlLight, System::Drawing::Color::Empty, nullptr));
			System::Windows::Forms::ListViewItem^ listViewItem5 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(1) { L"Volume Down" },
				-1, System::Drawing::SystemColors::ControlLight, System::Drawing::Color::Empty, nullptr));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(139, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(71, 18);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Application:";
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(18)), static_cast<System::Int32>(static_cast<System::Byte>(18)),
				static_cast<System::Int32>(static_cast<System::Byte>(18)));
			this->panel1->Controls->Add(this->label9);
			this->panel1->Controls->Add(this->textBox1);
			this->panel1->Controls->Add(this->label8);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->label7);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Location = System::Drawing::Point(206, 44);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(435, 257);
			this->panel1->TabIndex = 3;
			this->panel1->Visible = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Plus Jakarta Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(21, 122);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(350, 20);
			this->label9->TabIndex = 13;
			this->label9->Text = L"Some keys marked with \"(special)\" might not work correctly.";
			this->label9->Visible = false;
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(18)), static_cast<System::Int32>(static_cast<System::Byte>(18)),
				static_cast<System::Int32>(static_cast<System::Byte>(18)));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Plus Jakarta Sans", 9));
			this->textBox1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(167)), static_cast<System::Int32>(static_cast<System::Byte>(167)),
				static_cast<System::Int32>(static_cast<System::Byte>(167)));
			this->textBox1->Location = System::Drawing::Point(192, 64);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(240, 40);
			this->textBox1->TabIndex = 12;
			this->textBox1->Text = L"Keys";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			this->textBox1->Enter += gcnew System::EventHandler(this, &Form1::textBox1_Enter);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Plus Jakarta Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(20, 102);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(208, 20);
			this->label8->TabIndex = 11;
			this->label8->Text = L"You are already using these keys for";
			this->label8->Visible = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Plus Jakarta Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(188, 142);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(116, 20);
			this->label5->TabIndex = 10;
			this->label5->Text = L"% Volume Increase";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Plus Jakarta Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(188, 184);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(70, 20);
			this->label7->TabIndex = 9;
			this->label7->Text = L"Consume*";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(21, 226);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(337, 18);
			this->label3->TabIndex = 3;
			this->label3->Text = L"*when checked, this hotkey won\'t be send to other applications";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Plus Jakarta Sans", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(20, 7);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(65, 28);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Action";
			// 
			// listView1
			// 
			this->listView1->BackColor = System::Drawing::Color::Black;
			this->listView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->listView1->Font = (gcnew System::Drawing::Font(L"Plus Jakarta Sans", 9.749999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listView1->HideSelection = false;
			this->listView1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(5) {
				listViewItem1, listViewItem2,
					listViewItem3, listViewItem4, listViewItem5
			});
			this->listView1->Location = System::Drawing::Point(14, 44);
			this->listView1->MultiSelect = false;
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(183, 244);
			this->listView1->TabIndex = 4;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::List;
			this->listView1->DrawItem += gcnew System::Windows::Forms::DrawListViewItemEventHandler(this, &Form1::listView1_DrawItem);
			this->listView1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listView1_SelectedIndexChanged);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->Filter = L"Applications (*.exe)|*.exe";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog1_FileOk);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(12, 11);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(56, 18);
			this->label6->TabIndex = 5;
			this->label6->Text = L"Autostart";
			// 
			// linkLabel1
			// 
			this->linkLabel1->AutoSize = true;
			this->linkLabel1->LinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->linkLabel1->Location = System::Drawing::Point(13, 287);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(109, 18);
			this->linkLabel1->TabIndex = 12;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"©Luca Trefz    v1.0.2";
			this->linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Form1::linkLabel1_LinkClicked);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(30, 259);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 18);
			this->label4->TabIndex = 13;
			// 
			// Form1
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(653, 311);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->linkLabel1);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label1);
			this->Font = (gcnew System::Drawing::Font(L"Plus Jakarta Sans", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(167)), static_cast<System::Int32>(static_cast<System::Byte>(167)),
				static_cast<System::Int32>(static_cast<System::Byte>(167)));
			this->MaximumSize = System::Drawing::Size(669, 350);
			this->MinimumSize = System::Drawing::Size(669, 350);
			this->Name = L"Form1";
			this->Text = L"Hotkeyfy";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Shown += gcnew System::EventHandler(this, &Form1::Form1_Shown);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		CTextBox^ processTextBox;
		Toggle^ consumeToggle;
		CNumericUpDown^ volumeUpDown;

		void checkKeys(::Keys _keys) {
			if (std::string action = config::alreadySet(msclr::interop::marshal_as<std::string>(label2->Text), _keys).value_or(std::string()); 
				!_keys.empty() && !action.empty())
			{
				label8->Visible = true;
				label8->Text = msclr::interop::marshal_as <System::String^>("You are already using these keys for " + action);
				return;
			}
			label8->Visible = false;
		}

		void setAction(System::String^ _name) {
			// no action selected label
			label8->Visible = false;
			panel1->Visible = true;

			label2->Text = _name;

			::Action hotkey = config::getHotkeys(msclr::interop::marshal_as<std::string>(_name));
			if (hotkey.keys.empty())
			{// default = consume
				consumeToggle->setCheck(true);
			}
			else {
				consumeToggle->setCheck(hotkey.consume);
			}

			std::wstring keys;
			for (auto& key : hotkey.keys)
			{
				if (!keys.empty())
				{
					keys += L"+";
				}
				keys += KeyListener::getKeyName(key);
			}
			if (keys.empty())
			{
				textBox1->Text = "No Hotkey set!";
			}
			else {
				textBox1->Text = msclr::interop::marshal_as<String^>(keys);
			}
			textBox1->ForeColor = Colors::lightGrayBrush->Color;

			checkKeys(hotkey.keys);

			if (_name == "Volume Up")
			{
				volumeUpDown->Visible = true;
				label5->Visible = true;
				label5->Text = "% Volume Increase";
				volumeUpDown->setValue(config::getVolumeIncrement());
			}
			else if (_name == "Volume Down")
			{
				volumeUpDown->Visible = true;
				label5->Visible = true;
				label5->Text = "% Volume Decrease";
				volumeUpDown->setValue(config::getVolumeDecrement());
			}
			else {
				volumeUpDown->Visible = false;
				label5->Visible = false;
			}
		}
		void initCustomControls() {
			// autoStart toggle
			Toggle^ autoStartToggle = gcnew Toggle();
			autoStartToggle->Location = System::Drawing::Point(70, 5);
			autoStartToggle->ToggleChange += gcnew System::EventHandler(this, &Form1::checkBox2_CheckedChanged);
			autoStartToggle->setCheck(config::getAutoStart());

			this->Controls->Add(autoStartToggle);
			
			
			// process text box
			processTextBox = gcnew CTextBox();
			processTextBox->Location = System::Drawing::Point(180, 3);
			processTextBox->setText(msclr::interop::marshal_as<String^>(config::getProcess()));
			processTextBox->TextChanged += gcnew System::EventHandler(this, &Form1::processTextBox_TextChanged);
			this->Controls->Add(processTextBox);


			// chooseProcessButton
			CButton^ chooseProcessButton = gcnew CButton();
			chooseProcessButton->Location = System::Drawing::Point(550, 3);
			chooseProcessButton->Height = 36;
			chooseProcessButton->Click += gcnew System::EventHandler(this, &Form1::processChoose_Click);
			chooseProcessButton->setText("Choose");
			this->Controls->Add(chooseProcessButton);


			// action panel
			Rounded::Rounded<Panel>^ actionPanel = gcnew Rounded::Rounded<Panel>(panel1, Colors::darkGrayBrush, 30);
			for each (System::Windows::Forms::Control ^ control in panel1->Controls)
			{
				actionPanel->Controls->Add(control);
				control->Refresh();
			}

			consumeToggle = gcnew Toggle();
			consumeToggle->Location = System::Drawing::Point(20, 131);
			consumeToggle->ToggleChange = gcnew System::EventHandler(this, &Form1::consumeInputToggle_CheckedChanged);

			actionPanel->Controls->Add(consumeToggle);

			actionPanel->Controls->Add(label2);
			actionPanel->Controls->Add(label3);
			actionPanel->Controls->Add(textBox1);
			actionPanel->Controls->Add(label5);
			actionPanel->Controls->Add(label7);
			actionPanel->Controls->Add(label8);


			// key selector button
			CButton^ keySelectorButton = gcnew CButton();
			keySelectorButton->Location = System::Drawing::Point(20, 50);
			keySelectorButton->Width = 150;
			keySelectorButton->setText("Edit Hotkey");
			keySelectorButton->Click += gcnew System::EventHandler(this, &Form1::hotkeyChoose_Click);
			keySelectorButton->Refresh();
			actionPanel->Controls->Add(keySelectorButton);


			// volume UpDown
			volumeUpDown = gcnew CNumericUpDown();
			volumeUpDown->Location = System::Drawing::Point(20, 100);
			volumeUpDown->ValueChanged += gcnew System::EventHandler(this, &Form1::volumeUpDown_ValueChanged);
			actionPanel->Controls->Add(volumeUpDown);

			panel1 = actionPanel;
		}
		void loadIcon() {
			HICON hIcon = LoadIconA(GetModuleHandle(NULL), MAKEINTRESOURCEA(1));
			this->Icon = System::Drawing::Icon::FromHandle(System::IntPtr(hIcon));
		}
		void ChangeTitleBarColor() {
			// Get the handle of the window
			HWND hwnd = (HWND)this->Handle.ToPointer();
			SetWindowLongPtr(hwnd, GWL_EXSTYLE, GetWindowLongPtr(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
			SetLayeredWindowAttributes(hwnd, RGB(255, 0, 0), 0, LWA_COLORKEY);
		}
		void enableDarkTitleBar() {
			HWND hWnd = static_cast<HWND>(Handle.ToPointer());
			BOOL USE_DARK_MODE = true;
			DwmSetWindowAttribute(
				hWnd, DWMWINDOWATTRIBUTE::DWMWA_USE_IMMERSIVE_DARK_MODE,
				&USE_DARK_MODE, sizeof(USE_DARK_MODE));
		}
		void loadConfig()
		{
			std::wstring path;
			path.resize(MAX_PATH);
			SHGetSpecialFolderPathW(NULL, path.data(), CSIDL_APPDATA, true);
			path.resize(wcslen(path.c_str()));

			config::load(path + L"/Hotkeyfy/config.json");
		}
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
		enableDarkTitleBar();

		loadIcon();

		loadConfig();

		initCustomControls();

		KeyListener::init();
		KeyListener::enableHotkeys();
		
		ListView_SetItemState(static_cast<HWND>(listView1->Handle.ToPointer()), 0, LVIS_SELECTED, LVIS_SELECTED);
	}
	private: System::Void listView1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		ListView^ listView = (ListView^)sender;
		if (listView->SelectedItems->Count)
		{
			setAction(listView->SelectedItems[0]->Text);
		}
	}
	private: System::Void processChoose_Click(System::Object^ sender, System::EventArgs^ e) {
		openFileDialog1->ShowDialog();
	}
	private: System::Void openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
		processTextBox->setText(System::IO::Path::GetFileName(openFileDialog1->FileName));
	}
	private: System::Void hotkeyChoose_Click(System::Object^ sender, System::EventArgs^ e) {
		KeyListener::listen();
		KeyListener::disableHotkeys();
		timer1->Start();
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		auto Hotkeys = config::getHotkeys(msclr::interop::marshal_as<std::string>(label2->Text));
		
		checkKeys(KeyListener::getKeys());
		
		std::wstring keys;
		for (auto& i : KeyListener::getKeys())
		{
			std::wstring key = KeyListener::getKeyName(i);
			if (keys.empty())
			{
				keys = key;
				continue;
			}
			keys += L"+" + key;
		}
		
		textBox1->ForeColor = Colors::lightOrangeBrush->Color;

		if (keys.empty())
		{
			textBox1->Text = "Press any key or key sequence...";
			
		}
		else {
			textBox1->Text = gcnew System::String(keys.c_str());
		}

		if (!KeyListener::isListening())
		{
			config::setHotkeys(msclr::interop::marshal_as<std::string>(label2->Text), KeyListener::getKeys(), consumeToggle->isChecked());

			timer1->Stop();
			KeyListener::enableHotkeys();
			textBox1->ForeColor = Color::LimeGreen;
		}
	}
	private: System::Void Form1_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		config::save();
	}
	private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		config::setAutoStart(((Toggle^)sender)->isChecked());
	}
	private: System::Void processTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		config::setProcess(msclr::interop::marshal_as<std::string>(processTextBox->Text));
		KeyListener::reloadConfig();
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		// label9->Visible = textBox1->Text->Contains("(special)");
	}
	private: System::Void consumeInputToggle_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		config::setHotkeys(msclr::interop::marshal_as<std::string>(label2->Text), {}, consumeToggle->isChecked());
	}
	private: System::Void volumeUpDown_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (label2->Text == "Volume Up")
		{
			config::setVolumeIncrement(volumeUpDown->getValue());
		}
		if (label2->Text == "Volume Down")
		{
			config::setVolumeDecrement(volumeUpDown->getValue());
		}
	}
	private: System::Void listView1_DrawItem(System::Object^ sender, System::Windows::Forms::DrawListViewItemEventArgs^ e) {
	}
	private: System::Void Form1_Shown(System::Object^ sender, System::EventArgs^ e) {
		// this fixes the white background on custom controls
		panel1->Refresh();
	}
private: System::Void linkLabel1_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
	System::Diagnostics::Process::Start(L"https://github.com/Random-typ/Hotkeyfy");
}
private: System::Void textBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
	label4->Focus();
}
};
}
