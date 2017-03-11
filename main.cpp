#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <memory>
#include <vector>
#include <map>

#include "src/IEnumerable.hpp"

using namespace linq;

int main(int argc, char **argv)
{
	// ### Where, Skip, Take ###
	
	auto dataset = IEnumerable<int>::Range(0,1000)
					.Where([](const int& i) { return i % 2 == 0; })
					.Where([](const int& i) { return i % 3 == 0; });
					
	std::cout << "where/count => " << dataset.Count() << std::endl;

	dataset = dataset.Skip(3)
					 .Take(5);
	
	std::cout << "where/skip/take: " << std::endl;
	for(auto& x : dataset)
		std::cout << " # " << x << std::endl;

	std::cout << "where/skip/take: " << std::endl;
	for(auto& x : dataset)
		std::cout << " # " << x << std::endl;

	// ### First && Last ###
	
	std::cout << "first/last:" << std::endl;

	auto datapoint_first = IEnumerable<int>::Range(0,1000)
					.Where([](const int& i) { return i % 2 == 0 && i % 5 == 0; })
					.First();
	auto datapoint_last = IEnumerable<int>::Range(0,1000)
					.Where([](const int& i) { return i % 2 == 0 && i % 5 == 0; })
					.Last();

	std::cout << " # "<< datapoint_first << std::endl;
	std::cout << " # "<< datapoint_last << std::endl;
	
	// ### From std::vector ###
	
	std::cout << "adapted vector: " << std::endl;

	auto dummy = std::vector<int>{ 7, 7*7, 7*7*7, 7*7*7*7, 7*7*7*7*7, 7*7*7*7*7*7 };
	auto adapted = Adapt(dummy);

	for(auto& x : adapted.Take(3))
		std::cout << " # " << x << std::endl;
	
	// ### From std::map ###
	
	std::cout << "adapted map: " << std::endl;

	auto dummy_map = std::map<int, std::string>{ 
		std::make_pair(7, "seven"),
		std::make_pair(49, "forty nine"),
		std::make_pair(343, "three hundred and three"),
	};
	auto adapted_map = Adapt(dummy_map);

	for(auto& x : adapted_map.Take(2))
		std::cout << " # " << x.first << " -> " << x.second << std::endl;

	// ### Select ###
	
	std::cout << "select: " << std::endl;

	auto keys = adapted_map.Select([](auto x){ return x.first; });
	
	for(auto& x : keys)
		std::cout << " # " << x << std::endl;

	auto values = adapted_map.Select([](auto x){ return x.second; });

	for(auto& x : values)
		std::cout << " # " << x << std::endl;
	
	// ### GroupBy ###
	
	std::cout << "select: " << std::endl;

	auto grouped = IEnumerable<int>::Range(0, 1000)
					.Where([](auto x) { return x % 2 == 0; })
					.Select([](auto x) { return std::to_string(x); })
					.GroupBy([](auto x) { return x.length(); });
	
	for(auto x : grouped)
		std::cout << " # " << x.Key << " (count: " << x.Count() << ")" << std::endl;
	
	return EXIT_SUCCESS;
}
