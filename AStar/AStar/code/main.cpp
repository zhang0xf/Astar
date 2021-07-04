#include "simple_graph.h"
#include "square_grid.h"
#include "grid_weights.h"

int main()
{
	// test_breadth_first_search_in_simple_graph();
	// test_draw_square_grid();
	// test_draw_path_by_breadth_first_search_in_square_grid();
	// test_draw_path_by_breadth_first_search_in_square_grid_to_goal();
	// test_draw_path_by_dijkstra_search_in_weighted_grid();
	test_draw_path_by_a_star_search_in_weighted_grid();
	system("pause");
	return 0;
}
