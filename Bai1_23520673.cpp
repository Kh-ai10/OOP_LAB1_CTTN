#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

struct Phanso {
    long long tu, mau;
};

// Hàm nhập phân số
void Nhap(Phanso &x) {
    cout << "Nhap tu so: ";
    cin >> x.tu;
    cout << "Nhap mau so: ";
    cin >> x.mau;
}

// Hàm xuất phân số
void Xuat(const Phanso &x) {
    if (x.mau == 0) {
        cout << "Khong ton tai phan so" << endl; 
    } else if (x.tu == 0) {
        cout << "Phan so sau khi rut gon: 0" << endl; 
    } else if (x.mau == 1) {
        cout << "Phan so sau khi rut gon: " << x.tu << endl; 
    } else {
        cout << "Phan so sau khi rut gon: " << x.tu << "/" << x.mau << endl; 
    }
}

/*Hàm rút gọn phân số
Đầu vào: Tử và mẫu của 1 phân số.
Đầu ra: Phân số đã được rút gọn.
Thực thi: Chia tử và mẫu cho UCLN của chúng đến khi không chia được nữa.
*/ 
void Rutgon(Phanso &x) {
    if (x.mau == 0) {
        return; 
    }

    if (x.mau < 0) { 
        x.tu = -x.tu; 
        x.mau = -x.mau; 
    }

    int rutgon = __gcd(abs(x.tu), abs(x.mau)); 
    x.tu /= rutgon;
    x.mau /= rutgon;
}

int main() {
    Phanso x;
    Nhap(x);
    Rutgon(x);
    Xuat(x);

    return 0;
}
