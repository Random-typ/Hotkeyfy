#pragma once
#include "Rounded.hpp"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Hotkeyfy {

	/// <summary>
	/// Summary for Toggle
	/// </summary>
	public ref class Toggle : public System::Windows::Forms::UserControl
	{
	public:
		Toggle(void)
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
		~Toggle()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Panel^ panel2;
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
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(83)), static_cast<System::Int32>(static_cast<System::Byte>(83)),
				static_cast<System::Int32>(static_cast<System::Byte>(83)));
			this->panel1->Controls->Add(this->panel2);
			this->panel1->Location = System::Drawing::Point(3, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(324, 127);
			this->panel1->TabIndex = 0;
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::White;
			this->panel2->Location = System::Drawing::Point(3, 3);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(120, 120);
			this->panel2->TabIndex = 1;
			// 
			// Toggle
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->panel1);
			this->Name = L"Toggle";
			this->Size = System::Drawing::Size(331, 133);
			this->Load += gcnew System::EventHandler(this, &Toggle::toggle_Load);
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void toggle_Load(System::Object^ sender, System::EventArgs^ e) {
		SolidBrush^ grayBrush = gcnew SolidBrush(Color::FromArgb(83, 83, 83));
		SolidBrush^ orangeBrush = gcnew SolidBrush(Color::FromArgb(239, 87, 0));
		SolidBrush^ whiteBrush = gcnew SolidBrush(Color::FromArgb(255, 255, 255));

		Rounded::Rounded<Panel>^ backgroundPanel = gcnew Rounded::Rounded<Panel>(panel1, grayBrush, 40);
		Rounded::Rounded<Panel>^ switchPanel = gcnew Rounded::Rounded<Panel>(panel2, whiteBrush, 50);
		backgroundPanel->Controls->Add(switchPanel);

	}
	};
}
