#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

vector<int> deepCopy(vector<int> &arraySource)
{

    vector<int> arrayDestination;
    for (int i = 0; i < arraySource.size(); i++)
    {
        arrayDestination.push_back(arraySource[i]);
    }
    return arrayDestination;
}

void printArray(vector<int> &array)
{
    for (int i = 0; i < array.size(); i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

void BubbleSort(vector<int> &array)
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
#pragma omp critical
                {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

void merge(vector<int> &arr, int start, int end, int mid)
{
    vector<int> L;
    vector<int> R;

    for (int i = start; i <= mid; i++)
    {
        L.push_back(arr[i]);
    }
    for (int i = mid + 1; i <= end; i++)
    {
        R.push_back(arr[i]);
    }

    int i = 0;
    int j = 0;
    int k = start;
    while (i < L.size() && j < R.size())
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i++];
        }
        else
        {
            arr[k] = R[j++];
        }
        k++;
    }

    while (i < L.size())
    {
        arr[k++] = L[i++];
    }

    while (j < R.size())
    {
        arr[k++] = R[j++];
    }
}

void MergeSortParallel(vector<int> &array, int start, int end)
{
    if (start < end)
    {

        int mid = (start + end) / 2;

#pragma omp parallel sections
        {
#pragma omp section
            MergeSortParallel(array, start, mid);

#pragma omp section
            MergeSortParallel(array, mid + 1, end);
        }

        merge(array, start, end, mid);
    }
}

void MergeSort(vector<int> &array, int start, int end)
{
    if (start < end)
    {

        int mid = (start + end) / 2;

        MergeSort(array, start, mid);
        MergeSort(array, mid + 1, end);

        merge(array, start, end, mid);
    }
}

int main()
{
    vector<int> array = {64, 34, 25, 12, 22, 11, 90};

    // Give me random array of 50000 elements
    for (int i = 0; i < 25; i++)
    {
        array.push_back(rand() % 1000);
    }
    vector<int> arr_cp1 = deepCopy(array);

    double start = omp_get_wtime();
    BubbleSort(array);
    double end = omp_get_wtime();
    cout << "Sequential Bubble Sort Time: " << end - start << endl;

    start = omp_get_wtime();
    parallelBubbleSort(arr_cp1);
    end = omp_get_wtime();
    cout << "Parallel Bubble Sort Time: " << end - start << endl;

    auto arr_cp2 = deepCopy(array);
    auto start2 = omp_get_wtime();
    MergeSort(arr_cp2, 0, array.size() - 1);
    auto end2 = omp_get_wtime();
    // printArray(arr_cp2);
    cout << "Sequential Merge Sort Time: " << end2 - start2 << endl;

    auto arr_cp3 = deepCopy(array);
    auto start3 = omp_get_wtime();
    MergeSortParallel(arr_cp3, 0, array.size() - 1);
    auto end3 = omp_get_wtime();
    // printArray(arr_cp3);
    cout << "Parallel Merge Sort Time: " << end3 - start3 << endl;

    return 0;
}