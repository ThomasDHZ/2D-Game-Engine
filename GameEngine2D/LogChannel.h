#pragma once
#include "Logger.h"

struct LogEntry;

class IChannel
{
public:
	virtual ~IChannel() = default;
	virtual void Submit(LogEntry& log) = 0;
};