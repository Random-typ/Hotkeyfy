#pragma once
#include "HotkeyfyColors.hpp"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Hotkeyfy {

	/// <summary>
	/// Summary for CButton
	/// </summary>
	public ref class CButton : public System::Windows::Forms::UserControl
	{
	public:
		CButton(void)
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
		~CButton()
		{
			if (components)
			{
				delete components;
			}
		}

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
			this->SuspendLayout();
			// 
			// CButton
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Transparent;
			this->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Font = (gcnew System::Drawing::Font(L"Plus Jakarta Sans", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::SystemColors::Control;
			this->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->Name = L"CButton";
			this->Size = System::Drawing::Size(98, 50);
			this->MouseEnter += gcnew System::EventHandler(this, &CButton::CButton_MouseEnter);
			this->MouseLeave += gcnew System::EventHandler(this, &CButton::CButton_MouseLeave);
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		String^ text;
		bool hover = false;
	protected:
		virtual void OnPaint(PaintEventArgs^ e) override
		{
			Graphics^ g = e->Graphics;
			g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

			System::Drawing::Drawing2D::GraphicsPath^ pillPath = gcnew System::Drawing::Drawing2D::GraphicsPath();
			RectangleF pillLeft(1, 1, this->Size.Height - 2, this->Size.Height - 2);
			RectangleF pillRight(this->Size.Width - this->Size.Height, 1, this->Size.Height - 2, this->Size.Height - 2);
			if (hover)
			{
				pillLeft.Inflate(1, 1);
				pillRight.Inflate(1, 1);
			}

			pillPath->AddArc(pillLeft, 90, 180);
			pillPath->AddArc(pillRight, -90, 180);
			g->FillPath(Colors::lightOrangeBrush, pillPath);

			// text
			StringFormat^ format = gcnew StringFormat();
			format->Alignment = StringAlignment::Center;
			format->LineAlignment = StringAlignment::Center;
			
			g->DrawString(text, this->Font, gcnew SolidBrush(this->ForeColor), this->ClientRectangle, format);
		}
	public:
		void setText(String^ _text) {
			text = _text;
			Refresh();
		}
	private: System::Void CButton_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		hover = true;
		Refresh();
	}
	private: System::Void CButton_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		hover = false;
		Refresh();
	}
	};
}
