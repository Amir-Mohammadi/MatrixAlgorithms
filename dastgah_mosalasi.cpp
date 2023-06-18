
#include <iostream>
#include <vector>

using namespace std;

// تابع برای حل دستگاه معادلات خطی به روش مثلثی
vector<double> solve(vector<vector<double> > A, vector<double> b) {
    int n = A.size();

    // جایگذاری عمودی
    for (int i = 0; i < n; i++) {
        // بررسی صفر نبودن عنصر اصلی در سطر i
        if (A[i][i] == 0) {
            bool found = false;
            for (int j = i + 1; j < n; j++) {
                if (A[j][i] != 0) {
                    found = true;
                    swap(A[i], A[j]);
                    swap(b[i], b[j]);
                    break;
                }
            }
            if (!found) {
                cout << "The system has no unique solution." << endl;
                
            }
        }
        // جایگذاری به صورت دیاگونال
        double pivot = A[i][i];
        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / pivot;
            for (int k = i; k < n; k++) {
                A[j][k] -= factor * A[i][k];
            }
            b[j] -= factor * b[i];
        }
    }

    // حل معادلات به صورت معکوس ماتریس
    vector<double> x(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }

    return x;
}

int main() {
    int n;
    cout << "Enter the number of equations: ";
    cin >> n;

    // خواندن ضرایب دستگاه معادلات خطی از کاربر
    vector<vector<double> > A(n, vector<double>(n, 0));
    vector<double> b(n, 0);
    cout << "Enter the coefficients of the equations:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
        cin >> b[i];
    }

    // حل دستگاه معادلات خطی
    vector<double> x = solve(A, b);

    // چاپ جواب
    if (!x.empty()) {
        cout << "The solution is:" << endl;
        for (int i = 0; i < n; i++) {
            cout << x[i] << " ";
        }
        cout << endl;
    }

    return 0;
}