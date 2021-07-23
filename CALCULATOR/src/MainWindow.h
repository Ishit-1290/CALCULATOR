#pragma once

#include "wx\wx.h"


#define CALCAREA 10001
#define EQUALS 10109

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

