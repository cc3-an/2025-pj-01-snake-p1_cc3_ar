#include <stdio.h>
#include <string.h>

#include "snake_utils.h"
#include "state.h"

int main(int argc, char* argv[]) {
  char* in_filename = NULL;
  char* out_filename = NULL;
  game_state_t* state = NULL;

  // Parsea los argumentos recibidos
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
      in_filename = argv[i + 1];
      i++;
      continue;
    }
    if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
      out_filename = argv[i + 1];
      i++;
      continue;
    }
    fprintf(stderr, "Usage: %s [-i filename] [-o filename]\n", argv[0]);
    return 1;
  }

  // NO MODIFIQUEN NADA ARRIBA DE ESTA LINEA.


/* Tarea 7 */

 // Leer el tablero de un archivo, o crear un tablero por defecto.

 if (in_filename != NULL) {
       // 1. Cargar el tablero desde el archivo
 	state = load_board(in_filename);

        // 2. Si no se pudo abrir el archivo, salir con código de error -1
 	if (state == NULL) {
 		return -1;
	 }
	 
	 
	// 3. Inicializar las serpientes
 	 initialize_snakes(state);
 	
 	

 } else {
        // Si no hay archivo, cargar el tablero por defecto
 	 state = create_default_state();
 }
 
  update_state(state, deterministic_food);
  

 if (out_filename != NULL) {
 	FILE* out = fopen(out_filename, "w");
 	if (out != NULL) {
 	print_board(state, out);
 	fclose(out);
 	}
 } else {
 
	
 }
 free_state(state); 

 return 0;
}
