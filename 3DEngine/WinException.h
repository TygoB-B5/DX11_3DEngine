#ifndef WINEXCEPTION_H
#define WINEXCEPTION_H

#include <string>
#include <algorithm>
#include "WinFixed.h"

class Debug
{
public:
	static void LogError(unsigned int line, std::string file, std::string errorMsg) noexcept;
	static void LogError(unsigned int line, std::string file, std::string errorMsg, HRESULT hResult) noexcept;
	static void LogError(unsigned int line, std::string file, HRESULT hResult) noexcept;

	static void Log(std::string s) noexcept;
	static void Log(float f) noexcept;
	static void Log(HRESULT hr) noexcept;
};

#endif