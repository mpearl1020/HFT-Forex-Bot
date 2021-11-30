// #include "trade_logger.hpp"
// #include "bellman_ford.hpp"
// #include "data_preprocessing.hpp"

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <unordered_set>
#include <unordered_map>
#include <iomanip>

using namespace std;

int main() {
    // SIMULATION AND LOGGER TEST
    /*
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
                exchange_rate = 50 - static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100)));
            }
            exchange_graph.addEdge(ticker_1, ticker_2, exchange_rate);
        }
    }

    while (true) {
        // every 5 seconds, impute a random value

        std::vector<std::string> trade_sequence = bellman_ford(exchange_graph, "KWD");

        ofstream log;

        execute_trade(trade_sequence);

        // log profit -> how many times to make trade -> need original graph weights?
        // append instead of overwrite file?
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // sleep for 1 second
    }
    */

    // MAIN SIMULATOR
    std::unordered_set<std::string> currency_set = {
        "KWD", "BHD", "OMR", "JOD", 
        "GBP", "KYD", "EUR", "CHF", 
        "USD", "BSD", "BMD", "PAB", 
        "CAD", "AUD", "SGD", "BND", 
        "NZD", "BGN", "FJD", "BRL"
    };

    std::unordered_map<std::string, float> portfolio;

    cout << "Enter your currencies" << endl;
    bool exit = false;
    int currency_counter = 1;

    std::string current_ticker;
    float current_amount;
    std::string more_currencies;

    while (true) {
        if (exit) {
            break;
        }
        cout << "Enter ticker for currency " << currency_counter << ": ";
        cin >> current_ticker;
        if (!(currency_set.find(current_ticker) != currency_set.end())) {
            std::cout << "Please enter a valid currency" << endl;
            continue;
        }
        cout << "Enter amount for curreny " << currency_counter << ": ";
        cin >> current_amount;
        if (!(portfolio.find(current_ticker) != portfolio.end())) {
            portfolio[current_ticker] += current_amount;
        } else {
            portfolio[current_ticker] = current_amount;
        }
        cout << "Would you like to enter another currency? (Y/N): ";
        cin >> more_currencies;
        if (more_currencies == "N") {
            exit = true;
        } else if (more_currencies == "Y") {
            continue;
        } else {
            // ERROR CONDITION
        }
        currency_counter++;
    }

    // AFTER INITIAL PORTFOLIO CONSTRUCTION

    // OUTPUT SUMMARY OF PORTFOLIO

    // START SCRAPING -> UPDATE EVERY 5 SECONDS

    // OUTPUT FINAL RETURNS ON EXIT
}