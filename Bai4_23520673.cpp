#include <iostream>
#include <cmath>

#define EPSILON 0.00001
#define PI 3.14159265358979323846

double xu_li(double x) {
    // Giảm x về khoảng [0, 2π]
    x = fmod(x, 2 * PI);
    if (x < 0) {
        x += 2 * PI; // Đưa về khoảng dương
    }

    double tam = x; // Khởi tạo giá trị đầu tiên của chuỗi Taylor
    double tong = x;  // Khởi tạo tổng với giá trị đầu tiên
    int n = 1;       // Biến đếm số hạng

    while (fabs(tam) >= EPSILON) {
        tam *= -x * x / (2 * n * (2 * n + 1)); // Tính số hạng tiếp theo
        tong += tam; // Cộng số hạng vào tổng
        n++;
    }

    return tong;
}

int main() {
    double x;
    std::cout << "Nhap gia tri x (radian): ";
    std::cin >> x;

    double kqua = xu_li(x);
    std::cout << "Gia tri sin(" << x << ") = " << kqua << std::endl;

    return 0;
}
