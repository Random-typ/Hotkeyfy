#include "pch.h"

#include "Form1.h"
#include "../Hotkeyfy-api/Hotkeyfy.h"

using namespace System::Windows::Forms;

[System::STAThread]
int main(array<System::String^>^ args)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = DefWindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = L"HotkeyfyServiceClass";

	// Register the window class
	if (!RegisterClassEx(&wc)) {
		MessageBox::Show("Failed to register window class", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return -1;
	}
	// The GUI is only ment to be started from the service
	if (args->Length < 1 || args[0] != msclr::interop::marshal_as<String^>(config::launchedFromService))
	{
		if (Hotkeyfy::Hotkeyfy::sendLaunchGUI())
		{
			return 0;
		}
		System::Windows::Forms::MessageBox::Show("Failed to launch service. Your installation may be corrupted, please reinstall the program.", "Failed to launch service!", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
	}

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Hotkeyfy::Form1());
	return 0;
}