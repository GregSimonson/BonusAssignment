#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocation;

// implement merge sort
// extraMemoryAllocation counts bytes of extra memory allocated
void merge(int array[], int left, int middle, int right)
{
    int i, j, k;
    int N1 = middle - left + 1;
    int N2 = right - middle;

    int L[N1], R[N2];

    for (i = 0; i < N1; i++)
        L[i] = array[left + i];
    for (j = 0; j < N2; j++)
        R[j] = array[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < N1 && j < N2)
    {
        if (L[i] <= R[j])
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < N1)
    {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < N2)
    {
        array[k] = R[j];
        j++;
        k++;
    }
}

// implement insertion sort
// extraMemoryAllocation counts bytes of memory allocated
void insertionSort(int array[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

// implement bubble sort
// extraMemoryAllocation counts bytes of extra memory allocated
void bubbleSort(int array[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

// implement selection sort
// extraMemoryAllocation counts bytes of extra memory allocated
void selectionSort(int array[], int n)
{
    int i, j, minimumIndex;
    for (i = 0; i < n - 1; i++)
    {
        minimumIndex = i;
        for (j = i + 1; j < n; j++)
        {
            if (array[j] < array[minimumIndex])
                minimumIndex = j;
        }
        int temp = array[minimumIndex];
        array[minimumIndex] = array[i];
        array[i] = temp;
        extraMemoryAllocation += 2 * sizeof(int);
    }
}

void heapify(int array[], int n, int i)
{
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // left = 2*i + 1
    int right = 2 * i + 2; // right = 2*i + 2

    if (left < n && array[left] > array[largest])
        largest = left;

    if (right < n && array[right] > array[largest])
        largest = right;

    if (largest != i)
    {
        int temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;
        heapify(array, n, largest); // Recursively heapify the affected sub-tree
    }
}

// Implement heap sort
void heapSort(int array[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--)
    {
        // Move current root to end
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        // call max heapify on the reduced heap
        heapify(array, i, 0);
    }
}

void mergeSort(int array[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        mergeSort(array, left, middle);
        mergeSort(array, middle + 1, right);

        merge(array, left, middle, right);
    }
}

// prints first and last 100 items in the data array

int main()
{
    int n = 10000;
    int array[n];
    srand(time(0));
    // initialize array with random values
    for (int i = 0; i < n; i++)
        array[i] = rand() % 100;

    printf("------------------\n");
    printf("Data size: 10000\n");
    printf("------------------\n");

    // heap sort
    extraMemoryAllocation = 0;
    clock_t timeToStart = clock();
    heapSort(array, n);
    printf("Heap sort: %.2fs\n", (double)(clock() - timeToStart) / CLOCKS_PER_SEC);
    printf("Extra memory allocated: %d bytes\n", extraMemoryAllocation);

    // merge sort
    extraMemoryAllocation = 0;
    timeToStart = clock();
    mergeSort(array, 0, n - 1);
    printf("Merge sort: %.2fs\n", (double)(clock() - timeToStart) / CLOCKS_PER_SEC);
    printf("Extra memory allocated: %d bytes\n", extraMemoryAllocation);

    // insertion sort
    extraMemoryAllocation = 0;
    timeToStart = clock();
    insertionSort(array, n);
    printf("Insertion sort: %.2fs\n", (double)(clock() - timeToStart) / CLOCKS_PER_SEC);
    printf("Extra memory allocated: %d bytes\n", extraMemoryAllocation);

    // bubble sort
    extraMemoryAllocation = 0;
    timeToStart = clock();
    bubbleSort(array, n);
    printf("Bubble sort: %.2fs\n", (double)(clock() - timeToStart) / CLOCKS_PER_SEC);
    printf("Extra memory allocated: %d bytes\n", extraMemoryAllocation);

    // selection sort
    extraMemoryAllocation = 0;
    timeToStart = clock();
    selectionSort(array, n);
    printf("Selection sort: %.2fs\n", (double)(clock() - timeToStart) / CLOCKS_PER_SEC);
    printf("Extra memory allocated: %d bytes\n", extraMemoryAllocation);

    return 0;
}