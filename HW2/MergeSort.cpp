#include <iostream>
#include <vector>

// 두 개의 정렬된 하위 벡터를 병합하는 헬퍼 함수
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 임시 벡터 생성
    std::vector<int> L(n1), R(n2);

    // 데이터를 임시 벡터 L과 R에 복사
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    // 임시 벡터들을 다시 원래 벡터(arr)에 병합
    int i = 0; // L의 초기 인덱스
    int j = 0; // R의 초기 인덱스
    int k = left; // 병합될 벡터(arr)의 초기 인덱스

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // L 또는 R에 남아있는 요소들을 복사
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * @brief 병합 정렬을 사용하여 벡터를 정렬합니다. (재귀 호출)
 * @param arr 정렬할 정수 벡터
 * @param left 시작 인덱스
 * @param right 끝 인덱스
 */
void merge_sort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        // 중간 지점을 계산하여 배열을 두 부분으로 나눔
        int mid = left + (right - left) / 2;

        // 각 부분을 재귀적으로 정렬
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        // 정렬된 두 부분을 병합
        merge(arr, left, mid, right);
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

    // 병합 정렬 함수 호출 (초기 호출)
    merge_sort(data, 0, data.size() - 1);

    std::cout << "Sorted array:   ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}