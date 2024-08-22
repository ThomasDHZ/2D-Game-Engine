#pragma once
#include <string>

enum LogLevel
{
	Trace,
	Debug,
	Info,
	Warning,
	Error,
	Fatal
};

std::wstring Logger_GetLevelName(LogLevel logLevel);