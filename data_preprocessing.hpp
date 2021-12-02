#ifndef DATA_PREPROCESSING_HPP
#define DATA_PREPROCESSING_HPP

#include "graph.hpp"

#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

std::unordered_map<std::string, float> read_data_from_file(string file_path);

// assume given "<ticker_1><ticker_2>" and weight as an unordered map
graph construct_initial_graph(std::unordered_map<std::string, float>);

// alter data so it works with the Bellman Ford Algorithm
graph prepare_for_bf(graph initial_graph);

// random imputations to simulate arbitrage opportunities appearing
graph random_data_imputations(graph exchange_graph);

#endif