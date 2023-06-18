#include <iostream>
using namespace std;

int main() {
  int n;
  cout << "Enter the size of matrix: ";
  cin >> n;

  // تعریف ماتریس A و ماتریس معکوس
  double A[n][n], inv[n][n];
  cout << "Enter the elements of matrix A: " << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> A[i][j];
      // مقدار اولیه ماتریس معکوس را برابر با ماتریس واحد قرار می‌دهیم
      if (i == j) {
        inv[i][j] = 1;
      } else {
        inv[i][j] = 0;
      }
    }
  }

  // تبدیل ماتریس A به شکل سه گانه پایین
  for (int k = 0; k < n; k++) {
    for (int i = k + 1; i < n; i++) {
      double factor = A[i][k] / A[k][k];
      for (int j = k; j < n; j++) {
        A[i][j] = A[i][j] - factor * A[k][j];
      }
      for (int j = 0; j < n; j++) {
        inv[i][j] = inv[i][j] - factor * inv[k][j];
      }
    }
  }

  // تبدیل ماتریس A به شکل سه گانه بالا و حل دستگاه معادلات
  for (int k = n - 1; k >= 0; k--) {
    for (int i = k - 1; i >= 0; i--) {
      double factor = A[i][k] / A[k][k];
      for (int j = k; j < n; j++) {
        A[i][j] = A[i][j] - factor * A[k][j];
      }
      for (int j = 0; j < n; j++) {
        inv[i][j] = inv[i][j] - factor * inv[k][j];
      }
    }
    double factor = 1 / A[k][k];
    for (int j = 0; j < n; j++) {
      A[k][j] = A[k][j] * factor;
      inv[k][j] = inv[k][j] * factor;
    }
  }

  // نمایش ماتریس معکوس
  cout << "Inverse matrix: " << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << inv[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}