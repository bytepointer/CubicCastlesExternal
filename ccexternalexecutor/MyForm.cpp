#include "CCExternal.h"

using namespace System;
using namespace System::Windows::Forms;

void main(array<String^>^ args) {

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ccexternalexecutor::CCExternal form;
	Application::Run(% form);
}