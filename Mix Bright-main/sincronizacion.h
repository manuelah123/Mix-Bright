#ifndef SINCRONIZACION_H
#define SINCRONIZACION_H

#include "lista.h"
#include "arbolavl.h"
#include "hash.h"

// Funciones de sincronización para insertar/eliminar de todas las estructuras
int insertarCancionSincronizada(const char* id, const char* titulo, const char* ruta, const char* genero, int calificacion);
int eliminarCancionSincronizada(const char* id);

#endif
