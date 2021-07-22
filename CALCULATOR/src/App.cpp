#include "App.h"

//Implementing Main Function
wxIMPLEMENT_APP(App);

//Constructor
App::App() {

}

//Destructor
App::~App() {

}

bool App::OnInit() {
	m_frame = new MainWindow();
	m_frame->Show();
	return true;
}