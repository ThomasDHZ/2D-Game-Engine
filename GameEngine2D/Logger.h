#pragma once
#include "LogLevel.h"
#include <chrono>

struct LogEntry
{
	LogLevel LoggerLevel;
	std::wstring LoggerBody;
	const wchar_t* LoggerSourceFile;
	const wchar_t* LoggerSourceFunctionName;
	int LoggerSourceLine;
	std::chrono::system_clock::time_point LoggerTimestamp;
};