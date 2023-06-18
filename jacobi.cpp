#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// حل سیستم معادلات خطی با استفاده از روش ژاکوبی
vector<double> jacobiMethod(const vector<vector<double> > &A,
                                 const vector<double> &b,
                                 double epsilon,
                                 int maxIterations) {
  int n = A.size();
  vector<double> x(n, 0.0); // بردار جواب

  int iterations = 0;
  double error = epsilon + 1.0; // خطا

  while (error > epsilon && iterations < maxIterations) {
    vector<double> x_new(n, 0.0); // بردار جواب جدید

    for (int i = 0; i < n; i++) {
      double sum = 0.0;
      for (int j = 0; j < n; j++) {
        if (j != i) {
          sum += A[i][j] * x[j];
        }
      }
      x_new[i] = (b[i] - sum) / A[i][i];
    }

    error = 0.0;
    for (int i = 0; i < n; i++) {
      error += abs(x_new[i] - x[i]);
    }

    x = x_new;
    iterations++;
  }

  if (iterations >= maxIterations) {
    cout << "تعداد حداکثر مجاز مراحل تکرار برای دستیابی به جواب نهایی "
                 "تجاوز شد.\n";
  }

  return x;
}

int main() {
  int n;
  cout << "تعداد متغیرها (ابعاد سیستم): ";
  cin >> n;

  vector<vector<double> > A(n, vector<double>(n, 0.0));
  vector<double> b(n, 0.0);

  cout << "عناصر ماتریس A را وارد کنید:\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> A[i][j];
    }
  }

  cout << "عناصر بردار b را وارد کنید:\n";
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }

  double epsilon;
  cout << "خطای مجاز (epsilon): ";
  cin >> epsilon;

  int maxIterations;
  cout << "حداکثر تعداد مراحل تکرار: ";
  cin >> maxIterations;

  vector<double> solution = jacobiMethod(A, b, epsilon, maxIterations);

  cout << "\nبردار جواب:\n";
  for (int i = 0; i < n; i++) {
    cout << "x[" << i + 1 << "] = " << solution[i] << endl;
  }

  return 0;
}