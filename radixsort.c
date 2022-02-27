/*
Strategy:

Do a LSD Radix Sort for uint32s (== uint).

LSD looks at the rightmost character first. You can do this by casting the uint as a char*, but you have to be careful because no \0!
*/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "queue.h"

#define RADIX 256
#define INTLN sizeof(uint)

// sorts
void rsort(uint* arr, uint len);
void bsort(uint* arr, uint len);

// bit-twiddliness
uint extractByte(uint num, uint col); 
void injectByte(uint* num, uint byte, uint col);

// other utils
void printArray(uint* arr, uint len);
uint* generateRangeArray(uint len);
bool isSorted(uint* arr, uint len);
void shuffle(uint* arr, uint len);
void swap(int* f, int* s);


int main(int argc, char* argv[]) {
    long longlen;
    uint* arr;
    uint len;
    char* p;

    // Handle arguments
    if (argc > 2) {
        printf("Error: too many arguments.\n");
        return 1;
    } else if (argc < 2) {
        printf("Error: no argument supplied.\n");
        return 1;
    }

    // Make sure that number passed in can fit in a uint
    longlen = strtol(argv[1], &p, 10);
    if (*p != '\0' || longlen <= 0 || longlen > UINT_MAX) {
        printf("Error: array length must be a positive integer below %d.\n", UINT_MAX);
    }
    len = (uint) longlen;

    assert(len == longlen);

    // Generate array
    arr = generateRangeArray(len);
    printArray(arr, len);
    assert(isSorted(arr, len));

    // Shuffle
    shuffle(arr, len);
    printArray(arr, len);

    // Try bubble sort
    bsort(arr, len);
    assert(isSorted(arr, len));
    printArray(arr, len);

    // Shuffle again
    shuffle(arr, len);
    printArray(arr, len);

    // Try radix sort
    rsort(arr, len);
    assert(isSorted(arr, len));
    printArray(arr, len);

    return 0;
}

// bsort is bubble sort. 
void bsort(uint* arr, uint len) {
    int i, t;
    bool again;

    again = true;
    while (again) {
        again = false;

        for (i = 0; i < len-1; i++) if (arr[i] > arr[i+1]) {
            swap(arr + i, arr + i + 1);
            again = true;
        }
    }
}

void rsort(uint* arr, uint len) {
    queue** freqs;
    uint col, row, freqInd;  // To loop (j addresses arr, k addresses freqs)

    freqs = (queue **)malloc(RADIX * (sizeof *freqs));    // Allocate char array of length 256 with zeroes
    for (freqInd = 0; freqInd < RADIX; freqInd++) {
        freqs[freqInd] = new_queue(len / RADIX + 1);
    }

    // Loop right to left of each column
    for (col = 0; col < (sizeof *arr); col++)  // Hey! This is pretty useful. Don't forget it!
    {
        printf("col is %d\n", col);
        // Make sure that freqs has been reset
        // for (freqInd = 0; freqInd < RADIX; freqInd++) {
        //     assert(freqs[freqInd] == 0);
        // }

        printf("About to loop through each char row\n");
        // Loop through each char row
        for (row = 0; row < len; row++) 
        {
            freqInd = extractByte(arr[row], col);
            enqueue(freqs[freqInd], arr[row]);
        }

        printf("About to dequeue\n");
        freqInd = 0;
        for (row = 0; row < len; row++) {
            while (is_empty(freqs[freqInd])) {
                freqInd++;
            }
            dequeue(freqs[freqInd], (arr + row));
        }

        assert(row == len);
    }
    // Free 
    free(freqs);
}

uint extractByte(uint num, uint col) {
    uint shift = 8 * col;
    uint mask = 0xff << shift;
    uint byte = (num & mask) >> shift;

    return byte;
}

void injectByte(uint* num, uint byte, uint col) {
    uint shift = 8 * col;
    uint mask = 0x000000ff << shift;
    *num = ((*num) & (~mask)) | (byte << shift);
}

uint* generateRangeArray(uint len) {
    uint* res = (uint*)malloc(len * sizeof(uint));
    for (uint i = 0; i < len; i++) res[i] = i;
    return res;
}

// Fisher-Yates shuffle. 
void shuffle(uint* arr, uint len) {
    int f, r, i;

    for (i = 0; i < len; i++) {
        r = (rand() % (len-i)) + i;
        swap(arr + i, arr + r);
    }
}

// Prints array in single row. 
void printArray(uint* arr, uint len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("]\n");
}

// Returns true if sorted.
bool isSorted(uint* arr, uint len) {
    for (int i = 0; i < len-1; i++) if (arr[i] > arr[i+1]) {
        return false;
    }
    return true;
}

// Swaps!
void swap(int* f, int* s) {
    int t;

    t = *f;
    *f = *s;
    *s = t;
}
