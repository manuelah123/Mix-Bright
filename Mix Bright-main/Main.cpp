#include <stdio.h>
#include "lista.h"
#include "audio.h"
#include "archivo.h"
#include "interfaz.h"
#include "arbolAVL.h"
#include "hash.h"
#include "pagerank.h"
#include "sincronizacion.h"

//La clase prinsipal de nuestro proyecto donde esta nuestro menu principal
int main(int argc, char *argv[]) {
    
    //Primero iniciamos el Audio llamando a la funcion
    initAudio();
    
    // Inicializar estructuras de datos
    inicializarAVL();
    inicializarHash();
    
    // Ahora debemos de cargar los datos por medio de nuestro archivo txt en formato csv separado por ";"
    const char* csv_filename = "C:/Users/manue/Downloads/Mix_Bright-main/Mix Bright-main/playlist.txt";
    printf("Cargando canciones...\n");
    
    //llamamos a la funcion de cargar los datos para que se puedan generar nuestro nodos 
    load_data_from_csv(csv_filename);
    
    // Inicializar grafo de PageRank después de cargar las canciones
    inicializarGrafo();

    // Verificamos que se cargaron correctamente nuestras canciones.
    if (head == NULL) {
        printf("Error: No se cargaron canciones. Revisa el archivo CSV.\n");
        // Esperar tecla antes de salir
        getchar(); 
        cerrarAudio();
        return 1;
    }
    
    
    int opcion = -1;// opcion del menu
    do{
    	
    	system("cls");
    	printf("\n========================================\n");
    	printf("      BIENVENIDO A MIX BRIGHT\n");
    	printf("========================================\n");
    	printf("1. Imprimir lista de canciones\n");
    	printf("2. Reproducir musica\n");
    	printf("3. Reproducir cancion aleatoria\n");
    	printf("4. Buscar cancion por nombre (AVL)\n");
    	printf("5. Buscar cancion por ID (Hash Table)\n");
    	printf("6. Insertar nueva cancion\n");
    	printf("7. Eliminar cancion\n");
    	printf("8. Ver recomendaciones (PageRank)\n");
    	printf("0. Salir\n");
    	printf("========================================\n");
    	printf("Opcion: ");
    	scanf("%d",&opcion);// Se optiene y se guarda en memoria la opcion del usuario.
    	
    	
    	switch (opcion){
    		
    		case 1 : 
    		    displayForward(); 
    		    printf("\nPresione cualquier tecla para continuar...");
    		    getchar();
    		    getchar();
    		    break;
    		
    		case 2: 
    		    menuReproduccion(); 
    		    break;
    		
    		case 3: 
    		    menuReproduccionAleatoria(); 
    		    break;
    		
    		case 4: 
    		    buscarYReproducirPorTitulo();
                printf("\nPresione cualquier tecla para continuar...");
                getchar();
                getchar();
                break;
    		
    		case 5:
    		    buscarYReproducirPorHash();
    		    break;
    		
    		case 6:
    		    menuInsertarCancion();
    		    break;
    		
    		case 7:
    		    menuEliminarCancion();
    		    break;
    		
    		case 8:
    		    menuRecomendacionesPageRank();
    		    break;
    		
    		case 0: 
    		    printf("Cerrando programa...\n");
    		    break;
    		
    		default: 
    		    printf("ERROR! Ingrese una opcion valida del menu...\n");
    		    printf("Presione cualquier tecla para continuar...");
    		    getchar();
    		    getchar();
    		    break;
		}
    	
	}while (opcion != 0);
    
    
    
    
    
    
    
    

    // Liverar memoria para que nuestro PC no explote :V
    cerrarAudio();
    liberarAVL(raizAVL);
    liberarHash();
    liberarGrafo();
    freeList();
    
    printf("\n5.0 Para Todo el grupo.\n");
    return 0;
}