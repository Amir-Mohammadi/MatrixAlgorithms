// Amir Reza Mohammadi 

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int row;
    cout << "how many row and columns in matrix : ";
    cin >> row;

    //
    int matrix[row][row];
    for (int i = 0; i < row; i++) {
        cout << "line : " << i+1 << " Enter row of matrix with spaces : ";
        for (int j = 0; j < row; j++) {
            cin >> matrix[i][j];
        }
    }

    // ستون های ماتریس را برای محور گیری جزئی جدا کنید
    int a = matrix[0][0], b = matrix[1][0], c = matrix[2][0], d = matrix[3][0];
    int e = matrix[0][1], f = matrix[1][1], g = matrix[2][1], h = matrix[3][1];
    int i = matrix[0][2], j = matrix[1][2], k = matrix[2][2], l = matrix[3][2];
    int m = matrix[0][3], n = matrix[1][3], o = matrix[2][3], p = matrix[3][3];

    // مقدار دلتا را محاسبه کنید
    int delta = a*f*k*p + b*g*l*m + c*h*i*n + d*e*j*o - d*f*i*n - c*e*l*p - b*h*k*o - a*g*j*m;

    // بررسی کنید که آیا یک راه حل یکتا برای سیستم معادلات وجود دارد یا خیر
    if (delta == 0) {
        cout << "راه حل یکتایی وجود ندارد." << endl;
    } else {
        // ستون های سیستم معادلات را برای محور گیری کلی جدا کنید
        int q = matrix[0][4], r = matrix[1][4], s = matrix[2][4], t = matrix[3][4];

        // مقادیر آلفا، بتا، گامارا با استفاده از محور گیری جزئی محاسبه کنید
        int alpha = f*k*p*q + g*l*m*t + h*i*n*r + e*j*o*s - e*k*n*t - h*f*m*s - g*j*p*r - f*i*o*q;
        int beta = b*k*p*t + c*l*m*r + d*i*n*s + a*j*o*q - a*k*n*r - d*j*p*s - c*h*q*t - b*g*o*m;
        int gamma = b*f*s*q + c*g*r*t + d*h*n*p + a*e*m*o - a*f*n*t - d*e*r*s - c*j*q*p - b*h*o*m;

        double delta1 = a*f*k*p + b*g*l*m + c*h*i*n + d*e*j*o - d*f*i*n - c*e*l*p - b*h*k*o - a*g*j*m;
        double delta2 = e*k*n*p + h*f*m*q + g*j*p*r + f*i*o*s - f*k*o*r - g*i*n*q - h*j*s*p - e*l*m*s;
        double delta3 = i*n*t + l*o*q + k*p*r + j*m*s - j*n*r - k*m*t - l*i*s - o*p*q;
        double delta4 = f*k*s*t + g*l*q*r + h*i*p*s + e*j*m*t - e*k*p*r - h*f*q*s - g*j*s*t - f*i*m*q;

        // مقادیر x، y، z و w را با استفاده از محور گیری کلی محاسبه کنید
        double x = (double)alpha / delta;
        double y = (double)beta / delta;
        double z = (double)gamma / delta;
        double w = (double)delta4 / delta;

        // راه حل را چاپ کنید
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        cout << "z = " << z << endl;
        cout << "w = " << w << endl;
    }

    return 0;
}
