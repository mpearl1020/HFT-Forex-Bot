#ifndef TRADE_EXECUTOR_HPP
#define TRADE_EXECUTOR_HPP

#include "graph.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

std::unordered_map<std::string, float> execute_trade(graph exchange_graph, std::vector<std::string> currency_vector, std::unordered_map<std::string, std::vector<string>> all_arbitrage_opportunities, std::unordered_set<std::string> currencies_in_arbitrage, std::unordered_set<std::string> portfolio_currencies, std::unordered_map<std::string, float> portfolio);

#endif