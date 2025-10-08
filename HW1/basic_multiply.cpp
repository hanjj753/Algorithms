#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

/**
 * @brief 전통적인 초등학교 곱셈 알고리즘을 구현합니다.
 * @param x 첫 번째 큰 정수 (문자열)
 * @param y 두 번째 큰 정수 (문자열)
 * @return x * y의 결과 (문자열)
 */

std::string basic_multiply(std::string x, std::string y) {
    if (x == "0" || y == "0") {
        return "0";
    }

    // 결과의 최대 길이는 두 숫자의 길이의 합과 같습니다.
    // 그 길이 만큼을 0으로 채워서 result를 초기화함. ex) 123 *  45 => 00000 (5자리)
    std::string result(x.length() + y.length(), '0');

    // 뒤에서부터(오른쪽부터) 계산을 시작합니다.
    for (int i = x.length() - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = y.length() - 1; j >= 0; j--) {
            // 현재 자릿수의 숫자들을 곱하고, 이전 계산의 carry와 현재 위치의 값을 더합니다.
            // x[i]와 y[j]는 문자이므로 '0'을 빼서 정수로 변환합니다. ex) '5' - '0' = 5
            // result에서 i+j+1인 이유는, 123 * 45에서 3 * 5를 한다고 할 때, (3-1)번째, (2-1)번째 이므로 (5-1)번째 자리는 ((3-1)+(2-1)+1)임.
            int p = (x[i] - '0') * (y[j] - '0') + (result[i + j + 1] - '0') + carry;
            result[i + j + 1] = (p % 10) + '0'; // 현재 자릿수 갱신
            carry = p / 10;                     // 다음 자릿수로 넘길 carry 계산
        }
        result[i] += carry; // 마지막 carry를 더해줍니다.
    }

    // 결과 문자열 앞부분의 불필요한 '0'을 제거합니다.
    size_t startpos = result.find_first_not_of('0');
    if (std::string::npos != startpos) {
        return result.substr(startpos);
    }

    return "0";
}

int main() {
    std::string x = "123456789123456789";
    std::string y = "987654321987654321";

    std::cout << "Input 1: " << x << std::endl;
    std::cout << "Input 2: " << y << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Basic Multiply Result: " << basic_multiply(x, y) << std::endl;

    return 0;
}