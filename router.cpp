#include "Router.h"

Router::Router(std::string id) : id(id) {}

std::string Router::getId() const {
    return id;
}

void Router::addNeighbor(std::string neighborId, int cost) {
    neighbors[neighborId] = cost;
}

void Router::removeNeighbor(std::string neighborId) {
    neighbors.erase(neighborId);
}

std::map<std::string, int> Router::getNeighbors() const {
    return neighbors;
}

bool Router::isNeighbor(std::string neighborId) const {
    return neighbors.find(neighborId) != neighbors.end();
}

int Router::getLinkCost(std::string neighborId) const {
    auto it = neighbors.find(neighborId);
    if (it != neighbors.end()) {
        return it->second;
    }
    return -1; // Indica que no es vecino
}

void Router::setCostTable(std::map<std::string, int> costTable) {
    this->costTable = costTable;
}

void Router::setPathTable(std::map<std::string, std::vector<std::string>> pathTable) {
    this->pathTable = pathTable;
}

std::map<std::string, int> Router::getCostTable() const {
    return costTable;
}

std::map<std::string, std::vector<std::string>> Router::getPathTable() const {
    return pathTable;
}

int Router::getCostTo(std::string dest) const {
    auto it = costTable.find(dest);
    if (it != costTable.end()) {
        return it->second;
    }
    return -1;
}

std::vector<std::string> Router::getPathTo(std::string dest) const {
    auto it = pathTable.find(dest);
    if (it != pathTable.end()) {
        return it->second;
    }
    return std::vector<std::string>();
}

void Router::printRoutingTable() const {
    std::cout << "Tabla de enrutamiento para " << id << ":\n";
    std::cout << "Destino\tCosto\tCamino\n";
    for (const auto& entry : costTable) {
        std::string dest = entry.first;
        int cost = entry.second;
        std::vector<std::string> path = pathTable.at(dest);

        std::cout << dest << "\t" << cost << "\t";
        for (size_t i = 0; i < path.size(); i++) {
            std::cout << path[i];
            if (i < path.size() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
    }
}

void Router::clearTables() {
    costTable.clear();
    pathTable.clear();
}
