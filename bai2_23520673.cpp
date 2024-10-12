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
        cout << "0" << endl; 
    } else if (x.mau == 1) {
        cout  << x.tu << endl; 
    } else {
        cout  << x.tu << "/" << x.mau << endl; 
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

    long long rutgon = __gcd(abs(x.tu), abs(x.mau)); 
    x.tu /= rutgon;
    x.mau /= rutgon;
}

/*Hàm tìm hai phân số lớn nhất
Đầu vào: 2 phân số
Đầu ra: Phân số lớn hơn
Thực thi: Quy đồng và so sánh tử
*/ 
Phanso PhanSoLonNhat(const Phanso &x, const Phanso &y) {
    if (x.tu * y.mau > y.tu * x.mau) {
        return x;
    } else if (x.tu * y.mau < y.tu * x.mau) {
        return y;
    } else {
        // Trả về một phân số bằng nhau (có thể là x hoặc y)
        return x; 
    }
}

int main() {
    Phanso x, y;
    Nhap(x);
    Rutgon(x);

    Nhap(y);
    Rutgon(y);

    // Kiem tra mau
    if (x.mau == 0 || y.mau == 0) {
        cout << "Khong so sanh duoc vi co phan so khong ton tai" << endl; 
    } else {
        //Truong hop hai phan so bang nhau
        Phanso psln = PhanSoLonNhat(x, y);
        if (x.tu * y.mau == y.tu * x.mau) {
            cout << "Hai phan so bang nhau: ";
            Xuat(x);
        } else {
            cout << "Phan so lon nhat: ";
            Xuat(psln);
        }
    }

    return 0;
}
