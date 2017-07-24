#include "../assert.hpp"
#include "../src/IEnumerable.hpp"

using namespace linq;

template <typename S>
void test(S source)
{
	assertEquals( 3, source.Min());
	assertEquals(10, source.Max());
	assertEquals( 8, source.Count());
	assertEquals(52, source.Sum());
	assertEquals( 3, source.Take(3).Min());
	assertEquals( 5, source.Take(3).Max());
	assertEquals( 6, source.Skip(3).Min());
	assertEquals(10, source.Skip(3).Max());
	assertEquals( 3, source.TakeWhile([](int x){ return x < 5; }).Min());
	assertEquals( 4, source.TakeWhile([](int x){ return x < 5; }).Max());
	assertEquals( 5, source.SkipWhile([](int x){ return x < 5; }).Min());
	assertEquals( 4, source.Where([](int x){ return x < 7; }).Count());
	assertEquals( 6, source.Where([](int x){ return x % 3 == 0; }).Skip(1).First());
	assertEquals( 2, source.GroupBy([](int x){ return x < 5; }).Count());
	assertEquals( 6, source.GroupBy([](int x){ return x < 5; }).First().Count());
	assertEquals( 2, source.GroupBy([](int x){ return x < 5; }).Last().Count());
	assertEquals( 5, source.Single([](int x){ return x == 5; }));
}

int main()
{
	auto data = std::vector<int>{3,4,5,6,7,8,9,10};

	test(IEnumerable<int>::Range(3,10));
	test(IEnumerable<int>::Range(0,100).Where([](int x){ return x >= 3 && x <= 10; }));
	test(IEnumerable<int>::Range(3,5).Concat(IEnumerable<int>::Range(6,10)));
	test(IEnumerable<int>::Range(3,5).Union(IEnumerable<int>::Range(4,10)));
	test(AdaptView(std::vector<int>{3,4,5,6,7,8,9,10}));
	test(AdaptView(data));

	return EXIT_SUCCESS;
}