#pragma once

namespace Logger
{
	struct Entry;
	class IDriver
	{
	public:
		virtual ~IDriver() = default;
		virtual void Submit(const Entry& entry) = 0;
	};
}

