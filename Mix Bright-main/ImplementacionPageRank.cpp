#include "pagerank.h"

// Definición del grafo global
Grafo* grafoPageRank = NULL;

// Función auxiliar para obtener el índice de una canción por su ID
int obtenerIndicePorID(const char* id) {
    extern NodoCancion* head;
    extern NodoCancion* tail;
    
    if (head == NULL || id == NULL) {
        return -1;
    }
    
    NodoCancion* actual = head;
    int indice = 0;
    
    do {
        if (strcmp(actual->id, id) == 0) {
            return indice;
        }
        actual = actual->next;
        indice++;
    } while (actual != head);
    
    return -1; // No encontrado
}

// Función auxiliar para obtener una canción por su índice
NodoCancion* obtenerCancionPorIndice(int indice) {
    extern NodoCancion* head;
    
    if (head == NULL || indice < 0) {
        return NULL;
    }
    
    NodoCancion* actual = head;
    int contador = 0;
    
    do {
        if (contador == indice) {
            return actual;
        }
        actual = actual->next;
        contador++;
    } while (actual != head);
    
    return NULL;
}

// Inicializar el grafo de PageRank
void inicializarGrafo() {
    extern NodoCancion* head;
    extern NodoCancion* tail;
    
    if (head == NULL) {
        printf("Error: No hay canciones cargadas para inicializar el grafo.\n");
        return;
    }
    
    // Contar cantidad de canciones
    int cantidad = 0;
    NodoCancion* temp = head;
    do {
        cantidad++;
        temp = temp->next;
    } while (temp != head);
    
    // Crear grafo
    grafoPageRank = (Grafo*)malloc(sizeof(Grafo));
    if (grafoPageRank == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el grafo.\n");
        return;
    }
    
    grafoPageRank->cantidadNodos = cantidad;
    grafoPageRank->factorAmortiguacion = 0.85; // Factor de amortiguación estándar
    
    // Crear array de nodos
    grafoPageRank->nodos = (NodoGrafo*)malloc(cantidad * sizeof(NodoGrafo));
    if (grafoPageRank->nodos == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para los nodos del grafo.\n");
        free(grafoPageRank);
        grafoPageRank = NULL;
        return;
    }
    
    // Inicializar nodos
    temp = head;
    int i = 0;
    do {
        grafoPageRank->nodos[i].indice = i;
        grafoPageRank->nodos[i].pagerank = 1.0 / cantidad; // Inicializar con valor uniforme
        grafoPageRank->nodos[i].pagerankAnterior = 0.0;
        grafoPageRank->nodos[i].adyacentes = NULL;
        temp = temp->next;
        i++;
    } while (temp != head);
    
    // Crear conexiones básicas: cada canción conectada con algunas otras
    // Para que PageRank funcione, necesitamos conexiones en el grafo
    // Simulamos que cada canción tiene conexiones con canciones del mismo género o cercanas
    for (int origen = 0; origen < cantidad; origen++) {
        // Cada canción se conecta con las siguientes 5 (simulando una lista de reproducción)
        for (int j = 1; j <= 5 && (origen + j) < cantidad; j++) {
            agregarArista(origen, origen + j);
        }
        // También conectamos con algunas canciones aleatorias para dar estructura al grafo
        if (origen + 10 < cantidad) {
            agregarArista(origen, origen + 10);
        }
        // Conexión circular: la última canción conecta con la primera
        if (origen == cantidad - 1) {
            agregarArista(origen, 0);
        }
    }
    
    printf("Grafo de PageRank inicializado con %d nodos y conexiones basicas.\n", cantidad);
}

// Agregar una arista al grafo
void agregarArista(int origen, int destino) {
    if (grafoPageRank == NULL || origen < 0 || destino < 0 || 
        origen >= grafoPageRank->cantidadNodos || destino >= grafoPageRank->cantidadNodos) {
        return;
    }
    
    // Verificar si la arista ya existe
    Arista* actual = grafoPageRank->nodos[origen].adyacentes;
    while (actual != NULL) {
        if (actual->destino == destino) {
            actual->peso++; // Incrementar peso si ya existe
            return;
        }
        actual = actual->siguiente;
    }
    
    // Crear nueva arista
    Arista* nuevaArista = (Arista*)malloc(sizeof(Arista));
    if (nuevaArista == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para la arista.\n");
        return;
    }
    
    nuevaArista->destino = destino;
    nuevaArista->peso = 1;
    nuevaArista->siguiente = grafoPageRank->nodos[origen].adyacentes;
    grafoPageRank->nodos[origen].adyacentes = nuevaArista;
}

// Registrar una transición entre dos canciones (cuando se reproduce una después de otra)
void registrarTransicion(const char* idOrigen, const char* idDestino) {
    if (grafoPageRank == NULL) {
        inicializarGrafo();
    }
    
    int indiceOrigen = obtenerIndicePorID(idOrigen);
    int indiceDestino = obtenerIndicePorID(idDestino);
    
    if (indiceOrigen == -1 || indiceDestino == -1) {
        return;
    }
    
    agregarArista(indiceOrigen, indiceDestino);
}

// Calcular PageRank con un número específico de iteraciones
void calcularPageRank(int iteraciones) {
    if (grafoPageRank == NULL) {
        inicializarGrafo();
        if (grafoPageRank == NULL) {
            printf("Error: No se pudo inicializar el grafo.\n");
            return;
        }
    }
    
    int n = grafoPageRank->cantidadNodos;
    double d = grafoPageRank->factorAmortiguacion;
    double tolerancia = 1e-6;
    
    printf("\nCalculando PageRank con %d iteraciones...\n", iteraciones);
    
    // Calcular grados de salida una sola vez (optimización)
    int* gradosSalida = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        gradosSalida[i] = 0;
        Arista* arista = grafoPageRank->nodos[i].adyacentes;
        while (arista != NULL) {
            gradosSalida[i] += arista->peso;
            arista = arista->siguiente;
        }
        // Si un nodo no tiene salidas, se considera que apunta a todos los nodos
        if (gradosSalida[i] == 0) {
            gradosSalida[i] = n; // Evitar división por cero
        }
    }
    
    for (int iter = 0; iter < iteraciones; iter++) {
        // Guardar valores anteriores
        for (int i = 0; i < n; i++) {
            grafoPageRank->nodos[i].pagerankAnterior = grafoPageRank->nodos[i].pagerank;
            grafoPageRank->nodos[i].pagerank = 0.0;
        }
        
        // Calcular nuevo PageRank para cada nodo
        for (int i = 0; i < n; i++) {
            double suma = 0.0;
            
            // Sumar contribuciones de todos los nodos que apuntan a i
            for (int j = 0; j < n; j++) {
                Arista* arista = grafoPageRank->nodos[j].adyacentes;
                double contribucion = 0.0;
                
                // Buscar si hay arista de j a i
                while (arista != NULL) {
                    if (arista->destino == i) {
                        contribucion += arista->peso;
                    }
                    arista = arista->siguiente;
                }
                
                // Si no hay aristas salientes, el nodo se considera conectado a todos
                if (gradosSalida[j] == n && contribucion == 0.0) {
                    contribucion = 1.0;
                }
                
                if (contribucion > 0 && gradosSalida[j] > 0) {
                    suma += (grafoPageRank->nodos[j].pagerankAnterior * contribucion) / gradosSalida[j];
                }
            }
            
            // Fórmula de PageRank: PR(i) = (1-d)/n + d * suma
            grafoPageRank->nodos[i].pagerank = (1.0 - d) / n + d * suma;
        }
        
        // Verificar convergencia
        if ((iter + 1) % 100 == 0) {
            double diferencia = 0.0;
            for (int i = 0; i < n; i++) {
                diferencia += fabs(grafoPageRank->nodos[i].pagerank - grafoPageRank->nodos[i].pagerankAnterior);
            }
            if (diferencia < tolerancia) {
                printf("Convergencia alcanzada en la iteracion %d.\n", iter + 1);
                break;
            }
        }
        
        if ((iter + 1) % 500 == 0) {
            printf("Iteracion %d/%d completada...\n", iter + 1, iteraciones);
        }
    }
    
    free(gradosSalida);
    printf("PageRank calculado exitosamente.\n");
}

// Generar recomendaciones basadas en PageRank (top N canciones)
void generarRecomendaciones(int topN) {
    if (grafoPageRank == NULL) {
        printf("Error: El grafo no está inicializado. Ejecute PageRank primero.\n");
        return;
    }
    
    // Crear array de índices para ordenar
    int* indices = (int*)malloc(grafoPageRank->cantidadNodos * sizeof(int));
    if (indices == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria.\n");
        return;
    }
    
    for (int i = 0; i < grafoPageRank->cantidadNodos; i++) {
        indices[i] = i;
    }
    
    // Ordenar índices por PageRank (burbuja simple, orden descendente)
    for (int i = 0; i < grafoPageRank->cantidadNodos - 1; i++) {
        for (int j = 0; j < grafoPageRank->cantidadNodos - i - 1; j++) {
            if (grafoPageRank->nodos[indices[j]].pagerank < grafoPageRank->nodos[indices[j + 1]].pagerank) {
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }
    
    // Mostrar top N recomendaciones
    printf("\n========================================\n");
    printf("   TOP %d RECOMENDACIONES (PageRank)\n", topN);
    printf("========================================\n");
    
    int mostrar = (topN < grafoPageRank->cantidadNodos) ? topN : grafoPageRank->cantidadNodos;
    
    for (int i = 0; i < mostrar; i++) {
        int idx = indices[i];
        NodoCancion* cancion = obtenerCancionPorIndice(idx);
        if (cancion != NULL) {
            printf("%d. [PageRank: %.6f] %s - %s\n", 
                   i + 1, 
                   grafoPageRank->nodos[idx].pagerank,
                   cancion->id, 
                   cancion->titulo);
        }
    }
    printf("========================================\n");
    
    free(indices);
}

// Liberar memoria del grafo
void liberarGrafo() {
    if (grafoPageRank == NULL) {
        return;
    }
    
    for (int i = 0; i < grafoPageRank->cantidadNodos; i++) {
        Arista* actual = grafoPageRank->nodos[i].adyacentes;
        while (actual != NULL) {
            Arista* siguiente = actual->siguiente;
            free(actual);
            actual = siguiente;
        }
    }
    
    free(grafoPageRank->nodos);
    free(grafoPageRank);
    grafoPageRank = NULL;
    printf("Grafo de PageRank liberado.\n");
}
