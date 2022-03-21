/*
** ETNA PROJECT, 17/06/2021 by dousse_r
** /home/slowiizz/Documents/etna/SummerProject
** File description:
**      ladder header
*/

#ifndef _FILE_H_
#define _FILE_H_

#include "my_includes.h"


void add_score_to_ladder();
int** files_to_scores_array();
int** files_to_scores_array();
void swap(int* a, int* b);
void my_bubble(int* array, int array_size);
int count_lines_in_file(FILE* file);
int** sort_arrays(int** array);


#endif