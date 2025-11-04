#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <map>
#include <vector>
#include <iostream>

class Router {
private:
    std::string id;
    std::map<std::string, int> neighbors; // vecino -> costo
    std::map<std::string, int> costTable; // destino -> costo mínimo
    std::map<std::string, std::vector<std::string>> pathTable; // destino -> camino completo

public:
    // Constructor y básicos
    Router(std::string id);
    std::string getId() const;

    // Gestión de vecinos
    void addNeighbor(std::string neighborId, int cost);
    void removeNeighbor(std::string neighborId);
    std::map<std::string, int> getNeighbors() const;
    bool isNeighbor(std::string neighborId) const;
    int getLinkCost(std::string neighborId) const;

    // Gestión de tablas de enrutamiento
    void setCostTable(std::map<std::string, int> costTable);
    void setPathTable(std::map<std::string, std::vector<std::string>> pathTable);
    std::map<std::string, int> getCostTable() const;
    std::map<std::string, std::vector<std::string>> getPathTable() const;

    // Consultas de ruta
    int getCostTo(std::string dest) const;
    std::vector<std::string> getPathTo(std::string dest) const;
    void printRoutingTable() const;

    // Utilidades
    void clearTables();
};

#endif
