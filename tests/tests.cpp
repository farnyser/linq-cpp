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
	assertEquals( 5, Adapt(std::vector<int>{1,5,6,7,5}).Intersect(source).Min());
	assertEquals( 7, Adapt(std::vector<int>{1,5,6,7,5}).Intersect(source).Max());
	assertEquals( 3, Adapt(std::vector<int>{1,5,6,7,5}).Intersect(source).Count());
	assertEquals( 3, source.Intersect(Adapt(std::vector<int>{1,5,6,7,5})).Count());
	assertEquals( 5, source.Except(Adapt(std::vector<int>{1,5,6,7,5})).Count());
	assertEquals( 3, source.Except(IEnumerable<int>::Range(5,9)).Count());
	assertEquals( 8, source.Intersect(source).Count());
	assertEquals( 0, source.Except(source).Count());
}

int main()
{
	auto data = std::vector<int>{3,4,5,6,7,8,9,10};

	test(IEnumerable<int>::Range(3,10));
	test(IEnumerable<int>::Range(0,100).Where([](int x){ return x >= 3 && x <= 10; }));
	test(IEnumerable<int>::Range(3,5).Concat(IEnumerable<int>::Range(6,10)));
	test(IEnumerable<int>::Range(3,5).Union(IEnumerable<int>::Range(4,10)));
	test(Adapt(std::vector<int>{3,4,5,6,7,8,9,10}));
//	test(AdaptView(data)); // TODO Fix this with multiple usage in the same query
	test(Adapt(std::move(data)));

	return EXIT_SUCCESS;
}