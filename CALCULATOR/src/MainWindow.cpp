#include "MainWindow.h"

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Calculator") {
	// Initialization
	baseSizer = new wxBoxSizer(wxVERTICAL); //Vertical Sizer
	calcArea = new wxTextCtrl(this, CALCAREA, "", wxPoint(0, 0), wxSize(100, 40));
	btnGrid = new wxGridSizer(3, 3, wxSize(8,8));
	
	// Making the Button Grid from 1 to 9
	for (int i = 0, numbers = 7; i < 3; i++) {	

		for (int j = 0; j < 3; j++) {
			btnGrid->Add(new wxButton(this, 1000 + numbers, std::to_string(numbers), wxPoint(0, 0), wxSize(70, 50)));
			numbers++;
		}
		if (numbers == 10)
			numbers = 4;
		else
			numbers = 1;
	}

	// Allowing calcArea to expand to full width
	baseSizer->Add(calcArea, 0, wxEXPAND | wxALL, 8);
	baseSizer->Add(btnGrid, 0, wxSHAPED | wxLEFT, 8);
	baseSizer->Add(new wxButton(this, 1000, "0", wxPoint(0, 0), wxSize(66, 50)), 0, wxSHAPED | wxALL, 8);
	
	

	this->SetSizer(baseSizer);

	//Relayout the window according to area acquired
	this->Layout();
}
MainWindow::~MainWindow() {
	
}