#pragma once
#include "HotkeyfyColors.hpp"
#include "Rounded.hpp"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Hotkeyfy {

	/// <summary>
	/// Summary for CComboBox
	/// </summary>
	public ref class CComboBox : public System::Windows::Forms::UserControl
	{
	public:
		CComboBox(void)
		{
			InitializeComponent();
			Rounded::Rounded<Panel>^ textBoxPanel = gcnew Rounded::Rounded<Panel>(panel1, Colors::highlightGrayBrush, 10);
			textBoxPanel->Click += gcnew System::EventHandler(this, &CComboBox::panel1_Click);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CComboBox()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::ListView^ listView1;
	protected:

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
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->panel1->ForeColor = System::Drawing::SystemColors::Control;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(116, 25);
			this->panel1->TabIndex = 1;
			this->panel1->Click += gcnew System::EventHandler(this, &CComboBox::panel1_Click);
			// 
			// listView1
			// 
			this->listView1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->listView1->HideSelection = false;
			this->listView1->Location = System::Drawing::Point(0, 38);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(116, 190);
			this->listView1->TabIndex = 2;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->Visible = false;
			// 
			// CComboBox
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->panel1);
			this->ForeColor = System::Drawing::SystemColors::Control;
			this->Name = L"CComboBox";
			this->Size = System::Drawing::Size(400, 228);
			this->ResumeLayout(false);

		}
#pragma endregion
	protected:
		virtual void OnPaint(PaintEventArgs^ e) override
		{


			Graphics^ g = e->Graphics;
			g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

			System::Drawing::Drawing2D::GraphicsPath^ switchPath = gcnew System::Drawing::Drawing2D::GraphicsPath();
			switchPath->AddEllipse(RectangleF(2, 2, 20, 20));


			System::Drawing::Drawing2D::GraphicsPath^ pillPath = gcnew System::Drawing::Drawing2D::GraphicsPath();
			RectangleF pillLeft(0, 0, 22, 24);
			RectangleF pillRight(22, 0, 24, 24);
			pillPath->AddArc(pillLeft, 90, 180);
			pillPath->AddArc(pillRight, -90, 180);

			g->FillPath(Colors::orangeBrush, pillPath);



			g->FillPath(Colors::whiteBrush, switchPath);


			RectangleF textBox(0, 0, 20, 20);

			// text
			StringFormat^ format = gcnew StringFormat();
			format->Alignment = StringAlignment::Center;
			format->LineAlignment = StringAlignment::Center;

			g->DrawString(text, this->Font, gcnew SolidBrush(this->ForeColor), this->ClientRectangle, format);
		}
	private:
		String^ text;
	public:
		void setText(String^ _text) {
			text = _text;
			Refresh();
		}
	private: System::Void panel1_Click(System::Object^ sender, System::EventArgs^ e) {
		listView1->Visible = true;
	}
};
}
