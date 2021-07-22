#pragma once

#include "wx\wx.h"

// Area for writing expressions
#define CALCAREA 10001

// Main window for the app.
class MainWindow : public wxFrame
{
public:
	MainWindow();
	~MainWindow();
private:
	//Sizer
	wxBoxSizer* baseSizer = nullptr;
	wxGridSizer* btnGrid = nullptr;

	//Widgets
	
	wxTextCtrl* calcArea = nullptr;
};

