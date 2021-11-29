#include "graph.hpp"
#include "bellman_ford.hpp"

#include <vector>
#include <string>

#include <iostream>

using namespace std;

std::vector<std::string> bellman_ford(graph exchange_graph, string src_ticker) {
    std::vector<std::string> trading_sequence;

    std::unordered_map<std::string, std::unordered_map<std::string, float>> adjMap = exchange_graph.adjMap;
    
    std::unordered_map<std::string, float> distance;
    std::unordered_map<std::string, string> parent;

    int num_vertices = 0;

    for (const auto & [ ticker, adj_tickers ] : adjMap) {
        num_vertices ++;
        distance[ticker] = INT_MAX;
        parent[ticker] = "NONE";
    }

    distance[src_ticker] = 0;

    std::string negative_cycle_source = "~";

    for (int i = 0; i < num_vertices - 1; i++) {
        for (const auto & [ ticker_1, adj_tickers ] : adjMap) {
            for (const auto & [ ticker_2, weight ] : adj_tickers) {
                if (distance[ticker_1] != INT_MAX && distance[ticker_1] + weight < distance[ticker_2]) {
                    distance[ticker_2] = distance[ticker_1] + weight;
                    parent[ticker_2] = ticker_1;
                }
            }
        }
    }

    for (const auto & [ ticker_1, adj_tickers ] : adjMap) {
        for (const auto & [ ticker_2, weight ] : adj_tickers) {
            if (distance[ticker_1] != INT_MAX && distance[ticker_1] + weight < distance[ticker_2]) {
                negative_cycle_source = ticker_2;
                break;
            }
        }
    }

    if (negative_cycle_source != "~") {
        for (int i = 0; i < num_vertices; i++) {
            std::string p = parent[negative_cycle_source];
            negative_cycle_source = p;
        }
        std::string ticker = negative_cycle_source;
        while (true) {
            trading_sequence.push_back(ticker);
            ticker = parent[ticker];
            if (ticker == negative_cycle_source && trading_sequence.size() > 1) {
                break;
            }
        }
    }

    std::reverse(trading_sequence.begin(), trading_sequence.end());

    return trading_sequence;
}