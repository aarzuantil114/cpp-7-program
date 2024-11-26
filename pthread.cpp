#include <iostream>
#include <pthread.h>
#include <vector>
using namespace std;

// Structure to hold the range of numbers and partial sum
struct ThreadData {
    int start;       // Start index
    int end;         // End index
    vector<int>* numbers; // Pointer to the array of numbers
    int partialSum;  // Sum calculated by the thread
};

// Function executed by each thread
void* calculatePartialSum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->partialSum = 0;

    for (int i = data->start; i <= data->end; i++) {
        data->partialSum += (*data->numbers)[i];
    }

    pthread_exit(0);
}

int main() {
    int n, numThreads;

    // Input the total number of elements
    cout << "Enter the number of elements: ";
    cin >> n;

    // Input the number of threads
    cout << "Enter the number of threads: ";
    cin >> numThreads;

    // Input the numbers
    vector<int> numbers(n);
    cout << "Enter the numbers:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    // Create thread data and threads
    vector<ThreadData> threadData(numThreads);
    vector<pthread_t> threads(numThreads);

    int range = n / numThreads; // Determine how many elements each thread processes

    // Create threads and assign ranges
    for (int i = 0; i < numThreads; i++) {
        threadData[i].start = i * range;
        threadData[i].end = (i == numThreads - 1) ? (n - 1) : (i + 1) * range - 1;
        threadData[i].numbers = &numbers;
        pthread_create(&threads[i], NULL, calculatePartialSum, (void*)&threadData[i]);
    }

    // Wait for all threads to finish
    int totalSum = 0;
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
        totalSum += threadData[i].partialSum;
    }

    // Output the total sum
    cout << "The total sum is: " << totalSum << endl;

    return 0;
}