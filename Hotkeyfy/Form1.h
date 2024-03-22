#pragma once

#ifdef _DEBUG
#define _AFXDLL
#endif //!_DEBUG

#include "KeyListener.h"
#include "../Hotkeyfy-api/config.h"
#include <Shlobj.h>

#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include "resource.h"
#include "Rounded.hpp"

#include "toggle.h"

#pragma comment(lib, "Shell32.lib")

#pragma comment(lib, "../x64/Debug/Hotkeyfy-api.lib")

namespace CppCLRWinFormsProject {

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
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::Button^ button2;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown1;

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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(137, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(71, 18);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Application:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(217, 8);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(501, 21);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"Spotify.exe";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(724, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(87, 33);
			this->button1->TabIndex = 2;
			this->button1->Text = L"choose";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->numericUpDown1);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->checkBox1);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Location = System::Drawing::Point(217, 44);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(596, 257);
			this->panel1->TabIndex = 3;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(76, 137);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(123, 16);
			this->label5->TabIndex = 8;
			this->label5->Text = L"% Volume Increase";
			this->label5->Visible = false;
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->DecimalPlaces = 1;
			this->numericUpDown1->Font = (gcnew System::Drawing::Font(L"Plus Jakarta Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numericUpDown1->Location = System::Drawing::Point(11, 133);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(57, 22);
			this->numericUpDown1->TabIndex = 7;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown1->Visible = false;
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown1_ValueChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(123, 83);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(37, 16);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Keys";
			this->label4->Visible = false;
			this->label4->TextChanged += gcnew System::EventHandler(this, &Form1::label4_TextChanged);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::White;
			this->button2->FlatAppearance->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(87)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button2->Font = (gcnew System::Drawing::Font(L"Plus Jakarta Sans", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::Color::Black;
			this->button2->Location = System::Drawing::Point(8, 64);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(106, 51);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Choose";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Visible = false;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(8, 226);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(337, 18);
			this->label3->TabIndex = 3;
			this->label3->Text = L"*when checked, this hotkey won\'t be send to other applications";
			this->label3->Visible = false;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(8, 193);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(111, 22);
			this->checkBox1->TabIndex = 2;
			this->checkBox1->Text = L"Consume input*";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->Visible = false;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(3, 7);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(54, 20);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Action";
			this->label2->Visible = false;
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
			this->listView1->Size = System::Drawing::Size(196, 257);
			this->listView1->TabIndex = 4;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::List;
			this->listView1->DrawItem += gcnew System::Windows::Forms::DrawListViewItemEventHandler(this, &Form1::listView1_DrawItem);
			this->listView1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listView1_SelectedIndexChanged);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"Applications (*.exe)|*.exe";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog1_FileOk);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Checked = true;
			this->checkBox2->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox2->Location = System::Drawing::Point(14, 11);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(75, 22);
			this->checkBox2->TabIndex = 5;
			this->checkBox2->Text = L"Autostart";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox2_CheckedChanged);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(46)), static_cast<System::Int32>(static_cast<System::Byte>(46)),
				static_cast<System::Int32>(static_cast<System::Byte>(46)));
			this->ClientSize = System::Drawing::Size(820, 311);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Font = (gcnew System::Drawing::Font(L"Plus Jakarta Sans", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->MaximumSize = System::Drawing::Size(836, 350);
			this->MinimumSize = System::Drawing::Size(836, 350);
			this->Name = L"Form1";
			this->Text = L"Hotkeyfy";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void setAction(System::String^ _name) {
		label2->Text = _name;
		std::wstring keys;
		for (auto& key : config::getHotkeys(msclr::interop::marshal_as<std::wstring>(_name)))
		{
			keys += KeyListener::getKeyName(key);
		}
		label4->Text = gcnew System::String(keys.c_str());

		if (_name == "Volume Up")
		{
			numericUpDown1->Visible = true;
			label5->Visible = true;
			label5->Text = "% Volume Increase";
		}
		else if (_name == "Volume Down")
		{
			numericUpDown1->Visible = true;
			label5->Visible = true;
			label5->Text = "% Volume Decrease";
		}
		else {
			numericUpDown1->Visible = false;
			label5->Visible = false;
		}
	}
	private: System::Void listView1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		label2->Visible = true;
		label3->Visible = true;
		label4->Visible = true;
		button2->Visible = true;
		checkBox1->Visible = true;
		ListView^ listView = (ListView^)sender;
		// this feels stupid
		for each (ListViewItem ^ selectedItem in listView->SelectedItems) {
			setAction(selectedItem->Text);
		}
	}
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
		// load icon
		HICON hIcon = LoadIconA(GetModuleHandle(NULL), MAKEINTRESOURCEA(1));
		this->Icon = System::Drawing::Icon::FromHandle(System::IntPtr(hIcon));

		std::wstring path;
		path.resize(MAX_PATH);
		SHGetSpecialFolderPathW(NULL, path.data(), CSIDL_APPDATA, true);
		path.resize(wcslen(path.c_str()));
		config::load(path + L"/Hotkeyfy/config.json");

		// make rounded controls
		SolidBrush^ orangeBrush = gcnew SolidBrush(Color::FromArgb(239, 87, 0));
		SolidBrush^ blackBrush = gcnew SolidBrush(Color::FromArgb(10, 10, 10));

		Rounded::Rounded<Button>^ button = gcnew Rounded::Rounded<Button>(button2, orangeBrush, 45);
		button->FlatStyle = button2->FlatStyle;
		button2 = button;

		Rounded::Rounded<ListView>^ listView = gcnew Rounded::Rounded<ListView>(listView1, blackBrush, 100);
		listView->BorderStyle = BorderStyle::None;
		listView->View = listView1->View;
		listView->LabelWrap = listView1->LabelWrap;
		listView->MultiSelect = listView1->MultiSelect;
		for each (ListViewItem^ item in listView1->Items) {
			ListViewItem^ newItem = (ListViewItem^)item->Clone();;
			listView->Items->Add(newItem);
		}
		listView->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listView1_SelectedIndexChanged);

		checkBox2->Checked = config::getAutoStart();


		Hotkeyfy::Toggle^ toggle = gcnew Hotkeyfy::Toggle();
		
		panel1->Controls->Add(toggle);
		toggle->Size = System::Drawing::Size(50, 50);

		KeyListener::init();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		openFileDialog1->ShowDialog();
	}
	private: System::Void openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
		textBox1->Text = System::IO::Path::GetFileName(openFileDialog1->FileName);
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		KeyListener::listen();
		timer1->Start();
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
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
		label4->Text = gcnew System::String(keys.c_str());
		if (!KeyListener::isListening())
		{
			timer1->Stop();
		}
	}
	private: System::Void Form1_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		config::save();
	}
	private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		config::setAutoStart(checkBox2->Checked);
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label4_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		config::setHotkeys(msclr::interop::marshal_as<std::wstring>(label2->Text), KeyListener::getKeys(), checkBox1->Checked);
	}
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		config::setHotkeys(msclr::interop::marshal_as<std::wstring>(label2->Text), KeyListener::getKeys(), checkBox1->Checked);
	}
	private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (label2->Text == "Volume Up")
		{
			config::setVolumeIncrement(System::Decimal::ToDouble(numericUpDown1->Value));
		}
		if (label2->Text == "Volume Down")
		{
			config::setVolumeDecrement(System::Decimal::ToDouble(numericUpDown1->Value));
		}
	}
	private: System::Void listView1_DrawItem(System::Object^ sender, System::Windows::Forms::DrawListViewItemEventArgs^ e) {
	}
	};
}
