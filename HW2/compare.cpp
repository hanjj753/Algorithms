#include <iostream>
#include <vector>
#include <string>
#include <chrono>   // 시간 측정
#include <random>   // 난수 생성
#include <algorithm>// std::sort, std::reverse, std::swap
#include <iomanip>  // 출력 포맷팅

// ===================================================================
// SECTION 1: SORTING ALGORITHMS
// ===================================================================

// 1.1 Insertion Sort
void insertion_sort(std::vector<int>& arr) {
    for (int i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 1.2 Merge Sort
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void merge_sort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// 1.3 Quick Sort
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quick_sort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// ===================================================================
// SECTION 2: INPUT GENERATION
// ===================================================================

// C++11 표준의 고품질 난수 생성기
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// 2.1 Random Array
std::vector<int> generate_random_array(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rng();
    }
    return arr;
}

// 2.2 Sorted Array
std::vector<int> generate_sorted_array(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i;
    }
    return arr;
}

// 2.3 Reversed Array
std::vector<int> generate_reversed_array(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = size - 1 - i;
    }
    return arr;
}

// 2.4 Nearly Sorted Array
std::vector<int> generate_nearly_sorted_array(int size) {
    std::vector<int> arr = generate_sorted_array(size);
    int swaps = size * 0.10; // 10% of elements
    for (int i = 0; i < swaps; ++i) {
        int pos1 = rng() % size;
        int pos2 = rng() % size;
        std::swap(arr[pos1], arr[pos2]);
    }
    return arr;
}

// ===================================================================
// SECTION 3: PERFORMANCE EVALUATION
// ===================================================================

int main() {
    std::vector<int> sizes = {1000, 10000, 100000};
    std::vector<std::string> types = {"Random", "Sorted", "Reversed", "Nearly Sorted"};

    // 결과 테이블 헤더 출력
    std::cout << std::left << std::setw(16) << "| Type"
              << std::setw(12) << "| Size"
              << std::setw(20) << "| Insertion Sort (ms)"
              << std::setw(16) << "| Merge Sort (ms)"
              << std::setw(16) << "| Quick Sort (ms)"
              << "|" << std::endl;
    std::cout << std::string(82, '-') << std::endl;


    for (const std::string& type : types) {
        for (int size : sizes) {
            std::vector<int> original_arr;
            if (type == "Random") original_arr = generate_random_array(size);
            else if (type == "Sorted") original_arr = generate_sorted_array(size);
            else if (type == "Reversed") original_arr = generate_reversed_array(size);
            else if (type == "Nearly Sorted") original_arr = generate_nearly_sorted_array(size);
            
            std::cout << "| " << std::left << std::setw(14) << type
                      << "| " << std::setw(10) << size;

            // --- Insertion Sort 측정 ---
            // 매우 느릴 수 있으므로 10만개 이상에서는 주의
            if (size > 50000 && (type == "Random" || type == "Reversed")) {
                 std::cout << "| " << std::right << std::setw(18) << "skipped ";
            } else {
                std::vector<int> arr_copy = original_arr;
                auto start = std::chrono::high_resolution_clock::now();
                insertion_sort(arr_copy);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                std::cout << "| " << std::right << std::setw(18) << duration.count() << " ";
            }

            // --- Merge Sort 측정 ---
            std::vector<int> arr_copy_merge = original_arr;
            auto start_merge = std::chrono::high_resolution_clock::now();
            merge_sort(arr_copy_merge, 0, arr_copy_merge.size() - 1);
            auto end_merge = std::chrono::high_resolution_clock::now();
            auto duration_merge = std::chrono::duration_cast<std::chrono::milliseconds>(end_merge - start_merge);
            std::cout << "| " << std::right << std::setw(14) << duration_merge.count() << " ";

            // --- Quick Sort 측정 ---
            // 정렬/역순 배열에서 매우 느릴 수 있음
            if (size > 50000 && (type == "Sorted" || type == "Reversed")) {
                 std::cout << "| " << std::right << std::setw(14) << "skipped " << "|"<< std::endl;
                 continue;
            }
            std::vector<int> arr_copy_quick = original_arr;
            auto start_quick = std::chrono::high_resolution_clock::now();
            quick_sort(arr_copy_quick, 0, arr_copy_quick.size() - 1);
            auto end_quick = std::chrono::high_resolution_clock::now();
            auto duration_quick = std::chrono::duration_cast<std::chrono::milliseconds>(end_quick - start_quick);
            std::cout << "| " << std::right << std::setw(14) << duration_quick.count() << " |" << std::endl;
        }
    }

    return 0;
}