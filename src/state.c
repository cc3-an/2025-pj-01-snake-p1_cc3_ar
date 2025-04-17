#include "state.h"    

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

// Definiciones de funciones de ayuda.
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_state_t* state, unsigned int snum);
static char next_square(game_state_t* state, unsigned int snum);
static void update_tail(game_state_t* state, unsigned int snum);
static void update_head(game_state_t* state, unsigned int snum);


/* Tarea 1 */
game_state_t* create_default_state() { /*voy a devolver un puntero que apunta a una estructura de tipo game_state_t, esta estructura será el juego por defecto entonces voy a inicializar cada elemento de las estructuras game_state_t y snake_t para que formen el juego de la imagen de la tarea1 :)    */



// crea espacio en el heap para snake_T  y game_state_t 
  
	game_state_t *defoult_state = calloc(1,sizeof(game_state_t));   
	snake_t *defoult_snake = calloc(1,sizeof(snake_t)); 
  
  //inicializar cada elemento de las estructuras
  // game_state:
  
 	defoult_state -> num_rows = 18;                                       //18 filas del tablero
  	defoult_state -> num_snakes = 1 ;
  	defoult_state -> snakes = defoult_snake;
  
	defoult_state -> board = calloc(defoult_state->num_rows, sizeof(char*));  //se reserva espacio en el heap para el arreglo 
 
        
  	int f;
	for (f = 0; f <= 17; f++) {  //for para reservar espacio para cada fila y asignar los punteros al arreglo board
   
    		defoult_state -> board[f] = malloc(21 * sizeof(char));   //por los 20 chars + caracter nulo  "\0"
    		
    		if (f == 0 || f == 17) {
        		strcpy(defoult_state -> board[f],"####################");
   		} else if (f == 2) {
        		strcpy(defoult_state -> board[f],"# d>D    *         #");
    		} else {
        		strcpy(defoult_state -> board[f],"#                  #");
    		}
}


/* arriba se aparto espacio para el arreglo de punteros, calloc aparto 18 espacios del tamaño de un puntero de tipo char (32bits)
   y devolvio el valor de la primera dirección de ese arreglo a board, a continución en el for en cada iteración del mismo se aparta un espacio en memoria de 21 chars la dirección del primer char se guarda en board[f] que es el arreglo en la posición f así se va llenando el arreglo de punteros. Apartado el espacio para la fila se van llenando los 21 caracteres con strcpy dependiendo de la fila se escoge dentro del condicional if para poder llenar con los caracteres respectivos de ese numero de fila para el tablero o board por defoult */
   
   

 
  //snake_t:
  
  defoult_snake -> tail_row = 2;
  defoult_snake -> tail_col  = 2;
  defoult_snake -> head_row = 2;
  defoult_snake -> head_col = 4;
  defoult_snake -> live = true ;  
  
  return defoult_state;  //devuelvo el puntero a mi  juego por defecto que es de tipo defoult_state;
}







/* Tarea 2 */
void free_state(game_state_t* state) {   //a liberar todo lo que reserve en la tarea 1, de dentro hacia afuera

     unsigned int num_rowsToFree = state -> num_rows;

 
     int f;
     for (f = 0; f < num_rowsToFree; f++) {           //libero cada fila que reserve con malloc
          free(state -> board[f]);
     }
     
     free(state -> board);                //libero el arreglo de punteros
     
     free(state ->snakes );               //libero el espacio de memoria reservado para la estrcutura snake_t
     
     free(state);                         //libero la estructura completa de state, todo lo demás que tenía	
  return;
}























/* Tarea 3 */
void print_board(game_state_t* state, FILE* fp) {  //como argumentos un puntero "stare" a una estructura de tipo game_state_t y un puntero "fp" a un archivo en el cual se debe imprimir el tablero

	unsigned int num_rowsToPrint = state -> num_rows;
	
	int p;
	for(p = 0; p < num_rowsToPrint; p++){
	
        	fprintf(fp, "%s\n", state -> board[p]);              //en el archivo fp imprimir board[p] "cada fila" 
	}
	
  
  return;
}











/**
 * Guarda el estado actual a un archivo. No modifica el objeto/struct state.
 * (ya implementada para que la utilicen)
*/
void save_board(game_state_t* state, char* filename) {
  FILE* f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Tarea 4.1 */


/**
 * Funcion de ayuda que obtiene un caracter del tablero dado una fila y columna
 * (ya implementado para ustedes).
*/
char get_board_at(game_state_t* state, unsigned int row, unsigned int col) {
  return state->board[row][col];
}


/**
 * Funcion de ayuda que actualiza un caracter del tablero dado una fila, columna y
 * un caracter.
 * (ya implementado para ustedes).
*/
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch) {
  state->board[row][col] = ch;
}


/**
 * Retorna true si la variable c es parte de la cola de una snake.
 * La cola de una snake consiste de los caracteres: "wasd"
 * Retorna false de lo contrario.
*/
static bool is_tail(char c) {
  // TODO: Implementar esta funcion.
  return true;
}


/**
 * Retorna true si la variable c es parte de la cabeza de una snake.
 * La cabeza de una snake consiste de los caracteres: "WASDx"
 * Retorna false de lo contrario.
*/
static bool is_head(char c) {
  // TODO: Implementar esta funcion.
  return true;
}


/**
 * Retorna true si la variable c es parte de una snake.
 * Una snake consiste de los siguientes caracteres: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  // TODO: Implementar esta funcion.
  return true;
}


/**
 * Convierte un caracter del cuerpo de una snake ("^<v>")
 * al caracter que correspondiente de la cola de una
 * snake ("wasd").
*/
static char body_to_tail(char c) {
  // TODO: Implementar esta funcion.
  return '?';
}


/**
 * Convierte un caracter de la cabeza de una snake ("WASD")
 * al caracter correspondiente del cuerpo de una snake
 * ("^<v>").
*/
static char head_to_body(char c) {
  // TODO: Implementar esta funcion.
  return '?';
}


/**
 * Retorna cur_row + 1 si la variable c es 'v', 's' o 'S'.
 * Retorna cur_row - 1 si la variable c es '^', 'w' o 'W'.
 * Retorna cur_row de lo contrario
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  // TODO: Implementar esta funcion.
  return cur_row;
}


/**
 * Retorna cur_col + 1 si la variable c es '>' or 'd' or 'D'.
 * Retorna cur_col - 1 si la variable c es '<' or 'a' or 'A'.
 * Retorna cur_col de lo contrario
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  // TODO: Implementar esta funcion.
  return cur_col;
}


/**
 * Tarea 4.2
 *
 * Funcion de ayuda para update_state. Retorna el caracter de la celda
 * en donde la snake se va a mover (en el siguiente paso).
 *
 * Esta funcion no deberia modificar nada de state.
*/
static char next_square(game_state_t* state, unsigned int snum) {
  // TODO: Implementar esta funcion.
  return '?';
}


/**
 * Tarea 4.3
 *
 * Funcion de ayuda para update_state. Actualiza la cabeza de la snake...
 *
 * ... en el tablero: agregar un caracter donde la snake se va a mover (¿que caracter?)
 *
 * ... en la estructura del snake: actualizar el row y col de la cabeza
 *
 * Nota: esta funcion ignora la comida, paredes, y cuerpos de otras snakes
 * cuando se mueve la cabeza.
*/
static void update_head(game_state_t* state, unsigned int snum) {
  // TODO: Implementar esta funcion.
  return;
}


/**
 * Tarea 4.4
 *
 * Funcion de ayuda para update_state. Actualiza la cola de la snake...
 *
 * ... en el tablero: colocar un caracter blanco (spacio) donde se encuentra
 * la cola actualmente, y cambiar la nueva cola de un caracter de cuerpo (^<v>)
 * a un caracter de cola (wasd)
 *
 * ...en la estructura snake: actualizar el row y col de la cola
*/
static void update_tail(game_state_t* state, unsigned int snum) {
  // TODO: Implementar esta funcion.
  return;
}

/* Tarea 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  // TODO: Implementar esta funcion.
  return;
}

/* Tarea 5 */
game_state_t* load_board(char* filename) {
  // TODO: Implementar esta funcion.
  return NULL;
}


/**
 * Tarea 6.1
 *
 * Funcion de ayuda para initialize_snakes.
 * Dada una structura de snake con los datos de cola row y col ya colocados,
 * atravezar el tablero para encontrar el row y col de la cabeza de la snake,
 * y colocar esta informacion en la estructura de la snake correspondiente
 * dada por la variable (snum)
*/
static void find_head(game_state_t* state, unsigned int snum) {
  // TODO: Implementar esta funcion.
  return;
}

/* Tarea 6.2 */
game_state_t* initialize_snakes(game_state_t* state) {
  // TODO: Implementar esta funcion.
  return NULL;
}
