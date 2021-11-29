#ifndef TRADE_LOGGER_HPP
#define TRADE_LOGGER_HPP

#include <fstream>
#include <vector>
#include <string>

using namespace std;

void execute_trade(ofstream log, std::vector<std::string> trade_sequence);

#endif