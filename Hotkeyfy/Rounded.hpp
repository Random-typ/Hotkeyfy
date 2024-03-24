#pragma once

#include <Windows.h>
#include <vcclr.h>

namespace Rounded {
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;
    using namespace System::Windows::Forms;

    template<class _T>
    public ref class Rounded : public _T {
    protected:
        virtual void OnPaint(PaintEventArgs^ e) override {
            Graphics^ g = e->Graphics;
            g->SmoothingMode = SmoothingMode::AntiAlias;
            g->Clear(this->BackColor);

            System::Drawing::Rectangle rect = this->ClientRectangle;
            rect.Inflate(-4, -4);
            
            GraphicsPath^ path = gcnew GraphicsPath();
            path->AddArc(rect.X, rect.Y, radius, radius, 180, 90);
            path->AddArc(rect.X + rect.Width - radius, rect.Y, radius, radius, 270, 90);
            path->AddArc(rect.X + rect.Width - radius, rect.Y + rect.Height - radius, radius, radius, 0, 90);
            path->AddArc(rect.X, rect.Y + rect.Height - radius, radius, radius, 90, 90);
            path->CloseFigure();
            


            this->Region = gcnew System::Drawing::Region(path);

            g->FillPath(brush, path);

            StringFormat^ format = gcnew StringFormat();
            format->Alignment = StringAlignment::Center;
            format->LineAlignment = StringAlignment::Center;
            
            g->DrawString(this->Text, this->Font, gcnew SolidBrush(this->ForeColor), rect, format);

            _T::OnPaint(e);
        }
        Brush^ brush;
        int radius;
    public:
        Rounded(_T^ _copy, Brush^ _brush, int _radius) : Rounded(_brush, _radius) {
            this->Location = _copy->Location;
            this->Name = _copy->Name;
            this->Size = _copy->Size;
            this->Enabled = _copy->Enabled;
            this->Visible = _copy->Visible;
            this->TabIndex = _copy->TabIndex;
            this->Text = _copy->Text;
            this->ForeColor = _copy->ForeColor;
            this->BackColor = _copy->BackColor;
            this->Padding = _copy->Padding;
            this->Font = _copy->Font;

            _copy->Parent->Controls->Add(this);
            _copy->Parent->Controls->Remove(_copy);
        }
        Rounded(Brush^ _brush, int _radius) {
            brush = _brush;
            radius = _radius;
        }

    };
}