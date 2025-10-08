#include <iostream>
#include <vector>

/**
 * @brief 삽입 정렬을 사용하여 벡터를 정렬합니다.
 * @param arr 정렬할 정수 벡터 (참조로 전달되어 직접 수정됨)
 */
void insertion_sort(std::vector<int>& arr) {
    // 벡터의 두 번째 요소(인덱스 1)부터 시작합니다.
    // 첫 번째 요소(인덱스 0)는 이미 정렬된 부분으로 간주합니다.
    for (int i = 1; i < arr.size(); ++i) {
        int key = arr[i]; // 현재 정렬할 요소(key)를 선택합니다.
        int j = i - 1;

        // key를 이미 정렬된 부분(arr[0...i-1])의 올바른 위치에 삽입합니다.
        // key보다 큰 요소들을 한 칸씩 오른쪽으로 이동시킵니다.
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        // 찾은 위치에 key를 삽입합니다.
        arr[j + 1] = key;
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

    // 삽입 정렬 함수 호출
    insertion_sort(data);

    std::cout << "Sorted array:   ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}