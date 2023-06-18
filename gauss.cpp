#include <iostream>
using namespace std;

int main() {
  int n;
  cout << "Enter the size of matrix: ";
  cin >> n;

  // تعریف ماتریس A و بردار b
  double A[n][n];
  double b[n];
  cout << "Enter the elements of matrix A: " << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> A[i][j];
    }
  }
  cout << "Enter the elements of vector b: " << endl;
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }

  // تبدیل ماتریس A به شکل سه گانه پایین
  for (int k = 0; k < n; k++) {
    for (int i = k + 1; i < n; i++) {
      double factor = A[i][k] / A[k][k];
      for (int j = k; j < n; j++) {
        A[i][j] = A[i][j] - factor * A[k][j];
      }
      b[i] = b[i] - factor * b[k];
    }
  }

  // تبدیل ماتریس A به شکل سه گانه بالا و حل دستگاه معادلات
  double x[n];
  for (int i = n - 1; i >= 0; i--) {
    x[i] = b[i];
    for (int j = i + 1; j < n; j++) {
      x[i] = x[i] - A[i][j] * x[j];
    }
    x[i] = x[i] / A[i][i];
  }

  // نمایش پاسخ
  cout << "Solution: ";
  for (int i = 0; i < n; i++) {
    cout << x[i] << " ";
  }
  cout << endl;
    
  return 0;
}
