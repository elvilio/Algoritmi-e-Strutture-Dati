#include <iostream>
#include <vector>
#include <string>
#include <list>
 
#include <limits>
 
#include <set>
#include <utility>
#include <algorithm>
#include <iterator>

/** Definitions **/

typedef int vertex_t;
typedef int weight_t;

const weight_t max_weight = std::numeric_limits<int>::max();

struct neighbor {
	vertex_t target;
	weight_t weight;
	neighbor(vertex_t arg_target, weight_t arg_weight)
		: target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;

/** Functions **/

void DijkstraComputePaths(vertex_t source,
						  const adjacency_list_t &adjacency_list,
						  std::vector<weight_t> &min_distance,
						  std::vector<vertex_t> &previous) {
	int n = adjacency_list.size();
	min_distance.clear();
	min_distance.resize(n, max_weight);
	min_distance[source] = 0;
	previous.clear();
	previous.resize(n, -1);
	std::set<std::pair<weight_t, vertex_t> > vertex_queue;
	vertex_queue.insert(std::make_pair(min_distance[source], source));

	while (!vertex_queue.empty()) {
		weight_t dist = vertex_queue.begin()->first;
		vertex_t u = vertex_queue.begin()->second;
		vertex_queue.erase(vertex_queue.begin());

		const std::vector<neighbor> &neighbors = adjacency_list[u];
		for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
			 neighbor_iter != neighbors.end();
			 neighbor_iter++) {
			vertex_t v = neighbor_iter->target;
			weight_t weight = neighbor_iter->weight;
			weight_t distance_through_u = dist + weight;
			if (distance_through_u < min_distance[v]) {
				vertex_queue.erase(std::make_pair(min_distance[v], v));

				min_distance[v] = distance_through_u;
				previous[v] = u;
				vertex_queue.insert(std::make_pair(min_distance[v], v));
			}
		}
	}
}

adjacency_list_t leggiGrafo(int N, int M){
	adjacency_list_t adjacency_list(N);

	for (int i=0; i<M; i++) {
		int u, v, p;
		std::cin >> u >> v >> p;

		adjacency_list[u].push_back(neighbor(v, p));
	}

	return adjacency_list;
}

/** Main **/

int main() {
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);

	int N, M;
	std::cin >> N >> M;

	adjacency_list_t adjacency_list = leggiGrafo(N, M);

	std::vector<weight_t> min_distance;
    std::vector<vertex_t> previous;

    DijkstraComputePaths(0, adjacency_list, min_distance, previous);
	
	if (min_distance[N-1] == max_weight) {
		std::cout << -1 << std::endl;
	}
	else {
		std::cout << min_distance[N-1] << std::endl;
	}

	return 0;
}