#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;

struct Sotietkiem {
    string maso;
    string phanloai_tk;
    string hoten;
    string CMND;
    string ngay_mo_so;
    double tien_gui;
    int ki_han; // Kì hạn gửi tiết kiệm (tháng)
};



#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

using namespace std;

/*Tính số ngày giữa 2 ngày 
Đầu vào: ngày cần tính theo định dạng dd/mm/yyyy
         ngày hiện tại (theo thời gian thật ngoài đời): dd/mm/yyyy
Đầu ra: Số ngày giữa 2 mốc thời gian trên
Hàm mktime() trong thư viện <ctime> cho phép ta truy xuất số giây của mốc thời gian
*/
int tinhSoNgay(const string& ngay_mo_so) {
    //dd/mm/yyyy
    int day, month, year;
    sscanf(ngay_mo_so.c_str(), "%d/%d/%d", &day, &month, &year);
    
    // Tạo cấu trúc tm cho ngày mở sổ
    tm moSo = {};
    moSo.tm_mday = day;
    moSo.tm_mon = month - 1;  // Tháng trong tm bắt đầu từ 0
    moSo.tm_year = year - 1900;  // Năm trong tm tính từ 1900

    // Chuyển về time_t
    time_t t1 = mktime(&moSo);

    // Lấy ngày hiện tại
    time_t now = time(0);
    tm* today = localtime(&now);
    time_t t2 = mktime(today);

    // Tính khoảng cách giữa hai ngày (đơn vị giây) rồi đổi ra ngày
    int soNgay = difftime(t2, t1) / (60 * 60 * 24);
    return soNgay;
}

// Định dạng mã sổ
bool ktra_maso(const string& maso) {
    regex pattern("^[A-Za-z0-9]{1,5}$");
    return regex_match(maso, pattern);
}

// Phân loại sổ tiết kiệm
bool phanloai_kihan(const string& loai) {
    if(loai=="ngan han") return true; // <=6
    if(loai == "dai han") return true;// >=6
    if(loai == "khong ky han") return true;
    return false;
}

// Định dạng họ tên
bool ktra_hoten(const string& hoten) {
    regex pattern("^[A-Za-z\\s]{1,30}$");
    return regex_match(hoten, pattern);
}

// Định dạng CMND
bool ktra_CMND(const string& CMND) {
    regex pattern("^\\d{9}|\\d{12}$");
    return regex_match(CMND, pattern);
}

// Kiểm tra năm nhuận
bool namnhuan(int nam) {
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

// Kiểm tra ngày hợp lệ (dd/mm/yyyy)
bool ktra_Ngay(const string& ngay) {
    regex pattern("^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\\d{4}$");
    if (!regex_match(ngay, pattern)) return false;
    if(tinhSoNgay(ngay)<0) return false;
    int day = stoi(ngay.substr(0, 2));
    int month = stoi(ngay.substr(3, 2));
    int year = stoi(ngay.substr(6, 4));

    int ngayTrongThang[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (namnhuan(year)) ngayTrongThang[2] = 29;

    return (day > 0 && day <= ngayTrongThang[month]);
}

// Kiểm tra xem một sổ đã tồn tại chưa
bool ktratrungmaso(const vector<Sotietkiem>& ds, const string& maso) {
    for (const auto& stk : ds) {
        if (stk.maso == maso) {
            return true;
        }
    }
    return false;
}


bool ktraKH(const int ki_han,const string& loai)
{
    if(loai=="ngan han" && ki_han<=6) return true; // <=6
    if(loai =="dai han" && ki_han>=6) return true;// >=6
    if(loai == "khong ky han") return true;
    return false;
}

/* Hàm nhập
Đầu vào: mã sổ, phân loại, họ tên, CMND, ngày mở sổ, số tiền gửi
Đầu ra: Nếu đúng định dạng thì trả về các thuộc tính trên.
*/
Sotietkiem Nhap(const vector<Sotietkiem>& ds) {
    Sotietkiem stk;
    cout << " \t    Nhap ma so: ";
    while (true) {
        cin >> stk.maso;
        if (!ktra_maso(stk.maso)||ktratrungmaso(ds,stk.maso)) {
            cout << "\t(!) Ma so bi trung hoac khong hop le. Nhap lai: ";
        } else {
            break;
        }
    }

    cout << "\t    Nhap loai tiet kiem (ngan han, dai han, khong ky han): ";
    while (true) {
        cin.ignore();
        getline(cin, stk.phanloai_tk);
        if (!phanloai_kihan(stk.phanloai_tk)) {
            cout << "\t(!) Loai tiet kiem khong hop le. Nhap lai: ";
        } else {
            break;
        }
    }

    cout << "\t    Nhap ho ten khach hang: ";
    while (true) {
        getline(cin, stk.hoten);
        if (!ktra_hoten(stk.hoten)) {
            cout << "\t(!) Ho ten khong hop le. Nhap lai: ";
        } else {
            break;
        }
    }

    cout << "\t    Nhap CMND (9 hoac 12 chu so): ";
    while (true) {
        cin >> stk.CMND;
        if (!ktra_CMND(stk.CMND)) {
            cout << "\t(!) CMND khong hop le. Nhap lai: ";
        } else {
            break;
        }
    }

    cout << "\t    Nhap ngay mo so (dd/mm/yyyy): ";
    while (true) {
        cin >> stk.ngay_mo_so;
        if (ktra_Ngay(stk.ngay_mo_so)) break;
        else cout << "\t(!) Ngay khong hop le. Nhap lai: ";
    }

    cout << "\t    Nhap so tien gui VND(so duong): ";
    while (true) {
        cin >> stk.tien_gui;
        if (stk.tien_gui > 0) break;
        else cout << "\t(!) So tien gui phai la so duong. Nhap lai: ";
    }

    cout << "\t    Nhap ky han (thang): ";
    while (true) {
        int kh;
        cin >> kh;
        if (kh <= 0)
        {
            cout << "\t(!) Ky han phai la so duong. Nhap lai: ";
            continue;
        }
        if(ktraKH(kh, stk.phanloai_tk))
            {
                stk.ki_han = kh;
                break;
            }
        else cout << "\t(!) Day la loai so tiet kiem "<<stk.phanloai_tk<<". Vui long nhap lai: ";

    }

    return stk;
}

// Hàm so sánh để sắp xếp danh sách sổ tiết kiệm
bool Sapxep(const Sotietkiem& a, const Sotietkiem& b) {
    // So sánh theo số tiền gửi giảm dần
    if (a.tien_gui != b.tien_gui) {
        return a.tien_gui > b.tien_gui;  // Số tiền gửi giảm dần
    }

    // Tách ngày mở sổ cho a
    int dayA, monthA, yearA;
    sscanf(a.ngay_mo_so.c_str(), "%d/%d/%d", &dayA, &monthA, &yearA);
    tm ngay_mo_soA = {};
    ngay_mo_soA.tm_mday = dayA;
    ngay_mo_soA.tm_mon = monthA - 1;  // Tháng bắt đầu từ 0
    ngay_mo_soA.tm_year = yearA - 1900;  // Năm tính từ 1900

    // Tách ngày mở sổ cho b
    int dayB, monthB, yearB;
    sscanf(b.ngay_mo_so.c_str(), "%d/%d/%d", &dayB, &monthB, &yearB);
    tm ngay_mo_soB = {};
    ngay_mo_soB.tm_mday = dayB;
    ngay_mo_soB.tm_mon = monthB - 1;
    ngay_mo_soB.tm_year = yearB - 1900;

    // So sánh theo ngày mở sổ
    return difftime(mktime(&ngay_mo_soA), mktime(&ngay_mo_soB)) < 0; // Ngày cũ hơn được xếp trước
}

/*Hàm tính lãi
Đầu vào: số ngaỳ từ khi mở sổ, lãi mặc định
Đầu ra: Lãi theo thời gian gửi
*/ 
void tinhlaiSTK(Sotietkiem& stk, double laiSuat) {
    int soNgay = tinhSoNgay(stk.ngay_mo_so);  // Tính số ngày từ khi mở sổ đến hiện tại
    double lai = stk.tien_gui * (laiSuat / 100) * (soNgay / 365.0);  // Công thức tính lãi theo năm
    stk.tien_gui += lai;
    cout << "\t(!) Lai suat tinh theo thoi gian gui la: " << lai << " VND\n";
}

// Hàm xuất các thông tin tương ứng
void Xuat(const Sotietkiem& stk) {
    cout << left << setw(10) << stk.maso
         << setw(15) << stk.phanloai_tk
         << setw(20) << stk.hoten
         << setw(15) << stk.CMND
         << setw(15) << stk.ngay_mo_so
         << setw(15) << stk.tien_gui << "\n";
}

/*Hàm cập nhật lãi
Đầu vào: Danh sách các sổ tiết kiệm, lãi suất ngắn hạn, lãi suất dài hạn
Đầu ra: Tính tiền lãi cho sổ.
*/
void Cap_nhat(vector<Sotietkiem>& ds, double ls_ngan, double ls_dai) {
    for (auto& stk : ds) {
        int soNgay = tinhSoNgay(stk.ngay_mo_so);
        double lai = 0;
        if (stk.ki_han <= 6) {  // Ngắn hạn
            lai = stk.tien_gui * (ls_ngan / 100) * (soNgay / 365.0);
        } else {  // Dài hạn
            lai = stk.tien_gui * (ls_dai / 100) * (soNgay / 365.0);
        }
        stk.tien_gui += lai;
        cout << "\t(!) Tinh lai cho so " << stk.maso << ": " << lai << " VND\n";
    }
}

/*Hàm cho phép người dùng rút tiền từ sổ tiết kiệm
Đầu vào: danh sách các sổ tiết kiệm, số tiền cần rút
Cách hoạt động: Hệ thống sẽ kiểm tra ngày mở sổ, phân loại sổ tiết kiệm, 
                từ đó tính tiền lãi suất tương ứng
                Nếu số tiền muốn rút lớn hơn số tiền hiện có thì không rút được.
                Ngược lại trả về số tiền còn lại trong sổ.
Đầu ra: 
    Nếu không được rút thì trả về: Rút không thành công.
    Nếu được rút thì trả về số tiền rút, lãi, tiền còn trong sổ.
*/ 
void Ruttien(Sotietkiem& stk, double laiSuat, double laiSuatRutTruocHan) {
    double soTienRut;
    cout << "\t(+) Nhap so tien can rut: ";
    cin >> soTienRut;

    if (soTienRut <= 0) {
        cout << "\t(!) So tien rut phai lon hon 0.\n";
        return;
    }

    // Kiểm tra thời gian gửi để tính lãi
    int soNgay = tinhSoNgay(stk.ngay_mo_so);
    bool rutTruocHan = soNgay < (stk.ki_han * 30); // Nếu số ngày đã gửi < Kì hạn

    if (soTienRut > stk.tien_gui) {
        cout << "\t(!) So tien rut lon hon so tien trong so tiet kiem.\n";
    } else {
        // Tính lãi suất
        double lai;
        if (rutTruocHan) {
            lai = stk.tien_gui * (laiSuatRutTruocHan / 100) * (soNgay / 365.0);
            cout << "\t(!) Ban rut tien truoc han, lai suat ap dung la: " << laiSuatRutTruocHan << "%/nam\n";
        } else {
            lai = stk.tien_gui * (laiSuat / 100) * (soNgay / 365.0);
            cout << "\t(!) Ban rut tien dung han, lai suat ap dung la: " << laiSuat << "%/nam\n";
        }

        stk.tien_gui -= soTienRut;  // Rút tiền
        cout << "\t(!) Ban da rut thanh cong: " << soTienRut << " VND\n";
        cout << "    Lai thang duoc tinh la: " << lai << " VND\n";
        cout << "    So du con lai trong so tiet kiem: " << stk.tien_gui << " VND\n";
    }
}

// Hàm tìm kiếm sổ tiết kiệm theo CMND hoặc mã sổ
void timSTK(const vector<Sotietkiem>& ds) {
    string keyword;
    cout << "\t(+) Nhap CMND hoac ma so de tim kiem: ";
    cin.ignore();
    getline(cin, keyword);
    vector<Sotietkiem> res;
    bool timThay = false;
    for (const auto& stk : ds) {
        if (stk.CMND == keyword || stk.maso == keyword) {
            res.push_back(stk);
            timThay = true;
        }
    }

    if (!timThay) {
        cout << "\t(!) Khong tim thay so tiet kiem voi CMND hoac ma so nay.\n";
    }
    else
    {
        cout<<"\n";
        cout<<"\t\t\t        Cac So Tiet Kiem Tim Thay\n";
            cout << string(90, '-') << "\n";
            cout << left << setw(10) << "Ma So"
                 << setw(15) << "Loai"
                 << setw(20) << "Ho Ten"
                 << setw(15) << "CMND"
                 << setw(15) << "Ngay Mo So"
                 << setw(15) << "So Tien (VND)" << "\n";
            cout << string(90, '-') << "\n";

            for (const auto& stk : res) {
                Xuat(stk);
            }
            cout << string(90, '-') << "\n";
    }
}

// Hàm liệt kê sổ tiết kiệm theo khoảng thời gian
void tim_theo_thoigian(const vector<Sotietkiem>& ds) {
    string ngayBatDau, ngayKetThuc;

    while (true) {
        cout << "\t(+) Nhap ngay bat dau (dd/mm/yyyy): ";
        cin >> ngayBatDau;
        cout << "\t    Nhap ngay ket thuc (dd/mm/yyyy): ";
        cin >> ngayKetThuc;

        if (!ktra_Ngay(ngayBatDau) || !ktra_Ngay(ngayKetThuc)) {
            cout << "\t(!) Ngay nhap khong hop le!\n";
            continue;
        }
        break;
    }

    int dayB, monthB, yearB;
    sscanf(ngayBatDau.c_str(), "%d/%d/%d", &dayB, &monthB, &yearB);
    tm dateStart = {0};
    dateStart.tm_mday = dayB;
    dateStart.tm_mon = monthB - 1; // Tháng bắt đầu từ 0
    dateStart.tm_year = yearB - 1900; // Năm tính từ 1900
    time_t tStart = mktime(&dateStart);

    int dayK, monthK, yearK;
    sscanf(ngayKetThuc.c_str(), "%d/%d/%d", &dayK, &monthK, &yearK);
    tm dateEnd = {0};
    dateEnd.tm_mday = dayK;
    dateEnd.tm_mon = monthK - 1;
    dateEnd.tm_year = yearK - 1900;
    time_t tEnd = mktime(&dateEnd);

    bool coSotietkiem = false;
    vector<Sotietkiem> res;

    for (const auto& stk : ds) {
        int dayMS, monthMS, yearMS;
        sscanf(stk.ngay_mo_so.c_str(), "%d/%d/%d", &dayMS, &monthMS, &yearMS);
        tm ngay_mo_so = {0};
        ngay_mo_so.tm_mday = dayMS;
        ngay_mo_so.tm_mon = monthMS - 1;
        ngay_mo_so.tm_year = yearMS - 1900;
        time_t tngay_mo_so = mktime(&ngay_mo_so);

        if (difftime(tngay_mo_so, tStart) >= 0 && difftime(tEnd, tngay_mo_so) >= 0) {
            res.push_back(stk);
            coSotietkiem = true;
        }
    }

    if (!coSotietkiem) {
        cout << "\t(!) Khong co so tiet kiem nao trong khoang thoi gian nay.\n";
    } else {
        cout << "\n";
        cout << "\t\t\t        Cac So Tiet Kiem Tim Thay\n";
        cout << string(90, '-') << "\n";
        cout << left << setw(10) << "Ma So"
             << setw(15) << "Loai"
             << setw(20) << "Ho Ten"
             << setw(15) << "CMND"
             << setw(15) << "Ngay Mo So"
             << setw(15) << "So Tien (VND) " << "\n";
        cout << string(90, '-') << "\n";

        for (const auto& stk : res) {
            Xuat(stk);
        }
        cout << string(90, '-') << "\n";
    }
}

int main() {
    vector<Sotietkiem> dsSO;
    double ls_ngan = 2, ls_dai = 3,ls_kthan = 0.05; // Khởi tạo lãi suất mặc định
    char luaChon;

    do {
    cout << "~~~~~>~~ QUAN LY SO TIET KIEM ~~<~~~~~~\n";
    cout << "\t1. Nhap so tiet kiem\n";
    cout << "\t2. Rut tien\n";
    cout << "\t3. Xem danh sach so tiet kiem\n";
    cout << "\t4. Cap nhat lai suat\n";
    cout << "\t5. Tim kiem theo ma so hoac CMND\n";
    cout << "\t6. Tim kiem cac so tiet kiem duoc mo trong 1 khoang thoi gian\n";
    cout << "\t7. Tinh tien lai hien tai\n";
    cout << "\t8. Thoat\n";  // Thêm chức năng cập nhật lãi suất
    cout << "\tLua chon: ";
    cin >> luaChon;
    cout<<"\n";
    switch (luaChon) {
        case '1': {
            int n,i=1 ;
            cout << "\t(+) Nhap so luong STK can nhap: ";
            cin>>n;
            while(n--)
            {
                cout<<"\t"<<i<<".\n";
                Sotietkiem stk = Nhap(dsSO);

                if(stk.phanloai_tk == "dai han") tinhlaiSTK(stk, ls_dai);
                else if (stk.phanloai_tk == "ngan han")  tinhlaiSTK(stk, ls_ngan);
                else tinhlaiSTK(stk, ls_kthan);

                dsSO.push_back(stk);

                cout << "\t(+) Da nhap thanh cong so tiet kiem thu "<<i<<"!\n";
                i++;
            }
            sort(dsSO.begin(), dsSO.end(), Sapxep);
            break;
        }
        case '2': {
            if (dsSO.empty()) {
                cout << "\t(!) Vui long nhap so tiet kiem!\n";
            } else {
                cout << "\t(+) Chon so tiet kiem de rut:\n";

                cout << string(90, '-') << "\n";
                cout << left << setw(10) << "Ma So"
                 << setw(15) << "Loai"
                 << setw(20) << "Ho Ten"
                 << setw(15) << "CMND"
                 << setw(15) << "Ngay Mo So"
                 << setw(15) << "So Tien (VND)" << "\n";
                cout << string(90, '-') << "\n";

            for (const auto& stk : dsSO) {
                Xuat(stk);
            }
            cout << string(90, '-') << "\n";

                string Mastk;
                int s=0;
                cout << "\t(+) Nhap ma so tiet kiem: ";
                cin >> Mastk;
                for (const auto& stk : dsSO) {
                    if(stk.maso == Mastk) break;
                    s++;
                }
                if (ktratrungmaso(dsSO,Mastk)) {
                    if(dsSO[s].phanloai_tk == "dai han") Ruttien(dsSO[s], ls_dai, 1.0);// Lãi suất 3% cho năm, 1% nếu rút trước hạn
                    else if (dsSO[s].phanloai_tk == "ngan han") Ruttien(dsSO[s], ls_ngan, 0.05);
                    else Ruttien(dsSO[s], ls_kthan, 0.025);
                } else {
                    cout << "\t(!) Lua chon khong hop le.\n";
                }
            }
            break;
        }
        case '3': {
            if(dsSO.size()==0)
            {
                cout<<"\t(!) Vui long nhap so tiet kiem.\n";
                break;
            }
            cout << string(90, '-') << "\n";
            cout << left << setw(10) << "Ma So"
                 << setw(15) << "Loai"
                 << setw(20) << "Ho Ten"
                 << setw(15) << "CMND"
                 << setw(15) << "Ngay Mo So"
                 << setw(15) << "So Tien (VND)" << "\n";
            cout << string(90, '-') << "\n";

            for (const auto& stk : dsSO) {
                Xuat(stk);
            }
            cout << string(90, '-') << "\n";
            break;
        }
        case '4': {  // Chức năng cập nhật lãi suất
            cout << "\t(+) Nhap lai suat ngan han (%/nam): ";
            cin >> ls_ngan;
            cout << "\t(+) Nhap lai suat dai han (%/nam): ";
            cin >> ls_dai;
            Cap_nhat(dsSO, ls_ngan, ls_dai);
            break;
        }
        case '5': {
            if (dsSO.empty()) {
                cout << "\t(!) Vui long nhap so tiet kiem!\n";
                break;
                }
                timSTK(dsSO);
                break;
            }
            case '6': {
                if (dsSO.empty()) {
                cout << "\t(!) Vui long nhap so tiet kiem!\n";
                    break;
                }
                tim_theo_thoigian(dsSO);
                break;
            }
        case '7':
            {
                if (dsSO.empty()) {
                cout << "\t(!) Vui long nhap so tiet kiem!\n";
                break;
                }
                cout << "\t(+) Chon so tiet kiem de tinh tien lai:\n";
                cout << string(90, '-') << "\n";
                cout << left << setw(10) << "Ma So"
                 << setw(15) << "Loai"
                 << setw(20) << "Ho Ten"
                 << setw(15) << "CMND"
                 << setw(15) << "Ngay Mo So"
                 << setw(15) << "So Tien (VND)" << "\n";
                cout << string(90, '-') << "\n";

            for (const auto& stk : dsSO) {
                Xuat(stk);
            }
            cout << string(90, '-') << "\n";
            string Mastk;
                int s=0;
                cout << "\t(+) Nhap ma so tiet kiem: ";
                cin >> Mastk;
                for (const auto& stk : dsSO) {
                    if(stk.maso == Mastk) break;
                    s++;
                }
                if (ktratrungmaso(dsSO,Mastk)) {
                    if(dsSO[s].phanloai_tk == "dai han") tinhlaiSTK(dsSO[s], ls_dai);
                    else if (dsSO[s].phanloai_tk == "ngan han")  tinhlaiSTK(dsSO[s], ls_ngan);
                    else tinhlaiSTK(dsSO[s], ls_kthan);
                }
                else cout << "\t(!) Lua chon khong hop le.\n";
                break;

            }
        case '8': {
            cout << "(!) Thoat chuong trinh.\n";
            break;
        }
        default:
            cout << "\t(!) Lua chon khong hop le. Vui long nhap lai.\n";
    }
} while (luaChon != '8');


    return 0;
}
