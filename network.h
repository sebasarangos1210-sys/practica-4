#ifndef NETWORK_H
#define NETWORK_H

#include "Router.h"
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <functional>
#include <limits>
#include <random>

class Network {
private:
    std::map<std::string, Router> routers;

    // Algoritmo de Dijkstra
    void dijkstra(std::string source);

    // Utilidades
    std::string generateRouterId(int index);
    int randomCost(int min, int max);

public:
    // Gestión de routers
    void addRouter(std::string id);
    void removeRouter(std::string id);
    bool containsRouter(std::string id) const;
    std::vector<std::string> getRouterIds() const;
    Router* getRouter(std::string id);

    // Gestión de enlaces
    void addLink(std::string id1, std::string id2, int cost);
    void removeLink(std::string id1, std::string id2);
    void updateLinkCost(std::string id1, std::string id2, int newCost);
    bool areConnected(std::string id1, std::string id2) const;
    int getLinkCost(std::string id1, std::string id2) const;

    // Carga y generación
    void loadFromFile(std::string filename);
    void saveToFile(std::string filename) const;
    void generateRandom(int numRouters, double connectionProbability, int maxCost = 10);
    void generateRandom(int numRouters, int minConnections, int maxConnections, int maxCost = 10);

    // Cálculo de rutas
    void computeRoutes();
    void computeRoutes(std::string algorithm);
    void updateAllRoutingTables();

    // Consultas
    void printPath(std::string from, std::string to) const;
    void printAllPaths() const;
    void printNetworkTopology() const;
    void printAllRoutingTables() const;
    std::vector<std::string> findShortestPath(std::string from, std::string to) const;
    int getShortestPathCost(std::string from, std::string to) const;

    // Información de la red
    int getRouterCount() const;
    int getLinkCount() const;
    double getNetworkDensity() const;
    bool isConnected() const;
    std::vector<std::vector<std::string>> getDisconnectedComponents() const;
};

#endif
