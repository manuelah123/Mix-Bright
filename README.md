[![en](https://img.shields.io/badge/Idioma-English-blue.svg)](#mix-bright--advanced-c-music-player)
![C++](https://img.shields.io/badge/C++-17-blue.svg?style=flat&logo=c%2B%2B)
![SDL2](https://img.shields.io/badge/SDL2-2.0+-009900.svg?style=flat&logo=sdl)
![License](https://img.shields.io/github/license/manuelah123/Mix-Bright)
![Stars](https://img.shields.io/github/stars/manuelah123/Mix-Bright?style=social)

# Mix Bright – Reproductor de Música Avanzado en C++

**Mix Bright** es un reproductor de música en lenguaje **C++** que utiliza la librería **SDL2**. Implementa estructuras de datos avanzadas (lista doblemente enlazada, árbol AVL y tabla hash) para gestionar eficientemente la información de las canciones. Entre sus funcionalidades se encuentran imprimer canciones, reproducir canciones, reproducciòn aleatoria, busqueda de cancion por id, busqueda de cancion por nombre, insertar cancion, eliminar cancion y recomendaciones inteligentes basadas en el algoritmo PageRank.

Este proyecto demuestra el uso de algoritmos y estructuras de datos para optimizar operaciones en un reproductor multimedia, con énfasis en eficiencia y rendimiento.

---

## Características Principales

| Funcionalidad                     | Estructura de Datos/Algoritmo | Beneficio Principal          |
|-----------------------------------|-------------------------------|------------------------------|
| Gestión de biblioteca de canciones| Tabla hash                    | Acceso eficiente O(1)        |
| Búsqueda rápida de canciones      | Árbol AVL                     | Búsqueda balanceada O(log n) |
| Navegación y edición de playlists | Lista doblemente enlazada     | Inserciones/eliminaciones O(1)|
| Recomendaciones de canciones      | Algoritmo PageRank            | Sugerencias personalizadas   |
| Reproducción de audio             | SDL2                          | Soporte multimedia nativo    |

---

## Software Design and Architecture

El proyecto se basa en principios de programación eficiente en C++, con implementaciones manuales de estructuras de datos para demostrar conceptos algorítmicos. La arquitectura separa la lógica de datos, el procesamiento de audio y la interfaz de usuario.

### 1. Estructuras de Datos Implementadas
- **Lista doblemente enlazada**: Para la gestión dinámica de playlists, permitiendo navegación bidireccional y modificaciones rápidas.
- **Árbol AVL**: Árbol binario de búsqueda auto-balanceado para búsquedas ordenadas por metadatos (título, id).
- **Tabla hash**: Para almacenamiento rápido de canciones por clave única (ID o hash de archivo).
- **Graph<Song**: Base para el sistema de recomendaciones.
  
### 2. Algoritmo de Recomendaciones: PageRank
Adaptación del algoritmo PageRank para un grafo de canciones, donde los nodos representan pistas y los enlaces modelan transiciones frecuentes en playlists. Esto genera recomendaciones basadas en "popularidad" relativa dentro de la biblioteca del usuario.
- **Recomendaciones**: Accede a sugerencias generadas por PageRank basadas en tu **historial de reproducción**. Cuanto más uses el reproductor, más precisas serán las sugerencias.

### 3. Integración con SDL2
- Manejo de eventos de usuario (teclado, mouse).

---

## Tecnologías Utilizadas

* **Lenguaje**: C++
* **Librería principal**: SDL2 (para ventana, eventos y audio)
* **Estructuras de datos**: Implementaciones personalizadas (lista doble, AVL, hash)
* **Algoritmo**: PageRank (adaptado para recomendaciones)

---

## Usage

1. **Carga tu biblioteca**: El programa escanea archivos de audio en el directorio actual y los indexa en las estructuras de datos.
2. **Búsqueda**: Usa la interfaz para buscar canciones por título o id (aprovechando el árbol AVL).
3. **Playlists**: Crea y edita listas con la lista doblemente enlazada.
4. **Reproducción**: Selecciona una canción para reproducir con SDL2.
---
 
### **Configuraciòn para ejecutar el codigo.**

###  **Rutas de Canciones (Obligatorio)**
El programa carga canciones desde un archivo `playlist.txt`.  
Por esto se debe editar las rutas de playlist.txt, las rutas de main.cpp y configurar las rutas include/lib de SDL2.

---
# Autora

Manuela Henao bedoya 
