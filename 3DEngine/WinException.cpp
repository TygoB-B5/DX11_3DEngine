#include "WinException.h"

void Debug::LogError(unsigned int line, std::string file, std::string errorMsg) noexcept
{
	MessageBoxA(nullptr, (LPCSTR)(errorMsg + "\n[LINE] " + std::to_string(line) + "\n[FILE] " + file).c_str(), "Error:", MB_OK | MB_ICONEXCLAMATION);
}

void Debug::LogError(unsigned int line, std::string file, std::string errorMsg, HRESULT hResult) noexcept
{
	LPTSTR errorText = NULL;

	FormatMessage(
		// use system message tables to retrieve error text
		FORMAT_MESSAGE_FROM_SYSTEM
		// allocate buffer on local heap for error text
		| FORMAT_MESSAGE_ALLOCATE_BUFFER
		// Important! will fail otherwise, since we're not 
		// (and CANNOT) pass insertion parameters
		| FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
		hResult,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&errorText,  // output 
		0, // minimum size for output buffer
		NULL);   // arguments - see note 

	std::string str = errorMsg + "\n[LINE] " + std::to_string(line) + "\n[FILE] " + file + "\n[HRESULT] ";
	std::wstring str2(str.length(), L' ');
	std::copy(str.begin(), str.end(), str2.begin());
	std::wstring m = str2 + (LPCWSTR)errorText;

	MessageBox(nullptr, m.c_str(), L"Error:", MB_OK | MB_ICONEXCLAMATION);
}

void Debug::LogError(unsigned int line, std::string file, HRESULT hResult) noexcept
{
	LPTSTR errorText = NULL;

	FormatMessage(
		// use system message tables to retrieve error text
		FORMAT_MESSAGE_FROM_SYSTEM
		// allocate buffer on local heap for error text
		| FORMAT_MESSAGE_ALLOCATE_BUFFER
		// Important! will fail otherwise, since we're not 
		// (and CANNOT) pass insertion parameters
		| FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
		hResult,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&errorText,  // output 
		0, // minimum size for output buffer
		NULL);   // arguments - see note 

	std::string str = "\n[LINE] " + std::to_string(line) + "\n[FILE] " + file + "\n[HRESULT] ";
	std::wstring str2(str.length(), L' ');
	std::copy(str.begin(), str.end(), str2.begin());
	std::wstring m = str2 + (LPCWSTR)errorText;

	MessageBox(nullptr, m.c_str(), L"Error:", MB_OK | MB_ICONEXCLAMATION);
}

void Debug::Log(std::string s) noexcept
{
	MessageBoxA(nullptr, s.c_str(), "Log String:", MB_OK | MB_ICONEXCLAMATION);
}

void Debug::Log(float f) noexcept
{
	std::string s = std::to_string(f);
	MessageBoxA(nullptr, s.c_str(), "Log Number:", MB_OK | MB_ICONEXCLAMATION);
}

void Debug::Log(HRESULT hr) noexcept
{
	LPTSTR errorText = NULL;

	FormatMessage(
		// use system message tables to retrieve error text
		FORMAT_MESSAGE_FROM_SYSTEM
		// allocate buffer on local heap for error text
		| FORMAT_MESSAGE_ALLOCATE_BUFFER
		// Important! will fail otherwise, since we're not 
		// (and CANNOT) pass insertion parameters
		| FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&errorText,  // output 
		0, // minimum size for output buffer
		NULL);   // arguments - see note 

	std::wstring m = (LPCWSTR)errorText;
	MessageBox(nullptr, m.c_str(), L"Log Hresult:", MB_OK | MB_ICONEXCLAMATION);
}
