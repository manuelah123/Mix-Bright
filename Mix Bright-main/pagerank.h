#ifndef PAGERANK_H
#define PAGERANK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lista.h"

// Estructura para representar una arista en el grafo (transición entre canciones)
typedef struct Arista {
    int destino; // Índice de la canción destino
    int peso;    // Número de veces que se reproduce esta transición
    struct Arista* siguiente;
} Arista;

// Estructura para representar un nodo en el grafo (canción)
typedef struct NodoGrafo {
    int indice;           // Índice de la canción en la lista
    double pagerank;      // Valor de PageRank
    double pagerankAnterior; // Para cálculos iterativos
    Arista* adyacentes;   // Lista de aristas salientes
} NodoGrafo;

// Estructura del grafo completo
typedef struct Grafo {
    NodoGrafo* nodos;     // Array de nodos
    int cantidadNodos;    // Cantidad de canciones
    double factorAmortiguacion; // Factor de amortiguación (damping factor), típicamente 0.85
} Grafo;

// Variable global del grafo
extern Grafo* grafoPageRank;

// Prototipos de funciones
void inicializarGrafo();
void agregarArista(int origen, int destino);
void calcularPageRank(int iteraciones);
void generarRecomendaciones(int topN);
void registrarTransicion(const char* idOrigen, const char* idDestino);
int obtenerIndicePorID(const char* id);
NodoCancion* obtenerCancionPorIndice(int indice);
void liberarGrafo();

#endif
