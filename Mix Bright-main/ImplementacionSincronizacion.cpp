#include "sincronizacion.h"
#include <stdio.h>
#include <string.h>

// Función para insertar una canción en todas las estructuras simultáneamente
int insertarCancionSincronizada(const char* id, const char* titulo, const char* ruta, const char* genero, int calificacion) {
    // 1. Insertar en la lista enlazada
    insertEnd(id, titulo, ruta, genero, calificacion);
    
    // 2. Insertar en el árbol AVL (usar tail que apunta al último nodo insertado)
    extern NodoCancion* tail;
    extern NodoAVL* raizAVL;
    
    if (tail != NULL) {
        raizAVL = insertarAVL(raizAVL, tail);
    }
    
    // 3. Insertar en la tabla hash
    if (tail != NULL) {
        insertarHash(tail);
    }
    
    printf("\nCancion '%s' insertada exitosamente en todas las estructuras (Lista, AVL, Hash).\n", titulo);
    return 1; // Éxito
}

// Función para eliminar una canción de todas las estructuras simultáneamente
int eliminarCancionSincronizada(const char* id) {
    // Primero buscar la canción para obtener el título (necesario para eliminar del AVL)
    extern NodoCancion* head;
    
    if (head == NULL || id == NULL) {
        printf("Error: No hay canciones o ID invalido.\n");
        return 0;
    }
    
    NodoCancion* cancion = NULL;
    NodoCancion* temp = head;
    
    // Buscar la canción por ID
    do {
        if (strcmp(temp->id, id) == 0) {
            cancion = temp;
            break;
        }
        temp = temp->next;
    } while (temp != head);
    
    if (cancion == NULL) {
        printf("Error: Cancion con ID '%s' no encontrada.\n", id);
        return 0;
    }
    
    char titulo[128];
    strncpy(titulo, cancion->titulo, sizeof(titulo) - 1);
    titulo[sizeof(titulo) - 1] = '\0';
    
    // 1. Eliminar de la tabla hash
    int hashResult = eliminarHash(id);
    
    // 2. Eliminar del árbol AVL
    extern NodoAVL* raizAVL;
    raizAVL = eliminarAVL(raizAVL, titulo);
    
    // 3. Eliminar de la lista enlazada
    int listaResult = eliminarCancionDeLista(id);
    
    if (hashResult && listaResult) {
        printf("\nCancion '%s' (ID: %s) eliminada exitosamente de todas las estructuras.\n", titulo, id);
        return 1; // Éxito
    } else {
        printf("\nAdvertencia: La cancion se elimino parcialmente. Algunas operaciones fallaron.\n");
        return 0;
    }
}
