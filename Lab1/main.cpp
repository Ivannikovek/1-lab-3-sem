#include "Map.hpp"
#include <string>
#include <iostream>

int main() {
	Map<int, std::string> m;

	m.insert(3, "three");
	m.insert(1, "one");
	m.insert(4, "four");
	m.insert(2, "two");
	m.insert(5, "five");
	m.insert(6, "six");

	std::cout << "Actual map: " << std::endl;
	m.print();
	std::cout << std::endl << "Is \"2\" in map?" << std::endl;
	std::cout << (m.find(2) ? "yes" : "no") << std::endl;

	std::cout << std::endl << "REMOVE 2" << std::endl;
	m.remove(2);
	std::cout << std::endl;

	std::cout << "Actual map: " << std::endl;
	m.print();
	std::cout << std::endl << "Is \"2\" in map?" << std::endl;
	std::cout << (m.find(2) ? "yes" : "no") << std::endl;

	std::cout << std::endl << "GET_VALUES" << std::endl;
	std::list<std::string> l1 = m.get_values();
	for (auto i : l1)
		std::cout << i << std::endl;
	std::cout << std::endl;

	std::cout << std::endl << "CLEAR" << std::endl;
	m.clear();
	std::cout << std::endl;

	std::cout << "Actual map: " << std::endl;
	m.print();
	std::cout << std::endl << "Is \"3\" in map?" << std::endl;
	std::cout << (m.find(2) ? "yes" : "no") << std::endl;

	return 0;
}

////int main() {
////	size_t count_of_exceptions = 0u;
////	size_t count_of_inserted = 0u;
////
////	Map<int, std::string> map;
////
////	for (size_t i = 0u; i < 100u; ++i) {
////		try {
////			if (map.insert(i, "abc" + std::to_string(i)))
////				++count_of_inserted; //from 0 to 99 inclusive are inserted (100 elements)
////		}
////		catch (...) {
////			++count_of_exceptions;
////		}
////	}
////	map.print();
////
////	std::cout << std::endl << std::endl << std::endl;
////	std::cout << 100 << ' ' << count_of_inserted << std::endl;
////
////	for (size_t i = 200; i >= 10; --i) {
////		try {
////			std::cout << i << std::endl;
////			std::cout << map.find(96) << std::endl;
////			if (i == 96) {
////				/*std::cout << map.find(96) << std::endl;*/
////				std::cout << "." << std::endl;
////
////			}
////			if (map.insert(i, "..." + std::to_string(i)))
////				++count_of_inserted; //only from 199u downto 100 inclusive are inserted (100 elements)		
////		}
////
////		catch (...) {
////			++count_of_exceptions;
////		}
////	}
////
////	//map.print();
////
////	//std::cout << 200 << ' ' << count_of_inserted << std::endl;
////
////	//std::cout << 0 << ' ' << count_of_exceptions << std::endl;
////
////	return 0;
////}
//
//#include "Map.hpp"
//#include <string>
//#include <iostream>
//
//int main() {
//	size_t count_of_exceptions = 0u;
//	size_t count_of_removed = 0u;
//
//	Map<int, std::string> map;
//
//	for (size_t i = 0u; i < 20u; ++i) {
//		try {
//			if (map.remove(i))
//				++count_of_removed; //waiting for 0, because map is empty
//		}
//		catch (...) {
//			++count_of_exceptions;
//		}
//	}
//
//	for (size_t i = 0u; i < 20u; ++i)
//		map.insert(i, "abc" + std::to_string(i));
//
//	for (size_t i = 20u; i < 100u; ++i) {
//		try {
//			if (map.remove(i))
//				++count_of_removed; //waiting for 0, because keys are not in map
//		}
//		catch (...) {
//			++count_of_exceptions;
//		}
//	}
//
//	//srand(time(0));
//	//if (map.remove(rand() % 20)) //random number from [0; 20)
//	//	++count_of_removed; //waiting for 1
//
//	for (size_t i = 0u; i <= 20u; ++i) {
//		try {
//			if (map.remove(i))
//				++count_of_removed; //waiting for 19
//		}
//		catch (...) {
//			++count_of_exceptions;
//		}
//	}
//	return 0;
//}