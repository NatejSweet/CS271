/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] Nathan Sweet
 * [TERM] FALL 2023
 * 
 ****************************************/
#include "parser.h"

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
				s_new[i++]='\n';
			}
			break;
		}if (*s2 == '\n' && *(s2-1)){
			s_new[i++]='\n';
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
	char inst_type;
	
	
	while (fgets(line,sizeof(line),file)){
		strip(line);
		if (line[0] != '\n'){
			if (is_Atype(line)){
				inst_type = 'A';
			}else if (is_label(line)){
				inst_type = 'L';
			}else if (is_Ctype(line)){
				inst_type = 'C';
			}
			printf("%c  %s", inst_type, line);
		}
	}
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