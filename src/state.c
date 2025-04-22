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
	  if(c == 'w' || c == 'a' || c=='s' || c == 'd'){
	  	 return true;
	  }else{
	  	return false;
	  }
  
}


/**
 * Retorna true si la variable c es parte de la cabeza de una snake.
 * La cabeza de una snake consiste de los caracteres: "WASDx"
 * Retorna false de lo contrario.
*/
static bool is_head(char c) {
	  if(c == 'W' || c == 'A' || c == 'S' || c == 'D'){
	  	 return true;
	  }else{
	  	return false;
	  }
  
}


/**
 * Retorna true si la variable c es parte de una snake.
 * Una snake consiste de los siguientes caracteres: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
	   if(c == 'W' || c == 'A' || c == 'S' || c == 'D' || c == 'w' || c == 'a' || c == 's' || c == 'd' ||c == '<' || c == '>' || c == '^' || c == 'v' ){
  	        return true;
           }else{
  	        return false;
           }
}


/**
 * Convierte un caracter del cuerpo de una snake ("^<v>")
 * al caracter que correspondiente de la cola de una
 * snake ("wasd").
*/
static char body_to_tail(char c) {
	   switch (c) {
		case '<': return 'a';
		case '>': return 'd';
		case '^': return 'w';
		case 'v': return 's';
		default:  return '?';
	    }
}


/**
 * Convierte un caracter de la cabeza de una snake ("WASD")
 * al caracter correspondiente del cuerpo de una snake
 * ("^<v>").
*/
static char head_to_body(char c) {
	switch (c) {
		case 'A': return '<';
		case 'D': return '>';
		case 'W': return '^';
		case 'S': return 'v';
		default:  return '?';
	    }
	  
}


/**
 * Retorna cur_row + 1 si la variable c es 'v', 's' o 'S'.
 * Retorna cur_row - 1 si la variable c es '^', 'w' o 'W'.
 * Retorna cur_row de lo contrario
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {

       
		if (c == 'v' || c == 's' || c=='S' ){
	  	 	return cur_row + 1 ;
		} else if (c == '^' || c == 'w' || c=='W'){
	  		return (cur_row > 0 ) ? cur_row - 1  :0 ; // si en caso la fila actual sea 0 no se podra hacer 0-1 se quedará en la fila 0
		} else {
	      		return cur_row;
		}
	
}


/**
 * Retorna cur_col + 1 si la variable c es '>' or 'd' or 'D'.
 * Retorna cur_col - 1 si la variable c es '<' or 'a' or 'A'.
 * Retorna cur_col de lo contrario
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
	if (c == '>' || c == 'd' || c=='D'){
	  	 return cur_col + 1 ;
	} else if (c == '<' || c == 'a' || c =='A'){
	  	return cur_col - 1;
	} else {
	      	return cur_col;
	}
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
  //state es el puntero a la estructura state, snum es el numero de serpiente en el arreglo snake_t, en state existe un puntero a este arrelo de estructuras llamado snakes (snake_t *snakes: Un arreglo de estructuras snake_t.)
         
        //voy a el elemento de snakes[snum] en la posicion snum y dentro de la estrucuta snake veo la fila y columna de la cabeza
  	unsigned int head_row = state->snakes[snum].head_row;
        unsigned int head_col = state->snakes[snum].head_col;
        
        
        //ya tengo la fila y columna  ahora voy a leer lo que hay en la interseccion de ambas usando la funcion que nos dieron
        char head_char = get_board_at(state,head_row, head_col);
        
        //obtengo mi la siguiente fila y columna apartir del elemento de la cabeza
        unsigned int next_row = get_next_row(head_row, head_char);  //fila, elemento
        unsigned int next_col = get_next_col(head_col, head_char);  //fila, columna
        
        //uso nuevamente la función proporcionada para leer lo que hay en la siguiente posicion 
        char next_square = get_board_at(state, next_row, next_col);
        
  return next_square;
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
   //la primera parte como la de arriba... a buscar primero el numero de la fila y columan donde este la snake No.snum
  	unsigned int head_row = state->snakes[snum].head_row;
        unsigned int head_col = state->snakes[snum].head_col;
        
        char head_char = get_board_at(state,head_row, head_col); //leo el caracter que guarda la interseccion de la fila y columna
        
        //siguiente posición
        unsigned int next_row = get_next_row(head_row, head_char);  
        unsigned int next_col = get_next_col(head_col, head_char);
        
        
        
        //convierto la cabeza en una parte del cuerpo 
         char body_char = head_to_body(head_char); 
         
         
         set_board_at(state, head_row, head_col,body_char); //donde estaba la cabeza se coloca un caracter de cuerpo correspondiente
         set_board_at(state, next_row, next_col,head_char); //cabeza se mueve a la siguiente posción en el tablero
         
         
         
    
        //actualizar la estructura snake con la nueva fila y columna
        state->snakes[snum].head_row = next_row;
        state->snakes[snum].head_col = next_col;
        
           
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

   
   //posción donde se encuentra la cola actualemente 
        unsigned int tail_row = state->snakes[snum].tail_row;
        unsigned int tail_col = state->snakes[snum].tail_col;
        
   //obtengo el caracter de la cola en
        char tail_char = get_board_at(state,tail_row, tail_col);
        
   
   //coloco espacio en blanco
   set_board_at(state,tail_row,tail_col,' ');
   
   //siguiente posición 
   
   unsigned int next_row = get_next_row(tail_row, tail_char);  
   unsigned int next_col = get_next_col(tail_col, tail_char);
   
   //leer lo que hay en la siguiente posición y guardarlo en un char
   char body_char = get_board_at(state, next_row, next_col);
   
   //cambiar de body a tail 
   char next_tail = body_to_tail(body_char);
   
   //ya teniendo la nueva cola la colocamos en la posición siguiente que se habia obtenido con la función dada
   set_board_at(state,next_row,next_col,next_tail);
    
   //a actualizar la estructura
   state->snakes[snum].tail_row = next_row;
   state->snakes[snum].tail_col = next_col;
    
  return;
}


/* Tarea 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
   unsigned int i;
   unsigned int snakes = state->num_snakes;

    for (i = 0; i < snakes; i++) {
        if (state->snakes[i].live) {

            char next_char = next_square(state, i);

            if (next_char == '#' || is_snake(next_char)) {
                unsigned int head_row = state->snakes[i].head_row;
                unsigned int head_col = state->snakes[i].head_col;
                set_board_at(state, head_row, head_col, 'x');
                state->snakes[i].live = false;

            } else if (next_char == '*') {
                update_head(state, i);
                add_food(state);

            } else if (next_char == ' ') {
                update_head(state, i);
                update_tail(state, i);
            }
        }
    }
    return;
}

/* Tarea 5 */
game_state_t* load_board(char* filename) {
  	
   //abro mi archivo de los boards para lectura y null para que pare cuando ya no queda nada en el archivo
    FILE* fboards = fopen(filename, "r");
    if (fboards == NULL) {
        return NULL;
    }

    char bufferRow[1024];                                //bufer temporal donde se va a ir guardando la fila leída
    char** board = NULL;                                 //puntero a un arrelo de punteros a las filas crece a  medida que se lea la siguiente fila
    
    unsigned int num_rows = 0;

    while (fgets(bufferRow, 1024, fboards) != NULL) {
    
        size_t length = strlen(bufferRow);//veo el tamaño de lo que se guardo en el bufferRow así luego se puede apartar memoria en el heap con el malloc 
        
        if (length > 0 && bufferRow[length - 1] == '\n') {
	    bufferRow[length - 1] = '\0';
	    length--;  
        }
        
       
        char* row = malloc((length + 1) * sizeof(char));
        strcpy(row, bufferRow);                                     //copiar en el puntero row lo que tiene bufferRow

        board = realloc(board, (num_rows + 1) * sizeof(char*));        //aparto memoria expansible para el arrelo de punteros
        board[num_rows] = row;                                    // en el arreglo board en la posicion (num_rows) colocar el puntero row
        num_rows++; 
    } 

    fclose(fboards); 

    game_state_t *state = malloc(sizeof(game_state_t));
    state->board = board;
    state->num_rows = num_rows;
    state->snakes = NULL;
    state->num_snakes = 0;

    return state; 
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
