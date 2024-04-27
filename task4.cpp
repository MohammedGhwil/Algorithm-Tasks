#include <iostream>
using namespace std;

int partition(int MyArray[], int low, int high) {
    int pivot = MyArray[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (MyArray[j] <= pivot) {
            i++;
            swap(MyArray[i], MyArray[j]);
        }
    }
    swap(MyArray[i + 1], MyArray[high]);
    return (i + 1);
}

void quickSort(int MyArray[], int low, int high, int target) {
    int targetIndex = -1;
    for (int i = low; i <= high; i++) {
        if (MyArray[i] == target) {
            targetIndex = i;
            break;
        }
    }
    if (targetIndex != -1) {
        swap(MyArray[targetIndex], MyArray[high]);
        if (low < high) {
            int partitionIndex = partition(MyArray, low, high);
            quickSort(MyArray, low, partitionIndex - 1, target);
            quickSort(MyArray, partitionIndex + 1, high, target);
        }
    }
}

int main() {
    int MyArray[] = { -3,23,45,67,9,1,2,3,-55,-43,9,50,60,70,30,66,120,300,230,59,60 };

    int size = sizeof(MyArray) / sizeof(MyArray[0]);
    cout << "Array Before Pivoting on target\n";
    for (int i = 0; i < size; i++) {
        cout << MyArray[i] << " ";
    }
    cout << "\n";
    int target = 45;
    quickSort(MyArray, 0, size - 1, target);
    cout << "Array after pivoting on target\n";
    for (int i = 0; i < size; i++) {
        cout << MyArray[i] << " ";
    }
    return 0;
}
