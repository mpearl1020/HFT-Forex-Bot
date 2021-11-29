#include "trade_logger.hpp"
#include "bellman_ford.hpp"
#include "data_preprocessing.hpp"

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    // SIMULATION AND LOGGER TEST
    std::vector<std::string> currencies = {
        "KWD", "BHD", "OMR", "JOD", 
        "GBP", "KYD", "EUR", "CHF", 
        "USD", "BSD", "BMD", "PAB", 
        "CAD", "AUD", "SGD", "BND", 
        "NZD", "BGN", "FJD", "BRL"
    };

    graph exchange_graph { currencies };

    for (std::string ticker_1 : currencies) {
        for (std::string ticker_2 : currencies) {
            float exchange_rate = 0;
            if (ticker_1 == ticker_2) {
                exchange_rate = 1;
            } else {
                exchange_rate = 0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100)));
            }
            exchange_graph.addEdge(ticker_1, ticker_2, exchange_rate);
        }
    }

    while (true) {
        std::vector<std::string> trade_sequence = bellman_ford(exchange_graph, "KWD");

        ofstream log;

        execute_trade(trade_sequence);

        // log profit -> how many times to make trade -> need original graph weights?
        // append instead of overwrite file?
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // sleep for 1 second
    }
}