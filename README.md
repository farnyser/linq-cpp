Linq C++
========

Yet another Simplified Linq for C++ !

Example
-------

```c++
struct Point { int x; int y }
std::vector<Point> source = GetAllPointsInRange();

// find point with max X coordinate having Y coordinate lower than 1.0
auto p = AdaptView(source)
		.Where([](const auto& p) { return p.y < 1.0; })
		.Max([](const auto& p) { return p.x; });
```

Supported operations
--------------------

* Range
* Where, Skip, SkipWhile, Take, TakeWhile
* Select
* GroupBy
* First, Last, Single, Min, Max
* Count, Sum
* Concat, Union, Distinct, Intersect, Except
* Any, All, Contains

What's next
------------

* SelectMany
* OrderBy, OrderByDescending
* ToMap