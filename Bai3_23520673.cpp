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
        cout << "Khong thuc hien duoc vi co phan so khong ton tai" << endl; 
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

// Ham cong hai phan so
Phanso Cong(const Phanso &x, const Phanso &y) {
    Phanso ketqua;
    ketqua.tu = x.tu * y.mau + y.tu * x.mau; // Tinh tu
    ketqua.mau = x.mau * y.mau; // Tinh mau
    Rutgon(ketqua); // Rut gon
    return ketqua;
}

// Ham tru hai phan so
Phanso Tru(const Phanso &x, const Phanso &y) {
    Phanso ketqua;
    ketqua.tu = x.tu * y.mau - y.tu * x.mau; // Tinh tu
    ketqua.mau = x.mau * y.mau; // Tinh mau
    Rutgon(ketqua); // Rut gon
    return ketqua;
}

// Ham nhan hai phan so
Phanso Nhan(const Phanso &x, const Phanso &y) {
    Phanso ketqua;
    ketqua.tu = x.tu * y.tu; // Tinh tu
    ketqua.mau = x.mau * y.mau; // Tinh mau
    Rutgon(ketqua); // Rut gon
    return ketqua;
}

// Ham chia hai phan so
Phanso Chia(const Phanso &x, const Phanso &y) {
    Phanso ketqua;
    // Kiem tra phan so thu hai co bang 0?
    if (y.tu == 0) {
        cout << "Khong the chia cho phan so bang 0" << endl;
        ketqua.tu = 0;
        ketqua.mau = 0;
        return ketqua;
    }
    ketqua.tu = x.tu * y.mau; // Tinh tu
    ketqua.mau = x.mau * y.tu; // Tinh mau
    Rutgon(ketqua); // Rut gon
    return ketqua;
}

int main() {
    Phanso x, y;
    Nhap(x);
    Rutgon(x);

    Nhap(y);
    Rutgon(y);

    // Xuat ket qua
    Phanso tong = Cong(x, y);
    cout << "Tong: ";
    Xuat(tong);

    Phanso hieu = Tru(x, y);
    cout << "Hieu: ";
    Xuat(hieu);

    Phanso tich = Nhan(x, y);
    cout << "Tich: ";
    Xuat(tich);

    Phanso thuong = Chia(x, y);
    if (y.tu != 0) {
        cout << "Thuong: ";
        Xuat(thuong);
    }

    return 0;
}
