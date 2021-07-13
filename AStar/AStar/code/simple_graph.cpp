#include <queue>
#include <unordered_set>
#include <iostream>
#include "simple_graph.h"

// 图的广度优先搜索
void breadth_first_search(SimpleGraph graph, char start)
{
	std::queue<char> frontier;
	frontier.push(start);

	std::unordered_set<char> reached;
	reached.insert(start);

	while (!frontier.empty())
	{
		char current = frontier.front();
		frontier.pop();

		std::cout << "visiting: " << current << "\n";

		for (char next : graph.neighbors(current))
		{
			if (reached.find(next) == reached.end())
			{
				reached.insert(next);
				frontier.push(next);
			}
		}
	}
}

void test_breadth_first_search_in_simple_graph()
{
	// 创建图
	SimpleGraph example_graph{ {
	{'A', {'B'}},
	{'B', {'C'}},
	{'C', {'B', 'D', 'F'}},
	{'D', {'C', 'E'}},
	{'E', {'F'}},
	{'F', {}},
	}};

	std::cout << "Reachable from A:\n";
	breadth_first_search(example_graph, 'A');
	std::cout << "Reachable from E:\n";
	breadth_first_search(example_graph, 'E');
}