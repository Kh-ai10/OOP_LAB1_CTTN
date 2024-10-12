#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct Hocsinh {
    string hoten;
    float diemtoan, diemvan, diem_nn;

    float dtb() {
        return ((2 * diemtoan) + diemvan + diem_nn) / 4;
    }

    string Phanloai() {
        float diem_tb = dtb();
        if (diem_tb < 5.0) return "Hoc sinh yeu";
        else if (diem_tb >= 5.0 && diem_tb < 6.5) return "Hoc sinh trung binh";
        else if (diem_tb >= 6.5 && diem_tb < 8.0) return "Hoc sinh kha";
        else if (diem_tb >= 8.0 && diem_tb < 9.0) return "Hoc sinh gioi";
        else return "Hoc sinh xuat sac";
    }
};

bool kiemtra(const string hoten) {
    if (hoten.length() < 1 || hoten.length() > 100) return false;
    for (char c : hoten) {
        if (isdigit(c)) return false;  
    }
    return true;
}

void Nhap(Hocsinh &hs) {
    cout << "Nhap ho ten: ";
    cin.ignore();
    getline(cin, hs.hoten);
    while (!kiemtra(hs.hoten)) {
        cout << "Ho ten khong hop le. Nhap lai: ";
        getline(cin, hs.hoten);
    }

    auto Nhapdiem = [](float &diem) {
        do {
            cout << "Nhap diem (ngoai ngu/toan/van): ";
            cin >> diem;
            if (diem < 0.0 || diem > 10.0) cout << "Nhap lai: ";
        } while (diem < 0.0 || diem > 10.0);
    };
    Nhapdiem(hs.diem_nn);
    Nhapdiem(hs.diemtoan);
    Nhapdiem(hs.diemvan);
}

void Xuat(Hocsinh &hs) {
    cout << "Ho ten: " << hs.hoten << "\n";
    cout << "Diem toan: " << hs.diemtoan << "\n";
    cout << "Diem van: " << hs.diemvan << "\n";
    cout << "Diem ngoai ngu: " << hs.diem_nn << "\n";
    cout << "Diem trung binh: " << hs.dtb() << "\n";
    cout << "Xep loai: " << hs.Phanloai() << "\n";
}

void toLower(string &str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void CHON() {
    cout << "\n~~%~ CHUONG TRINH QUAN LY HOC SINH ~%~~\n";
    cout << "1. Nhap thong tin cho cac hoc sinh\n";
    cout << "2. Xuat danh sach cac hoc sinh\n";
    cout << "3. Tim hoc sinh co diem trung binh cao nhat\n";
    cout << "4. Tim kiem hoc sinh theo ho ten\n";
    cout << "5. Tim nhung hoc sinh co diem toan thap nhat\n";
    cout << "6. Ket thuc chuong trinh\n";
}

int main() {
    int n = 0;
    Hocsinh* danhsach = nullptr;

    while (true) {
        CHON();
        int choice;
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 1: // Nhap thong tin cho cac hoc sinh
                cout << "Nhap so luong hoc sinh: ";
                cin >> n;
                danhsach = new Hocsinh[n];

                for (int i = 0; i < n; i++) {
                    cout << "Nhap thong tin cho hoc sinh thu " << i + 1 << "\n";
                    Nhap(danhsach[i]);
                }
                break;

            case 2: // Xuat danh sach cac hoc sinh
                if (danhsach == nullptr) {
                    cout << "Chua co thong tin hoc sinh.\n";
                } else {
                    for (int i = 0; i < n; i++) {
                        cout << "~~~> Thong tin hoc sinh thu " << i + 1 << " <~~~" << "\n";
                        Xuat(danhsach[i]);
                        cout << "\n";
                    }
                    cout <<"\n";
                }
                break;

            case 3: // Tim hoc sinh co diem trung binh cao nhat
                if (danhsach == nullptr) {
                    cout << "Chua co thong tin hoc sinh.\n";
                } else {
                    float diemCaoNhat = danhsach[0].dtb();
                    int soHSTranhNhat = 1;

                    // Đếm số học sinh có điểm trung bình cao nhất
                    for (int i = 1; i < n; i++) {
                        if (danhsach[i].dtb() > diemCaoNhat) {
                            diemCaoNhat = danhsach[i].dtb();
                            soHSTranhNhat = 1; // Reset số học sinh tranh nhất
                        } else if (danhsach[i].dtb() == diemCaoNhat) {
                            soHSTranhNhat++;
                        }
                    }

                    // Lưu học sinh có điểm trung bình cao nhất vào mảng
                    Hocsinh* hsCaoNhat = new Hocsinh[soHSTranhNhat];
                    int index = 0;

                    for (int i = 0; i < n; i++) {
                        if (danhsach[i].dtb() == diemCaoNhat) {
                            hsCaoNhat[index++] = danhsach[i];
                        }
                    }

                    cout << "Hoc sinh co diem trung binh cao nhat la:\n";
                    for (int i = 0; i < soHSTranhNhat; i++) {
                        cout << hsCaoNhat[i].hoten << " (Diem trung binh: " << hsCaoNhat[i].dtb() << ")\n";
                    }
                    delete[] hsCaoNhat;
                }
                break;

            case 4: // Tìm kiếm học sinh theo tên
                if (danhsach == nullptr) {
                    cout << "Chua co thong tin hoc sinh.\n";
                } else {
                    string tu_khoa;
                    cout << "Nhap ten hoc sinh can tim: ";
                    cin.ignore();
                    getline(cin, tu_khoa);
                    toLower(tu_khoa); // Chuyển từ khóa tìm kiếm về chữ thường

                    cout << "Ket qua: ";
                    bool found = false; // Biến để kiểm tra nếu có kết quả tìm thấy
                        for (int i = 0; i < n; i++) {
                        // Tách tên học sinh để kiểm tra tên
                            size_t lastSpaceIndex = danhsach[i].hoten.find_last_of(' ');
                            string ten = (lastSpaceIndex != string::npos) ? danhsach[i].hoten.substr(lastSpaceIndex + 1) : danhsach[i].hoten;

                            string tenLower = ten; // Lưu tên gốc để in
                            toLower(tenLower); // Chuyển tên học sinh về chữ thường
                            if (tenLower.find(tu_khoa) != string::npos) {
                                cout << danhsach[i].hoten << "\n"; // In ra tên học sinh gốc
                                found = true; // Đánh dấu là có kết quả tìm thấy
                            }
                        }
                        if (!found) {
                            cout << "Khong tim thay.\n";
                        }
                }
                break;


            case 5: // Tim nhung hoc sinh co diem toan thap nhat
                if (danhsach == nullptr) {
                    cout << "Chua co thong tin hoc sinh.\n";
                } else {
                    float diemtoanthapnhat = danhsach[0].diemtoan;
                    for (int i = 0; i < n; i++) {
                        if (danhsach[i].diemtoan < diemtoanthapnhat) diemtoanthapnhat = danhsach[i].diemtoan;
                    }

                    cout << "Nhung hoc sinh co diem toan thap nhat la: " << "\n";
                    for (int i = 0; i < n; i++) {
                        if (danhsach[i].diemtoan == diemtoanthapnhat) {
                            cout << "Ho ten: " << danhsach[i].hoten << "\n";
                            cout << "Diem toan: " << danhsach[i].diemtoan << "\n";
                        }
                    }
                }
                break;

            case 6: // Ket thuc chuong trinh
                delete[] danhsach; // Giải phóng bộ nhớ
                cout << "Ket thuc chuong trinh.\n";
                return 0;

            default:
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
        }
    }

    return 0;
}
