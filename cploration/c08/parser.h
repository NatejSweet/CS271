/****************************************
 * C-ploration 7 for CS 271
 * 
 * [NAME] Nathan Sweet
 * [TERM] FALL 2023
 * 
 ****************************************/
#ifndef __PARSER_H__
#define __PARSER_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH-2
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS
/** function prototypes **/
char *strip(char *s);
void parse(FILE * file);
char* extract_label(const char*);
bool is_Atype(const char*);
bool is_label(const char*);
bool is_Ctype(const char*);
typedef int16_t hack_addr;
typedef int16_t opcode;

enum instr_type{
    invalid = -1,
    a_type,
    c_type
};
typedef struct c_instruction{
    opcode a:1;
    opcode comp:6;
    opcode dest:3;
    opcode jump:3;
}c_instruction;

typedef struct a_instruction{
    union {
        hack_addr address;
        char* label;
    };
    bool is_addr;
}a_instruction;

typedef struct instruction{
    union {
        a_instruction a;
        c_instruction c;
    };
    enum instr_type type;
}instruction;

#endif

