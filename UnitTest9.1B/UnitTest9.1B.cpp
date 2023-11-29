#include "pch.h"
#include "CppUnitTest.h"
#include "../Project9.1B/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest91B
{
	TEST_CLASS(UnitTest91B)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            Specialty specialty;
            specialty.value = 0; 
            const char* str = specialtyToString(specialty);
            Assert::AreEqual("Mathematics", str);
            
		}
	};
}
