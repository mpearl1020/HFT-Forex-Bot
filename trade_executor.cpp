#include "trade_executor.hpp"
#include "graph.hpp"
#include "data_preprocessing.hpp"
#include "bellman_ford.hpp"
#include "trade_logger.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <chrono>
#include <cmath>

using namespace std;

std::unordered_map<std::string, float> execute_trade(graph exchange_graph, std::vector<std::string> currency_vector, std::unordered_map<std::string, std::vector<string>> all_arbitrage_opportunities, std::unordered_set<std::string> currencies_in_arbitrage, std::unordered_set<std::string> portfolio_currencies, std::unordered_map<std::string, float> portfolio) {
    std::vector<std::string> trading_sequence;

    for (auto ticker : currency_vector) {
        trading_sequence = bellman_ford(prepare_for_bf(exchange_graph), ticker);
        all_arbitrage_opportunities[ticker] = trading_sequence;
        for (auto t : trading_sequence) {
            currencies_in_arbitrage.insert(t);
        }
    }

    log_trade(trading_sequence);

    std::vector<std::string> intersection;

    std::set_intersection(portfolio_currencies.begin(), portfolio_currencies.end(),
                            currencies_in_arbitrage.begin(), currencies_in_arbitrage.end(),
                            std::back_inserter(intersection));
    
    std::string starting_currency;

    if (intersection.size() > 0) {
        int r = rand() % intersection.size();
        auto iter = intersection.begin();
        while (r--) {
            ++iter;
        }
        starting_currency = *iter;
    } 

    std::unordered_map<std::string, std::unordered_map<std::string, float>> adjMap = exchange_graph.adjMap;

    std::chrono::steady_clock::time_point init_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point curr;

    int count = 0;

    while (std::chrono::duration_cast<std::chrono::microseconds>(curr - init_time).count() < 1000) {
        cout << count << endl;
        curr = std::chrono::steady_clock::now();
        
        for (int i = 0; i < trading_sequence.size(); i++) {}
        count++;
    }

    std::string ticker_1;
    std::string ticker_2;
    
    float multiplier = 1;
    for (int i = 0; i < trading_sequence.size() - 1; i++) {
        ticker_1 = trading_sequence[i];
        ticker_2 = trading_sequence[i+1];
        float exchange_rate = adjMap[ticker_1][ticker_2];

        multiplier *= exchange_rate;
    }

    float final_exchange_rate = adjMap[trading_sequence[trading_sequence.size() - 1]][trading_sequence[0]];
    multiplier *= final_exchange_rate;

    portfolio[starting_currency] = (portfolio[starting_currency] * pow (multiplier, count));

    return portfolio;
}