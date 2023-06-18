#include <iostream>
#include <vector>
using namespace std;



// تجزیه ماتریس به روش LU دولیتل
void luDecomposition(const vector<vector<double> >& matrix,
 vector<vector<double> >& L,
  vector<vector<double> >& U) {
    int n = matrix.size();

    // ماتریس L را با مقادیر صفر مقداردهی اولیه کنید
    L.resize(n, vector<double>(n, 0.0));
    // ماتریس U را با مقادیر صفر مقداردهی اولیه کنید
    U.resize(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        // عنصر اصلی قطری ماتریس L برابر با 1 است
        L[i][i] = 1.0;

        // محاسبه مقادیر ماتریس U
        for (int k = i; k < n; k++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++) {
                sum += (L[i][j] * U[j][k]);
            }
            U[i][k] = matrix[i][k] - sum;
        }

        // محاسبه مقادیر ماتریس L
        for (int k = i + 1; k < n; k++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++) {
                sum += (L[k][j] * U[j][i]);
            }
            L[k][i] = (matrix[k][i] - sum) / U[i][i];
        }
    }
}

int main() {
    int n;
    cout << "اندازه ماتریس را وارد کنید: ";
    cin >> n;

    // خواندن ماتریس از ورودی
    vector<vector<double> > matrix(n, vector<double>(n));
    cout << "عناصر ماتریس را وارد کنید:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    // تجزیه ماتریس به روش LU دولیتل
    vector<vector<double> > L, U;
    luDecomposition(matrix, L, U);

    // نمایش ماتریس L
    cout << "\nماتریس L:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << L[i][j] << " ";
        }
        cout << endl;
    }

    // نمایش ماتریس U
    cout << "\nماتریس U:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << U[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}