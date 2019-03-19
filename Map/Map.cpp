//
// Created by Hubert on 2/9/2019.
//

#include "Map.h"
#include "Vertex.h"
#include "Edge.h"
#include <iostream>
#include <algorithm>

Map::Map() {
    vertices = std::vector<Vertex>();
    edges = std::vector<Edge>();
    regions = std::vector<std::string>();
    subgraphs = std::vector<Map>();
}

void Map::addVertex(Vertex v) {
    vertices.push_back(v);
}

void Map::addEdge(Vertex &u, Vertex &v, int cost) {
    Edge e = Edge(u, v, cost);
    u.addEdge(e);
    v.addEdge(e);
    edges.push_back(e);
}

int Map::numVertex() {
    return vertices.size();
}

int Map::numEdges() {
    return edges.size();
}

std::vector<Vertex> Map::getVertices() {
    return vertices;
}

std::vector<Edge> Map::getEdges() {
    return edges;
}

int Map::degree(Vertex v) {
    return v.getEdges()->size();
}

std::vector<Edge>* Map::getVertexEdges(Vertex v) {
    return v.getEdges();
}

Vertex Map::opposite(Vertex v, Edge e) {
    Vertex* endpoints = e.getEndpoints();
    if(endpoints[0] == v) {
        return endpoints[1];
    }
    else {
        return endpoints[0];
    }
}

bool Map::BFS() {
    auto level = std::vector<Vertex>();
    auto known = std::vector<Vertex>();
    level.push_back(vertices.at(0));
    known.push_back(vertices.at(0));
    while(!level.empty()) {
        auto nextLevel = std::vector<Vertex>();
        for(auto &u : level) {
            for(auto &e : *getVertexEdges(u)) {
                Vertex v = opposite(u, e);
                if(!(std::find(known.begin(), known.end(), v) != known.end())) {
                    known.push_back(v);
                    nextLevel.push_back(v);
                }
            }
        }
        level = nextLevel;
    }
    return known.size() == numVertex();
}

std::ostream &operator<<(std::ostream &os, Map &m) {
    os << "Regions:\n";
    for(const auto &r : m.getRegions()) {
        os << r << "\n";
    }
    os << "\nVertices:\n";
    for(int i = 0; i < m.numVertex(); i++) {
        os << m.getVertices().at(i);
    }
    os << "\nEdges:\n";
    for(int i = 0; i < m.numEdges(); i++) {
        os << m.getEdges().at(i);
    }
    os << "\n";
    return os;
}

Vertex Map::findVertex(std::string s) {
    for (auto v : vertices) {
        if(v.getName() == s ) {
            return v;
        }
    }
}

void Map::createSubgraphs() {
    int i = 0;
    for(auto r : regions) {
        Map g = Map();
        g.addRegion(r);
        for(auto v : vertices) {
            if(r == v.getRegion()) {
                g.addVertex(v);
            }
        }
        for(auto e : edges) {
            Vertex* endpoints = e.getEndpoints();
            if(endpoints[0].getRegion() == r && endpoints[1].getRegion() == r) {
                g.addEdge(e);
            }
        }
        subgraphs.push_back(g);
        i++;
    }
}

void Map::addRegion(std::string region) {
    regions.push_back(region);
}

std::vector<std::string> Map::getRegions() {
    return regions;
}

std::vector<Map> Map::getSubgraphs() {
    return subgraphs;
}

void Map::addEdge(Edge &e) {
    edges.push_back(e);
}

//void Map::placeHouse(Vertex v, House h) {
//    v.setHouse(h);
//}
