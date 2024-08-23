#include "CppUnitTest.h"
#include "../External/ChiliTomatoNoodle/ChiliContainer.h"
#include <LogBuilder.h>
#include <LogLevel.h>
#include <LogChannel.h>
#include <memory>
#include <LogDriver.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::string_literals;
using namespace Logger;

namespace Logger
{
	#define chilog EntryBuilder{ __FILEW__, __FUNCTIONW__, __LINE__ }
	class MockChannel : public IChannel
	{
	public:
		void Submit(Entry& e) override
		{
			entry_ = e;
		}

		void AttachDriver(std::shared_ptr<IDriver> driver) override
		{

		}

		Entry entry_;
	};

	namespace Infrastructure
	{
		TEST_CLASS(LogTests)
		{
		public:
			TEST_METHOD(LoggerTest)
			{
				MockChannel chan;
				chilog.Info(L"HI").chan(&chan);
				Assert::AreEqual(L"HI"s, chan.entry_.note_);
				Assert::IsTrue(Level::Info == chan.entry_.level_);
			}
		};
	}
}