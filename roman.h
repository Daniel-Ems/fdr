#ifndef ROMAN_H
#define ROMAN_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct dictionary{
    struct key_value *head;   
}dictionary;

typedef struct key_value{
    struct key_value *next;
    char key;
    int value;
}key_value;

struct dictionary *create(void);
void insert(struct dictionary *dict, char key, int value);
int error_check(char *roman_numerals);
int roman(char *roman_numerals);
void dict_destroy(struct dictionary *dict);
#endif
