#include "hash.h"

// Definición de la tabla hash global
TablaHash* tablaHash = NULL;

// Función hash simple: suma de caracteres del ID módulo TAMANO_HASH (función estática)
static int hashFuncion(const char* clave) {
    int suma = 0;
    int i = 0;
    while (clave[i] != '\0') {
        suma += clave[i];
        i++;
    }
    return suma % TAMANO_HASH;
}

// Inicializar la tabla hash
void inicializarHash() {
    if (tablaHash == NULL) {
        tablaHash = (TablaHash*)malloc(sizeof(TablaHash));
        if (tablaHash == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria para la tabla hash.\n");
            return;
        }
        
        // Inicializar todos los buckets a NULL
        for (int i = 0; i < TAMANO_HASH; i++) {
            tablaHash->buckets[i] = NULL;
        }
        tablaHash->cantidad = 0;
        printf("Tabla Hash inicializada correctamente.\n");
    }
}

// Insertar una canción en la tabla hash (usando ID como clave)
void insertarHash(NodoCancion* cancion) {
    if (tablaHash == NULL) {
        inicializarHash();
    }
    
    if (cancion == NULL) {
        return;
    }
    
    // Calcular índice usando función hash
    int indice = hashFuncion(cancion->id);
    
    // Crear nuevo nodo hash
    NodoHash* nuevoNodo = (NodoHash*)malloc(sizeof(NodoHash));
    if (nuevoNodo == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el nodo hash.\n");
        return;
    }
    
    nuevoNodo->cancion = cancion;
    nuevoNodo->siguiente = tablaHash->buckets[indice]; // Insertar al inicio de la lista
    tablaHash->buckets[indice] = nuevoNodo;
    tablaHash->cantidad++;
    
    printf("Cancion '%s' insertada en tabla hash (indice: %d).\n", cancion->titulo, indice);
}

// Buscar canción por ID en la tabla hash
NodoCancion* buscarHashPorID(const char* id) {
    if (tablaHash == NULL || id == NULL) {
        return NULL;
    }
    
    int indice = hashFuncion(id);
    NodoHash* actual = tablaHash->buckets[indice];
    
    // Buscar en la lista enlazada del bucket
    while (actual != NULL) {
        if (strcmp(actual->cancion->id, id) == 0) {
            return actual->cancion;
        }
        actual = actual->siguiente;
    }
    
    return NULL; // No encontrado
}

// Buscar canción por título en la tabla hash (búsqueda lineal en toda la tabla)
NodoCancion* buscarHashPorTitulo(const char* titulo) {
    if (tablaHash == NULL || titulo == NULL) {
        return NULL;
    }
    
    // Buscar en todos los buckets
    for (int i = 0; i < TAMANO_HASH; i++) {
        NodoHash* actual = tablaHash->buckets[i];
        while (actual != NULL) {
            if (strcmp(actual->cancion->titulo, titulo) == 0) {
                return actual->cancion;
            }
            actual = actual->siguiente;
        }
    }
    
    return NULL; // No encontrado
}

// Eliminar canción de la tabla hash por ID
int eliminarHash(const char* id) {
    if (tablaHash == NULL || id == NULL) {
        return 0; // Falla
    }
    
    int indice = hashFuncion(id);
    NodoHash* actual = tablaHash->buckets[indice];
    NodoHash* anterior = NULL;
    
    // Buscar el nodo a eliminar
    while (actual != NULL) {
        if (strcmp(actual->cancion->id, id) == 0) {
            // Encontrado, eliminar de la lista
            if (anterior == NULL) {
                // Es el primer nodo
                tablaHash->buckets[indice] = actual->siguiente;
            } else {
                // No es el primer nodo
                anterior->siguiente = actual->siguiente;
            }
            
            free(actual);
            tablaHash->cantidad--;
            printf("Cancion con ID '%s' eliminada de la tabla hash.\n", id);
            return 1; // Éxito
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    
    return 0; // No encontrado
}

// Liberar memoria de la tabla hash
void liberarHash() {
    if (tablaHash == NULL) {
        return;
    }
    
    for (int i = 0; i < TAMANO_HASH; i++) {
        NodoHash* actual = tablaHash->buckets[i];
        while (actual != NULL) {
            NodoHash* siguiente = actual->siguiente;
            free(actual);
            actual = siguiente;
        }
        tablaHash->buckets[i] = NULL;
    }
    
    free(tablaHash);
    tablaHash = NULL;
    printf("Memoria de la tabla hash liberada.\n");
}
