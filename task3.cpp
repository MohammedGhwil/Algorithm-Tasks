#include <iostream>
#include <algorithm>
#include <chrono>
#include<fstream>
using namespace std::chrono;
using namespace std;



int heapify(int arr[], int n, int i, int count = 0) {
    int minimum = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[minimum]) {
        minimum = left;
        count++;
    }

    if (right < n && arr[right] < arr[minimum]) {
        minimum = right;
        count++;
    }

    if (minimum != i) {
        swap(arr[i], arr[minimum]);
        heapify(arr, n, minimum, count);
    }

    return count;
}

int BuildHeap(int arr[], int n) {
    int count = 0;
    for (int i = n / 2 - 1; i >= 0; i--) {
        count = count + heapify(arr, n, i);
    }
    return count;
}

int HeapSort(int arr[], int n) {
    int count = BuildHeap(arr, n);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        count = count + heapify(arr, i, 0);
    }

    return count;
}

int HeapSortCount(int arr[], int n) {
    return HeapSort(arr, n);
}


int BubbleSortCount(int* arr, int n) {
    int CountBubble = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            CountBubble++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    return CountBubble;
}

int InsertionSortCount(int* arr, int n) {
    int CountInsret = 0, i, j, key;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        CountInsret++;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    return CountInsret;
}

int SelectionSortCount(int arr[], int n) {
    int i, j, MinimumIndex, count = 0;

    for (i = 0; i < n - 1; i++) {
        MinimumIndex = i;
        for (j = i + 1; j < n; j++) {
            count++;
            if (arr[j] < arr[MinimumIndex])
                MinimumIndex = j;
        }
        if (MinimumIndex != i)
            swap(arr[MinimumIndex], arr[i]);
    }
    return count;
}

void TestingNumberOfComparisons() {
    ofstream file("SortingResultsTest2.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return;
    }

    file << "n,heap,bubble,insertion,selection\n";
    cout << "   " << "n" << "       " << "heap" << "       " << "bubble" << "       " << "insertion" << "       " << "selection" << endl;
    for (int n = 1; n <= 30; n = n + 1) {
        int* random_arr = new int[n];
        int* sorted_arr = new int[n];
        int* inverse_arr = new int[n];

        for (int i = 0; i < n; i++) {
            random_arr[i] = rand() % 150 + 1;
            sorted_arr[i] = i + 1;
            inverse_arr[i] = n - i;
        }

        int heapR = HeapSortCount(random_arr, n);
        int bubbleR = BubbleSortCount(random_arr, n);
        int insertionR = InsertionSortCount(random_arr, n);
        int selectionR = SelectionSortCount(random_arr, n);

        int heapS = HeapSortCount(sorted_arr, n);
        int bubbleS = BubbleSortCount(sorted_arr, n);
        int insertionS = InsertionSortCount(sorted_arr, n);
        int selectionS = SelectionSortCount(sorted_arr, n);

        int heapV = HeapSortCount(inverse_arr, n);
        int bubbleV = BubbleSortCount(inverse_arr, n);
        int insertionV = InsertionSortCount(inverse_arr, n);
        int selectionV = SelectionSortCount(inverse_arr, n);

        cout << "   " << n << "       " << heapR << "       " << bubbleR << "       " << insertionR << "       " << selectionR << endl << endl;
        cout << "   " << n << "       " << heapS << "       " << bubbleS << "       " << insertionS << "       " << selectionS << endl << endl;
        cout << "   " << n << "       " << heapV << "       " << bubbleV << "       " << insertionV << "       " << selectionV << endl << endl;
        file << n << "," << heapR << "," << bubbleR << "," << insertionR << "," << selectionR << "\n";
        file << n << "," << heapS << "," << bubbleS << "," << insertionS << "," << selectionS << "\n";
        file << n << "," << heapV << "," << bubbleV << "," << insertionV << "," << selectionV << "\n";
    }
    file.close();

}

void TestingExectuionTime() {
    ofstream file("ExecutionTestResults3.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return;
    }
    file << "n,heap,bubble,insertion,selection\n";
    cout << "   " << "n" << "       " << "heap" << "       " << "bubble" << "       " << "insertion" << "       " << "selection" << endl;

    for (int n = 1; n <= 30; n = n + 1) {
        int* random_arr = new int[n];
        int* sorted_arr = new int[n];
        int* inverse_arr = new int[n];

        for (int i = 0; i < n; i++) {
            random_arr[i] = rand() % 150 + 1;
            sorted_arr[i] = i + 1;
            inverse_arr[i] = n - i;
        }

        auto startHeap = chrono::high_resolution_clock::now();
        HeapSortCount(random_arr, n);
        auto endHeap = chrono::high_resolution_clock::now();
        double heap = chrono::duration_cast<chrono::nanoseconds>(endHeap - startHeap).count();

        auto startBubble = chrono::high_resolution_clock::now();
        BubbleSortCount(random_arr, n);
        auto endBubble = chrono::high_resolution_clock::now();
        double bubble = chrono::duration_cast<chrono::nanoseconds>(endBubble - startBubble).count();

        auto startInsert = chrono::high_resolution_clock::now();
        InsertionSortCount(random_arr, n);
        auto endInsert = chrono::high_resolution_clock::now();
        double insertion = chrono::duration_cast<chrono::nanoseconds>(endInsert - startInsert).count();

        auto startSelect = chrono::high_resolution_clock::now();
        SelectionSortCount(random_arr, n);
        auto endSelect = chrono::high_resolution_clock::now();
        double selection = chrono::duration_cast<chrono::nanoseconds>(endSelect - startSelect).count();

        cout << "   " << n << "       " << heap << "       " << bubble << "       " << insertion << "       " << selection << endl;

        startHeap = chrono::high_resolution_clock::now();
        HeapSortCount(sorted_arr, n);
        endHeap = chrono::high_resolution_clock::now();
        heap = chrono::duration_cast<chrono::nanoseconds>(endHeap - startHeap).count();

        startBubble = chrono::high_resolution_clock::now();
        BubbleSortCount(sorted_arr, n);
        endBubble = chrono::high_resolution_clock::now();
        bubble = chrono::duration_cast<chrono::nanoseconds>(endBubble - startBubble).count();

        startInsert = chrono::high_resolution_clock::now();
        InsertionSortCount(sorted_arr, n);
        endInsert = chrono::high_resolution_clock::now();
        insertion = chrono::duration_cast<chrono::nanoseconds>(endInsert - startInsert).count();

        startSelect = chrono::high_resolution_clock::now();
        SelectionSortCount(sorted_arr, n);
        endSelect = chrono::high_resolution_clock::now();
        selection = chrono::duration_cast<chrono::nanoseconds>(endSelect - startSelect).count();

        cout << "   " << n << "       " << heap << "       " << bubble << "       " << insertion << "       " << selection << endl;

        startHeap = chrono::high_resolution_clock::now();
        HeapSortCount(inverse_arr, n);
        endHeap = chrono::high_resolution_clock::now();
        heap = chrono::duration_cast<chrono::nanoseconds>(endHeap - startHeap).count();

        startBubble = chrono::high_resolution_clock::now();
        BubbleSortCount(inverse_arr, n);
        endBubble = chrono::high_resolution_clock::now();
        bubble = chrono::duration_cast<chrono::nanoseconds>(endBubble - startBubble).count();

        startInsert = chrono::high_resolution_clock::now();
        InsertionSortCount(inverse_arr, n);
        endInsert = chrono::high_resolution_clock::now();
        insertion = chrono::duration_cast<chrono::nanoseconds>(endInsert - startInsert).count();

        startSelect = chrono::high_resolution_clock::now();
        SelectionSortCount(inverse_arr, n);
        endSelect = chrono::high_resolution_clock::now();
        selection = chrono::duration_cast<chrono::nanoseconds>(endSelect - startSelect).count();

        cout << "   " << n << "       " << heap << "       " << bubble << "       " << insertion << "       " << selection << endl;

        delete[] random_arr;
        delete[] sorted_arr;
        delete[] inverse_arr;
        file << n << "," << heap << "," << bubble << "," << insertion << "," << selection << "\n";

    }
    file.close();

}

int main() {
    cout << "Comparison Time" << endl;
    TestingNumberOfComparisons();

    cout << endl << "Execution time" << endl;
    TestingExectuionTime();


    return 0;
}
