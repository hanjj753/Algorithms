#include <iostream>
#include <vector>
#include <utility> // std::swap을 위해 필요

// 피벗을 기준으로 배열을 분할하고 피벗의 최종 위치를 반환하는 헬퍼 함수
int partition(std::vector<int>& arr, int low, int high) {
    // 가장 오른쪽 요소를 피벗으로 선택
    int pivot = arr[high];
    int i = (low - 1); // 피벗보다 작은 요소들의 마지막 인덱스

    for (int j = low; j < high; ++j) {
        // 현재 요소가 피벗보다 작거나 같으면
        if (arr[j] <= pivot) {
            i++; // 작은 요소 영역을 확장하고
            std::swap(arr[i], arr[j]); // 현재 요소를 해당 영역으로 이동
        }
    }
    // 마지막으로 피벗을 올바른 위치(i+1)로 이동
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

/**
 * @brief 퀵 정렬을 사용하여 벡터를 정렬합니다. (재귀 호출)
 * @param arr 정렬할 정수 벡터
 * @param low 시작 인덱스
 * @param high 끝 인덱스
 */
void quick_sort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // 분할 작업을 수행하고 피벗의 위치(pi)를 얻음
        int pi = partition(arr, low, high);

        // 피벗을 기준으로 좌우 하위 배열을 재귀적으로 정렬
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// 프로그램 실행을 위한 main 함수
int main() {
    std::vector<int> data = {8, 2, 7, 3, 9, 1, 5, 4, 6, 0};

    std::cout << "Original array: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 퀵 정렬 함수 호출 (초기 호출)
    quick_sort(data, 0, data.size() - 1);

    std::cout << "Sorted array:   ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}