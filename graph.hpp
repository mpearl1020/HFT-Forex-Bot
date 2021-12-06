#ifndef GRAPH_VERTEX_HPP
#define GRAPH_VERTEX_HPP

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class graph {
    public:
        std::unordered_map<std::string, std::unordered_map<std::string, float>> adjMap; 
        
        graph(std::vector<std::string>);
        bool addEdge(std::string, std::string, float);
};

#endif