#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include "../../Lab1/Lab1/Map.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(DefaultConstructor_system)
		{
			size_t count_of_exceptions = 0u;

			try {
				Map<int, std::string> map;
			}
			catch (...) {
				++count_of_exceptions;
			}

			try {
				Map<std::string, std::string> m2;
			}
			catch (...) {
				++count_of_exceptions;
			}

			try {
				Map<int, int> m3;
			}
			catch (...) {
				++count_of_exceptions;
			}

			try {
				Map<short, double> m4;
			}
			catch (...) {
				++count_of_exceptions;
			}

			Assert::AreEqual(0u, count_of_exceptions);
		}

		TEST_METHOD(Insert)
		{
			size_t count_of_exceptions = 0u;
			size_t count_of_inserted = 0u;

			Map<int, std::string> map;

			for (size_t i = 0u; i < 20u; ++i) {
				try {
					if (map.insert(i, "abc" + std::to_string(i)))
						++count_of_inserted; //from 0 to 19 inclusive are inserted (20 elements)
				}
				catch (...) {
					++count_of_exceptions;
				}
			}

			Assert::AreEqual(20u, count_of_inserted);

			for (size_t i = 39u; i >= 5u; --i) {
				try {
					if (map.insert(i, "abc" + std::to_string(i)))
						++count_of_inserted; //only from 39 downto 5 inclusive are inserted (20 elements)
				}
				catch (...) {
					++count_of_exceptions;
				}
			}

			Assert::AreEqual(40u, count_of_inserted);

			Assert::AreEqual(0u, count_of_exceptions);
		}

		TEST_METHOD(Remove)
		{
			size_t count_of_exceptions = 0u;
			size_t count_of_removed = 0u;

			Map<int, std::string> map;

			for (size_t i = 0u; i < 20u; ++i) {
				try {
					if (map.remove(i))
						++count_of_removed; //waiting for 0, because map is empty
				}
				catch (...) {
					++count_of_exceptions;
				}
			}

			Assert::AreEqual(count_of_removed, 0u);

			for (size_t i = 0u; i < 20u; ++i)
				map.insert(i, "abc" + std::to_string(i));

			for (size_t i = 20u; i < 100u; ++i) {
				try {
					if (map.remove(i))
						++count_of_removed; //waiting for 0, because keys are not in map
				}
				catch (...) {
					++count_of_exceptions;
				}
			}

			Assert::AreEqual(count_of_removed, 0u);

			srand(time(0));
			if (map.remove(rand() % 20)) //random number from [0; 20)
				++count_of_removed; //waiting for 1

			Assert::AreEqual(count_of_removed, 1u);

			for (size_t i = 0u; i < 20u; ++i) {
				try {
					if (map.find(i)) //!!!
						++count_of_removed; //waiting for 19
				}
				catch (...) {
					++count_of_exceptions;
				}
			}

			Assert::AreEqual(count_of_removed, 20u);

			Assert::AreEqual(count_of_exceptions, 0u);
		}

		TEST_METHOD(Find)
		{
			size_t count_of_exceptions = 0u;
			size_t count_of_found = 0u;

			Map<int, std::string> map;

			for (size_t i = 0u; i < 100u; ++i) {
				try {
					if (map.find(i))
						++count_of_found; //waiting for 0, because map is empty
				}
				catch (...) {
					++count_of_exceptions;
				}
			}

			Assert::AreEqual(count_of_found, 0u);

			for (size_t i = 0u; i < 100u; ++i)
				map.insert(i, "abc" + std::to_string(i));

			for (size_t i = 100u; i < 1000u; ++i) {
				try {
					if (map.find(i))
						++count_of_found; //waiting for 0, because keys are not in map
				}
				catch (...) {
					++count_of_exceptions;
				}
			}

			Assert::AreEqual(count_of_found, 0u);

			srand(time(0));
			if (map.find(rand() % 100)) //random number from [0; 100)
				++count_of_found; //waiting for 1

			Assert::AreEqual(count_of_found, 1u);

			for (size_t i = 0u; i < 100u; ++i) {
				try {
					if (map.find(i))
						++count_of_found; //waiting for 100
				}
				catch (...) {
					++count_of_exceptions;
				}
			}

			Assert::AreEqual(count_of_found, 101u);

			Assert::AreEqual(count_of_exceptions, 0u);
		}

		TEST_METHOD(Clear)
		{
			size_t count_of_exceptions = 0u;
			size_t count_of_found = 0u;

			Map<int, std::string> map;

			for (size_t i = 0u; i < 100u; ++i)
				map.insert(i, "abc" + std::to_string(i));

			for (size_t i = 0u; i < 100u; ++i) {
				if (map.find(i))
					++count_of_found; //waiting for 100
			}

			Assert::AreEqual(100u, count_of_found);

			try {
				map.clear(); //clear all elements
			}
			catch (...) {
				++count_of_exceptions;
			}

			Assert::AreEqual(0u, count_of_exceptions);

			count_of_found = 0;
			for (size_t i = 0u; i < 100u; ++i) {
				if (map.find(i))
					++count_of_found; //waiting for 0
			}

			Assert::AreEqual(0u, count_of_found);
		}

		TEST_METHOD(GetKeys)
		{
			size_t count_of_exceptions = 0u;
			size_t count_of_right_key = 0u;

			Map<int, std::string> map;

			for (size_t i = 0u; i < 100u; ++i)
				map.insert(i, "abc" + std::to_string(i));

			std::list<int> list;

			try {
				list = map.get_keys(); //get list of keys
			}
			catch (...) {
				++count_of_exceptions;
			}

			Assert::AreEqual(count_of_exceptions, 0u);

			for (size_t i = 0u; i < 100u; ++i) {
				if (list.front() == i)
					++count_of_right_key; //waiting for 100

				list.pop_front();
			}

			Assert::AreEqual(count_of_right_key, 100u);

			Assert::IsTrue(list.empty()); //list should became empty
		}

		TEST_METHOD(GetValues)
		{
			size_t count_of_exceptions = 0u;
			size_t count_of_right_value = 0u;

			Map<int, std::string> map;

			for (size_t i = 0u; i < 100u; ++i)
				map.insert(i, "abc" + std::to_string(i));

			std::list<std::string> list;

			try {
				list = map.get_values(); //get list of values
			}
			catch (...) {
				++count_of_exceptions;
			}

			Assert::AreEqual(count_of_exceptions, 0u);

			for (size_t i = 0u; i < 100u; ++i) {
				if (list.front() == "abc" + std::to_string(i))
					++count_of_right_value; //waiting for 100

				list.pop_front();
			}

			Assert::AreEqual(count_of_right_value, 100u);

			Assert::IsTrue(list.empty()); //list should became empty
		}
	};
}
