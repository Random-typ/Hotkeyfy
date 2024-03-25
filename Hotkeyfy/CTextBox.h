#pragma once
#include "HotkeyfyColors.hpp"
#include <Windows.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Hotkeyfy {
	/// <summary>
	/// Summary for CTextBox
	/// </summary>
	public ref class CTextBox : public System::Windows::Forms::UserControl
	{
	public:
		CTextBox(void)
		{
			InitializeComponent();
			invisibleLabel = (gcnew System::Windows::Forms::Label());
			invisibleLabel->Size.Width = 0;
			invisibleLabel->Size.Height = 0;

			Controls->Add(invisibleLabel);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CTextBox()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->textBox1->ForeColor = System::Drawing::SystemColors::Control;
			this->textBox1->Location = System::Drawing::Point(6, 5);
			this->textBox1->Margin = System::Windows::Forms::Padding(10, 3, 40, 3);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(259, 20);
			this->textBox1->TabIndex = 0;
			this->textBox1->WordWrap = false;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &CTextBox::textBox1_TextChanged);
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &CTextBox::textBox1_KeyPress);
			// 
			// CTextBox
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Transparent;
			this->Controls->Add(this->textBox1);
			this->Name = L"CTextBox";
			this->Size = System::Drawing::Size(275, 24);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		System::String^ prevText;
		Label^ invisibleLabel;

	protected:
		virtual void OnPaint(PaintEventArgs^ e) override
		{
			Graphics^ g = e->Graphics;
			g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

			//
			// body
			//
			System::Drawing::Rectangle bodyRect = this->ClientRectangle;

			int radius = 20;
			System::Drawing::Size size = System::Drawing::Size(radius, radius);
			System::Drawing::Rectangle arc = System::Drawing::Rectangle(bodyRect.Location, size);


			System::Drawing::Drawing2D::GraphicsPath^ body = gcnew System::Drawing::Drawing2D::GraphicsPath();

			body->AddArc(arc, 180, 90);
			arc.X = bodyRect.Right - radius;
			body->AddArc(arc, 270, 90);
			arc.Y = bodyRect.Bottom - radius;
			body->AddArc(arc, 0, 90);
			arc.X = bodyRect.Left;
			body->AddArc(arc, 90, 90);

			g->FillPath(Colors::highlightGrayBrush, body);

		}
		public:
			String^ getText() {
				return textBox1->Text;
			}
			void setText(String^ _text) {
				textBox1->Text = _text;
			}

private: System::Void textBox1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (e->KeyChar == VK_RETURN)
	{
		e->Handled = true;
		invisibleLabel->Focus();
		return;
	}
	if (e->KeyChar == VK_ESCAPE)
	{
		invisibleLabel->Focus();
	}

}
	   
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	if (textBox1->Text->Contains("\n"))
	{
		textBox1->Text = prevText;
	}
	else
	{
		prevText = textBox1->Text;
		this->Text = textBox1->Text;
	}
}
};
}
