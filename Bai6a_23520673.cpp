#include <iostream>
#include <vector>
using namespace std;

// Kiểm tra xem mảng A có xuất hiện liên tiếp trong mảng B không
bool kt_mang_con(const vector<int>& A, const vector<int>& B, int batdau) {
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] != B[batdau + i]) {
            return false;
        }
    }
    return true;
}

// Đếm số lần mảng A xuất hiện trong mảng B và lưu vị trí
int dem(const vector<int>& A, const vector<int>& B, vector<int>& vi_tri) {
    int count = 0;
    for (int i = 0; i <= B.size() - A.size(); ++i) {
        if (kt_mang_con(A, B, i)) {
            count++;
            vi_tri.push_back(i); // Lưu vị trí xuất hiện
        }
    }
    return count;
}

int main() {
    int nA, nB;     // Kích thước mảng
    cout << "Nhap kich thuoc mang A va mang B: ";
    cin >> nA >> nB;

    vector<int> A(nA);
    vector<int> B(nB);

    cout << "Nhap phan tu cua mang A: ";
    for (int i = 0; i < nA; ++i) {
        cin >> A[i];
    }

    cout << "Nhap phan tu cua mang B: ";
    for (int i = 0; i < nB; ++i) {
        cin >> B[i];
    }

    vector<int> vi_tri; // Vector lưu vị trí của mảng A
    int result = dem(A, B, vi_tri);

    // In kết quả
    cout << "Mang A xuat hien trong mang B: " << result << " lan" << endl;
    if (!vi_tri.empty()) {
        cout << "Vi tri xuat hien: ";
        for (size_t i = 0; i < vi_tri.size(); ++i) {
            cout << vi_tri[i];
            if (i < vi_tri.size() - 1) {
                cout << ", "; // Ngăn cách các vị trí
            }
        }
        cout << endl;
    } else {
        cout << "Khong tim thay vi tri xuat hien." << endl;
    }

    return 0;
}
