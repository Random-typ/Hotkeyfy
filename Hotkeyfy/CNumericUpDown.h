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
	/// Summary for CNumericUpDown
	/// </summary>
	public ref class CNumericUpDown : public System::Windows::Forms::UserControl
	{
	public:
		System::EventHandler^ ValueChanged;

		CNumericUpDown(void)
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
		~CNumericUpDown()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;


	private: System::ComponentModel::IContainer^ components;
	protected:

	protected:
	protected:

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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(51)));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->ForeColor = System::Drawing::Color::White;
			this->textBox1->Location = System::Drawing::Point(5, 5);
			this->textBox1->MaxLength = 5;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(27, 13);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &CNumericUpDown::textBox1_TextChanged);
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &CNumericUpDown::textBox1_KeyPress);
			// 
			// button1
			// 
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button1->Location = System::Drawing::Point(31, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(22, 23);
			this->button1->TabIndex = 1;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &CNumericUpDown::button1_Click);
			this->button1->MouseEnter += gcnew System::EventHandler(this, &CNumericUpDown::button1_MouseEnter);
			// 
			// CNumericUpDown
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Transparent;
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Name = L"CNumericUpDown";
			this->Size = System::Drawing::Size(53, 23);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		// used to un-focus the textbox
		Label^ invisibleLabel;
		double Value = 0;

		static System::Drawing::Pen^ arrowPen = gcnew System::Drawing::Pen(Colors::lightGrayBrush->Color, 2.4);
	protected:
		virtual void OnPaint(PaintEventArgs^ e) override
		{
			Graphics^ g = e->Graphics;
			g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
			
			//
			// body
			//
			System::Drawing::Rectangle bodyRect = this->ClientRectangle;

			int radius = 10;
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

			//
			// arrows
			//
			System::Drawing::Drawing2D::GraphicsPath^ bottomArrow = gcnew System::Drawing::Drawing2D::GraphicsPath();
			
			int start = textBox1->Location.X + textBox1->Size.Width + 5;

			array<System::Drawing::Point>^ bottomArrowpoints = { 
				System::Drawing::Point(start, 18),
				System::Drawing::Point(start + 5, 22),
				System::Drawing::Point(start + 10, 18)
			};
			bottomArrow->AddLines(bottomArrowpoints);

			System::Drawing::Drawing2D::GraphicsPath^ topArrow = gcnew System::Drawing::Drawing2D::GraphicsPath();

			array<System::Drawing::Point>^ topArrowPoints = {
				System::Drawing::Point(start, 13),
				System::Drawing::Point(start + 5, 9),
				System::Drawing::Point(start + 10, 13)
			};
			topArrow->AddLines(topArrowPoints);

			g->DrawPath(arrowPen, bottomArrow);
			g->DrawPath(arrowPen, topArrow);

			textBox1->Text = Value.ToString();
			if (!textBox1->Text->Contains("."))
			{
				textBox1->Text += ".0";
			}
		}

	public:
		double getValue() {
			return Value;
		}
		void setValue(double _value) {
			Value = _value;
			Refresh();
		}
		void offsetValue(double _off) {
			if (Value + _off < 0.0 || Value + _off > 100.0)
			{
				return;
			}
			Value += _off;
			textBox1->Text = Value.ToString();
			if (!textBox1->Text->Contains("."))
			{
				textBox1->Text += ".0";
			}
		}
private: System::Void textBox1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	
	if (e->KeyChar == VK_RETURN || e->KeyChar == VK_ESCAPE)
	{
		e->Handled = true;
		invisibleLabel->Focus();
		return;
	}

	if (e->KeyChar == '.')
	{
		if (textBox1->Text->Contains("."))
		{
			System::Media::SystemSounds::Exclamation->Play();
			e->Handled = true;
		}
		return;
	}

	if (!Char::IsDigit(e->KeyChar) && e->KeyChar != VK_BACK)
	{
		System::Media::SystemSounds::Exclamation->Play();
		e->Handled = true;
		return;
	}
	if (e->KeyChar == VK_BACK)
	{
		return;
	}

	String^ newInput = textBox1->Text->Insert(textBox1->SelectionStart, e->KeyChar.ToString());;
	System::Globalization::CultureInfo^ culture = gcnew System::Globalization::CultureInfo("en-US");// make it always assume period (".") for floating point numbers

	double value;
	if (!Double::TryParse(newInput, System::Globalization::NumberStyles::Any, culture, value) || value > 100)
	{
		e->Handled = true;
		System::Media::SystemSounds::Exclamation->Play();
	}
}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	System::Globalization::CultureInfo^ culture = gcnew System::Globalization::CultureInfo("en-US");// make it always assume period (".") for floating point numbers


	if (!textBox1->Text->Contains("."))
	{
		int value;
		if (Int32::TryParse(textBox1->Text, System::Globalization::NumberStyles::Any, culture, value) || value <= 100)
		{
			Value = value;
		}
	}
	else
	{
		double value;
		if (Double::TryParse(textBox1->Text, System::Globalization::NumberStyles::Any, culture, value) || value <= 100.0)
		{
			Value = value;
		}
	}
	ValueChanged->BeginInvoke(this, {}, {}, {});
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	MouseEventArgs^ mouseEvent = dynamic_cast<MouseEventArgs^>(e);
	if (mouseEvent->Y <= 15)
	{
		offsetValue(1.0);
	}
	else
	{
		offsetValue(-1.0);
	}
}
private: System::Void button1_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
	button1->FlatAppearance->MouseOverBackColor = this->BackColor;
	button1->FlatAppearance->MouseDownBackColor = this->BackColor;
	//button1->FlatAppearance->BorderColor = this->BackColor;
}
};
}
