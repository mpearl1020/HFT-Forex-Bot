#ifndef TRADE_LOGGER_HPP
#define TRADE_LOGGER_HPP

#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

void log_portfolio(std::unordered_map<std::string, float> portfolio);

void execute_trade(std::vector<std::string> trade_sequence);

#endif