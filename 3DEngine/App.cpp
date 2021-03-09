#include "App.h"

App::App()
	:
	wnd(800, 600, L"Cool window")
{}

std::pair<bool, int> App::Go()
{
	while (true)
	{
		std::pair<bool, int> a = Window::ProcessMassage();
		if (a.first)
		{
			return a;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	t.Tick();
	const double c = sin(t.DeltaTime()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(c, 1.0f, c);
	wnd.Gfx().EndFrame();
}
