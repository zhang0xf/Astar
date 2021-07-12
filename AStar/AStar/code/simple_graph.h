#pragma once
#include <unordered_map>

// 图的顶点使用char表示
struct SimpleGraph
{
	std::unordered_map<char, std::vector<char> > edges;

	std::vector<char> neighbors(char id) {
		return edges[id];
	}
};

void test_breadth_first_search_in_simple_graph();