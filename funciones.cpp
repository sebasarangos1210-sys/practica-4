
#include "funciones.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <cstdlib>

//FUNCIONES DE INTERFAZ

void mostrarMenu() {
    std::cout << "\n╔════════════════════════════════════════════════════════╗\n";
    std::cout << "║                    MENÚ PRINCIPAL                      ║\n";
    std::cout << "╠════════════════════════════════════════════════════════╣\n";
    std::cout << "║  1. Gestión de Routers                                 ║\n";
    std::cout << "║  2. Gestión de Enlaces                                 ║\n";
    std::cout << "║  3. Cargar/Generar Red                                 ║\n";
    std::cout << "║  4. Consultas y Análisis                               ║\n";
    std::cout << "║  5. Ver Topología de Red                               ║\n";
    std::cout << "║  6. Ver Tablas de Enrutamiento                         ║\n";
    std::cout << "║  7. Información y Estadísticas                         ║\n";
    std::cout << "║  8. Ejecutar Ejemplo de la Práctica                    ║\n";
    std::cout << "║  9. Demostración Completa                              ║\n";
    std::cout << "║  0. Salir                                              ║\n";
    std::cout << "╚════════════════════════════════════════════════════════╝\n";
}

void mostrarMenuRouters() {
    std::cout << "\n╔═══════════════════════════════════════╗\n";
    std::cout << "║      GESTIÓN DE ROUTERS               ║\n";
    std::cout << "╠═══════════════════════════════════════╣\n";
    std::cout << "║  1. Agregar Router                    ║\n";
    std::cout << "║  2. Eliminar Router                   ║\n";
    std::cout << "║  3. Listar Routers                    ║\n";
    std::cout << "║  4. Ver Detalles de un Router         ║\n";
    std::cout << "║  0. Volver                            ║\n";
    std::cout << "╚═══════════════════════════════════════╝\n";
}

void mostrarMenuEnlaces() {
    std::cout << "\n╔═══════════════════════════════════════╗\n";
    std::cout << "║      GESTIÓN DE ENLACES               ║\n";
    std::cout << "╠═══════════════════════════════════════╣\n";
    std::cout << "║  1. Agregar Enlace                    ║\n";
    std::cout << "║  2. Eliminar Enlace                   ║\n";
    std::cout << "║  3. Actualizar Costo de Enlace        ║\n";
    std::cout << "║  4. Consultar Enlace                  ║\n";
    std::cout << "║  5. Listar Todos los Enlaces          ║\n";
    std::cout << "║  0. Volver                            ║\n";
    std::cout << "╚═══════════════════════════════════════╝\n";
}

void mostrarMenuCargaGeneracion() {
    std::cout << "\n╔═══════════════════════════════════════╗\n";
    std::cout << "║   CARGAR/GENERAR RED                  ║\n";
    std::cout << "╠═══════════════════════════════════════╣\n";
    std::cout << "║  1. Cargar desde Archivo              ║\n";
    std::cout << "║  2. Guardar en Archivo                ║\n";
    std::cout << "║  3. Generar Red Aleatoria (Prob.)     ║\n";
    std::cout << "║  4. Generar Red Aleatoria (Conex.)    ║\n";
    std::cout << "║  5. Crear Red de Prueba               ║\n";
    std::cout << "║  6. Limpiar Red                       ║\n";
    std::cout << "║  0. Volver                            ║\n";
    std::cout << "╚═══════════════════════════════════════╝\n";
}

void mostrarMenuConsultas() {
    std::cout << "\n╔═══════════════════════════════════════╗\n";
    std::cout << "║     CONSULTAS Y ANÁLISIS              ║\n";
    std::cout << "╠═══════════════════════════════════════╣\n";
    std::cout << "║  1. Camino más Corto (2 routers)     ║\n";
    std::cout << "║  2. Todos los Caminos                 ║\n";
    std::cout << "║  3. Analizar Conectividad             ║\n";
    std::cout << "║  4. Encontrar Router Central          ║\n";
    std::cout << "║  5. Enlaces Críticos                  ║\n";
    std::cout << "║  6. Calcular Diámetro                 ║\n";
    std::cout << "║  7. Recalcular Rutas                  ║\n";
    std::cout << "║  8. Generar Reporte                   ║\n";
    std::cout << "║  0. Volver                            ║\n";
    std::cout << "╚═══════════════════════════════════════╝\n";
}

// ==================== FUNCIONES DE ENTRADA/SALIDA ====================

void pausar() {
    std::cout << "\n➤ Presione ENTER para continuar...";
    std::cin.get();
}

void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string leerString(const std::string& mensaje) {
    std::string input;
    std::cout << mensaje;
    std::getline(std::cin, input);
    return trim(input);
}

int leerEntero(const std::string& mensaje, int min, int max) {
    int valor;
    while (true) {
        std::cout << mensaje;
        if (std::cin >> valor) {
            limpiarBuffer();
            if (valor >= min && valor <= max) {
                return valor;
            }
            std::cout << "✗ El valor debe estar entre " << min << " y " << max << "\n";
        } else {
            std::cout << "✗ Entrada inválida. Ingrese un número.\n";
            limpiarBuffer();
        }
    }
}

double leerDouble(const std::string& mensaje, double min, double max) {
    double valor;
    while (true) {
        std::cout << mensaje;
        if (std::cin >> valor) {
            limpiarBuffer();
            if (valor >= min && valor <= max) {
                return valor;
            }
            std::cout << "✗ El valor debe estar entre " << min << " y " << max << "\n";
        } else {
            std::cout << "✗ Entrada inválida. Ingrese un número.\n";
            limpiarBuffer();
        }
    }
}

bool confirmar(const std::string& mensaje) {
    char respuesta;
    std::cout << mensaje << " (s/n): ";
    std::cin >> respuesta;
    limpiarBuffer();
    return (respuesta == 's' || respuesta == 'S');
}

//FUNCIONES DE VALIDACIÓN

bool validarRouterId(const std::string& id) {
    if (id.empty()) {
        std::cout << "✗ El ID no puede estar vacío.\n";
        return false;
    }
    // Validar que no contenga espacios
    if (id.find(' ') != std::string::npos) {
        std::cout << "✗ El ID no puede contener espacios.\n";
        return false;
    }
    return true;
}

bool validarCosto(int costo) {
    if (costo <= 0) {
        std::cout << "✗ El costo debe ser un número positivo.\n";
        return false;
    }
    return true;
}

bool validarArchivo(const std::string& filename) {
    std::ifstream file(filename);
    bool existe = file.good();
    file.close();
    return existe;
}

//FUNCIONES DE MENÚS INTERACTIVOS

void menuGestionRouters(Network& red) {
    int opcion;

    do {
        mostrarMenuRouters();
        opcion = leerEntero("\n➤ Seleccione una opción: ", 0, 4);
        std::cout << "\n";

        switch(opcion) {
        case 1: {
            std::string id = leerString("➤ Ingrese ID del router: ");
            if (validarRouterId(id)) {
                red.addRouter(id);
            }
            pausar();
            break;
        }

        case 2: {
            std::string id = leerString("➤ Ingrese ID del router a eliminar: ");
            if (red.containsRouter(id)) {
                if (confirmar("¿Está seguro de eliminar este router?")) {
                    red.removeRouter(id);
                }
            } else {
                std::cout << "✗ El router no existe.\n";
            }
            pausar();
            break;
        }

        case 3: {
            auto ids = red.getRouterIds();
            if (ids.empty()) {
                std::cout << "ℹ No hay routers en la red.\n";
            } else {
                imprimirBanner("LISTA DE ROUTERS");
                std::cout << "Total: " << ids.size() << " router(s)\n\n";
                for (size_t i = 0; i < ids.size(); i++) {
                    std::cout << "  " << (i + 1) << ". " << ids[i] << "\n";
                }
            }
            pausar();
            break;
        }

        case 4: {
            std::string id = leerString("➤ Ingrese ID del router: ");
            Router* router = red.getRouter(id);
            if (router) {
                router->printRoutingTable();
                std::cout << "\n";
                router->printNeighbors();
            } else {
                std::cout << "✗ El router no existe.\n";
            }
            pausar();
            break;
        }

        case 0:
            break;

        default:
            std::cout << "✗ Opción inválida.\n";
            pausar();
        }

    } while(opcion != 0);
}

void menuGestionEnlaces(Network& red) {
    int opcion;

    do {
        mostrarMenuEnlaces();
        opcion = leerEntero("\n➤ Seleccione una opción: ", 0, 5);
        std::cout << "\n";

        switch(opcion) {
        case 1: {
            std::string id1 = leerString("➤ Router 1: ");
            std::string id2 = leerString("➤ Router 2: ");
            int costo = leerEntero("➤ Costo: ", 1, 1000);

            if (validarRouterId(id1) && validarRouterId(id2)) {
                red.addLink(id1, id2, costo);
            }
            pausar();
            break;
        }

        case 2: {
            std::string id1 = leerString("➤ Router 1: ");
            std::string id2 = leerString("➤ Router 2: ");

            if (red.areConnected(id1, id2)) {
                if (confirmar("¿Está seguro de eliminar este enlace?")) {
                    red.removeLink(id1, id2);
                }
            } else {
                std::cout << "✗ Los routers no están conectados.\n";
            }
            pausar();
            break;
        }

        case 3: {
            std::string id1 = leerString("➤ Router 1: ");
            std::string id2 = leerString("➤ Router 2: ");

            if (red.areConnected(id1, id2)) {
                int costoActual = red.getLinkCost(id1, id2);
                std::cout << "ℹ Costo actual: " << costoActual << "\n";
                int nuevoCosto = leerEntero("➤ Nuevo costo: ", 1, 1000);
                red.updateLinkCost(id1, id2, nuevoCosto);
            } else {
                std::cout << "✗ Los routers no están conectados.\n";
            }
            pausar();
            break;
        }

        case 4: {
            std::string id1 = leerString("➤ Router 1: ");
            std::string id2 = leerString("➤ Router 2: ");

            if (red.areConnected(id1, id2)) {
                int costo = red.getLinkCost(id1, id2);
                std::cout << "✓ Enlace: " << id1 << " ↔ " << id2
                          << " (Costo: " << costo << ")\n";
            } else {
                std::cout << "✗ Los routers NO están conectados.\n";
            }
            pausar();
            break;
        }

        case 5: {
            imprimirBanner("LISTA DE ENLACES");
            std::cout << "Total de enlaces: " << red.getLinkCount() << "\n\n";

            auto ids = red.getRouterIds();
            std::set<std::pair<std::string, std::string>> mostrados;

            for (const auto& id1 : ids) {
                Router* router = red.getRouter(id1);
                if (router) {
                    auto vecinos = router->getNeighbors();
                    for (const auto& vecino : vecinos) {
                        std::string id2 = vecino.first;
                        int costo = vecino.second;

                        auto par = (id1 < id2) ?
                                       std::make_pair(id1, id2) : std::make_pair(id2, id1);

                        if (mostrados.find(par) == mostrados.end()) {
                            std::cout << "  • " << id1 << " ↔ " << id2
                                      << " (costo: " << costo << ")\n";
                            mostrados.insert(par);
                        }
                    }
                }
            }
            pausar();
            break;
        }

        case 0:
            break;

        default:
            std::cout << "✗ Opción inválida.\n";
            pausar();
        }

    } while(opcion != 0);
}

void menuCargaGeneracion(Network& red) {
    int opcion;

    do {
        mostrarMenuCargaGeneracion();
        opcion = leerEntero("\n➤ Seleccione una opción: ", 0, 6);
        std::cout << "\n";

        switch(opcion) {
        case 1: {
            std::string archivo = leerString("➤ Nombre del archivo: ");
            red.loadFromFile(archivo);
            pausar();
            break;
        }

        case 2: {
            if (red.isEmpty()) {
                std::cout << "✗ La red está vacía. No hay nada que guardar.\n";
            } else {
                std::string archivo = leerString("➤ Nombre del archivo: ");
                red.saveToFile(archivo);
            }
            pausar();
            break;
        }

        case 3: {
            int numRouters = leerEntero("➤ Número de routers: ", 2, 100);
            double prob = leerDouble("➤ Probabilidad de conexión (0.0 - 1.0): ", 0.0, 1.0);
            int maxCosto = leerEntero("➤ Costo máximo: ", 1, 100);

            red.generateRandom(numRouters, prob, maxCosto);
            pausar();
            break;
        }

        case 4: {
            int numRouters = leerEntero("➤ Número de routers: ", 2, 100);
            int minConex = leerEntero("➤ Conexiones mínimas por router: ", 1, numRouters - 1);
            int maxConex = leerEntero("➤ Conexiones máximas por router: ", minConex, numRouters - 1);
            int maxCosto = leerEntero("➤ Costo máximo: ", 1, 100);

            red.generateRandom(numRouters, minConex, maxConex, maxCosto);
            pausar();
            break;
        }

        case 5: {
            crearRedPrueba(red);
            pausar();
            break;
        }

        case 6: {
            if (confirmar("¿Está seguro de limpiar toda la red?")) {
                red.clear();
                std::cout << "✓ Red limpiada.\n";
            }
            pausar();
            break;
        }

        case 0:
            break;

        default:
            std::cout << "✗ Opción inválida.\n";
            pausar();
        }

    } while(opcion != 0);
}

void menuConsultas(Network& red) {
    int opcion;

    do {
        mostrarMenuConsultas();
        opcion = leerEntero("\n➤ Seleccione una opción: ", 0, 8);
        std::cout << "\n";

        switch(opcion) {
        case 1: {
            std::string origen = leerString("➤ Router origen: ");
            std::string destino = leerString("➤ Router destino: ");
            red.printPath(origen, destino);
            pausar();
            break;
        }

        case 2:
            red.printAllPaths();
            pausar();
            break;

        case 3:
            analizarConectividad(red);
            pausar();
            break;

        case 4: {
            std::string central = encontrarRouterCentral(red);
            if (!central.empty()) {
                std::cout << "✓ Router más central: " << central << "\n";
            }
            pausar();
            break;
        }

        case 5: {
            auto criticos = encontrarEnlacesCriticos(red);
            imprimirBanner("ENLACES CRÍTICOS");
            if (criticos.empty()) {
                std::cout << "ℹ No hay enlaces críticos (la red es robusta).\n";
            } else {
                std::cout << "Total: " << criticos.size() << " enlace(s) crítico(s)\n\n";
                for (const auto& par : criticos) {
                    std::cout << "  • " << par.first << " ↔ " << par.second << "\n";
                }
            }
            pausar();
            break;
        }

        case 6: {
            int diametro = calcularDiametro(red);
            if (diametro >= 0) {
                std::cout << "✓ Diámetro de la red: " << diametro << "\n";
            }
            pausar();
            break;
        }

        case 7:
            red.computeRoutes();
            std::cout << "✓ Rutas recalculadas exitosamente.\n";
            pausar();
            break;

        case 8: {
            std::string archivo = leerString("➤ Nombre del archivo de reporte: ");
            generarReporte(red, archivo);
            pausar();
            break;
        }

        case 0:
            break;

        default:
            std::cout << "✗ Opción inválida.\n";
            pausar();
        }

    } while(opcion != 0);
}

//FUNCIONES DE EJEMPLOS Y PRUEBAS

void ejemploPractica() {
    imprimirBanner("EJEMPLO DE LA PRÁCTICA (Figura 1)");

    Network ejemplo;

    std::cout << "Creando red con 4 routers (A, B, C, D)...\n\n";

    ejemplo.addRouter("A");
    ejemplo.addRouter("B");
    ejemplo.addRouter("C");
    ejemplo.addRouter("D");

    std::cout << "\nAgregando enlaces según Figura 1:\n";
    ejemplo.addLink("A", "B", 4);
    ejemplo.addLink("A", "C", 10);
    ejemplo.addLink("A", "D", 5);
    ejemplo.addLink("B", "C", 3);
    ejemplo.addLink("B", "D", 1);
    ejemplo.addLink("C", "D", 2);

    std::cout << "\nCalculando rutas óptimas...\n";
    ejemplo.computeRoutes();

    std::cout << "\n";
    ejemplo.printNetworkTopology();

    std::cout << "\n";
    ejemplo.printAllRoutingTables();

    imprimirBanner("ANÁLISIS DE RESULTADOS");

    std::cout << "Observaciones:\n\n";
    std::cout << "• Router A quiere llegar a C:\n";
    std::cout << "  - Ruta directa: A → C (costo: 10)\n";
    std::cout << "  - Ruta óptima: A → B → C (costo: 7) ✓\n\n";

    ejemplo.printPath("A", "C");

    std::cout << "\n";
    ejemplo.printNetworkInfo();
}

void crearRedPrueba(Network& red) {
    imprimirBanner("CREANDO RED DE PRUEBA");

    red.clear();

    std::cout << "Configurando red de 6 routers...\n\n";

    red.addRouter("A");
    red.addRouter("B");
    red.addRouter("C");
    red.addRouter("D");
    red.addRouter("E");
    red.addRouter("F");

    red.addLink("A", "B", 2);
    red.addLink("A", "C", 5);
    red.addLink("B", "C", 1);
    red.addLink("B", "D", 3);
    red.addLink("C", "D", 2);
    red.addLink("C", "E", 4);
    red.addLink("D", "E", 1);
    red.addLink("D", "F", 2);
    red.addLink("E", "F", 3);

    red.computeRoutes();

    std::cout << "\n✓ Red de prueba creada exitosamente.\n";
    red.printNetworkInfo();
}

void demostracionCompleta() {
    imprimirBanner("DEMOSTRACIÓN COMPLETA DEL PROGRAMA");

    Network demo;

    std::cout << "\n1. Creando red con 5 routers...\n";
    pausar();

    demo.addRouter("Madrid");
    demo.addRouter("Barcelona");
    demo.addRouter("Valencia");
    demo.addRouter("Sevilla");
    demo.addRouter("Bilbao");

    std::cout << "\n2. Agregando conexiones entre ciudades...\n";
    pausar();

    demo.addLink("Madrid", "Barcelona", 6);
    demo.addLink("Madrid", "Valencia", 4);
    demo.addLink("Madrid", "Sevilla", 5);
    demo.addLink("Barcelona", "Valencia", 3);
    demo.addLink("Barcelona", "Bilbao", 5);
    demo.addLink("Valencia", "Sevilla", 7);

    std::cout << "\n3. Calculando rutas óptimas...\n";
    pausar();
    demo.computeRoutes();

    std::cout << "\n4. Visualizando topología:\n";
    demo.printNetworkTopology();
    pausar();

    std::cout << "\n5. Mostrando tablas de enrutamiento:\n";
    demo.printAllRoutingTables();
    pausar();

    std::cout << "\n6. Consultando caminos específicos:\n";
    demo.printPath("Madrid", "Bilbao");
    demo.printPath("Sevilla", "Barcelona");
    pausar();

    std::cout << "\n7. Análisis de la red:\n";
    analizarConectividad(demo);
    pausar();

    std::cout << "\n8. Simulando fallo de enlace Madrid-Valencia...\n";
    demo.removeLink("Madrid", "Valencia");
    std::cout << "\n   Ruta actualizada Madrid → Valencia:\n";
    demo.printPath("Madrid", "Valencia");
    pausar();

    std::cout << "\n✓ Demostración completa finalizada.\n";
}

// FUNCIONES DE ANÁLISIS

void analizarConectividad(const Network& red) {
    imprimirBanner("ANÁLISIS DE CONECTIVIDAD");

    if (red.isEmpty()) {
        std::cout << "✗ La red está vacía.\n";
        return;
    }

    bool conectada = red.isConnected();

    std::cout << "Estado: " << (conectada ? "✓ CONECTADA" : "✗ DESCONECTADA") << "\n\n";

    if (!conectada) {
        auto componentes = red.getDisconnectedComponents();
        std::cout << "Número de componentes: " << componentes.size() << "\n\n";

        for (size_t i = 0; i < componentes.size(); i++) {
            std::cout << "Componente " << (i + 1) << " ("
                      << componentes[i].size() << " routers):\n  ";
            for (size_t j = 0; j < componentes[i].size(); j++) {
                std::cout << componentes[i][j];
                if (j < componentes[i].size() - 1) std::cout << ", ";
            }
            std::cout << "\n\n";
        }
    } else {
        std::cout << "Todos los routers pueden comunicarse entre sí.\n";
    }
}

std::string encontrarRouterCentral(const Network& red) {
    if (red.isEmpty()) {
        std::cout << "✗ La red está vacía.\n";
        return "";
    }

    auto ids = red.getRouterIds();
    std::string routerCentral;
    int menorSuma = std::numeric_limits<int>::max();

    for (const auto& id : ids) {
        const Router* router = red.getRouter(id);
        if (!router) continue;

        auto costTable = router->getCostTable();
        int suma = 0;

        for (const auto& entry : costTable) {
            if (entry.second > 0) {
                suma += entry.second;
            }
        }

        if (suma < menorSuma) {
            menorSuma = suma;
            routerCentral = id;
        }
    }

    return routerCentral;
}

std::vector<std::pair<std::string, std::string>> encontrarEnlacesCriticos(Network& red) {
    std::vector<std::pair<std::string, std::string>> criticos;

    if (!red.isConnected()) {
        return criticos; // Si ya está desconectada, no tiene sentido buscar
    }

    auto ids = red.getRouterIds();
    std::set<std::pair<std::string, std::string>> procesados;

    for (const auto& id1 : ids) {
        Router* router = red.getRouter(id1);
        if (!router) continue;

        auto vecinos = router->getNeighbors();
        for (const auto& vecino : vecinos) {
            std::string id2 = vecino.first;
            int costo = vecino.second;

            auto par = (id1 < id2) ?
                           std::make_pair(id1, id2) : std::make_pair(id2, id1);

            if (procesados.find(par) != procesados.end()) {
                continue;
            }
            procesados.insert(par);

            // Eliminar temporalmente el enlace
            red.removeLink(id1, id2);

            // Verificar conectividad
            if (!red.isConnected()) {
                criticos.push_back(par);
            }

            // Restaurar el enlace
            red.addLink(id1, id2, costo);
        }
    }

    return criticos;
}

int calcularDiametro(const Network& red) {
    if (red.isEmpty()) {
        std::cout << "✗ La red está vacía.\n";
        return -1;
    }

    if (!red.isConnected()) {
        std::cout << "✗ La red no está conectada.\n";
        return -1;
    }

    int diametro = 0;
    auto ids = red.getRouterIds();

    for (const auto& id : ids) {
        const Router* router = red.getRouter(id);
        if (!router) continue;

        auto costTable = router->getCostTable();
        for (const auto& entry : costTable) {
            if (entry.second > diametro && entry.second < std::numeric_limits<int>::max()) {
                diametro = entry.second;
            }
        }
    }

    return diametro;
}

// FUNCIONES DE VISUALIZACIÓN

void imprimirBanner(const std::string& titulo) {
    int longitud = titulo.length() + 4;
    if (longitud < 60) longitud = 60;

    std::cout << "\n" << std::string(longitud, '=') << "\n";
    std::cout << "  " << titulo << "\n";
    std::cout << std::string(longitud, '=') << "\n\n";
}

void imprimirSeparador(char caracter, int longitud) {
    std::cout << std::string(longitud, caracter) << "\n";
}

void imprimirEstadisticas(const Network& red) {
    imprimirBanner("ESTADÍSTICAS DE LA RED");

    if (red.isEmpty()) {
        std::cout << "La red está vacía.\n";
        return;
    }

    int numRouters = red.getRouterCount();
    int numEnlaces = red.getLinkCount();
    double densidad = red.getNetworkDensity();
    bool conectada = red.isConnected();

    std::cout << "┌─────────────────────────────────────────┐\n";
    std::cout << "│ Número de Routers:      " << std::setw(15) << std::left << numRouters << "│\n";
    std::cout << "│ Número de Enlaces:      " << std::setw(15) << std::left << numEnlaces << "│\n";
    std::cout << "│ Densidad:               " << std::setw(15) << std::left
              << std::fixed << std::setprecision(4) << densidad << "│\n";
    std::cout << "│ Red Conectada:          " << std::setw(15) << std::left
              << (conectada ? "Sí" : "No") << "│\n";

    if (conectada) {
        int diametro = calcularDiametro(red);
        if (diametro >= 0) {
            std::cout << "│ Diámetro:               " << std::setw(15) << std::left << diametro << "│\n";
        }

        std::string central = encontrarRouterCentral(red);
        if (!central.empty()) {
            std::cout << "│ Router Central:         " << std::setw(15) << std::left << central << "│\n";
        }
    }

    std::cout << "└─────────────────────────────────────────┘\n";
}

void generarReporte(const Network& red, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "✗ Error: No se pudo crear el archivo de reporte.\n";
        return;
    }

    file << "╔══════════════════════════════════════════════════════════╗\n";
    file << "║           REPORTE DE RED DE ENRUTADORES                  ║\n";
    file << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Información general
    file << "1. INFORMACIÓN GENERAL\n";
    file << "   " << std::string(50, '-') << "\n";
    file << "   Número de Routers: " << red.getRouterCount() << "\n";
    file << "   Número de Enlaces: " << red.getLinkCount() << "\n";
    file << "   Densidad de Red: " << std::fixed << std::setprecision(4)
         << red.getNetworkDensity() << "\n";
    file << "   Red Conectada: " << (red.isConnected() ? "Sí" : "No") << "\n\n";

    // Topología
    file << "2. TOPOLOGÍA DE LA RED\n";
    file << "   " << std::string(50, '-') << "\n";

    auto ids = red.getRouterIds();
    for (const auto& id : ids) {
        const Router* router = red.getRouter(id);
        if (router) {
            file << "   Router " << id << " conectado a: ";
            auto vecinos = router->getNeighbors();
            if (vecinos.empty()) {
                file << "(sin conexiones)";
            } else {
                bool first = true;
                for (const auto& vecino : vecinos) {
                    if (!first) file << ", ";
                    file << vecino.first << "(" << vecino.second << ")";
                    first = false;
                }
            }
            file << "\n";
        }
    }
    file << "\n";

    // Tablas de enrutamiento
    file << "3. TABLAS DE ENRUTAMIENTO\n";
    file << "   " << std::string(50, '-') << "\n\n";

    for (const auto& id : ids) {
        const Router* router = red.getRouter(id);
        if (router) {
            file << "   Router " << id << ":\n";
            file << "   Destino | Costo | Camino\n";
            file << "   " << std::string(40, '-') << "\n";

            auto costTable = router->getCostTable();
            auto pathTable = router->getPathTable();

            for (const auto& entry : costTable) {
                std::string dest = entry.first;
                int cost = entry.second;
                auto pathIt = pathTable.find(dest);

                file << "   " << std::setw(7) << std::left << dest << " | ";
                file << std::setw(5) << std::right << cost << " | ";

                if (pathIt != pathTable.end()) {
                    const auto& path = pathIt->second;
                    for (size_t i = 0; i < path.size(); i++) {
                        file << path[i];
                        if (i < path.size() - 1) file << " -> ";
                    }
                }
                file << "\n";
            }
            file << "\n";
        }
    }

    // Análisis
    file << "4. ANÁLISIS\n";
    file << "   " << std::string(50, '-') << "\n";

    if (red.isConnected()) {
        int diametro = calcularDiametro(red);
        if (diametro >= 0) {
            file << "   Diámetro de la red: " << diametro << "\n";
        }

        std::string central = encontrarRouterCentral(red);
        if (!central.empty()) {
            file << "   Router más central: " << central << "\n";
        }
    } else {
        auto componentes = red.getDisconnectedComponents();
        file << "   La red NO está conectada.\n";
        file << "   Número de componentes: " << componentes.size() << "\n";
    }

    file << "\n" << std::string(60, '=') << "\n";
    file << "Fin del reporte\n";

    file.close();
    std::cout << "✓ Reporte generado exitosamente en '" << filename << "'\n";
}

// FUNCIONES DE UTILIDAD

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

std::string toUpperCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::toupper(c); });
    return result;
}

std::string toLowerCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
