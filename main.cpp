#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <memory>

#include "src/IEnumerable.hpp"

using namespace linq;

int main(int argc, char **argv)
{
	auto dataset = IEnumerable<int>::Range(0,1000)
					.Where([](const int& i) { return i % 2 == 0; })
					.Where([](const int& i) { return i % 3 == 0; });
					
	std::cout << "where/count => " << dataset.Count() << std::endl;

	dataset = dataset.Skip(5)
					 .Take(10);

	std::cout << "where/skip/take: " << std::endl;
	for(auto& x : dataset)
		std::cout << " # " << x << std::endl;

	
	auto datapoint = IEnumerable<int>::Range(0,1000)
					.Where([](const int& i) { return i % 2 == 0 && i % 5 == 0; })
					.First();

	std::cout << "first:" << std::endl;
	std::cout << " # "<< datapoint << std::endl;
	
	return EXIT_SUCCESS;
}
