#include "graph.hpp"

// FOR TESTING -> REMOVE LATER
#include <iostream>

using namespace std;

graph::graph(std::vector<std::string> tickers) {
    for (auto ticker: tickers) {
        std::unordered_map<std::string, float> init_mapping;
        adjMap[ticker] = init_mapping;
    }
}

// adds directed weighted edge from currency_1 to currency_2
bool graph::addEdge(std::string currency_1, std::string currency_2, float exchange_rate) {
    if (currency_1 == currency_2) {
        return false;
    }

    // check if edge already exists -> probably don't need

    else {
        adjMap[currency_1][currency_2] = exchange_rate;
        return true;
    }
}