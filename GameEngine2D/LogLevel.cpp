#include "LogLevel.h"

std::wstring Logger_GetLevelName(LogLevel loggerLevel)
{
    switch (loggerLevel)
    {
        case LogLevel::Trace : return L"Trace";
        case LogLevel::Debug: return L"Debug";
        case LogLevel::Warning: return L"Warning";
        case LogLevel::Error: return L"Error";
        case LogLevel::Fatal: return L"Fatal";
        default: return L"Unknown";
    }
}
