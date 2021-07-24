#include "MainWindow.h"

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Calculator") {
	// Initialization
	baseSizer = new wxBoxSizer(wxVERTICAL); //Vertical Sizer
	calcArea = new wxTextCtrl(this, CALCAREA, "", wxPoint(0, 0), wxSize(100, 40));
	btnGrid = new wxGridSizer(3, 3, wxSize(8,8));
	wxBoxSizer* lastRow = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lastColumn = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* firstRow = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* gridlastColumn = new wxBoxSizer(wxHORIZONTAL);

	// Making the Button Grid from 1 to 9
	for (int i = 0, numbers = 7; i < 3; i++) {	

		for (int j = 0; j < 3; j++) {
			btnGrid->Add(new wxButton(this, 1000 + numbers, std::to_string(numbers), wxPoint(0, 0), wxSize(78, 58)));
			numbers++;
		}
		if (numbers == 10)
			numbers = 4;
		else
			numbers = 1;
	}
	
	gridlastColumn->Add(btnGrid, 0, wxFIXED_MINSIZE | wxALL, 8);
	
	//
	lastColumn->Add(new wxButton(this, 102, "÷", wxPoint(0, 0), wxSize(78, 58)), 0, wxFIXED_MINSIZE | wxTOP , 8);
	lastColumn->Add(new wxButton(this, 103, "×", wxPoint(0, 0), wxSize(78, 58)), 0, wxFIXED_MINSIZE | wxTOP , 8);
	lastColumn->Add(new wxButton(this, 104, "-", wxPoint(0, 0), wxSize(78, 58)), 0, wxFIXED_MINSIZE | wxTOP , 8);

	gridlastColumn->Add(lastColumn, 0, wxFIXED_MINSIZE | wxLEFT, 5);
	
	// Creating the last row
	lastRow->Add(new wxButton(this, 1000, "0", wxPoint(0, 0), wxSize(78, 58)), 0, wxFIXED_MINSIZE | wxLEFT , 8);
	lastRow->Add(new wxButton(this, EQUALS, "=", wxPoint(0, 0), wxSize(164, 58)), 0, wxFIXED_MINSIZE | wxLEFT, 8);
	lastRow->Add(new wxButton(this, 105, "+", wxPoint(0, 0), wxSize(78, 58)), 0, wxFIXED_MINSIZE | wxLEFT , 13);

	firstRow->Add(new wxButton(this, 1, "C", wxPoint(0, 0), wxSize(78, 58)), 0, wxFIXED_MINSIZE | wxLEFT, 8);
	firstRow->Add(new wxButton(this, 2, "±", wxPoint(0, 0), wxSize(78, 58)), 0, wxFIXED_MINSIZE | wxLEFT, 8);
	firstRow->Add(new wxButton(this, 12,"CE", wxPoint(0, 0), wxSize(78, 58)), 0, wxFIXED_MINSIZE | wxLEFT, 8);
	firstRow->Add(new wxButton(this, 3, "%", wxPoint(0, 0), wxSize(78, 58)), 0, wxFIXED_MINSIZE | wxLEFT, 13);
	
	// Allowing calcArea to expand to full width
	baseSizer->Add(calcArea, 0, wxEXPAND | wxALL, 8);
	baseSizer->Add(firstRow, 0, wxFIXED_MINSIZE | wxBOTTOM, 5);
	baseSizer->Add(gridlastColumn, 0, wxFIXED_MINSIZE);
	baseSizer->Add(lastRow, 0, wxFIXED_MINSIZE);
	
	
	
	
	this->SetSizer(baseSizer);
	
	//Relayout the window according to area acquired
	this->Layout();
}
MainWindow::~MainWindow() {
	
}