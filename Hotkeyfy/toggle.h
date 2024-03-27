#pragma once
#include "Rounded.hpp"
#include "HotkeyfyColors.hpp"

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
		System::EventHandler^ ToggleChange;

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
			this->SuspendLayout();
			// 
			// Toggle
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Transparent;
			this->Name = L"Toggle";
			this->Size = System::Drawing::Size(42, 24);
			this->Load += gcnew System::EventHandler(this, &Toggle::toggle_Load);
			this->Click += gcnew System::EventHandler(this, &Toggle::Toggle_Click);
			this->MouseEnter += gcnew System::EventHandler(this, &Toggle::Toggle_MouseEnter);
			this->MouseLeave += gcnew System::EventHandler(this, &Toggle::Toggle_MouseLeave);
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		bool hovering = false;
		bool checked = false;
	
	public:
		bool isChecked() {
			return checked;
		}
		void setCheck(bool _checked) {
			checked = _checked;
			Refresh();
		}
	protected:
		virtual void OnPaint(PaintEventArgs^ e) override
		{
			Graphics^ g = e->Graphics;
			g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

			System::Drawing::Drawing2D::GraphicsPath^ switchPath = gcnew System::Drawing::Drawing2D::GraphicsPath();
			if (checked)
			{
				switchPath->AddEllipse(RectangleF(24, 2, 20, 20));
			}
			else {
				switchPath->AddEllipse(RectangleF(2, 2, 20, 20));
			}


			System::Drawing::Drawing2D::GraphicsPath^ pillPath = gcnew System::Drawing::Drawing2D::GraphicsPath();
			RectangleF pillLeft(0, 0, 22, 24);
			RectangleF pillRight(22, 0, 24, 24);
			pillPath->AddArc(pillLeft, 90, 180);
			pillPath->AddArc(pillRight, -90, 180);

			if (checked)
			{
				if (hovering)
				{
					g->FillPath(Colors::lightOrangeBrush, pillPath);
				}
				else
				{
					g->FillPath(Colors::orangeBrush, pillPath);
				}
			}
			else {
				if (hovering)
				{
					g->FillPath(Colors::lightGrayBrush, pillPath);
				}
				else
				{
					g->FillPath(Colors::grayBrush, pillPath);
				}
			}

			g->FillPath(Colors::whiteBrush, switchPath);
		}
	private: System::Void toggle_Load(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void Toggle_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		hovering = true;
		Refresh();
	}
	private: System::Void Toggle_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		hovering = false;
		Refresh();
	}
	private: System::Void Toggle_Click(System::Object^ sender, System::EventArgs^ e) {
		checked = !checked;
		Refresh();
		ToggleChange->BeginInvoke(this, {}, {}, {});
	}
};
}
