#ifndef APP_H
#define APP_H

#include "Window.h"
#include <utility>

class App
{
public:
	App();
	std::pair<bool, int> Go();

private:
	void DoFrame();
	Window wnd;
	Time t;
};

#endif