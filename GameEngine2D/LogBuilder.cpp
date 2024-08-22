#include "LogBuilder.h"
#include "LogChannel.h"

LogBuilder::LogBuilder(const wchar_t* sourceFile, const wchar_t* sourceFunctionName, int sourceLine)
{
	LogEntry
	{
		.LoggerLevel = LogLevel::Error,
		.LoggerSourceFile = sourceFile,
		.LoggerSourceFunctionName = sourceFunctionName,
		.LoggerSourceLine = sourceLine
	};
}

LogBuilder::~LogBuilder()
{
	if (!pDestination)
	{
		pDestination->Submit(*this);
	}
}

LogBuilder& LogBuilder::Body(std::wstring body)
{
	LoggerBody = std::move(body);
	return *this;
}

LogBuilder& LogBuilder::Level(LogLevel logLevel)
{
	LoggerLevel = logLevel;
	return *this;
}

LogBuilder& LogBuilder::Channel(IChannel* channel)
{
	pDestination = channel;
	return *this;
}
