#ifndef LOADARRAY_H
#define LOADARRAY_H
#pragma once
#include "stdio.h"
#include "stdlib.h"

void loadArray2D(std::string filename, int arr[mapRows][mapCols])
{
    // open file for reading
    FILE* inputFile = fopen(filename.c_str(), "r");
    // read data into array
    for (int i = 0; i < mapRows; i++)
    {
        for (int j = 0; j < mapCols; j++)
        {
            fscanf(inputFile, "%d,", &arr[i][j]);
        }
    }
    // close file
    fclose(inputFile);
}

#endif