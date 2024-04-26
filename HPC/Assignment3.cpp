#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

long long arr_max(vector<long long> arr)
{
    long long maximum = arr[0];
    double start = omp_get_wtime();

#pragma omp parallel for reduction(max : maximum)
    for (long long i = 0; i < arr.size(); i++)
    {
        maximum = max(maximum, arr[i]);
    };
    double end = omp_get_wtime();
    cout << "Parallel Max Reduction Time: " << end - start << endl;
    cout << "Max: " << maximum;
    cout << endl;

    return maximum;
}
long long arr_max_seq(vector<long long> arr)
{
    long long maximum = arr[0];
    double start = omp_get_wtime();

    for (long long i = 0; i < arr.size(); i++)
    {
        maximum = max(maximum, arr[i]);
    };
    double end = omp_get_wtime();
    cout << "Seq Max Reduction Time: " << end - start << endl;
    cout << "Max: " << maximum;
    cout << endl;

    return maximum;
}
long long arr_min(vector<long long> arr)
{
    long long minimum = arr[0];
    double start = omp_get_wtime();

#pragma omp parallel for reduction(min : minimum)
    for (long long i = 0; i < arr.size(); i++)
    {
        minimum = min(minimum, arr[i]);
    };
    double end = omp_get_wtime();
    cout << "Parallel Min Reduction Time: " << end - start << endl;
    cout << "Min: " << minimum;
    cout << endl;
    return minimum;
}
long long arr_min_seq(vector<long long> arr)
{
    long long minimum = arr[0];
    double start = omp_get_wtime();
    for (long long i = 0; i < arr.size(); i++)
    {
        minimum = min(minimum, arr[i]);
    };
    double end = omp_get_wtime();
    cout << "Seq Min Reduction Time: " << end - start << endl;
    cout << "Min: " << minimum;
    cout << endl;

    return minimum;
}

long long arr_sum(vector<long long> arr)
{
    long long sum = 0;
    double start = omp_get_wtime();
#pragma omp parallel for reduction(+ : sum)
    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    double end = omp_get_wtime();
    cout << "Sum Reduction Time: " << end - start << endl;
    cout << "Sum: " << sum;
    cout << endl;
    return sum;
}
long long arr_sum_seq(vector<long long> arr)
{
    long long sum = 0;
    double start = omp_get_wtime();
    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    double end = omp_get_wtime();
    cout << "Seq Sum Reduction Time: " << end - start << endl;
    cout << "Sum: " << sum;
    cout << endl;
    return sum;
}

double arr_avg(vector<long long> arr)
{
    long long sum = 0;
    double start = omp_get_wtime();
#pragma omp parallel for reduction(+ : sum)
    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    double avg = sum / arr.size();
    double end = omp_get_wtime();
    cout << "Parallel Avg Reduction Time: " << end - start << endl;
    cout << "Avg: " << avg;
    cout << endl;
    return avg;
}

long long arr_avg_seq(vector<long long> arr)
{
    long long sum = 0;
    double start = omp_get_wtime();
    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    double avg = sum / arr.size();
    double end = omp_get_wtime();
    cout << "Sequential Avg Reduction Time: " << end - start << endl;
    cout << "Avg: " << avg;
    cout << endl;
    return avg;
}

int main()
{
    long long N = 90000000;
    vector<long long> arr = {1, 2, 4, 5, 7, 2, 6, 0};

    for (long long i = 0; i < N; i++)
    {
        arr.push_back(rand() % 1000);
    }

    arr_max(arr);
    arr_max_seq(arr);
    cout << endl;

    arr_min(arr);
    arr_min_seq(arr);
    cout << endl;

    arr_sum(arr);
    arr_sum_seq(arr);
    cout << endl;

    arr_avg(arr);
    arr_avg_seq(arr);
    cout << endl;

    return 0;
}