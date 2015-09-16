#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{		
	TEST_CLASS(MyClassTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// Assert::AreEqual(expected, method-result, L"message", LINE_INFO());
			Assert::AreEqual(0, 3, L"message", LINE_INFO());
		}

	};
}