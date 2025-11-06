#include "Router.h"
#include <iomanip>

// ==================== CONSTRUCTOR ====================

Router::Router(std::string id) : id(id) {}

// ==================== GETTERS BÁSICOS ====================

std::string Router::getId() const {
    return id;
}

// ==================== GESTIÓN DE VECINOS ====================

void Router::addNeighbor(std::string neighborId, int cost) {
    if (cost > 0) {
        neighbors[neighborId] = cost;
    }
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

// ==================== GESTIÓN DE TABLAS DE ENRUTAMIENTO ====================

void Router::setCostTable(const std::map<std::string, int>& costTable) {
    this->costTable = costTable;
}

void Router::setPathTable(const std::map<std::string, std::vector<std::string>>& pathTable) {
    this->pathTable = pathTable;
}

std::map<std::string, int> Router::getCostTable() const {
    return costTable;
}

std::map<std::string, std::vector<std::string>> Router::getPathTable() const {
    return pathTable;
}

// ==================== CONSULTAS DE RUTA ====================

int Router::getCostTo(std::string dest) const {
    auto it = costTable.find(dest);
    if (it != costTable.end()) {
        return it->second;
    }
    return -1; // No hay ruta
}

std::vector<std::string> Router::getPathTo(std::string dest) const {
    auto it = pathTable.find(dest);
    if (it != pathTable.end()) {
        return it->second;
    }
    return std::vector<std::string>();
}

// ==================== VISUALIZACIÓN ====================

void Router::printRoutingTable() const {
    std::cout << "\n╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║  Tabla de Enrutamiento - Router " << std::left << std::setw(22) << id << "║\n";
    std::cout << "╠════════════════════════════════════════════════════════════╣\n";
    std::cout << "║ Destino   │ Costo │ Camino                              ║\n";
    std::cout << "╠═══════════╪═══════╪═════════════════════════════════════╣\n";

    if (costTable.empty()) {
        std::cout << "║           │       │ (Tabla vacía)                       ║\n";
    } else {
        for (const auto& entry : costTable) {
            std::string dest = entry.first;
            int cost = entry.second;

            auto pathIt = pathTable.find(dest);
            if (pathIt != pathTable.end()) {
                std::vector<std::string> path = pathIt->second;

                std::cout << "║ " << std::left << std::setw(9) << dest << " │ ";
                std::cout << std::right << std::setw(5) << cost << " │ ";

                // Construir string del camino
                std::string pathStr;
                for (size_t i = 0; i < path.size(); i++) {
                    pathStr += path[i];
                    if (i < path.size() - 1) pathStr += " → ";
                }

                std::cout << std::left << std::setw(35) << pathStr << " ║\n";
            }
        }
    }

    std::cout << "╚════════════════════════════════════════════════════════════╝\n";
}

void Router::printNeighbors() const {
    std::cout << "Router " << id << " conectado a: ";
    if (neighbors.empty()) {
        std::cout << "(sin vecinos)";
    } else {
        bool first = true;
        for (const auto& neighbor : neighbors) {
            if (!first) std::cout << ", ";
            std::cout << neighbor.first << "(costo: " << neighbor.second << ")";
            first = false;
        }
    }
    std::cout << std::endl;
}

// ==================== UTILIDADES ====================

void Router::clearTables() {
    costTable.clear();
    pathTable.clear();
}
