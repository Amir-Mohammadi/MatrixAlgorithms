
#include <iostream>
#include <vector>

using namespace std;

// تابع برای حل دستگاه معادلات خطی به روش کرامر
vector<double> solve(vector<vector<double> > A, vector<double> b) {
    int n = A.size();
    vector<double> x(n, 0);

    // محاسبه determinant ماتریس A
    double detA = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double coef = A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] -= coef * A[i][k];
            }
            b[j] -= coef * b[i];
        }
        detA *= A[i][i];
    }

    // بررسی اینکه آیا ماتریس A دارای رتبه کامل است یا خیر
    int rankA = n;
    for (int i = 0; i < n; i++) {
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
                rankA--;
            }
        }
    }
    if (rankA < n) {
        cout << "The system has no unique solution." << endl;
      
    }

    // حل دستگاه معادلات خطی با استفاده از روش کرامر
    for (int i = 0; i < n; i++) {
        vector<vector<double> > Ai = A;
        for (int j = 0; j < n; j++) {
            Ai[j][i] = b[j];
        }
        double detAi = 1;
        for (int j = 0; j < n; j++) {
            detAi *= Ai[j][j];
        }
        x[i] = detAi / detA;
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