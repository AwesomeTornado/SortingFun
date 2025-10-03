// MemorySortTest1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <Windows.h>
#include "MemorySort.h"
#include "DataManager.h"

void screenDimensions(int* rows, int* columns) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void printList(int* list, int len) {
    for (int i = 0; i < len; i++) {
        std::cout << list[i] << ",";
    }
    std::cout << "\n";
}

void printHistogram(DataManager* data, int elements) {
    int rows, columns;
    screenDimensions(&rows, &columns);
    float* histogram = (float*)malloc((size_t)elements * sizeof(int));
    data->histogram(columns, histogram); // generate a histogram with width equal to columns.
    int chartHeight = rows * 0.50; // number of rows (height) in the histogram
    for (int row = chartHeight - 1; row >= 0; row--) { // print the histogram, with height XX% of screen
        for (int column = 0; column < min(elements, columns); column++) {
            float value = histogram[column];
            if (histogram[column] * (float)chartHeight >= (float)row) {
                std::cout << "#";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
    free(histogram);
}

int main()
{
    
    std::cout << "Hello World!\n";
    std::cout << "Please input number of elements\n";
    int elements = 0;
    std::cin >> elements;
    std::cout << "Initiating scramble of " << elements << " elements\n";
    
    DataManager data = DataManager(elements); // initialize our data storage class
    data.scramble(DataManager::randomizer::Random, 50); // and randomize the data.

    printHistogram(&data, elements);
    std::cout << "Initializing sorting function\n";
    sorter::MemorySort* memorySort = new sorter::MemorySort();

    auto start = std::chrono::high_resolution_clock::now();
    memorySort->sort(data.data, elements);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Done sorting, completed in " << (end - start).count() << " Nanoseconds\n";
    printHistogram(&data, elements);

    //std::cout << "Dimensions, rows: " << dims[0] << " columns: " << dims[1] << "\n";


    //for (int i = 0; i < data.length; i++) {
    //   std::cout << data.data[i] << ",";
    //}

    return -1;
}