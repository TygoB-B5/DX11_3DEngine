#ifndef WINDOWS_H
#define WINDOWS_H

#include "WinFixed.h"
#include "WinException.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Time.h"
#include "Graphics.h"
#include <string>
#include <utility>
#include <memory>

class Window
{
public:
	Window(int width, int height, const wchar_t* name);
	~Window();

	Window& operator=(const Window&) = delete;
	Window(const Window&) = delete;

	void SetTitle(const std::string);
	static std::pair<bool, int> ProcessMassage();
	Graphics& Gfx();

private:
	class WindowClass
	{
	public:
		static const wchar_t* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;

	private:
		WindowClass() noexcept;
		~WindowClass();

		static constexpr const wchar_t* wndClassName = L"WndClass";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	int width;
	int height;
	HWND hwnd;
	std::unique_ptr<Graphics> pGfx;

public:
	Keyboard kbd;
	Mouse mouse;
};
#endif