#include "trade_logger.hpp"

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iterator>

using namespace std;

void execute_trade(ofstream log, std::vector<std::string> trade_sequence) {
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    log.open("trade_log.txt");
    if (trade_sequence.size() == 0) {
        log << std::ctime(&time) << " : No arbitrage opportunity exists at this time" << endl;
        log.close();
        return;
    } else {
        log << std::ctime(&time) << " : Trade in the following sequence for arbitrage: ";
        for (int i = 0; i < trade_sequence.size() - 1; i++) {
            log << trade_sequence[i] << " -> ";
        }
        log << trade_sequence[trade_sequence.size() - 1];
        log << endl;    
    }
}