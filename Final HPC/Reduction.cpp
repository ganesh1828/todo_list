#include <iostream>
// #include <vector>
#include <omp.h>
#include <climits>
using namespace std;

// Parallel

void min_reduction(int arr[], int n)
{
    int min_value = INT_MAX;
#pragma omp parallel for reduction(min : min_value)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min_value)
        {
            min_value = arr[i];
        }
    }
    cout << "Minimum value: " << min_value << endl;
}

void max_reduction(int arr[], int n)
{
    int max_value = INT_MIN;
#pragma omp parallel for reduction(max : max_value)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max_value)
        {
            max_value = arr[i];
        }
    }
    cout << "Maximum value: " << max_value << endl;
}

void sum_reduction(int arr[], int n)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    cout << "Sum: " << sum << endl;
}

void average_reduction(int arr[], int n)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    cout << "Average: " << (double)sum / (n - 1) << endl;
}

// Serial

void serial_min_reduction(int arr[], int n)
{
    int min_value = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min_value)
        {
            min_value = arr[i];
        }
    }
    cout << "Minimum value: " << min_value << endl;
}

void serial_max_reduction(int arr[], int n)
{
    int max_value = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max_value)
        {
            max_value = arr[i];
        }
    }
    cout << "Maximum value: " << max_value << endl;
}

void serial_sum_reduction(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    cout << "Sum: " << sum << endl;
}

void serial_average_reduction(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    cout << "Average: " << (double)sum / (n - 1) << endl;
}

int main()
{
    int *arr, n;
    double start, stop, par_time, ser_time;
    cout << "\n enter total no of elements=>";
    cin >> n;
    arr = new int[n];
    cout << "\n enter elements=>";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    //   int arr[] = {5, 2, 9, 1, 7, 6, 8, 3, 4};
    //   int n = size(arr);

    start = omp_get_wtime();
    min_reduction(arr, n);
    max_reduction(arr, n);
    sum_reduction(arr, n);
    average_reduction(arr, n);
    stop = omp_get_wtime();
    par_time = stop - start;
    printf("\nParallel Time: %g\n", stop - start);

    start = omp_get_wtime();
    serial_min_reduction(arr, n);
    serial_max_reduction(arr, n);
    serial_sum_reduction(arr, n);
    serial_average_reduction(arr, n);
    stop = omp_get_wtime();
    par_time = stop - start;
    printf("\nSerial Time: %g\n", stop - start);

    string result;
    if (par_time > ser_time)
    {
        result = "Serial Faster";
    }
    else
    {
        result = "Parallel Faster";
    }
    cout << "\nTime Comparison: " << result << endl;

    return 0;
}