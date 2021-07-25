#include "MainWindow.h"

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Calculator") {
	// Initialization
	btns = new wxButton **[5];
	for (int i = 0; i < 5; i++) {
		if (i == 4) {
			btns[i] = new wxButton * [3];
			break;
		}
		btns[i] = new wxButton * [4];
	}
	
	baseSizer = new wxBoxSizer(wxVERTICAL); //Vertical Sizer
	calcArea = new wxTextCtrl(this, CALCAREA, "", wxPoint(0, 0), wxSize(105, 45));
	btnGrid = new wxGridSizer(3, 3, wxSize(8,8));
	wxBoxSizer* lastRow = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lastColumn = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* firstRow = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* gridlastColumn = new wxBoxSizer(wxHORIZONTAL);

	btns[0][0] = new wxButton(this, 1, "C", wxPoint(0, 0), wxSize(78, 58));
	btns[0][1] = new wxButton(this, 2, "±", wxPoint(0, 0), wxSize(78, 58));
	btns[0][2] = new wxButton(this, 3, "CE", wxPoint(0, 0), wxSize(78, 58));
	btns[0][3] = new wxButton(this, 4, "%", wxPoint(0, 0), wxSize(78, 58));

	btns[1][3] = new wxButton(this, 101, "÷", wxPoint(0, 0), wxSize(78, 58));
	btns[2][3] = new wxButton(this, 102, "×", wxPoint(0, 0), wxSize(78, 58));
	btns[3][3] = new wxButton(this, 103, "-", wxPoint(0, 0), wxSize(78, 58));
	
	btns[4][0] = new wxButton(this, 1000, "0", wxPoint(0, 0), wxSize(78, 58));
	btns[4][1] = new wxButton(this, EQUALS, "=", wxPoint(0, 0), wxSize(164, 58));
	btns[4][2] = new wxButton(this, 104, "+", wxPoint(0, 0), wxSize(78, 58));
	
	
	
	// First row of buttons
	firstRow->Add(btns[0][0], 0, wxFIXED_MINSIZE | wxLEFT, 8);
	firstRow->Add(btns[0][1], 0, wxFIXED_MINSIZE | wxLEFT, 8);
	firstRow->Add(btns[0][2], 0, wxFIXED_MINSIZE | wxLEFT, 8);
	firstRow->Add(btns[0][3], 0, wxFIXED_MINSIZE | wxLEFT, 13);
	
	// Making the Button Grid from 1 to 9
	for (int i = 0, numbers = 7; i < 3; i++) {	

		for (int j = 0; j < 3; j++) {
			btns[i + 1][j] = new wxButton(this, 1000 + numbers, std::to_string(numbers), wxPoint(0, 0), wxSize(78, 58));
			btnGrid->Add(btns[i+1][j]);
			numbers++;
		}
		if (numbers == 10)
			numbers = 4;
		else
			numbers = 1;
	}
	// Last Column of buttons
	lastColumn->Add(btns[1][3], 0, wxFIXED_MINSIZE | wxTOP , 8);
	lastColumn->Add(btns[2][3], 0, wxFIXED_MINSIZE | wxTOP , 8);
	lastColumn->Add(btns[3][3], 0, wxFIXED_MINSIZE | wxTOP , 8);
	
	// Last Row of buttons
	lastRow->Add(btns[4][0], 0, wxFIXED_MINSIZE | wxLEFT , 8);
	lastRow->Add(btns[4][1], 0, wxFIXED_MINSIZE | wxLEFT, 8);
	lastRow->Add(btns[4][2], 0, wxFIXED_MINSIZE | wxLEFT , 13);
	

	gridlastColumn->Add(btnGrid, 0, wxFIXED_MINSIZE | wxALL, 8);
	gridlastColumn->Add(lastColumn, 0, wxFIXED_MINSIZE | wxLEFT, 5);
	
	

	baseSizer->Add(calcArea, 0, wxEXPAND | wxALL, 8);
	baseSizer->Add(firstRow, 0, wxFIXED_MINSIZE | wxBOTTOM, 5);
	baseSizer->Add(gridlastColumn, 0, wxFIXED_MINSIZE);
	baseSizer->Add(lastRow, 0, wxFIXED_MINSIZE);

	//Stylesheet + Binding Events
	this->SetBackgroundColour(wxColour(41, 40, 41, 255));
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == 4 && j == 3) {
				break;
			}
			btns[i][j]->SetBackgroundColour(wxColour(41, 40, 41, 255));
			btns[i][j]->SetFont(wxFont(wxFONTSIZE_MEDIUM, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
			btns[i][j]->SetForegroundColour(wxColour(255, 255, 255, 255));
			if (i == 4 && j == 1) {
				btns[i][j]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonEquals, this);
			}
			btns[i][j]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);
		}
	}
	
	calcArea->SetBackgroundColour(wxColour(41, 40, 41, 255));
	calcArea->SetFont(wxFont(25, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	calcArea->SetValue("");
	calcArea->SetForegroundColour(wxColour(255, 255, 255, 255));
	this->SetSizer(baseSizer);
	this->SetMinSize(wxSize(375, 435));

	//Relayout the window according to area acquired
	this->Layout();
}
MainWindow::~MainWindow() {
	for (int i = 0; i < 5; i++) {
		delete[] btns[i];
	}
	delete[] btns;
}
void MainWindow::OnButtonClicked(wxCommandEvent& evt) {
	// Functionality of Numbers
	if (evt.GetId() >= 1000 && evt.GetId() <= 1009) {
		calcArea->SetValue(calcArea->GetValue() + std::to_string(evt.GetId() - 1000));
		evt.Skip();
		return;
	} 
	if (evt.GetId() == 1) {
		calcArea->SetValue("");
	}
	else if (evt.GetId() == 2) {
		std::string eq = (std::string)calcArea->GetValue();
		int i;
		bool positive = true;
		for (i = (eq.length() - 1); i >= 0; i--) {
			if (eq[i] == '+') {
				positive = true;
				break;
			}
			else if (eq[i] == '-') {
				positive = false;
				break;
			}
		}
		if (i == -1) {
			eq = "-" + eq;
			
		}
		else if (positive) {
			eq[i] = '-';
		}
		else {
			eq[i] = '+';
		}
		calcArea->SetValue(eq);
	} else if (evt.GetId() == 3) {
		std::string equation = (std::string)calcArea->GetValue();
		int index;
		for (index = equation.length() - 1; index >= 0; index--) {
			if (!(equation[index] >= '0' && equation[index] <= '9')) {
				break;
			}
		}
		if (index == -1) {
			calcArea->SetValue("");
		}
		else {
			for (int x = index + 1; x < equation.length(); x++) {
				if (x == index + 1) {
					equation[x] = '0';
				}
				else {
					equation[x] = ' ';
				}
			}
			calcArea->SetValue(equation);
		}
	}
	else if (evt.GetId() == 4) {

	}
	this->DeleteWhitespace();
	evt.Skip();
}
void MainWindow::OnButtonEquals(wxCommandEvent& evt) {
	evt.Skip();
}
void MainWindow::DeleteWhitespace() {
	std::string value = (std::string)calcArea->GetValue();
	std::string result = "";
	for (int i = 0; i < value.length(); i++) {
		if (value[i] == ' ') {
			continue;
		}
		result += value[i];
	}
	calcArea->SetValue(result);
}