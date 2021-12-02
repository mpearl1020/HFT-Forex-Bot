#include "data_preprocessing.hpp"
#include "graph.hpp"

#include <iostream>

#include <unordered_map>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

std::unordered_map<std::string, float> read_data_from_file(string file_path) {
    std::vector<string> lines;
    std::string line;

    std::ifstream input_file;
    input_file.open(file_path);

    while (!input_file.eof()) {
        getline(input_file, line);
        lines.push_back(line);
    }

    input_file.close();

    std::unordered_map<std::string, float> processed_data;

    for (auto data_line : lines) {
        std::vector<std::string> line_components;
        std::istringstream ss(data_line);
        std::string component;

        while (getline(ss, component, '\t')) {
            line_components.push_back(component);
        }

        if (line_components.size() > 0) {
            std::string ticker_1 = line_components[0];
            std::string ticker_2 = line_components[1];
            float exchange_val = std::stof(line_components[2]);

            std::string combined_tickers = ticker_1 + "/" + ticker_2;

            processed_data[combined_tickers] = exchange_val;
        }
        
    }

    // FIGURE OUT SEG FAULT -> OCCURRING AFTER FOR LOOP
    return processed_data;
}

graph construct_initial_graph(std::unordered_map<std::string, float> unformatted_data) {
    std::vector<string> all_tickers;
    std::set<string> ticker_set;

    for (const auto & [ ticker_strings, exchange_rate ] : unformatted_data) {
        std::string ticker_1 = ticker_strings.substr(0, 3);
        std::string ticker_2 = ticker_strings.substr(4, 3);

        ticker_set.insert(ticker_1);
        ticker_set.insert(ticker_2);

        if (ticker_set.find(ticker_1) != ticker_set.end()) {
            all_tickers.push_back(ticker_1);
        }
        if (ticker_set.find(ticker_2) != ticker_set.end()) {
            all_tickers.push_back(ticker_2);
        }
    }

    graph exchange_graph(all_tickers);

    for (const auto & [ ticker_strings, exchange_rate ] : unformatted_data) {
        std::string ticker_1 = ticker_strings.substr(0, 3);
        std::string ticker_2 = ticker_strings.substr(4, 3);

        bool successful_addition = exchange_graph.addEdge(ticker_1, ticker_2, exchange_rate);
    }

    return exchange_graph;
}

// take log(1 / R) for all R
graph prepare_for_bf(graph exchange_graph) {
    std::unordered_map<std::string, std::unordered_map<std::string, float>> adjMap = exchange_graph.adjMap;

    for (const auto & [ ticker_1, edges ] : adjMap) {
        for (const auto & [ ticker_2, weight ] : edges) {
            float modified_weight = log2(1 / weight);
            adjMap[ticker_1][ticker_2] = modified_weight;
        }
    }

    exchange_graph.adjMap = adjMap;

    return exchange_graph;
}

graph random_data_imputations(graph exchange_graph) {
    std::unordered_map<std::string, std::unordered_map<std::string, float>> adjMap = exchange_graph.adjMap;

    std::vector<std::string> currency_vector = {
        "KWD", "BHD", "OMR", "JOD", 
        "GBP", "KYD", "EUR", "CHF", 
        "USD", "BSD", "BMD", "PAB", 
        "CAD", "AUD", "SGD", "BND", 
        "NZD", "BGN", "FJD", "BRL"
    };

    std::vector<std::string> all_currency_pairs;

    for (auto ticker_1 : currency_vector) {
        for (auto ticker_2 : currency_vector) {
            if (ticker_1 != ticker_2) {
                all_currency_pairs.push_back(ticker_1 + "/" + ticker_2);
            }
        }
    }

    std::set<int> pick_set;
    int picks = 0;

    while (picks < 5) {
        int rand_num = rand() % 380;
        if (!(pick_set.find(rand_num) != pick_set.end())) {
            pick_set.insert(rand_num);
            picks++;
        }
    }

    for (auto rand_idx : pick_set) {
        std::string ticker_pair = all_currency_pairs[rand_idx];
        std::string ticker_1 = ticker_pair.substr(0, 3);
        std::string ticker_2 = ticker_pair.substr(4, 3);

        float rand_exchange_rate = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5));

        adjMap[ticker_1][ticker_2] = rand_exchange_rate;
    }

    exchange_graph.adjMap = adjMap;

    return exchange_graph;
}