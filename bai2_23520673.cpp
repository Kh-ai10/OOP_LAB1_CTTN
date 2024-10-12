#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

struct Phanso {
    long long tu, mau;
};

// Ham nhap phan so
void Nhap(Phanso &x) {
    cout << "Nhap tu so: ";
    cin >> x.tu;
    cout << "Nhap mau so: ";
    cin >> x.mau;
}

// Ham xuat phan so
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

// Ham rut gon phan so
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

// Ham tim phan so lon nhat
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
