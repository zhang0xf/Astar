#pragma once
#include "square_grid.h"

// 权重图与狄克斯特拉算法
struct GridWithWeights : SquareGrid
{
	// 森林地形的移动花费是5
	std::unordered_set<GridLocation> forests;
	GridWithWeights(int w, int h) : SquareGrid(w, h) {}
	double cost(GridLocation from_node, GridLocation to_node) const {
		return forests.find(to_node) != forests.end() ? 5 : 1;
	}
};

// 优先队列
template<typename T, typename priority_t>
struct PriorityQueue 
{
	typedef std::pair<priority_t, T> PQElement;
	// 底层容器使用vector
	std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> elements;

	inline bool empty() const {
		return elements.empty();
	}

	inline void put(T item, priority_t priority) {
		elements.emplace(priority, item);
	}

	T get() {
		T best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};

template<typename Location, typename Graph>
void dijkstra_search(
	Graph graph,
	Location start,
	Location goal,
	std::unordered_map<Location, Location>& came_from,
	std::unordered_map<Location, double>& cost_so_far)
{
	PriorityQueue<Location, double> frontier;
	frontier.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty()) {
		Location current = frontier.get();

		if (current == goal) {
			break;
		}

		for (Location next : graph.neighbors(current)) {
			double new_cost = cost_so_far[current] + graph.cost(current, next);
			if (cost_so_far.find(next) == cost_so_far.end()
				|| new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				came_from[next] = current;
				frontier.put(next, new_cost);
			}
		}
	}
}

// 构建路径
template<typename Location>
std::vector<Location> reconstruct_path(
	Location start, Location goal,
	std::unordered_map<Location, Location> came_from)
{
	std::vector<Location> path;
	Location current = goal;
	while (current != start) {
		path.push_back(current);
		current = came_from[current];
	}
	path.push_back(start); // 可选
	std::reverse(path.begin(), path.end());
	return path;
}

inline double heuristic(GridLocation a, GridLocation b) {
	// 曼哈顿距离
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

template<typename Location, typename Graph>
void a_star_search
(Graph graph,
	Location start,
	Location goal,
	std::unordered_map<Location, Location>& came_from,
	std::unordered_map<Location, double>& cost_so_far)
{
	PriorityQueue<Location, double> frontier;
	frontier.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty()) {
		Location current = frontier.get();

		if (current == goal) {
			break;
		}

		for (Location next : graph.neighbors(current)) {
			double new_cost = cost_so_far[current] + graph.cost(current, next);
			if (cost_so_far.find(next) == cost_so_far.end()
				|| new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				double priority = new_cost + heuristic(next, goal);
				frontier.put(next, priority);
				came_from[next] = current;
			}
		}
	}
}

void test_draw_path_by_dijkstra_search_in_weighted_grid();
void test_draw_path_by_a_star_search_in_weighted_grid();