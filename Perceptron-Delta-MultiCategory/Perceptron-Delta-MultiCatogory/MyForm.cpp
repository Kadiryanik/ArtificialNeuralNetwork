#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int Main(array<String^>^ args){
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	PerceptronDeltaMultiCatogory::MyForm form;
	Application::Run(%form);
	
	return 0;
}
