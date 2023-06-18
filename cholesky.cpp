#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// تجزیه ماتریس به روش چولسکی
bool choleskyDecomposition(const vector<vector<double> >& matrix,
 vector<vector<double> >& L) {
    int n = matrix.size();

    // ماتریس L را با مقادیر صفر مقداردهی اولیه کنید
    L.resize(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0.0;
            if (j == i) {
                for (int k = 0; k < j; k++) {
                    sum += pow(L[j][k], 2);
                }
                double diagonal = matrix[j][j] - sum;
                if (diagonal <= 0) {
                    // ماتریس ورودی نمی‌تواند به روش چولسکی تجزیه شود
                    return false;
                }
                L[j][j] = sqrt(diagonal);
            } else {
                for (int k = 0; k < j; k++) {
                    sum += L[i][k] * L[j][k];
                }
                L[i][j] = (matrix[i][j] - sum) / L[j][j];
            }
        }
    }

    return true;
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

    // تجزیه ماتریس به روش چولسکی
    vector<vector<double> > L;
    if (choleskyDecomposition(matrix, L)) {
        // نمایش ماتریس L
        cout << "\nماتریس L:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << L[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "ماتریس ورودی نمی‌تواند به روش چولسکی تجزیه شود.\n";
    }

    return 0;
}