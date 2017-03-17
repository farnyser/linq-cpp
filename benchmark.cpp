#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <memory>
#include <vector>
#include <map>

#include "src/IEnumerable.hpp"
#include "assert.hpp"

using namespace linq;

struct heavy {
	int map[1024];
	
	heavy() {
		for(auto& x: map)
			x = (int)(std::rand() * 10.0 / RAND_MAX);
	}
};

struct light {
	int map[1];
	
	light() {
		for(auto& x: map)
			x = (int)(std::rand() * 10.0 / RAND_MAX);
	}
};

int main(int argc, char **argv)
{
	std::vector<heavy> data(100000);
	//~ std::vector<light> data(100000);
	
	auto x1 = test("take-vector", [&](){
		int sum = 0;
		int i = 0;
		for(int i = 0; i < 10000; i++) {
			sum += data[i].map[0];
		}
		return sum;
	});
	
	auto x2 = test("take-enumerable", [&](){
		return Adapt(data)
				.Take(10000)
				.Select([](const auto& x) { return x.map[0]; })
				.Sum();
	});
	
	assertEquals(x1, x2);
	
	x1 = test("where-vector", [&](){
		int sum = 0;
		for(auto&x : data) {
			if(x.map[0] > 5)
				sum += x.map[0];
		}
		return sum;
	});
	
	x2 = test("where-enumerable", [&](){
		return Adapt(data)
				.Where([](const auto& x){ return x.map[0] > 5; })
				.Select([](const auto& x) { return x.map[0]; })
				.Sum();
	});
	
	assertEquals(x1, x2);
	
	x1 = test("where-take-vector", [&](){
		int sum = 0;
		int i = 0;
		for(auto&x : data) {
			if(x.map[0] > 5) {
				sum += x.map[0];
				if(++i >= 1) 
					break;
			}
		}
		return sum;
	});
	
	x2 = test("where-take-enumerable", [&](){
		return Adapt(data)
				.Where([](const auto& x){ return x.map[0] > 5; })
				.Take(1)
				.Select([](const auto& x) { return x.map[0]; })
				.Sum();
	});
	
	assertEquals(x1, x2);
	
	return EXIT_SUCCESS;
}