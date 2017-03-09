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
					.Where([](const int& i) { return i % 3 == 0; })
					.Skip(5)
					.Take(10);
	
	for(auto& x : dataset)
		std::cout << x << std::endl;
	
	return EXIT_SUCCESS;
}
