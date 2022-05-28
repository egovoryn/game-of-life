#ifndef SRC_GAME_OF_LIFE_H_
#define SRC_GAME_OF_LIFE_H_

#include <stdio.h>
#include <stdlib.h>

#define M 27  // Buffer field height
#define N 82  // Buffer field width

int **current_array();
int **future_array();
char **display_array();
void buffer(int **cur);
void logic(int **cur, int **fut, int *popul);
void display(int **cur, char **dis);
void output(char **dis);
char input(char *space, char *temp);
int files_import(int **cur);
void free_array(int **cur, int **fut, char **d);
int input_files_import(int version);

#endif  // SRC_GAME_OF_LIFE_H_
