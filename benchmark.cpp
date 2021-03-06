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

template <typename T> 
void bench()
{
	std::vector<T> data(200000);
	
	auto x1 = test("take-vector", [&](){
		int sum = 0;
		for(int i = 0; i < 10000; i++) {
			sum += data[i].map[0];
		}
		return sum;
	});

	auto x2 = test("take-enumerable", [&](){
		return AdaptView(data)
				.Take(10000)
				.Select([](const auto& x) { return x.map[0]; })
				.Sum();
	});

	assertEquals(x1, x2);

	x1 = test("min-2-vector", [&](){
		int min = data[0].map[0];
		for(int i = 0; i < data.size(); i++) {
			if(data[i].map[0] < min)
				min = data[i].map[0];
		}
		for(int i = 0; i < data.size(); i++) {
			if(data[i].map[0] < min)
				min = data[i].map[0];
		}
		return min;
	});

	x2 = test("min-2-enumerable", [&](){
		return AdaptView(data)
				.Concat(AdaptView(data))
				.Select([](const auto& x) { return x.map[0]; })
				.Min();
	});

	assertEquals(x1, x2);

	x1 = test("max-where-vector", [&](){
		int max = -1;
		for(int i = 0; i < data.size(); i++) {
			if(data[i].map[0] > max)
				max = data[i].map[0];
		}
		return max;
	});

	x2 = test("max-where-enumerable", [&](){
		return AdaptView(data)
				.Max([](const auto&  x) { return x.map[0]; })
				.map[0];
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
		return AdaptView(data)
				.Select([](const auto& x) { return x.map[0]; })
				.Where([](const auto& x){ return x > 5; })
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
		return AdaptView(data)
				.Where([](const auto& x){ return x.map[0] > 5; })
				.Take(1)
				.Select([](const auto& x) { return x.map[0]; })
				.Sum();
	});

	assertEquals(x1, x2);

	x1 = test("skip-while-take-while-vector", [&](){
		int sum = 0;
		bool step = false;
		for(auto&x : data) {
			if(!step && x.map[0] < 5)
				continue;

			step = true;

			if(x.map[0] >= 5)
				sum += x.map[0];
			else
				break;
		}
		return sum;
	});

	x2 = test("skip-while-take-while-enumerable", [&](){
		return AdaptView(data)
				.SkipWhile([](const auto& x){ return x.map[0] < 5; })
				.TakeWhile([](const auto& x){ return x.map[0] >= 5; })
				.Sum([](const auto& x) { return x.map[0]; });
	});

	assertEquals(x1, x2);

	x1 = test("concat-mod2-mod5-sum-vector", [&](){
		int sum = 0;
		for(auto&x : data) {
			if(x.map[0] % 2 != 0)
				continue;

			sum += x.map[0];
		}
		for(auto&x : data) {
			if(x.map[0] % 5 != 0)
				continue;

			sum += x.map[0];
		}
		return sum;
	});

	x2 = test("concat-mod2-mod5-sum-enumerable", [&](){
		return AdaptView(data).Where([](const auto& x){ return x.map[0] % 2 == 0; })
				.Concat(AdaptView(data).Where([](const auto& x){ return x.map[0] % 5 == 0; }))
				.Sum([](const auto& x) { return x.map[0]; });
	});

	assertEquals(x1, x2);
}

int main(int argc, char **argv)
{
	std::cout << "# Light objects" << std::endl;
	bench<light>();

	std::cout << "# Heavy objects" << std::endl;
	bench<heavy>();

	return EXIT_SUCCESS;
}