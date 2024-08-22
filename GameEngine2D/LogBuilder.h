#pragma once
#include "logger.h"

class IChannel;
class LogBuilder : public LogEntry
{
private:
	IChannel* pDestination = nullptr;
public:
	LogBuilder(const wchar_t* sourceFile, const wchar_t* sourceFunctionName, int sourceLine);
	~LogBuilder();

	LogBuilder& Body(std::wstring body);
	LogBuilder& Level(LogLevel logLevel);
	LogBuilder& Channel(IChannel* channel);

};