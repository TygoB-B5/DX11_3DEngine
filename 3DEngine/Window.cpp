#include "Window.h"
#include "resource.h"

Window::WindowClass
Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept: hInst(GetModuleHandle(nullptr))
{
	WNDCLASS wc = {0};
    wc.style = CS_OWNDC;
    wc.hInstance = GetInstance();
    wc.lpszClassName = GetName();
    wc.lpfnWndProc = HandleMsgSetup;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 128, 128, 0));
    wc.hCursor = nullptr;
    wc.lpszMenuName = nullptr; 
	RegisterClass(&wc);
}

Window::WindowClass::~WindowClass()
{
    UnregisterClass(wndClassName, GetInstance());
}

const wchar_t* Window::WindowClass::GetName() noexcept
{
    return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
    return wndClass.hInst;
}

Window::Window(int width, int height, const wchar_t* name)
{
    this->width = width;
    this->height = height;

    RECT wr{0};
    wr.left = 100;
    wr.top = 100;
    wr.right = width + wr.right;
    wr.bottom = height + wr.top;

    AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

    hwnd = CreateWindowEx(
        0,
        WindowClass::GetName(), name,
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
        nullptr, nullptr, WindowClass::GetInstance(), this
    );

    if (hwnd == nullptr)
    {
        Debug::LogError(__LINE__, __FILE__, "Failed To Create Hwnd");
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);

    pGfx = std::make_unique<Graphics>(hwnd);
}

Window::~Window()
{
    DestroyWindow(hwnd);
}

void Window::SetTitle(const std::string title)
{
    if (SetWindowTextA(hwnd, title.c_str()) == 0)
    {
        Debug::LogError(__LINE__, __FILE__, "Failed to change title");
    }
}

std::pair<bool, int> Window::ProcessMassage()
{
    MSG msg;

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
		{
			return std::make_pair(true, msg.wParam);
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
    return std::make_pair(false, 0);
}

Graphics& Window::Gfx()
{
    return *pGfx;
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    if (msg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));

        return pWnd->HandleMsg(hwnd, msg, wParam, lParam);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMsgThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    return pWnd->HandleMsg(hwnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (msg)
    {
    case WM_CLOSE:
    {
        PostQuitMessage(0);
        break;
    }

        /*Keyboard*/
    case WM_SYSKEYDOWN:
    case WM_KEYDOWN:
    {
        if ((HIWORD(lParam) & KF_REPEAT) == 0 || kbd.AutoRepeatIsEnabled())
        {
            kbd.OnKeyPressed((unsigned char)wParam);
        }
        break;
    }

    case WM_SYSKEYUP:
    case WM_KEYUP:
    {
        kbd.OnKeyReleased((unsigned char)wParam);
        break;
    }

	case WM_CHAR:
    {
        kbd.OnChar((unsigned char)wParam);
        break;
    }

    case WM_KILLFOCUS:
    {
        kbd.ClearState();
        break;
    }

        /*Mouse*/
    case WM_MOUSEMOVE:
    {
        POINTS pt = MAKEPOINTS(lParam);
        mouse.OnMouseMove(pt.x, pt.y);
        break;
    }

    case WM_LBUTTONDOWN:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnLeftPressed(pt.x, pt.y);
        break;
    }

    case WM_LBUTTONUP:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnLeftReleased(pt.x, pt.y);
        break;
    }

    case WM_RBUTTONDOWN:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnRightPressed(pt.x, pt.y);
        break;
    }

    case WM_RBUTTONUP:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnRightRelease(pt.x, pt.y);
        break;
    }

    case WM_MOUSEWHEEL:
    {
        const POINTS pt = MAKEPOINTS(lParam);

        if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
            mouse.OnWheelUp(pt.x, pt.y);
        else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
            mouse.OnWheelDown(pt.x, pt.y);
        break;
    }

    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}