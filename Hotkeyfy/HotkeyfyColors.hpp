
#ifndef __Hotkeyfy_Colors_
#define __Hotkeyfy_Colors_

namespace Hotkeyfy {
	using namespace System::Drawing;
	ref class Colors {
	public:
		static SolidBrush^ whiteBrush = gcnew SolidBrush(Color::FromArgb(255, 255, 255));
		static SolidBrush^ blackBrush = gcnew SolidBrush(Color::FromArgb(0, 0, 0));
		static SolidBrush^ highlightGrayBrush = gcnew SolidBrush(Color::FromArgb(51, 51, 51));
		static SolidBrush^ grayBrush = gcnew SolidBrush(Color::FromArgb(83, 83, 83));
		static SolidBrush^ darkGrayBrush = gcnew SolidBrush(Color::FromArgb(18, 18, 18));
		static SolidBrush^ lightGrayBrush = gcnew SolidBrush(Color::FromArgb(179, 179, 179));
		static SolidBrush^ orangeBrush = gcnew SolidBrush(Color::FromArgb(239, 87, 0));
		static SolidBrush^ lightOrangeBrush = gcnew SolidBrush(Color::FromArgb(255, 105, 0));
	};
}
#endif // __Hotkeyfy_Colors_
