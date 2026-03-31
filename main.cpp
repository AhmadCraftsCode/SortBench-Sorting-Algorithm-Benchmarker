#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// --- SORTING ALGORITHMS (Adapted for raw arrays) ---

void BubbleSort(int arr[], int n)
{
    for (int i = 0; i <= n - 2; i++)
    {
        for (int j = 0; j <= n - 2 - i; j++)
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

void SelectionSort(int arr[], int n)
{
    for (int i = 0; i <= n - 2; i++)
    {
        int min_index = i;
        for (int j = i + 1; j <= n - 1; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}

void InsertionSort(int arr[], int n)
{
    for (int i = 1; i <= n - 1; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort Helpers
void Merge(int left[], int leftSize, int right[], int rightSize, int arr[])
{
    int i = 0, j = 0, k = 0;
    while (i < leftSize && j < rightSize)
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    while (i < leftSize)
        arr[k++] = left[i++];
    while (j < rightSize)
        arr[k++] = right[j++];
}

void MergeSort(int arr[], int n)
{
    if (n > 1)
    {
        int mid = n / 2;
        int *left = new int[mid];
        int *right = new int[n - mid];

        for (int i = 0; i < mid; i++)
            left[i] = arr[i];
        for (int i = mid; i < n; i++)
            right[i - mid] = arr[i];

        MergeSort(left, mid);
        MergeSort(right, n - mid);
        Merge(left, mid, right, n - mid, arr);

        delete[] left;
        delete[] right;
    }
}

// Quick Sort Helpers
int Partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void QuickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivot_index = Partition(arr, low, high);
        QuickSort(arr, low, pivot_index - 1);
        QuickSort(arr, pivot_index + 1, high);
    }
}

// Heap Sort Helpers
void heapify(int arr[], int i, int n)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, largest, n);
    }
}

void HeapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, i, n);
    for (int i = n - 1; i >= 1; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, 0, i);
    }
}

// --- UTILITY FUNCTIONS ---

void copyArray(int source[], int target[], int n)
{
    for (int i = 0; i < n; i++)
        target[i] = source[i];
}

int main()
{
    srand(time(0));

    // Sizes required by PDF
    int sizes[] = {1000, 2000, 3000, 4000, 5000, 10000, 20000, 40000, 80000, 160000, 250000, 500000};
    int numSizes = 12;

    ofstream csvFile("runtime_results.csv");
    csvFile << "Input Size,Bubble,Selection,Insertion,Merge,Quick,Heap\n";

    cout << "Benchmarking Algorithms (Time in Milliseconds)...\n";
    cout << "Size\t\tBubble\t\tSelect\t\tInsert\t\tMerge\t\tQuick\t\tHeap\n";

    for (int s = 0; s < numSizes; s++)
    {
        int n = sizes[s];

        // Dynamic Allocation of raw arrays
        int *original = new int[n];
        int *tempArr = new int[n];

        // Fill with random data
        for (int i = 0; i < n; i++)
            original[i] = rand() % 100000;

        cout << n << "\t\t" << flush;
        csvFile << n;

        // BUBBLE SORT (Skip for very large sizes to save time)
        if (1)
        {
            copyArray(original, tempArr, n);
            auto start = high_resolution_clock::now();
            BubbleSort(tempArr, n);
            auto stop = high_resolution_clock::now();
            double time = duration_cast<microseconds>(stop - start).count() / 1000.0;
            cout << time << "\t\t";
            csvFile << "," << time;
        }

        // SELECTION SORT
        if (1)
        {
            copyArray(original, tempArr, n);
            auto start = high_resolution_clock::now();
            SelectionSort(tempArr, n);
            auto stop = high_resolution_clock::now();
            double time = duration_cast<microseconds>(stop - start).count() / 1000.0;
            cout << time << "\t\t";
            csvFile << "," << time;
        }


        // INSERTION SORT
        if (1)
        {
            copyArray(original, tempArr, n);
            auto start = high_resolution_clock::now();
            InsertionSort(tempArr, n);
            auto stop = high_resolution_clock::now();
            double time = duration_cast<microseconds>(stop - start).count() / 1000.0;
            cout << time << "\t\t";
            csvFile << "," << time;
        }


        // MERGE SORT
        copyArray(original, tempArr, n);
        auto mStart = high_resolution_clock::now();
        MergeSort(tempArr, n);
        auto mStop = high_resolution_clock::now();
        double mTime = duration_cast<microseconds>(mStop - mStart).count() / 1000.0;
        cout << mTime << "\t\t";
        csvFile << "," << mTime;

        // QUICK SORT
        copyArray(original, tempArr, n);
        auto qStart = high_resolution_clock::now();
        QuickSort(tempArr, 0, n - 1);
        auto qStop = high_resolution_clock::now();
        double qTime = duration_cast<microseconds>(qStop - qStart).count() / 1000.0;
        cout << qTime << "\t\t";
        csvFile << "," << qTime;

        // HEAP SORT
        copyArray(original, tempArr, n);
        auto hStart = high_resolution_clock::now();
        HeapSort(tempArr, n);
        auto hStop = high_resolution_clock::now();
        double hTime = duration_cast<microseconds>(hStop - hStart).count() / 1000.0;
        cout << hTime << "\n";
        csvFile << "," << hTime << "\n";

        // Memory Cleanup for this run
        delete[] original;
        delete[] tempArr;
    }

    csvFile.close();
    cout << "\nResults saved to 'runtime_results.csv'." << endl;
    return 0;
}