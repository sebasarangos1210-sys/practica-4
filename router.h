#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <map>
#include <vector>
#include <iostream>

class Router {
private:
    std::string id;                                            // Identificador único del router
    std::map<std::string, int> neighbors;                      // vecino -> costo del enlace
    std::map<std::string, int> costTable;                      // destino -> costo mínimo
    std::map<std::string, std::vector<std::string>> pathTable; // destino -> camino completo

public:
    // Constructor
    Router(std::string id);

    // Constructor por defecto necesario para std::map
    Router() : id("") {}

    // Getters básicos
    std::string getId() const;

    // Gestión de vecinos (routers directamente conectados)
    void addNeighbor(std::string neighborId, int cost);
    void removeNeighbor(std::string neighborId);
    std::map<std::string, int> getNeighbors() const;
    bool isNeighbor(std::string neighborId) const;
    int getLinkCost(std::string neighborId) const;

    // Gestión de tablas de enrutamiento
    void setCostTable(const std::map<std::string, int>& costTable);
    void setPathTable(const std::map<std::string, std::vector<std::string>>& pathTable);
    std::map<std::string, int> getCostTable() const;
    std::map<std::string, std::vector<std::string>> getPathTable() const;

    // Consultas de ruta específicas
    int getCostTo(std::string dest) const;
    std::vector<std::string> getPathTo(std::string dest) const;

    // Visualización
    void printRoutingTable() const;
    void printNeighbors() const;

    // Utilidades
    void clearTables();
};

#endif // ROUTER_H
