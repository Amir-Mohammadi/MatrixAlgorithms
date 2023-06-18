#include <cmath>
#include <iostream>
#include <vector>
using namespace std;


// حل سیستم معادلات خطی با استفاده از روش SOR
std::vector<double> sorMethod(const std::vector<std::vector<double> > &A,
                              const std::vector<double> &b, double omega,
                              double epsilon, int maxIterations) {
  int n = A.size();
  std::vector<double> x(n, 0.0); // بردار جواب

  int iterations = 0;
  double error = epsilon + 1.0; // خطا

  while (error > epsilon && iterations < maxIterations) {
    std::vector<double> x_new = x; // بردار جواب جدید

    for (int i = 0; i < n; i++) {
      double sum1 = 0.0;
      double sum2 = 0.0;
      for (int j = 0; j < i; j++) {
        sum1 += A[i][j] * x_new[j];
      }
      for (int j = i + 1; j < n; j++) {
        sum2 += A[i][j] * x[j];
      }
      x_new[i] =
          (1.0 - omega) * x[i] + (omega / A[i][i]) * (b[i] - sum1 - sum2);
    }

    error = 0.0;
    for (int i = 0; i < n; i++) {
      error += std::abs(x_new[i] - x[i]);
    }

    x = x_new;
    iterations++;
  }

  if (iterations >= maxIterations) {
    std::cout << "تعداد حداکثر مجاز مراحل تکرار برای دستیابی به جواب نهایی "
                 "تجاوز شد.\n";
  }

  return x;
}

int main() {
  int n;
  std::cout << "تعداد متغیرها (ابعاد سیستم): ";
  std::cin >> n;

  std::vector<std::vector<double> > A(n, std::vector<double>(n, 0.0));
  std::vector<double> b(n, 0.0);

  std::cout << "عناصر ماتریس A را وارد کنید:\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> A[i][j];
    }
  }

  std::cout << "عناصر بردار b را وارد کنید:\n";
  for (int i = 0; i < n; i++) {
    std::cin >> b[i];
  }

  double omega;
  std::cout << "پارامتر omega (0 < omega < 2): ";
  std::cin >> omega;

  double epsilon;
  std::cout << "خطای مجاز (epsilon): ";
  std::cin >> epsilon;

  int maxIterations;
  std::cout << "حداکثر تعداد مراحل تکرار: ";
  std::cin >> maxIterations;

  std::vector<double> solution = sorMethod(A, b, omega, epsilon, maxIterations);

  std::cout << "\nبردار جواب:\n";
  for (int i = 0; i < n; i++) {
    std::cout << "x[" << i + 1 << "] = " << solution[i] << std::endl;
  }

  return 0;
}