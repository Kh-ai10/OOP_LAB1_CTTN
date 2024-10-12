#include <iostream>
#include <algorithm>   
#include <cstring>      
#include <iomanip>
using namespace std;

struct Ngay {
    int ngay;
    int thang;
    int nam;
};


struct Gio {
    int gio;
    int phut;
};


struct ChuyenBay {
    char machuyenbay[6];
    Ngay d_khoihanh;
    Gio h_khoihanh;
    char di[21];             // gồm NULL, nên là 21
    char den[21];
};


bool namnhuan(int nam) {
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}


int ngay_trongthang(int thang, int nam) {
    int thangco_ngay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (namnhuan(nam)) 
        thangco_ngay[1] = 29;
    
    return thangco_ngay[thang - 1];
}


bool ktra_machuyenbay(const char* ma) {
    if (strlen(ma) > 5) return false;
    for (int i = 0; ma[i] != '\0'; ++i) 
        if (!((ma[i] >= 'A' && ma[i] <= 'Z') || (ma[i] >= 'a' && ma[i] <= 'z') || (ma[i] >= '0' && ma[i] <= '9'))) 
            return false;
      
    return true;
}


bool ktra_ngay(const Ngay& ngay_thang_nam) {
    if (ngay_thang_nam.nam < 1 || ngay_thang_nam.thang < 1 || ngay_thang_nam.thang > 12) return false;
    return ngay_thang_nam.ngay >= 1 && ngay_thang_nam.ngay <= ngay_trongthang(ngay_thang_nam.thang, ngay_thang_nam.nam);
}


bool ktra_gio(int gio, int phut) {
    return gio >= 0 && gio < 24 && phut >= 0 && phut < 60;
}


bool ktra_dd(const char* dd) {
    if (strlen(dd) > 20) return false;

    for (int i = 0; dd[i] != '\0'; ++i) 
        if (!((dd[i] >= 'A' && dd[i] <= 'Z') || (dd[i] >= 'a' && dd[i] <= 'z') || dd[i] == ' ')) 
            return false;
        
    return true;
}


ChuyenBay Nhap() {
    ChuyenBay cb;

    bool kiemTra;
    do {
        cout << "\t-Nhap ma chuyen bay (toi da 5 ky tu): ";
        cin >> cb.machuyenbay;
        kiemTra = ktra_machuyenbay(cb.machuyenbay);
        if (!kiemTra) {
            cout << "Ma chuyen bay khong hop le. Vui long nhap lai.\n";
        }
    } while (!kiemTra);

    do {
        cout << "\t-Nhap ngay khoi hanh theo dinh dang (dd/mm/yyyy): ";
        char ngay_[11]; // Tính cả NULL
        cin >> ngay_;
        sscanf(ngay_, "%d/%d/%d", &cb.d_khoihanh.ngay, &cb.d_khoihanh.thang, &cb.d_khoihanh.nam);
        kiemTra = ktra_ngay(cb.d_khoihanh);
        if (!kiemTra) {
            cout << "Ngay khong hop le. Vui long nhap lai.\n";
        }
    } while (!kiemTra);

    do {
        cout << "\t-Nhap gio khoi hanh theo dinh dang (HH:MM, 24h): ";
        char gio_[6]; // Tính cả NULL
        cin >> gio_;
        sscanf(gio_, "%d:%d", &cb.h_khoihanh.gio, &cb.h_khoihanh.phut);
        kiemTra = ktra_gio(cb.h_khoihanh.gio, cb.h_khoihanh.phut);
        if (!kiemTra) {
            cout << "Gio khong hop le. Vui long nhap lai.\n";
        }
    } while (!kiemTra);

    do {
        cout << "\t-Nhap noi di (toi da 20 ky tu): ";
        cin.ignore();
        cin.getline(cb.di, 21);      // Bỏ qua khoảng trắng
        kiemTra = ktra_dd(cb.di);
        if (!kiemTra) {
            cout << "Noi di khong hop le. Vui long nhap lai.\n";
        }
    } while (!kiemTra);

    do {
        cout << "\t-Nhap noi den (toi da 20 ky tu): ";
        cin.getline(cb.den, 21);
        kiemTra = ktra_dd(cb.den);
        if (!kiemTra) {
            cout << "Noi den khong hop le. Vui long nhap lai.\n";
        }
    } while (!kiemTra);

    return cb;
}


void Xuat(const ChuyenBay& cb) {
    cout << "| " << setw(6) << left << cb.machuyenbay 
         << "| " << setw(11) << left << (cb.d_khoihanh.ngay < 10 ? "0" : "") + to_string(cb.d_khoihanh.ngay) + "/" + 
         (cb.d_khoihanh.thang < 10 ? "0" : "") + to_string(cb.d_khoihanh.thang) + "/" + to_string(cb.d_khoihanh.nam)
         << "| " << setw(4) << left << (cb.h_khoihanh.gio < 10 ? "0" : "") + to_string(cb.h_khoihanh.gio) + ":" + 
         (cb.h_khoihanh.phut < 10 ? "0" : "") + to_string(cb.h_khoihanh.phut)
         << "| " << setw(20) << left << cb.di
         << "| " << setw(20) << left << cb.den << "|\n";
}


bool sosanh(const ChuyenBay& a, const ChuyenBay& b) {
    if (a.d_khoihanh.nam != b.d_khoihanh.nam)
        return a.d_khoihanh.nam < b.d_khoihanh.nam;
    if (a.d_khoihanh.thang != b.d_khoihanh.thang)
        return a.d_khoihanh.thang < b.d_khoihanh.thang;
    if (a.d_khoihanh.ngay != b.d_khoihanh.ngay)
        return a.d_khoihanh.ngay < b.d_khoihanh.ngay;
    if (a.h_khoihanh.gio != b.h_khoihanh.gio)
        return a.h_khoihanh.gio < b.h_khoihanh.gio;
    return a.h_khoihanh.phut < b.h_khoihanh.phut;
}


void Tim_theo_ma(ChuyenBay* ds, int n, const char* machuyenbay) {
    bool timThay = false;

    cout << "\nKET QUA TIM KIEM THEO MA CHUYEN BAY:\n";
    cout << "+-------+------------+------+---------------------+---------------------+\n";
    cout << "| Ma CB |    Ngay    | Gio  | Noi Di              | Noi Den             |\n";
    cout << "+-------+------------+------+---------------------+---------------------+\n";

    for (int i = 0; i < n; ++i) {
        if (strcmp(ds[i].machuyenbay, machuyenbay) == 0) {
            timThay = true;
            Xuat(ds[i]);
        }
    }

    cout << "+-------+------------+------+---------------------+---------------------+\n";

    if (!timThay) {
        cout << "(!) Khong tim thay chuyen bay nao phu hop.\n";
    }
}


void Tim_theo_noi_di(ChuyenBay* ds, int n, const char* di) {
    bool timThay = false;

    cout << "\nKET QUA TIM KIEM THEO NOI DI:\n";
    cout << "+-------+------------+------+---------------------+---------------------+\n";
    cout << "| Ma CB |    Ngay    | Gio  | Noi Di              | Noi Den             |\n";
    cout << "+-------+------------+------+---------------------+---------------------+\n";

    for (int i = 0; i < n; ++i) {
        if (strcmp(ds[i].di, di) == 0) {
            timThay = true;
            Xuat(ds[i]);
        }
    }

    cout << "+-------+------------+------+---------------------+---------------------+\n";

    if (!timThay) {
        cout << "(!) Khong tim thay chuyen bay nao phu hop.\n";
    }
}


void Tim_theo_noi_den(ChuyenBay* ds, int n, const char* den) {
    bool timThay = false;

    cout << "\nKET QUA TIM KIEM THEO NOI DEN:\n";
    cout << "+-------+------------+------+---------------------+---------------------+\n";
    cout << "| Ma CB |    Ngay    | Gio  | Noi Di              | Noi Den             |\n";
    cout << "+-------+------------+------+---------------------+---------------------+\n";

    for (int i = 0; i < n; ++i) {
        if (strcmp(ds[i].den, den) == 0) {
            timThay = true;
            Xuat(ds[i]);
        }
    }

    cout << "+-------+------------+------+---------------------+---------------------+\n";

    if (!timThay) {
        cout << "(!) Khong tim thay chuyen bay nao phu hop.\n";
    }
}


void Liet_ke(const ChuyenBay* ds, int soluong, const char* di, const Ngay& ngay) {
    bool timThay = false;

    cout << "\nKET QUA TIM KIEM THEO NOI KHOI HANH VA NGAY KHOI HANH:\n";
    cout << "+-------+------------+------+---------------------+---------------------+\n";
    cout << "| Ma CB |    Ngay    | Gio  | Noi Di              | Noi Den             |\n";
    cout << "+-------+------------+------+---------------------+---------------------+\n";

    for (int i = 0; i < soluong; ++i) {
        if (strcmp(ds[i].di, di) == 0 &&
            ds[i].d_khoihanh.ngay == ngay.ngay &&
            ds[i].d_khoihanh.thang == ngay.thang &&
            ds[i].d_khoihanh.nam == ngay.nam) {
            Xuat(ds[i]);
            cout << "+-------+------------+------+---------------------+---------------------+\n";
            timThay = true;
            
        }
    }
    if (!timThay) cout << "(!) Khong co chuyen bay nao khoi hanh tu " << di << " vao ngay " << ngay.ngay << "/" << ngay.thang << "/" << ngay.nam << ".\n";
}


int demChuyenBay(const ChuyenBay* ds, int soluong, const char* di, const char* den) {
    int dem = 0;
    for (int i = 0; i < soluong; ++i) {
        if (strcmp(ds[i].di, di) == 0 && strcmp(ds[i].den, den) == 0) {
            dem++;
        }
    }
    return dem;
}


void CHON() {
    cout << "\n~~%~ CHUONG TRINH QUAN LY CHUYEN BAY CUA ZKHAI ~%~~\n";
    cout << "1. Hien thi cac lua chon\n";
    cout << "2. Nhap thong tin cho cac chuyen bay\n";
    cout << "3. Xuat danh sach cac chuyen bay\n";
    cout << "4. Tim kiem chuyen bay theo ma chuyen bay\n";
    cout << "5. Tim kiem chuyen bay theo noi di\n";
    cout << "6. Tim kiem chuyen bay theo noi den\n";
    cout << "7. Liet ke chuyen bay theo noi di va ngay\n";
    cout << "8. Dem chuyen bay theo noi di va noi den\n";
    cout << "9. Ket thuc chuong trinh\n";
}


int main() {
    ChuyenBay* danhsach = nullptr;
    
    int soluong = 0;
    int luaChon;

    CHON();

    do {
        cout << "\nVui long chon so: "; 
        cin >> luaChon;

        switch (luaChon)
        {

        case 1: {
            CHON();
            break;
        }

        case 2: {
            cout << "Nhap so luong chuyen bay: ";
            while (true) {
                cin >> soluong;
                if (soluong > 0) break;
                else 
                    cout << "So luong chuyen bay phai lon hon 0. Vui long nhap lai: ";
            }

            danhsach = new ChuyenBay[soluong];
            for (int i = 0; i < soluong; ++i) {
                    cout << "\nNhap thong tin chuyen bay " << (i + 1) << ":\n";
                    danhsach[i] = Nhap();
            }

            sort(danhsach, danhsach + soluong, sosanh);
            break;
        }

        case 3: {
            cout << "\nDANH SACH CHUYEN BAY:\n";
            cout << "+-------+------------+------+---------------------+---------------------+\n";
            cout << "| Ma CB |    Ngay    | Gio  | Noi Di              | Noi Den             |\n";
            cout << "+-------+------------+------+---------------------+---------------------+\n";

            for (int i = 0; i < soluong; ++i) {
                Xuat(danhsach[i]);
                cout << "+-------+------------+------+---------------------+---------------------+\n";
            }
            break;
        }

        case 4: {
            char machuyenbay[6];
            while (true) {
                cout << "Nhap ma chuyen bay can tim: ";
                cin >> machuyenbay;

                if (!ktra_machuyenbay(machuyenbay)) {
                    cout << "Ma chuyen bay khong hop le. Vui long nhap lai.\n";
                } else {
                    Tim_theo_ma(danhsach, soluong, machuyenbay);
                    break;  
                }
            }
            break;
        }

        case 5: {
            char di[21];
            while (true) {
                cout << "Nhap noi di: ";
                cin.ignore();
                cin.getline(di, 21);

                if (!ktra_dd(di)) {
                    cout << "Noi di khong hop le. Vui long nhap lai.\n";
                } else {
                    Tim_theo_noi_di(danhsach, soluong, di);
                    break;  
                }
            }
            break;
        }

        case 6: {
            char den[21];
            while (true) {
                cout << "Nhap noi den: ";
                cin.ignore();
                cin.getline(den, 21);

                if (!ktra_dd(den)) {
                    cout << "Noi den khong hop le. Vui long nhap lai.\n";
                } else {
                    Tim_theo_noi_den(danhsach, soluong, den);
                    break;  
                }
            }
            break;
        }

        case 7: {
            char di[21];
            Ngay ngay;
            while (true) {
                cout << "Nhap noi di: ";
                cin.ignore();
                cin.getline(di, 21);

                cout << "Nhap ngay khoi hanh theo dinh dang (dd/mm/yyyy): ";
                char ngay_[11];
                cin >> ngay_;
                sscanf(ngay_, "%d/%d/%d", &ngay.ngay, &ngay.thang, &ngay.nam);

                if (!ktra_dd(di)) {
                    cout << "Noi di khong hop le. Vui long nhap lai.\n";
                } else if (!ktra_ngay(ngay)) {
                    cout << "Ngay khong hop le. Vui long nhap lai.\n";
                } else {
                    Liet_ke(danhsach, soluong, di, ngay);
                    break;  
                }
            }
            break;
        }

        case 8: {
            char di[21], den[21];
            while (true) {
                cout << "- Nhap noi di: ";
                cin.ignore();
                cin.getline(di, 21);

                cout << "- Nhap noi den: ";
                cin.getline(den, 21);

                if (!ktra_dd(di) || !ktra_dd(den)) {
                    cout << "Noi di hoac noi den khong hop le. Vui long nhap lai.\n";
                } else {
                    int soChuyenBay = demChuyenBay(danhsach, soluong, di, den);
                    cout << "(+) So chuyen bay tu " << di << " den " << den << " la: " << soChuyenBay << endl;
                    break;  
                }
            }
            break;
        }

        case 9: {
            cout << "Ket thuc chuong trinh. Cam on vi da su dung dich vu.\n";
            break;
        }

        default:
            cout << "Lua chon khong hop le. Vui long chon lai.\n";;
        }
    } while (luaChon != 9);

    delete[] danhsach;

    return 0;
}