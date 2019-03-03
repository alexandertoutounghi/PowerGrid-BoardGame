//
// Created by Hubert on 2/9/2019.
//

#ifndef COMP345TEAM21_MAP_H
#define COMP345TEAM21_MAP_H

#include <vector>
#include "Vertex.h"

class Map {
public:
    Map();
    Map(const Map &m);
    void addVertex(Vertex v);
    void addEdge(Vertex u, Vertex v, int cost);
    bool BFS(Vertex v);
private:
    std::vector<Vertex>* vertices;
    std::vector<Edge>* edges;
};

#endif //COMP345TEAM21_MAP_H