
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// تابعی برای چاپ ماتریس
void printMatrix(const vector<vector<double> > &matrix) {
  for (const auto &row : matrix) {
    for (const auto &element : row) {
      cout << element << " ";
    }
    cout << endl;
  }
}

// تابعی برای ضرب دو ماتریس
vector<vector<double> > multiplyMatrices(const vector<vector<double> > &matrix1,
                                        const vector<vector<double> > &matrix2) {
  int m1 = matrix1.size();
  int n1 = matrix1[0].size();
  int m2 = matrix2.size();
  int n2 = matrix2[0].size();

  if (n1 != m2) {
    throw runtime_error("Cannot multiply matrices. Invalid dimensions.");
  }

  vector<vector<double> > result(m1, vector<double>(n2, 0.0));

  for (int i = 0; i < m1; i++) {
    for (int j = 0; j < n2; j++) {
      for (int k = 0; k < n1; k++) {
        result[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }

  return result;
}

// تابعی برای تجزیه QR یک ماتریس
void qrDecomposition(const vector<vector<double> > &matrix,
                     vector<vector<double> > &Q, vector<vector<double> > &R) {
  int m = matrix.size();
  int n = matrix[0].size();

  vector<vector<double> > A(matrix);
  Q = vector<vector<double> >(m, vector<double>(m, 0.0));
  R = vector<vector<double> >(m, vector<double>(n, 0.0));

  for (int k = 0; k < n; k++) {
    vector<double> x(m, 0.0);
    for (int i = k; i < m; i++) {
      x[i] = A[i][k];
    }

    double normX = 0.0;
    for (int i = k; i < m; i++) {
      normX += x[i] * x[i];
    }
    normX = sqrt(normX);

    vector<double> u(m, 0.0);
    if (x[k] >= 0) {
      u[k] = x[k] + normX;
    } else {
      u[k] = x[k] - normX;
    }

    double normU = 0.0;
    for (int i = k; i < m; i++) {
      normU += u[i] * u[i];
    }
    normU = sqrt(normU);

    vector<double> v(m, 0.0);
    for (int i = k; i < m; i++) {
      v[i] = u[i] / normU;
    }

    vector<vector<double> > H(m, vector<double>(m, 0.0));
    for (int i = k; i < m; i++) {
      for (int j = k; j < m; j++) {
        H[i][j] = -2.0 * v[i] * v[j];
      }
    }
    for (int i = k; i < m; i++) {
      H[i][i] += 1.0;
    }

    A = multiplyMatrices(H, A);
    Q = multiplyMatrices(Q, H);
  }

  R = A;
}

// تابعی برای حل سیستم معادلات خطی با استفاده از تجزیه QR
vector<double> solveLinearSystem(const vector<vector<double> > &Q,
                                 const vector<vector<double> > &R,
                                 const vector<double> &b) {
  int n = R[0].size();

  vector<double> y(n, 0.0);
  for (int i = 0; i < n; i++) {
    double sum = 0.0;
    for (int j = 0; j < i; j++) {
      sum += R[j][i] * y[j];
    }
    y[i] = (b[i] - sum) / R[i][i];
  }

  vector<double> x(n, 0.0);
  for (int i = n - 1; i >= 0; i--) {
    double sum = 0.0;
    for (int j = i + 1; j < n; j++) {
      sum += Q[i][j] * x[j];
    }
    x[i] = y[i] - sum;
  }

  return x;
}

int main() {
  int n;
  cout << "اندازه ماتریس را وارد کنید: ";
  cin >> n;

  vector<vector<double> > matrix(n, vector<double>(n));

  cout << "ماتریس را وارد کنید:" << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> matrix[i][j];
    }
  }

  cout << "ماتریس اولیه:" << endl;
  printMatrix(matrix);

  vector<vector<double> > Q, R;
  qrDecomposition(matrix, Q, R);

  cout << "ماتریس Q:" << endl;
  printMatrix(Q);

  cout << "ماتریس R:" << endl;
  printMatrix(R);

  vector<double> b(n, 0.0);
  cout << "بردار ستونی معادلات را وارد کنید:" << endl;

  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }

  vector<double> solution = solveLinearSystem(Q, R, b);

  cout << "نتیجه:" << endl;
  for (const auto &element : solution) {
    cout << element << " ";
  }
  cout << endl;

  return 0;
}