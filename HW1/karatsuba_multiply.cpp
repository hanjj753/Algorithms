#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

// 헬퍼 함수 선언
std::string add(std::string num1, std::string num2);
std::string subtract(std::string num1, std::string num2);

/**
 * @brief 카라츠바의 분할 정복 곱셈 알고리즘을 구현합니다.
 * @param x 첫 번째 큰 정수 (문자열)
 * @param y 두 번째 큰 정수 (문자열)
 * @return x * y의 결과 (문자열)
 */

std::string karatsuba_multiply(std::string x, std::string y) {
    // 두 숫자의 길이를 맞추기 위해 짧은 쪽에 '0'을 채웁니다.
    int n = std::max(x.length(), y.length());
    while (x.length() < n) x.insert(0, "0");
    while (y.length() < n) y.insert(0, "0");

    // 기본 단계 (Base case): 숫자가 충분히 작으면 기본 곱셈으로 처리합니다.
    if (n <= 4) {
        return std::to_string(std::stoll(x) * std::stoll(y));
    }

    // 숫자를 반으로 나눕니다.
    int half = n / 2;
    std::string a = x.substr(0, n - half);
    std::string b = x.substr(n - half);
    std::string c = y.substr(0, n - half);
    std::string d = y.substr(n - half);

    // 3번의 재귀적 곱셈
    std::string z2 = karatsuba_multiply(a, c);
    std::string z0 = karatsuba_multiply(b, d);
    std::string z1 = karatsuba_multiply(add(a, b), add(c, d));

    // z1 - z2 - z0 계산
    std::string middle_term = subtract(subtract(z1, z2), z0);

    // 최종 결과 조합: z2 * 10^(2*half) + (z1-z2-z0) * 10^half + z0
    for (int i = 0; i < 2 * half; i++) z2.append("0");
    for (int i = 0; i < half; i++) middle_term.append("0");

    std::string result = add(add(z2, middle_term), z0);
    
    // 결과 문자열 앞부분의 불필요한 '0'을 제거
    size_t startpos = result.find_first_not_of('0');
    if (std::string::npos != startpos) {
        return result.substr(startpos);
    }
    
    return "0";
}

// --- 헬퍼 함수 구현 ---

// 두 문자열 숫자를 더하는 함수
std::string add(std::string num1, std::string num2) {
    std::string str = "";
    int i = num1.length() - 1, j = num2.length() - 1, carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry + (i >= 0 ? num1[i--] - '0' : 0) + (j >= 0 ? num2[j--] - '0' : 0);
        str.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    std::reverse(str.begin(), str.end());
    return str;
}

// 두 문자열 숫자를 빼는 함수 (num1 >= num2 라고 가정)
std::string subtract(std::string num1, std::string num2) {
    std::string str = "";
    int i = num1.length() - 1, j = num2.length() - 1, borrow = 0;
    while (j >= 0) {
        int sub = (num1[i] - '0') - (num2[j] - '0') - borrow;
        if (sub < 0) {
            sub += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        str.push_back(sub + '0');
        i--;
        j--;
    }
    while (i >= 0) {
        int sub = (num1[i] - '0') - borrow;
        if (sub < 0) {
            sub += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        str.push_back(sub + '0');
        i--;
    }
    std::reverse(str.begin(), str.end());
    // 앞쪽의 0 제거
    size_t startpos = str.find_first_not_of('0');
    if (std::string::npos != startpos) {
        return str.substr(startpos);
    }
    return "0";
}

int main() {
    std::string x = "123456789123456789";
    std::string y = "987654321987654321";

    std::cout << "Input 1: " << x << std::endl;
    std::cout << "Input 2: " << y << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Karatsuba Multiply Result: " << karatsuba_multiply(x, y) << std::endl;

    return 0;
}