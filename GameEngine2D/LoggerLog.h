#pragma once
#include "Logger.h"

void f(LogEntry* logEntry);
class LoggerLog : public LogEntry
{
	void g() { f(this); };
};

