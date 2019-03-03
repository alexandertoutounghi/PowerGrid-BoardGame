//
// Created by Hubert on 2/9/2019.
//

#ifndef COMP345TEAM21_VERTEX_H
#define COMP345TEAM21_VERTEX_H

#include <vector>
#include "Edge.h"

class Edge;

class Vertex {
public:
    Vertex();
    Vertex(std::string name, std::string region);
    Vertex(const Vertex &v);
    std::vector<Edge>* getEdges();
    int getCost();
    std::string getRegion();
    int getPlayerCount();
    std::string getPlayer(int i);
    std::string getName();
    Vertex& operator=(const Vertex &v);
private:
    int cost[3];
    int playerCount = 0;
    std::string players[3];
    std::string name;
    std::string region;
    std::vector<Edge> *edges;
};

#endif //COMP345TEAM21_VERTEX_H