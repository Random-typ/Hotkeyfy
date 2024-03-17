#pragma once
#include "KeyListener.h"
#include "../Hotkeyfy-api/config.h"
#include <Shlobj.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include "resource.h"

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
			System::Windows::Forms::ListViewItem^ listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(L"Play Pause"));
			System::Windows::Forms::ListViewItem^ listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(L"Previous Track"));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
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
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(118, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(62, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Application:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(186, 6);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(430, 20);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"Spotify.exe";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(622, 6);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"choose";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->checkBox1);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Location = System::Drawing::Point(186, 32);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(511, 186);
			this->panel1->TabIndex = 3;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(91, 56);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(37, 16);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Keys";
			this->label4->TextChanged += gcnew System::EventHandler(this, &Form1::label4_TextChanged);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(10, 52);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 5;
			this->button2->Text = L"choose";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 163);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(306, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"*when checked, this hotkey won\'t be send to other applications";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(7, 139);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(100, 17);
			this->checkBox1->TabIndex = 2;
			this->checkBox1->Text = L"Consume input*";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(3, 5);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(54, 20);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Action";
			// 
			// listView1
			// 
			this->listView1->Alignment = System::Windows::Forms::ListViewAlignment::Left;
			this->listView1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listView1->HideSelection = false;
			this->listView1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(2) { listViewItem1, listViewItem2 });
			this->listView1->LabelWrap = false;
			this->listView1->Location = System::Drawing::Point(12, 32);
			this->listView1->MultiSelect = false;
			this->listView1->Name = L"listView1";
			this->listView1->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->listView1->Size = System::Drawing::Size(168, 186);
			this->listView1->TabIndex = 4;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::SmallIcon;
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
			this->checkBox2->Location = System::Drawing::Point(12, 8);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(68, 17);
			this->checkBox2->TabIndex = 5;
			this->checkBox2->Text = L"Autostart";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox2_CheckedChanged);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(704, 225);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->MaximumSize = System::Drawing::Size(720, 264);
			this->MinimumSize = System::Drawing::Size(720, 264);
			this->Name = L"Form1";
			this->Text = L"Hotkeyfy";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
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
	label2->Visible = false;
	label3->Visible = false;
	label4->Visible = false;
	button2->Visible = false;
	checkBox1->Visible = false;
	// load icon
	HICON hIcon = LoadIconA(GetModuleHandle(NULL), MAKEINTRESOURCEA(1));
	this->Icon = System::Drawing::Icon::FromHandle(System::IntPtr(hIcon));

	std::wstring path;
	path.resize(MAX_PATH);
	SHGetSpecialFolderPathW(NULL, path.data(), CSIDL_APPDATA, true);
	path.resize(wcslen(path.c_str()));
	config::load(path + L"/Hotkeyfy/config.json");

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
}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label4_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	config::setHotkeys(msclr::interop::marshal_as<std::wstring>(label2->Text), KeyListener::getKeys(), checkBox1->Checked);
}
private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	config::setHotkeys(msclr::interop::marshal_as<std::wstring>(label2->Text), KeyListener::getKeys(), checkBox1->Checked);
}
};
}
