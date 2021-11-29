#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include "graph.hpp"

#include <vector>
#include <string>

using namespace std;

// finds a negative weight cycle if it exists
std::vector<std::string> bellman_ford(graph exchange_graph, string src_ticker);

#endif