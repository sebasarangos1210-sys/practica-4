#include "Network.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>

// Gestión de routers
void Network::addRouter(std::string id) {
    if (!containsRouter(id)) {
        routers.emplace(id, Router(id));
    }
}

void Network::removeRouter(std::string id) {
    // Eliminar el router
    routers.erase(id);

    // Eliminar todas las referencias a este router como vecino
    for (auto& pair : routers) {
        pair.second.removeNeighbor(id);
    }
}

bool Network::containsRouter(std::string id) const {
    return routers.find(id) != routers.end();
}

std::vector<std::string> Network::getRouterIds() const {
    std::vector<std::string> ids;
    for (const auto& pair : routers) {
        ids.push_back(pair.first);
    }
    return ids;
}

Router* Network::getRouter(std::string id) {
    auto it = routers.find(id);
    if (it != routers.end()) {
        return &(it->second);
    }
    return nullptr;
}

// Gestión de enlaces
void Network::addLink(std::string id1, std::string id2, int cost) {
    if (containsRouter(id1) && containsRouter(id2)) {
        routers[id1].addNeighbor(id2, cost);
        routers[id2].addNeighbor(id1, cost);
    }
}

void Network::removeLink(std::string id1, std::string id2) {
    if (containsRouter(id1) && containsRouter(id2)) {
        routers[id1].removeNeighbor(id2);
        routers[id2].removeNeighbor(id1);
    }
}

void Network::updateLinkCost(std::string id1, std::string id2, int newCost) {
    removeLink(id1, id2);
    addLink(id1, id2, newCost);
}

bool Network::areConnected(std::string id1, std::string id2) const {
    auto it = routers.find(id1);
    if (it != routers.end()) {
        return it->second.isNeighbor(id2);
    }
    return false;
}

int Network::getLinkCost(std::string id1, std::string id2) const {
    auto it = routers.find(id1);
    if (it != routers.end()) {
        return it->second.getLinkCost(id2);
    }
    return -1;
}

// Carga y generación
void Network::loadFromFile(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id1, id2;
        int cost;

        if (iss >> id1 >> id2 >> cost) {
            addRouter(id1);
            addRouter(id2);
            addLink(id1, id2, cost);
        }
    }
    file.close();
}

void Network::saveToFile(std::string filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo " << filename << std::endl;
        return;
    }

    std::set<std::pair<std::string, std::string>> writtenLinks;

    for (const auto& routerPair : routers) {
        std::string id1 = routerPair.first;
        auto neighbors = routerPair.second.getNeighbors();

        for (const auto& neighbor : neighbors) {
            std::string id2 = neighbor.first;
            int cost = neighbor.second;

            // Evitar duplicados
            std::pair<std::string, std::string> link = (id1 < id2) ?
                                                           std::make_pair(id1, id2) : std::make_pair(id2, id1);

            if (writtenLinks.find(link) == writtenLinks.end()) {
                file << id1 << " " << id2 << " " << cost << std::endl;
                writtenLinks.insert(link);
            }
        }
    }
    file.close();
}

void Network::generateRandom(int numRouters, double connectionProbability, int maxCost) {
    routers.clear();

    // Crear routers
    for (int i = 0; i < numRouters; i++) {
        addRouter(generateRouterId(i));
    }

    // Crear enlaces aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> probDist(0.0, 1.0);
    std::uniform_int_distribution<> costDist(1, maxCost);

    auto ids = getRouterIds();
    for (size_t i = 0; i < ids.size(); i++) {
        for (size_t j = i + 1; j < ids.size(); j++) {
            if (probDist(gen) < connectionProbability) {
                addLink(ids[i], ids[j], costDist(gen));
            }
        }
    }
}

void Network::generateRandom(int numRouters, int minConnections, int maxConnections, int maxCost) {
    routers.clear();

    // Crear routers
    for (int i = 0; i < numRouters; i++) {
        addRouter(generateRouterId(i));
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> connDist(minConnections, maxConnections);
    std::uniform_int_distribution<> costDist(1, maxCost);

    auto ids = getRouterIds();

    // Asegurar conectividad mínima
    for (size_t i = 0; i < ids.size(); i++) {
        int targetConnections = connDist(gen);
        int currentConnections = routers[ids[i]].getNeighbors().size();

        while (currentConnections < targetConnections) {
            // Encontrar router no conectado
            std::vector<std::string> candidates;
            for (size_t j = 0; j < ids.size(); j++) {
                if (i != j && !areConnected(ids[i], ids[j])) {
                    candidates.push_back(ids[j]);
                }
            }

            if (candidates.empty()) break;

            std::uniform_int_distribution<> indexDist(0, candidates.size() - 1);
            std::string selected = candidates[indexDist(gen)];
            addLink(ids[i], selected, costDist(gen));
            currentConnections++;
        }
    }
}

// Algoritmo de Dijkstra
void Network::dijkstra(std::string source) {
    if (!containsRouter(source)) return;

    std::map<std::string, int> dist;
    std::map<std::string, std::string> prev;
    std::set<std::string> visited;

    // Inicializar distancias
    for (const auto& id : getRouterIds()) {
        dist[id] = std::numeric_limits<int>::max();
    }
    dist[source] = 0;

    // Cola de prioridad: (distancia, nodo)
    using pii = std::pair<int, std::string>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        std::string u = pq.top().second;
        pq.pop();

        if (visited.find(u) != visited.end()) continue;
        visited.insert(u);

        Router* router = getRouter(u);
        if (!router) continue;

        auto neighbors = router->getNeighbors();
        for (const auto& neighbor : neighbors) {
            std::string v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    // Construir caminos
    std::map<std::string, std::vector<std::string>> paths;
    for (const auto& id : getRouterIds()) {
        std::vector<std::string> path;
        std::string current = id;

        while (current != source && prev.find(current) != prev.end()) {
            path.push_back(current);
            current = prev[current];
        }
        path.push_back(source);
        std::reverse(path.begin(), path.end());
        paths[id] = path;
    }

    // Actualizar el router fuente
    Router* sourceRouter = getRouter(source);
    if (sourceRouter) {
        sourceRouter->setCostTable(dist);
        sourceRouter->setPathTable(paths);
    }
}

void Network::computeRoutes() {
    for (const auto& router : routers) {
        dijkstra(router.first);
    }
}

void Network::computeRoutes(std::string algorithm) {
    // Por ahora solo implementamos Dijkstra
    if (algorithm == "Dijkstra" || algorithm == "dijkstra") {
        computeRoutes();
    } else {
        std::cout << "Algoritmo no soportado. Usando Dijkstra por defecto." << std::endl;
        computeRoutes();
    }
}

void Network::updateAllRoutingTables() {
    computeRoutes();
}

// Consultas
void Network::printPath(std::string from, std::string to) const {
    if (!containsRouter(from) || !containsRouter(to)) {
        std::cout << "Error: Uno o ambos routers no existen." << std::endl;
        return;
    }

    auto it = routers.find(from);
    int cost = it->second.getCostTo(to);
    std::vector<std::string> path = it->second.getPathTo(to);

    if (path.empty()) {
        std::cout << "No hay camino de " << from << " a " << to << std::endl;
        return;
    }

    std::cout << "Camino de " << from << " a " << to << ": ";
    for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i < path.size() - 1) std::cout << " -> ";
    }
    std::cout << " (Costo: " << cost << ")" << std::endl;
}

void Network::printAllPaths() const {
    auto ids = getRouterIds();
    for (size_t i = 0; i < ids.size(); i++) {
        for (size_t j = i + 1; j < ids.size(); j++) {
            printPath(ids[i], ids[j]);
        }
    }
}

void Network::printNetworkTopology() const {
    std::cout << "Topología de la red:\n";
    for (const auto& router : routers) {
        std::cout << "Router " << router.first << " conectado a: ";
        auto neighbors = router.second.getNeighbors();
        for (const auto& neighbor : neighbors) {
            std::cout << neighbor.first << "(" << neighbor.second << ") ";
        }
        std::cout << std::endl;
    }
}

void Network::printAllRoutingTables() const {
    for (const auto& router : routers) {
        router.second.printRoutingTable();
        std::cout << std::endl;
    }
}

std::vector<std::string> Network::findShortestPath(std::string from, std::string to) const {
    auto it = routers.find(from);
    if (it != routers.end()) {
        return it->second.getPathTo(to);
    }
    return std::vector<std::string>();
}

int Network::getShortestPathCost(std::string from, std::string to) const {
    auto it = routers.find(from);
    if (it != routers.end()) {
        return it->second.getCostTo(to);
    }
    return -1;
}

// Información de la red
int Network::getRouterCount() const {
    return routers.size();
}

int Network::getLinkCount() const {
    int count = 0;
    for (const auto& router : routers) {
        count += router.second.getNeighbors().size();
    }
    return count / 2; // Cada enlace se cuenta dos veces
}

double Network::getNetworkDensity() const {
    int n = getRouterCount();
    if (n <= 1) return 0.0;
    int maxPossibleLinks = n * (n - 1) / 2;
    return static_cast<double>(getLinkCount()) / maxPossibleLinks;
}

bool Network::isConnected() const {
    if (routers.empty()) return true;

    std::set<std::string> visited;
    std::queue<std::string> q;
    q.push(routers.begin()->first);
    visited.insert(routers.begin()->first);

    while (!q.empty()) {
        std::string current = q.front();
        q.pop();

        Router* router = getRouter(current);
        if (router) {
            auto neighbors = router->getNeighbors();
            for (const auto& neighbor : neighbors) {
                if (visited.find(neighbor.first) == visited.end()) {
                    visited.insert(neighbor.first);
                    q.push(neighbor.first);
                }
            }
        }
    }

    return visited.size() == routers.size();
}

std::vector<std::vector<std::string>> Network::getDisconnectedComponents() const {
    std::vector<std::vector<std::string>> components;
    std::set<std::string> visited;

    for (const auto& router : routers) {
        if (visited.find(router.first) == visited.end()) {
            std::vector<std::string> component;
            std::queue<std::string> q;
            q.push(router.first);
            visited.insert(router.first);
            component.push_back(router.first);

            while (!q.empty()) {
                std::string current = q.front();
                q.pop();

                Router* r = getRouter(current);
                if (r) {
                    auto neighbors = r->getNeighbors();
                    for (const auto& neighbor : neighbors) {
                        if (visited.find(neighbor.first) == visited.end()) {
                            visited.insert(neighbor.first);
                            q.push(neighbor.first);
                            component.push_back(neighbor.first);
                        }
                    }
                }
            }
            components.push_back(component);
        }
    }

    return components;
}

// Utilidades
std::string Network::generateRouterId(int index) {
    return "R" + std::to_string(index);
}

int Network::randomCost(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}
