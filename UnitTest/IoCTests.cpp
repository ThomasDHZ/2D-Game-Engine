//#include "CppUnitTest.h"
//#include "../External/ChiliTomatoNoodle/ChiliContainer.h"
//#include <memory>
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//struct Base
//{
//	virtual int Test() { return 32; }
//	virtual ~Base() = default;
//};
//
//struct Derived : public Base
//{
//	int Test() override { return 64; }
//};
//
//namespace Infrastructure
//{
//	TEST_CLASS(IoCTests)
//	{
//	private:
//		std::unique_ptr<chil::ioc::Container> pIoC;
//	public:
//		TEST_METHOD_INITIALIZE(Init)
//		{
//			pIoC = std::make_unique<chil::ioc::Container>();
//		}
//		TEST_METHOD(SimpleResolve)
//		{
//			 
//			pIoC->Register<Base>([] {return std::make_shared<Derived>(); });
//			Assert::AreEqual(64, pIoC->Resolve<Base>()->Test());
//		}
//
//		TEST_METHOD(SimpleResolveFail)
//		{
//			Assert::ExpectException<std::runtime_error>([this] { pIoC->Resolve<Base>(); });
//		}
//	};
//}
