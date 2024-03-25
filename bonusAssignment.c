#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocation;

// implement merge sort
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int N1 = m - l + 1;
    int N2 = r - m;

    int L[N1], R[N2];

    for (i = 0; i < N1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < N2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < N1 && j < N2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < N1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < N2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Will implement insertion sort
void insertionSort(int arr[], int t)
{
    int i, key, j;
    for (i = 1; i < t; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Will implement bubble sort
void bubbleSort(int arr[], int t)
{
    int i, j;
    for (i = 0; i < t - 1; i++)
    {
        for (j = 0; j < t - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// implement selection sort
void selectionSort(int arr[], int t)
{
    int i, j, min_idx;
    for (i = 0; i < t - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < t; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
        extraMemoryAllocation += 2 * sizeof(int);
    }
}

// parses the input file to an array

// Will peint the last and first 100 arrays

int main()
{
    int t = 10000;
    int arr[t];
    srand(time(0));

    for (int i = 0; i < t; i++)
        arr[i] = rand() % 100;

    printf("---------------------------\n");
    // printf("Dataset Size : %d\n",dataSz);
    printf("---------------------------\n");

    // merge sort
    extraMemoryAllocation = 0;
    clock_t timeStart = clock();
    mergeSort(arr, 0, t - 1);
    printf("Merge sort: %.2fs\t", (double)(clock() - timeStart) / CLOCKS_PER_SEC);
    printf("Extra memory allocated: %d bytes\t", extraMemoryAllocation);

    // insertion sort
    extraMemoryAllocation = 0;
    timeStart = clock();
    insertionSort(arr, t);
    printf("Insertion sort: %.2fs\t", (double)(clock() - timeStart) / CLOCKS_PER_SEC);
    printf("Extra memory allocated: %d bytes\t", extraMemoryAllocation);

    // bubble sort
    extraMemoryAllocation = 0;
    timeStart = clock();
    bubbleSort(arr, t);
    printf("Bubble sort: %.2fs\t", (double)(clock() - timeStart) / CLOCKS_PER_SEC);
    printf("Extra memory allocated: %d bytes\t", extraMemoryAllocation);

    // selection sort
    extraMemoryAllocation = 0;
    timeStart = clock();
    selectionSort(arr, t);
    printf("Selection sort: %.2fs\t", (double)(clock() - timeStart) / CLOCKS_PER_SEC);
    printf("Extra memory allocated: %d bytes\t", extraMemoryAllocation);

    return 0;
}