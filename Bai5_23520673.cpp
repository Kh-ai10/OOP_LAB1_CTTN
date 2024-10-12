#include <iostream>
using namespace std;

// Kiểm tra năm nhuận
bool nam_nhuan(int nam) {
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

// Tính số ngày trong tháng
int ngay_trong_thang(int thang, int nam) {
    if (thang == 2) {
        return nam_nhuan(nam) ? 29 : 28;
    } else if (thang == 4 || thang == 6 || thang == 9 || thang == 11) {
        return 30;
    } else {
        return 31;
    }
}

// Tính số ngày từ đầu năm đến ngày đó
int ngay_trong_nam(int ngay, int thang, int nam) {
    int ngay_thu = 0;
    for (int m = 1; m < thang; ++m) {
        ngay_thu += ngay_trong_thang(m, nam);
    }
    ngay_thu += ngay;
    return ngay_thu;
}

int main() {
    int ngay, thang, nam;
    cout << "Nhap ngay theo dinh dang (DD MM YYYY): ";
    cin >> ngay >> thang >> nam;

    // Tìm ngày kế tiếp
    int ngay_ke_tiep = ngay + 1;
    int thang_ke_tiep = thang;
    int nam_ke_tiep = nam;
    if (ngay_ke_tiep > ngay_trong_thang(thang, nam)) {
        ngay_ke_tiep = 1;
        thang_ke_tiep++;
        if (thang_ke_tiep > 12) {
            thang_ke_tiep = 1;
            nam_ke_tiep++;
        }
    }

    // Tìm ngày trước
    int ngay_truoc_do = ngay - 1;
    int thang_truoc_do = thang;
    int nam_truoc_do = nam;
    if (ngay_truoc_do == 0) {
        thang_truoc_do--;
        if (thang_truoc_do == 0) {
            thang_truoc_do = 12;
            nam_truoc_do--;
        }
        ngay_truoc_do = ngay_trong_thang(thang_truoc_do, nam_truoc_do);
    }
    int thu = ngay_trong_nam(ngay, thang, nam);

    // Xuất kết quả
    cout << "Ngay truoc: " << ngay_truoc_do << "/" << thang_truoc_do << "/" << nam_truoc_do << endl;
    cout << "Ngay ke tiep: " << ngay_ke_tiep << "/" << thang_ke_tiep << "/" << nam_ke_tiep << endl;
    cout << "Do la ngay thu " << thu << " trong nam";

    return 0;
}
