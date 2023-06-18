

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

// تابع برای پیدا کردن بزرگترین عنصر در یک ماتریس و مختصات آن
void findMax(const vector<vector<double> >& A, int& p, int& q, int n) {
    double max = 0;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(abs(A[i][j]) > max) {
                max = abs(A[i][j]);
                p = i;
                q = j;
            }
        }
    }
}

// تابع برای چرخش دو سطر و دو ستون در ماتریس
void rotate(vector<vector<double> >& A, vector<vector<double> >& R, int p, int q, int n) {
    double c, s;
    if(A[p][q] != 0) {
        double tau = (A[q][q] - A[p][p]) / (2 * A[p][q]);
        double t;
        if(tau >= 0) {
            t = 1 / (tau + sqrt(1 + tau * tau));
        } else {
            t = -1 / (-tau + sqrt(1 + tau * tau));
        }
        c = 1 / sqrt(1 + t * t);
        s = c * t;
    } else {
        c = 1;
        s = 0;
    }

    // چرخش دو سطر و دو ستون در ماتریس A
    double apq, app, aqq;
    apq = A[p][q];
    app = A[p][p];
    aqq = A[q][q];
    A[p][q] = 0;
    A[p][p] = c * c * app + s * s * aqq - 2 * c * s * apq;
    A[q][q] = s * s * app + c * c * aqq + 2 * c * s * apq;
    for(int i=0; i<n; i++) {
        if(i != p && i != q) {
            double api = A[p][i];
            double aqi = A[q][i];
            A[p][i] = c * api + s * aqi;
            A[i][p] = A[p][i];
            A[q][i] = -s * api + c * aqi;
            A[i][q] = A[q][i];
        }
    }

    // چرخش دو سطر و دو ستون در ماتریس R
    for(int i=0; i<n; i++) {
        double rpi = R[p][i];
        double rqi = R[q][i];
        R[p][i] = c * rpi + s * rqi;
        R[q][i] = -s * rpi + c * rqi;
    }
}

// تابع برای بدست آوردن بردارهای ویژه و مقادیر ویژه یک ماتریس
void jacobi(const vector<vector<double> >& A, vector<vector<double> >& R, vector<double>& lambda, int n) {
    // ماتریس های مورد نیاز برای چرخش
    R = vector<vector<double> >(n, vector<double>(n, 0));
    for(int i=0; i<n; i++) {
        R[i][i] = 1;
    }

    // الگوریتم Jacobi برای بدست آوردن بردارهای ویژه و مقادیر ویژه
    vector<vector<double> > B = A;
    int p, q;
    findMax(B, p, q, n);
    while(abs(B[p][q]) > 1e-10) {
        rotate(B, R, p, q, n);
        findMax(B, p, q, n);
    }

    // بدست آوردن مقادیر ویژه از قطر اصلی ماتریس B
    lambda = vector<double>(n, 0);
    for(int i=0; i<n; i++) {
        lambda[i] = B[i][i];
    }
}

int main() {
    int n;
    cout << "Enter the size of the matrix: ";
    cin >> n;

    // خواندن ماتریس از کاربر
    vector<vector<double> > A(n, vector<double>(n, 0));
    cout << "Enter the elements of the matrix:" << endl;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cin >> A[i][j];
        }
    }

    // بدست آوردن بردارهای ویژه و مقادیر ویژه
    vector<vector<double> > R;
    vector<double> lambda;
    jacobi(A, R, lambda, n);

    // چاپ بردارهای ویژه و مقادیر ویژه
    cout << "Eigenvalues:" << endl;
    for(int i=0; i<n; i++) {
        cout << lambda[i] << " ";
    }
    cout << endl;

    cout << "Eigenvectors:" << endl;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cout << R[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}