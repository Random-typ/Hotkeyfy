#include "pch.h"

#include "Form1.h"
#include "../Hotkeyfy-api/Hotkeyfy.h"

using namespace System::Windows::Forms;

[System::STAThread]
int main(array<System::String^>^ args)
{
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