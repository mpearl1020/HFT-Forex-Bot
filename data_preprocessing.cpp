#include "data_preprocessing.hpp"

#include <unordered_map>
#include <vector>
#include <set>
#include <string>
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
        int data_length = data_line.length();
        
        std::string ticker_1 = data_line.substr(0, 3);
        std::string ticker_2 = data_line.substr(4, 3);
        std::string combined_tickers = ticker_1 + ticker_2;

        std::string exchange_val_string = data_line.substr(8, data_length - 8);
        float exchange_val = std::stof(exchange_val_string);
        
        processed_data[combined_tickers] = exchange_val;
    }

    return processed_data;
}

graph construct_initial_graph(std::unordered_map<std::string, float> unformatted_data) {
    std::vector<string> all_tickers;
    std::set<string> ticker_set;

    for (const auto & [ ticker_strings, exchange_rate ] : unformatted_data) {
        std::string ticker_1 = ticker_strings.substr(0, 3);
        std::string ticker_2 = ticker_strings.substr(3, 3);

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

    // WILL THIS HAVE BOTH DIRECTIONS ALREADY? -> ADD EDGES
    for (const auto & [ ticker_strings, exchange_rate ] : unformatted_data) {
        std::string ticker_1 = ticker_strings.substr(0, 3);
        std::string ticker_2 = ticker_strings.substr(3, 3);

        bool successful_addition = exchange_graph.addEdge(ticker_1, ticker_2, exchange_rate);
    }

    return exchange_graph;
}

// take log(1 / R) for all R
void prepare_for_bf(graph exchange_graph) {
    std::unordered_map<std::string, std::unordered_map<std::string, float>> adjMap = exchange_graph.adjMap;

    for (const auto & [ ticker_1, edges ] : adjMap) {
        for (const auto & [ ticker_2, weight ] : edges) {
            float modified_weight = log2(1 / weight);
            adjMap[ticker_1][ticker_2] = modified_weight;
        }
    }
}