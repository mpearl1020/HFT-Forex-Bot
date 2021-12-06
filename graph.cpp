#include "graph.hpp"

using namespace std;

graph::graph(std::vector<std::string> tickers) {
    for (auto ticker: tickers) {
        std::unordered_map<std::string, float> init_mapping;
        adjMap[ticker] = init_mapping;
    }
}

bool graph::addEdge(std::string currency_1, std::string currency_2, float exchange_rate) {
    if (currency_1 == currency_2) {
        return false;
    } else {
        adjMap[currency_1][currency_2] = exchange_rate;
        return true;
    }
}