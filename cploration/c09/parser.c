/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] Nathan Sweet
 * [TERM] FALL 2023
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	
	char *s_new = (char*)malloc(strlen(s)+1);
	int i = 0;
	for (char *s2 = s; *s2; s2++) { 
		if (*s2 =='/' && *(s2+1)=='/'){
			if (*(s2-1)){
				s_new[i++]='\0';
			}
			break;
		}if (*s2 == '\n' && *(s2-1)){
			// s_new[i++]='\n';
		}else if (!isspace(*s2)){
			s_new[i++]=*s2;
		}
	}
	s_new[i]='\0';
	strcpy(s,s_new);
    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file){
	char line[MAX_LINE_LENGTH] = {0};
	unsigned int line_number = 0;
	unsigned int instr_num = 0;
	instruction instr;
	add_predefined_symbols();
	while (fgets(line,sizeof(line),file)){
		line_number++;
		char inst_type;
		if (instr_num>MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS+1);
		}
		strip(line);
		if (line[0] != '\n' && line[0] != '\0' && line[0] != '/'){
			// line_number++;
			// instr_num++;
			if (is_Atype(line)){
				inst_type = 'A';
				if (!parse_A_instruction(line, &instr.a)){
    				exit_program(EXIT_INVALID_A_INSTR, line_number, line);
 					}
 				instr.type = a_type;
			}else if (is_label(line)){
				inst_type = 'L';
				char* extracted_line = extract_label(line);
				if (!isalpha(line[1])){
					exit_program(EXIT_INVALID_LABEL, line_number,extracted_line);
				}else if (symtable_find(extracted_line)!=NULL){
					exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_number,extracted_line);
				}else{
					// printf("inserting %s at %u\n", extracted_line, instr_num);
					symtable_insert(extracted_line, instr_num);
					continue;
					strcpy(line, extracted_line);
					// line_number--;
					
				}
				
			}else if (is_Ctype(line)){
				inst_type = 'C';
			}
			// printf("%c  %s", inst_type, line);
			
		// printf("%u: %c  %s\n", instr_num, inst_type, line);
		instr_num++;
		}
	}
	
	
}

char* extract_label(const char* line) {
    char* new_line = malloc(strlen(line) + 1);
    int i = 0;
	int j = 0;
    for(i = 0; line[i] != '\0'; i++) {
        if(line[i] != '(' && line[i] != ')') {
            new_line[j++] = line[i];
        }
    }
    new_line[j] = '\0';
	
    return new_line;
}

bool is_Atype(const char* line){
	return (line[0] == '@');
}
bool is_label(const char* line){
	return (line[0] == '(');
}
bool is_Ctype(const char* line){
	return (!is_Atype(line) && !is_label(line));
}

void add_predefined_symbols(){
	for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){
		predefined_symbol symbol = predefined_symbols[i];
		symtable_insert(symbol.name, symbol.value);
	}
}

bool parse_A_instruction(const char *line, a_instruction *instr){
	char *s = (char*)malloc(strlen(line));
	strcpy(s, line+1);
	char *s_end = NULL;
	long result = strtol(s, &s_end, 10);
	if (s==s_end){
		instr->instrs.label = (char*)malloc(strlen(line));
		strcpy(instr ->instrs.label, s);

	}else if (*s_end != 0){
		return false;
	}else{
		instr->instrs.address = result;
		instr->is_addr = true;
	}
	return true;
}