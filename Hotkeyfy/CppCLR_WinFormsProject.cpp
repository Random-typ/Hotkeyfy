#include "pch.h"

// int main(array<System::String ^> ^args)
// {
//    return 0;
// }

#include "Form1.h"

using namespace System::Windows::Forms;

[System::STAThread]
int main(array<System::String^>^ args)
{
	if (args->Length < 2 || args[1] != msclr::interop::marshal_as<String^>(config::launchedFromService))
	{

		return 0;
	}

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Hotkeyfy::Form1());
	return 0;
}