#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h" // Para usar NodoCancion

// Tamaño de la tabla hash (primo para mejor distribución)
#define TAMANO_HASH 101

// Estructura para nodo en la tabla hash (encadenamiento)
typedef struct NodoHash {
    NodoCancion* cancion;  // Puntero a la canción en la lista
    struct NodoHash* siguiente;  // Para manejar colisiones con encadenamiento
} NodoHash;

// Estructura de la tabla hash
typedef struct TablaHash {
    NodoHash* buckets[TAMANO_HASH]; // Array de punteros a listas enlazadas
    int cantidad; // Cantidad de elementos en la tabla
} TablaHash;

// Variable global de la tabla hash
extern TablaHash* tablaHash;

// Prototipos de funciones
void inicializarHash();
void insertarHash(NodoCancion* cancion);
NodoCancion* buscarHashPorID(const char* id);
NodoCancion* buscarHashPorTitulo(const char* titulo);
int eliminarHash(const char* id);
void liberarHash();

#endif
