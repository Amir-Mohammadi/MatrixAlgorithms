#include <iostream>
using namespace std;

int main() {
  int n;
  cout << "Enter the size of matrix: ";
  cin >> n;

  // تعریف ماتریس A و ماتریس L و ماتریس U
  double A[n][n], L[n][n], U[n][n];
  cout << "Enter the elements of matrix A: " << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> A[i][j];
      // مقدار اولیه ماتریس L و ماتریس U را برابر با صفر قرار می‌دهیم
      L[i][j] = 0;
      U[i][j] = 0;
    }
  }

  // تعیین مقدار اولیه برای ماتریس L و ماتریس U
  for (int i = 0; i < n; i++) {
    L[i][i] = 1;
    U[i][i] = A[i][i];
  }

  // تبدیل ماتریس A به ماتریس L و ماتریس U
  for (int k = 0; k < n - 1; k++) {
    for (int i = k + 1; i < n; i++) {
      double factor = A[i][k] / A[k][k];
      L[i][k] = factor;
      for (int j = k + 1; j < n; j++) {
        A[i][j] = A[i][j] - factor * A[k][j];
      }
      U[k+1][i] = A[k+1][i];
    }
  }

  // نمایش ماتریس L و ماتریس U
  cout << "Matrix L: " << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << L[i][j] << " ";
    }
    cout << endl;
  }
  cout << "Matrix U: " << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << U[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}