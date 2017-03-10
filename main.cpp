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

	// ### First ###
	
	std::cout << "first:" << std::endl;

	auto datapoint = IEnumerable<int>::Range(0,1000)
					.Where([](const int& i) { return i % 2 == 0 && i % 5 == 0; })
					.First();

	std::cout << " # "<< datapoint << std::endl;
	
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

	return EXIT_SUCCESS;
}
