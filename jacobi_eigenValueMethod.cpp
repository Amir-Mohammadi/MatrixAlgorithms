
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// ماتریس ضرب دو ماتریس
const vector<vector<double> > matrixMultiplication(const vector<vector<double> > &A,
                      const vector<vector<double> > &B) {
  int n = A.size();
  int m = B[0].size();
  int p = B.size();

  vector<vector<double> > result(n, vector<double>(m, 0.0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < p; k++) {
        result[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  return result;
}

// ماتریس ترانهاده
vector<vector<double> >
matrixTranspose(const vector<vector<double> > &A) {
  int n = A.size();
  int m = A[0].size();

  vector<vector<double> > result(m, vector<double>(n, 0.0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      result[j][i] = A[i][j];
    }
  }

  return result;
}

// ماتریس چشمی
vector<vector<double> > identityMatrix(int n) {
  vector<vector<double> > result(n, vector<double>(n, 0.0));

  for (int i = 0; i < n; i++) {
    result[i][i] = 1.0;
  }

  return result;
}

// پیدا کردن مقادیر ویژه و بردارهای ویژه با استفاده از روش ژاکوبی
void jacobiEigenvalueAlgorithm(const vector<vector<double> > &A,
                               double epsilon, int maxIterations,
                               vector<double> &eigenvalues,
                               vector<vector<double> > &eigenvectors) {
  int n = A.size();
  eigenvectors = identityMatrix(n);

  int iterations = 0;
  double maxOffDiagonalElement = 0.0;

  while (iterations < maxIterations) {
    // پیدا کردن بزرگترین عنصر غیرقطری
    maxOffDiagonalElement = 0.0;
    int row = 0;
    int col = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (abs(A[i][j]) > maxOffDiagonalElement) {
          maxOffDiagonalElement = abs(A[i][j]);
          row = i;
          col = j;
        }
      }
    }

    if (maxOffDiagonalElement < epsilon) {
      break; // تمام عناصر غیرقطری بسیار کوچک شده‌اند، مقادیر ویژه به طور قابل
             // قبولی یافت شده‌اند
    }

    // محاسبه زاویه دوران
    double theta =
        0.5 * atan2(2.0 * A[row][col], A[row][row] - A[col][col]);

    // ساخت ماتریس چرخش
    vector<vector<double> > rotationMatrix = identityMatrix(n);
    rotationMatrix[row][row] = cos(theta);
    rotationMatrix[col][col] = cos(theta);
    rotationMatrix[row][col] = -sin(theta);
    rotationMatrix[col][row] = sin(theta);

    // اعمال چرخش بر روی ماتریس‌ها
    A == matrixMultiplication(matrixTranspose(rotationMatrix),
                             matrixMultiplication(A, rotationMatrix));

    eigenvectors = matrixMultiplication(eigenvectors, rotationMatrix);

    iterations++;
  }

  // استخراج مقادیر ویژه
  eigenvalues.resize(n);
  for (int i = 0; i < n; i++) {
    eigenvalues[i] = A[i][i];
  }
}

int main() {
  int n;
  cout << "ابعاد ماتریس: ";
  cin >> n;

  vector<vector<double> > A(n, vector<double>(n, 0.0));
  cout << "عناصر ماتریس را وارد کنید:\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> A[i][j];
    }
  }

  double epsilon;
  cout << "خطای مجاز: ";
  cin >> epsilon;

  int maxIterations;
  cout << "حداکثر تعداد مراحل تکرار: ";
  cin >> maxIterations;

  vector<double> eigenvalues;
  vector<vector<double> > eigenvectors;

  jacobiEigenvalueAlgorithm(A, epsilon, maxIterations, eigenvalues,
                            eigenvectors);

  cout << "\nمقادیر ویژه:\n";
  for (int i = 0; i < n; i++) {
    cout << "λ[" << i + 1 << "] = " << eigenvalues[i] << endl;
  }

  for (int i = 0; i < n; i++) {
    cout << "v[" << i + 1 << "] = (";
    for (int j = 0; j < n; j++) {
      cout << eigenvectors[j][i];
      if (j < n - 1) {
        cout << ", ";
      }
    }
    cout << ")\n";
  }

  return 0;
}

