#include "bellman_ford.hpp"
#include "data_preprocessing.hpp"
#include "graph.hpp"
#include "trade_logger.hpp"
#include "trade_logger.hpp"

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
        cout << "impute thread run" << endl;
    }
}

void dumb_func() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        cout << "dumb thread run" << endl;
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

    // CONSTRUCT INTIAL DATA
    // std::unordered_map<std::string, 

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

    log_portfolio(portfolio);

    // INITIAL GRAPH CONSTRUCTION
    std::unordered_map<std::string, float> unformatted_data = read_data_from_file("exchange_rates.txt");
    graph initial_exchange_graph = construct_initial_graph(unformatted_data); // always revert back to this
    graph exchange_graph = construct_initial_graph(unformatted_data);

    // std::thread t0(dumb_func);
    std::thread t1(impute, exchange_graph); // MAKE WHOLE SIM TIME 60 s -> COMPARE THREADING VS. STANDARD RETURNS
    // t0.join();
    t1.join();

    // TRADING
    while (true) {
        std::unordered_map<std::string, std::vector<string>> all_arbitrage_opportunities;
        std::unordered_set<std::string> currencies_in_arbitrage; 
        // RUN BF FROM EACH SOURCE -> NON-THREADED



        // exchange_graph = random_data_imputations(exchange_graph); // DO EVERY SO OFTEN

        

        for (auto ticker : currency_vector) {
            // REMOVE DEFAULT ARBITRAGE IN GRAPH
            std::vector<std::string> trading_sequence = bellman_ford(prepare_for_bf(exchange_graph), ticker);
            all_arbitrage_opportunities[ticker] = trading_sequence;
            for (auto t: trading_sequence) {
                currencies_in_arbitrage.insert(t);
            }
        }

        // CHECK IF WE HAVE ANY OF THE CURRENCIES -> curriencies_in_arbitrage and portfolio_currencies (CHECK THIS)
        std::vector<std::string> intersection;

        std::set_intersection(portfolio_currencies.begin(), portfolio_currencies.end(),
                              currencies_in_arbitrage.begin(), currencies_in_arbitrage.end(),
                              std::back_inserter(intersection));
        
        std::string starting_currency;

        if (intersection.size() > 0) {
            // pick random currency from intersection
            int r = rand() % intersection.size();
            auto iter = intersection.begin();
            while (r--) {
                ++iter;
            }
            starting_currency = *iter;
        } else {
            // IF NOT PICK A RANDOM ONE THAT WE HAVE, BUY A RANDOM ONE IN THE ARBITRAGE AND PROCEED
        }

        

        // PERFORM ARBITRAGE FOR 1 ms (SUBJECT TO CHANGE) -> REVERT BACK TO INITIAL GRAPH

        // EVERY 1 s -> RANDOM IMPUTATIONS
    }

    // OUTPUT SUMMARY OF PORTFOLIO

    // START SCRAPING -> UPDATE EVERY 5 SECONDS

    // OUTPUT FINAL RETURNS ON EXIT
}