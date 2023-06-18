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

// تابعی برای اعمال تبدیل هوسهولدر بر روی ماتریس
void applyHouseholderTransformation(vector<vector<double> > &matrix, int k) {
  int n = matrix.size();
  vector<double> u(n, 0.0);
  double normX = 0.0;

  for (int i = k + 1; i < n; i++) {
    u[i] = matrix[i][k];
    normX += u[i] * u[i];
  }

  normX = sqrt(normX);
  if (u[k + 1] >= 0) {
    u[k + 1] += normX;
  } else {
    u[k + 1] -= normX;
  }

  double beta = 2.0 / (normX * normX + u[k + 1] * u[k + 1]);

  // محاسبه ماتریس هوسهولدر H
  vector<vector<double> > H(n, vector<double>(n, 0.0));
  for (int i = k + 1; i < n; i++) {
    for (int j = k + 1; j < n; j++) {
      H[i][j] = -beta * u[i] * u[j];
    }
  }
  for (int i = k + 1; i < n; i++) {
    H[i][i] += 1.0;
  }

  // ضرب ماتریس H در چپتر
  vector<vector<double> > HtC = multiplyMatrices(H, matrix);

  // ضرب چپتر در ماتریس H
  matrix = multiplyMatrices(HtC, H);
}

// تابعی برای تبدیل ماتریس متقارن به سه قطری با استفاده از روش هوسهولدر
void convertToTridiagonal(vector<vector<double> > &matrix) {
  int n = matrix.size();

  for (int k = 0; k < n - 2; k++) {
    applyHouseholderTransformation(matrix, k);
  }
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

  convertToTridiagonal(matrix);

  cout << "ماتریس سه قطری:" << endl;
  printMatrix(matrix);

  return 0;
}