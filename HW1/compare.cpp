#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>   // 시간 측정을 위한 헤더
#include <random>   // 임의의 숫자 생성을 위한 헤더
#include <stdexcept>

// --- 이전에 작성한 곱셈 함수 및 헬퍼 함수들을 여기에 붙여넣으세요 ---

// 헬퍼 함수: add, subtract
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

std::string subtract(std::string num1, std::string num2) {
    std::string str = "";
    int i = num1.length() - 1, j = num2.length() - 1, borrow = 0;
    while (j >= 0) {
        int sub = (num1[i] - '0') - (num2[j] - '0') - borrow;
        if (sub < 0) { sub += 10; borrow = 1; } else { borrow = 0; }
        str.push_back(sub + '0');
        i--; j--;
    }
    while (i >= 0) {
        int sub = (num1[i] - '0') - borrow;
        if (sub < 0) { sub += 10; borrow = 1; } else { borrow = 0; }
        str.push_back(sub + '0');
        i--;
    }
    std::reverse(str.begin(), str.end());
    size_t startpos = str.find_first_not_of('0');
    if (std::string::npos != startpos) { return str.substr(startpos); }
    return "0";
}


// 기본 곱셈 함수
std::string basic_multiply(std::string x, std::string y) {
    if (x == "0" || y == "0") return "0";
    std::string result(x.length() + y.length(), '0');
    for (int i = x.length() - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = y.length() - 1; j >= 0; j--) {
            int p = (x[i] - '0') * (y[j] - '0') + (result[i + j + 1] - '0') + carry;
            result[i + j + 1] = (p % 10) + '0';
            carry = p / 10;
        }
        result[i] += carry;
    }
    size_t startpos = result.find_first_not_of('0');
    if (std::string::npos != startpos) return result.substr(startpos);
    return "0";
}


// 카라츠바 곱셈 함수
std::string karatsuba_multiply(std::string x, std::string y) {
    int n = std::max(x.length(), y.length());
    while (x.length() < n) x.insert(0, "0");
    while (y.length() < n) y.insert(0, "0");
    if (n <= 4) { return std::to_string(std::stoll(x) * std::stoll(y)); }

    int half = n / 2;
    std::string a = x.substr(0, n - half);
    std::string b = x.substr(n - half);
    std::string c = y.substr(0, n - half);
    std::string d = y.substr(n - half);

    std::string z2 = karatsuba_multiply(a, c);
    std::string z0 = karatsuba_multiply(b, d);
    std::string z1 = karatsuba_multiply(add(a, b), add(c, d));
    std::string middle_term = subtract(subtract(z1, z2), z0);

    for (int i = 0; i < 2 * half; i++) z2.append("0");
    for (int i = 0; i < half; i++) middle_term.append("0");

    std::string result = add(add(z2, middle_term), z0);
    size_t startpos = result.find_first_not_of('0');
    if (std::string::npos != startpos) return result.substr(startpos);
    return "0";
}

// --- 성능 측정 관련 함수들 ---

/**
 * @brief 지정된 길이의 랜덤한 숫자 문자열을 생성합니다.
 * @param length 생성할 문자열의 길이
 * @return 랜덤 숫자 문자열
 */
std::string generate_random_number_string(int length) {
    if (length <= 0) return "0";
    
    // C++11 이상에서 권장되는 랜덤 생성 방식
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 9);

    std::string result = "";
    // 첫 자리는 0이 아니도록 함 (1~9)
    result += std::to_string(distrib(gen) % 9 + 1);

    for (int i = 1; i < length; ++i) {
        result += std::to_string(distrib(gen));
    }
    return result;
}

int main() {
    // 테스트할 자릿수 목록
    std::vector<int> digit_lengths = {10, 20, 50, 100, 200, 400, 800, 1600, 3200, 6400};

    // CSV 헤더 출력
    std::cout << "Digits,Basic_Time_us,Karatsuba_Time_us" << std::endl;

    for (int len : digit_lengths) {
        std::cout << len << ",";

        // 테스트를 위한 랜덤 숫자 생성
        std::string num1 = generate_random_number_string(len);
        std::string num2 = generate_random_number_string(len);
        
        // --- 기본 곱셈 시간 측정 ---
        // 자릿수가 너무 커지면 basic_multiply는 매우 느려지므로 특정 자릿수 이상에서는 스킵
        if (len > 10000) {
             std::cout << "skipped,";
        } else {
            auto start_basic = std::chrono::steady_clock::now();
            basic_multiply(num1, num2);
            auto end_basic = std::chrono::steady_clock::now();
            auto diff_basic = std::chrono::duration_cast<std::chrono::microseconds>(end_basic - start_basic);
            std::cout << diff_basic.count() << ",";
        }

        // --- 카라츠바 곱셈 시간 측정 ---
        auto start_kara = std::chrono::steady_clock::now();
        karatsuba_multiply(num1, num2);
        auto end_kara = std::chrono::steady_clock::now();
        auto diff_kara = std::chrono::duration_cast<std::chrono::microseconds>(end_kara - start_kara);
        std::cout << diff_kara.count() << std::endl;
    }

    return 0;
}