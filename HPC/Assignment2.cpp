#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void printArray(vector<int> array)
{
    for (int i = 0; i < array.size(); i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

void BubbleSort(vector<int> array)
{
    int n = array.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (array[j] > array[j + 1])
                swap(array[j], array[j + 1]);
        }
    }

    printArray(array);
}

void parallelBubbleSort(vector<int> &arr)
{
    int N = arr.size();
    int i = 0, j = 0;
    for (i = 0; i < N - 1; i++)
    {
#pragma omp parallel for
        for (j = 0; j < N - 1; j += 1)
        {
            if (arr[j] > arr[j + 1])
            {
// #pragma omp critical
                {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    printArray(arr);
}

void MergeSort(vector<int> array, int left, int right)
{
}

int main()
{
    vector<int> array = {64, 34, 25, 12, 22, 11, 90};

    // Give me random array of 50000 elements
    // for (int i =0; i<50000; i++) {
    //     array.push_back(rand() % 1000);
    // }

    double start = omp_get_wtime();
    BubbleSort(array);
    double end = omp_get_wtime();
    cout << "Sequential Bubble Sort Time: " << end - start << endl;

    start = omp_get_wtime();
    parallelBubbleSort(array);
    end = omp_get_wtime();
    cout << "Parallel Bubble Sort Time: " << end - start << endl;

    return 0;
}