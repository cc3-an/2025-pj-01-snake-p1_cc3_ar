#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"

// Necesario por las funciones static en state.c
#include "state.c"

/* Vean el archivo asserts.c, para conocer algunas funciones de assert */

int greater_than_forty_two(int x) {
  return x > 42;
}

bool is_vowel(char c) {
  char* vowels = "aeiouAEIOU";
  for (int i = 0; i < strlen(vowels); i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

/**
 * Ejemplo 1: Retorna true si todos los tests pasan. false de lo contrario.
 *
 * La funcion greater_than_forty_two(int x) va a retornar true si x > 42. false de lo contrario.
 * Nota: Este test no cubre todo al 100%.
 */
bool test_greater_than_forty_two() {
  int testcase_1 = 42;
  bool output_1 = greater_than_forty_two(testcase_1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  int testcase_2 = -42;
  bool output_2 = greater_than_forty_two(testcase_2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  int testcase_3 = 4242;
  bool output_3 = greater_than_forty_two(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

/*
  Example 2: Returns true if all test cases pass. False otherwise.
    The function is_vowel(char c) will return true if c is a vowel (i.e. c is a,e,i,o,u)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
/**
 * Ejemplo 2: Retorna true si todos los tests pasan. false de lo contrario.
 *
 * La funcion is_vowel(char c) va a retornar true si c es una vocal (es decir, c es a,e,i,o,u)
 * y retorna false en el caso contrario
 * Nota: Este test no cubre todo al 100%.
 */
bool test_is_vowel() {
  char testcase_1 = 'a';
  bool output_1 = is_vowel(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_vowel(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'i';
  bool output_3 = is_vowel(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_vowel(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'u';
  bool output_5 = is_vowel(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'k';
  bool output_6 = is_vowel(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}




/* Task 4.1 */

//para las funciones is_tail, is_head, is_Snake, *r puntero a los resultados de cada funcion y *f puntero a la funcion 
/*
bool comparador(bool *r,bool (*f)(char c)){
	bool p;
	int i;
	char pruebas[17] = {'w','W','a','A','s','S','d','D',' ','/','<','>','v','^','w','f','a'};
	
	for(i = 0;i < 15; i++ ){
    
      		p = f( pruebas[i]);
      		if(p != r[i]){
       			printf("Fail\n");  
			printf("Error En char %c\nvalor esperado al valuar carácter: %d\nIteración No: %d\n\n",pruebas[i],r[i],i);
      			return false;                //si encuentra algún diferente
      		}
   	}
    
    	printf(" passed\n");
    	return true;                    // si son los mismos booleanos en p y en r para todos los caracteres 
}*/

//como las funciones de is tail is snake o is head usan respuestas del tipo bool pero las de body to tal de tipo char voy a usar un puntero generico *void así mi función comparador puede resivir cualquier tipo y ya luego lo voy a casterar al tipo correcto para cada caso

bool comparador_bool(bool *r,bool (*f)(char c)){
	bool p;
	int i;
	char pruebas[17] = {'w','W','a','A','s','S','d','D',' ','/','<','>','v','^','w','f','a'};
	
	for(i = 0;i < 17; i++ ){
    
      		p = f( pruebas[i]);
      		if(p != r[i]){
       			printf("Fail X\n");  
			printf("Error En char %c\nvalor esperado al valuar carácter: %d\nIteración No: %d\n\n",pruebas[i],r[i],i);
      			return false;                //si encuentra algún diferente
      		}
   	}
    
    	printf("   passed\n");
    	return true;                    // si son los mismos booleanos en p y en r para todos los caracteres 
}

bool comparador_char(char *r,char (*f)(char c)){
	char p;
	int i;
	char pruebas[11]={'<','A','>','D','^','W','v','S','a','A','/'};
	
	for(i = 0;i < 11; i++ ){
    		
	      		p = f( pruebas[i]);
	      		if(p != r[i]){
	       			printf("Fail X\n");  
				printf("Error En char %c\nvalor esperado al valuar carácter: %d\nIteración No: %d\n\n",pruebas[i],r[i],i);
	      			return false;                //si encuentra algún diferente
	      		}	
   	}
    
    	printf("  passed\n");
    	return true;                   
}

bool comparador_int(unsigned int *r,unsigned int (*f)(unsigned int,char c)){
	unsigned int p;
	int i;
	unsigned int fila[13] = {8,8,5,5,1,1,0,2,1,4,6,3,9};
	char caracter[13] = {'v','^','s','w','S','W','w','<','>','d','D','a','A'};
	
	
	for(i = 0;i < 9; i++ ){
	
		p = f(fila[i],caracter[i]);
	      	if( p != r[i]){
	      		
	      		printf(" Fail X \n");  
			printf(" Caracter: %c\n Fila actual: %d\n valor obtenido: %d\n valor esperado: %d\n\n ",caracter[i], fila[i],p,r[i]);
	      		return false;
	      		
	      		}	
   	}
    
    	printf(" passed\n");
    	return true;                    // si son los mismos booleanos en p y en r para todos los caracteres 
}







bool test_is_tail() {

    printf("\n Test is tail:      ");   
    bool resultados_tail[17]  = {true,false,true,false,true,false,true,false,false,false,false,false,false,false,true,false,true}; 
    bool *r = resultados_tail;                 //puntero a el arreglo de resultados para pasarlo a la función comparador
    bool (*f)(char c) = is_tail;             //puntero a función tail
    return comparador_bool(r,f);
   
}


bool test_is_head() { 
	printf("\n Test is head:      ");  
        bool resultados_Head[17]  = {false,true,false,true,false,true,false,true,false,false,false,false,false,false,false,false,false}; 
        bool *r = resultados_Head;                 //puntero a el arreglo de resultados para pasarlo a la función comparador
        bool (*f)(char)= is_head;             //puntero a función Head
        return comparador_bool(r,f);
}

bool test_is_snake(){
	
	printf("\n Test es snake:     ");  
        bool resultados_Snake[17]  = {true,true,true,true,true,true,true,true,false,false,true,true,true,true,true,false,true}; 
        bool *r = resultados_Snake;                 
        bool (*f)(char)= is_snake;            
        return comparador_bool(r,f);
}

bool test_body_to_tail() {

        printf("\n Test body to tail:  ");	
	char resultados_body_tail[11] = {'a','?','d','?','w','?','s','?','?','?','?'};
	char *r = resultados_body_tail;
	char (*f)(char) = body_to_tail;
	return comparador_char(r,f);
	  
}

bool test_head_to_body() {
  
   printf("\n Test head to body:  ");
        
        char resultados_head_body [11] = {'?','<','?','>','?','^','?','v','?','<','?'};
        char *r = resultados_head_body;
   	char (*f)(char) = head_to_body;
   	return comparador_char(r,f);
   		
}

/** probar esta función:
    next row
 * Retorna cur_row + 1 si la variable c es 'v', 's' o 'S'.
 * Retorna cur_row - 1 si la variable c es '^', 'w' o 'W'.
 * Retorna cur_row de lo contrario
*/

	
	
	
bool test_get_next_row() {
	
	
	printf("\n Test next row:   ");
	unsigned int resultados_next_row[13]= {9,7,6,4,2,0,0,2,1,4,6,3,9};
	unsigned int *r = resultados_next_row;
	unsigned int (*f)(unsigned int, char) = get_next_row;
	return comparador_int(r,f);
  
}

/**probar la función next_col que hace :
 * Retorna cur_col + 1 si la variable c es '>' or 'd' or 'D'.
 * Retorna cur_col - 1 si la variable c es '<' or 'a' or 'A'.
 * Retorna cur_col de lo contrario
*/

	
	
bool test_get_next_col() {

	printf("\n Test next col:   ");
	unsigned int resultados_next_col[13]= {8,8,5,5,1,1,0,1,2,5,7,2,8};
	unsigned int *r = resultados_next_col;
	unsigned int (*f)(unsigned int, char) = get_next_col;
	return comparador_int(r,f);
}










bool test_customs() {
  if (!test_greater_than_forty_two()) {
    printf("%s\n", "test_greater_than_forty_two failed.");
    return false;
  }
  if (!test_is_vowel()) {
    printf("%s\n", "test_is_vowel failed.");
    return false;
  }
  if (!test_is_tail()) {
    printf("%s\n", "test_is_tail failed");
    return false;
  }
  if (!test_is_head()) {
    printf("%s\n", "test_is_head failed");
    return false;
  }
  if (!test_is_snake()) {
    printf("%s\n", "test_is_snake failed");
    return false;
  }
  if (!test_body_to_tail()) {
    printf("%s\n", "test_body_to_tail failed");
    return false;
  }
  if (!test_head_to_body()) {
    printf("%s\n", "test_head_to_body failed");
    return false;
  }
  if (!test_get_next_row()) {
    printf("%s\n", "test_get_next_row failed");
    return false;
  }
  if (!test_get_next_col()) {
    printf("%s\n", "test_get_next_col failed");
    return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  init_colors();

  if (!test_and_print("custom", test_customs)) {
    return 0;
  }

  return 0;
}
