#pragma once
#include "wx\wx.h"

#include "MainWindow.h"

class App : public wxApp
{
public:
	App();
	~App();
	MainWindow* m_frame = nullptr;
public:
	virtual bool OnInit();
};