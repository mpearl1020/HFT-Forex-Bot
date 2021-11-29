#ifndef GRAPH_VERTEX_HPP
#define GRAPH_VERTEX_HPP

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

/*
HashMap[]
string: (string, float)
map of maps:

unordered_map_1(string: unordered_map_2(string, float))
*/

/*
graph allows for restrictions on trading
could be sparse for example
*/
class graph {
    public:
        std::unordered_map<std::string, std::unordered_map<std::string, float>> adjMap; // move to private
        
        graph(std::vector<std::string>);
        bool tickerExists(std::string);
        bool addEdge(std::string, std::string, float);
};

#endif