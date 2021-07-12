#pragma once
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstdlib>

// 坐标
struct GridLocation
{
	int x, y;

	bool operator==(const GridLocation& grid) const
	{
		return x == grid.x && y == grid.y;
	}

	bool operator!=(const GridLocation& grid) const
	{
		return x != grid.x || y != grid.y;
	}

	bool operator < (const GridLocation& grid) const
	{
		return std::tie(x, y) < std::tie(grid.x, grid.y);
	}
};

namespace std
{
	// implement hash function so we can put GridLocation into an unordered_set
	template <> struct hash<GridLocation> {
		typedef GridLocation argument_type;
		typedef std::size_t result_type;
		std::size_t operator()(const GridLocation& id) const noexcept {
			return std::hash<int>()(id.x ^ (id.y << 4));
		}
	};
}

struct SquareGrid
{
	int width, height;
	static std::array<GridLocation, 4> DIRS;
	std::unordered_set<GridLocation> walls;

	SquareGrid(int width_, int height_)
		: width(width_), height(height_) {}

	bool in_bounds(GridLocation id) const {
		return 0 <= id.x && id.x < width
			&& 0 <= id.y && id.y < height;
	}

	bool passable(GridLocation id) const {
		return walls.find(id) == walls.end();
	}

	std::vector<GridLocation> neighbors(GridLocation id) const; 
};

// 绘制网格地图
template<class Graph>
void draw_grid(const Graph& graph,
	std::unordered_map<GridLocation, double>* distances = nullptr,
	std::unordered_map<GridLocation, GridLocation>* point_to = nullptr,
	std::vector<GridLocation>* path = nullptr,
	GridLocation* start = nullptr,
	GridLocation* goal = nullptr)
{
	const int field_width = 3;
	std::cout << std::string(field_width * graph.width, '_') << '\n';
	for (int y = 0; y != graph.height; ++y) {
		for (int x = 0; x != graph.width; ++x) {
			GridLocation id{ x, y };
			if (graph.walls.find(id) != graph.walls.end()) {
				std::cout << std::string(field_width, '#');
			}
			else if (start && id == *start) {
				std::cout << " A ";
			}
			else if (goal && id == *goal) {
				std::cout << " Z ";
			}
			else if (path != nullptr && find(path->begin(), path->end(), id) != path->end()) {
				std::cout << " @ ";
			}
			else if (point_to != nullptr && point_to->count(id)) {
				GridLocation next = (*point_to)[id];
				if (next.x == x + 1) { std::cout << " > "; }
				else if (next.x == x - 1) { std::cout << " < "; }
				else if (next.y == y + 1) { std::cout << " v "; }
				else if (next.y == y - 1) { std::cout << " ^ "; }
				else { std::cout << " * "; }
			}
			else if (distances != nullptr && distances->count(id)) {
				std::cout << ' ' << std::left << std::setw(field_width - 1) << (*distances)[id];
			}
			else {
				std::cout << " . ";
			}
		}
		std::cout << '\n';
	}
	std::cout << std::string(field_width * graph.width, '~') << '\n';
}

// 广度优先搜索
template<typename Location, typename Graph>
std::unordered_map<Location, Location> breadth_first_search_in_square_grid(Graph graph, Location start)
{
	std::queue<Location> frontier;
	frontier.push(start);

	std::unordered_map<Location, Location> came_from;
	came_from[start] = start;

	while (!frontier.empty()) {
		Location current = frontier.front();
		frontier.pop();

		for (Location next : graph.neighbors(current)) {
			if (came_from.find(next) == came_from.end()) {
				frontier.push(next);
				came_from[next] = current;
			}
		}
	}
	return came_from;
}

// 广度优先搜索（寻找目标）
template<typename Location, typename Graph>
std::unordered_map<Location, Location> breadth_first_search_in_square_grid(Graph graph, Location start, Location goal)
{
	std::queue<Location> frontier;
	frontier.push(start);

	std::unordered_map<Location, Location> came_from;
	came_from[start] = start;

	while (!frontier.empty()) {
		Location current = frontier.front();
		frontier.pop();

		if (current == goal) {
			break;
		}

		for (Location next : graph.neighbors(current)) {
			if (came_from.find(next) == came_from.end()) {
				frontier.push(next);
				came_from[next] = current;
			}
		}
	}
	return came_from;
}

void add_rect(SquareGrid& grid, int x1, int y1, int x2, int y2);
SquareGrid make_diagram1();
void test_draw_square_grid();
void test_draw_path_by_breadth_first_search_in_square_grid();
void test_draw_path_by_breadth_first_search_in_square_grid_to_goal();