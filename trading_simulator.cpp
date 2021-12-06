#include "bellman_ford.hpp"
#include "data_preprocessing.hpp"
#include "graph.hpp"
#include "trade_logger.hpp"
#include "trade_logger.hpp"
#include "trade_executor.hpp"

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <unordered_set>
#include <unordered_map>
#include <iomanip>
#include <algorithm>


using namespace std;

void impute(graph exchange_graph) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        exchange_graph = random_data_imputations(exchange_graph);
    }
}

void trading_thread(graph exchange_graph, std::vector<std::string> currency_vector, std::unordered_map<std::string, std::vector<string>> all_arbitrage_opportunities, std::unordered_set<std::string> currencies_in_arbitrage, std::unordered_set<std::string> portfolio_currencies, std::unordered_map<std::string, float> portfolio) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    execute_trade(exchange_graph, currency_vector, all_arbitrage_opportunities, currencies_in_arbitrage, portfolio_currencies, portfolio);
}

void logger(std::unordered_map<std::string, float> portfolio) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        log_portfolio(portfolio);
    }
}

int main() {
    std::unordered_set<std::string> currency_set = {
        "KWD", "BHD", "OMR", "JOD", 
        "GBP", "KYD", "EUR", "CHF", 
        "USD", "BSD", "BMD", "PAB", 
        "CAD", "AUD", "SGD", "BND", 
        "NZD", "BGN", "FJD", "BRL"
    };

    std::vector<std::string> currency_vector = {
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

    // DO EXCEPTION HANDLING -> 0 OR NEGATIVE AMOUNTS, CORRECT TYPE, ETC.
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

    std::unordered_set<std::string> portfolio_currencies;

    for (const auto & [ ticker, amount ] : portfolio) {
        portfolio_currencies.insert(ticker);
    }

    std::thread log_thread(logger, portfolio);
    log_thread.join();

    std::unordered_map<std::string, float> unformatted_data = read_data_from_file("exchange_rates.txt");
    graph initial_exchange_graph = construct_initial_graph(unformatted_data); // always revert back to this
    graph exchange_graph = construct_initial_graph(unformatted_data);

    std::thread impute_thread(impute, exchange_graph);
    impute_thread.join();

    // TRADING
    while (true) {
        std::unordered_map<std::string, std::vector<string>> all_arbitrage_opportunities;
        std::unordered_set<std::string> currencies_in_arbitrage; 
        
        std::thread trade_thread(trading_thread, exchange_graph, currency_vector, all_arbitrage_opportunities, currencies_in_arbitrage, portfolio_currencies, portfolio);
        trade_thread.join();
        
        // PERFORM ARBITRAGE FOR 1 ms (SUBJECT TO CHANGE) -> REVERT BACK TO INITIAL GRAPH
        exchange_graph = initial_exchange_graph;

        // EVERY 1 s -> RANDOM IMPUTATIONS
    }

    // OUTPUT SUMMARY OF PORTFOLIO

    // START SCRAPING -> UPDATE EVERY 5 SECONDS

    // OUTPUT FINAL RETURNS ON EXIT
}