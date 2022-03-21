/*
** ETNA PROJECT, 17/06/2021 by dousse_r
** /home/slowiizz/Documents/etna/SummerProject
** File description:
**      ladder board
*/

#include "my_includes.h"

extern int score;

void swap(int* a, int* b)
{
    int tmp = *a;

    *a = *b;
    *b = tmp;
}

void my_bubble(int* array, int array_size)
{
    int swapped;

    do {
        swapped = 0;
        for (int i = 0; i < array_size; i++) {
            if (array[i] < array[i + 1]) {
                swap(&array[i], &array[i + 1]);
                swapped = 1;
            }
        };
    } while (swapped);
}

void add_score_to_ladder(int difficulty)
{
    FILE* file;
    char* file_path[5] = {"./ladder_adapt.csv",
    "./ladder_insane.csv",
    "./ladder_hard.csv",
    "./ladder_normal.csv",
    "./ladder_easy.csv"};

    file = fopen(file_path[difficulty], "a");
    if (file == NULL)
        exit(EXIT_FAILURE);
    fprintf(file, "%d\n", score);
    fclose(file);
}

int count_lines_in_file(FILE* file)
{
    int count = 0;
    while (!feof(file)) {
        if (fgetc(file) == '\n')
            count++;
    }
    return count;
}

int** files_to_scores_array()
{
    int** array;
    FILE* file;
    int test = 0;
    char* file_path[5] = {"./ladder_adapt.csv",
    "./ladder_insane.csv",
    "./ladder_hard.csv",
    "./ladder_normal.csv",
    "./ladder_easy.csv"};

    array = malloc(sizeof(*array) * 5);
    if (array == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < 5; i++) {
        int y = 0;
        file = fopen(file_path[i], "a+");
        if (file == NULL)
            exit(EXIT_FAILURE);
        array[i] = malloc(sizeof(**array) * (count_lines_in_file(file) + 1));
        if (array[i] == NULL)
            exit(EXIT_FAILURE);
        rewind(file);
        while (fscanf(file, "%d", &test) != EOF) {
            array[i][y] = test;
            y++;
        }
        array[i][y] = -1;
        fclose(file);
    };
    array = sort_arrays(array);
    return array;
}

int** sort_arrays(int** array)
{
    for (int i = 0; i < 5; i++) {
        int y = 0;
        while (array[i][y] != -1)
            y++;
        my_bubble(array[i], y);
    };
    return array;
}


