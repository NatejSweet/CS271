/****************************************
 * C-ploration 7 for CS 271
 * 
 * [NAME] Nathan Sweet
 * [TERM] FALL 2023
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
#define MAX_INSTRUCTION_COUNT 30000
int main(int argc, const char *argv[]){
	instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));		
	if (argc == 1){
		printf("ERROR: Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}	
	if (argc !=2){
		exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
	}
	
	FILE *fin = fopen(argv[1], "r");	
	if (fin == NULL){
		exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
	}
	parse(fin, instructions);
	// symtable_print_labels();
	// symtable_print_labels();
	fclose(fin);
	free(instructions);
}




