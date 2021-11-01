#include <math.h>

#include <iostream>

#include "utility.h"

void LeastSquares(std::vector<double> &data_x, std::vector<double> &data_y,
                  int data_n) {
  double A, B, C, D, E, F = 0.0;
  double x_square_sum, x_sum, y_sum, xy_multi_sum = 0.0;

  for (int i = 0; i < data_n; i++) {
    x_square_sum += data_x[i] * data_x[i];
    x_sum += data_x[i];
    xy_multi_sum += data_x[i] * data_y[i];
    y_sum += data_y[i];
  }

  // 计算斜率k和截距b
  double k, b, temp = 0;
  if (temp = (data_n * x_square_sum - x_sum * x_sum)) {
    k = (data_n * xy_multi_sum - x_sum * y_sum) / temp;
    b = (x_square_sum * y_sum - x_sum * xy_multi_sum) / temp;
  } else {
    k = 1;
    b = 0;
  }

  // 计算x和y线性相关系数r
  double Xmean, Ymean;
  Xmean = x_sum / data_n;
  Ymean = y_sum / data_n;

  double tempSumXX = 0.0, tempSumYY = 0.0;
  for (int i = 0; i < data_n; i++) {
    tempSumXX += (data_x[i] - Xmean) * (data_x[i] - Xmean);
    tempSumYY += (data_y[i] - Ymean) * (data_y[i] - Ymean);
    E += (data_x[i] - Xmean) * (data_y[i] - Ymean);
  }
  F = sqrt(tempSumXX) * sqrt(tempSumYY);

  double r;
  r = E / F;
  std::cout << "k: " << k << "\n"
            << "b: " << b << "\n"
            << "r: " << r << std::endl;
  // AX + BY + C = 0
  std::cout << "Direction Vector   (B,-A): (" << -1 << "," << -k << ")\n";
  std::cout << "Normal Vector      (A,B): (" << k << "," << -1 << ")\n";

  const char *title = "curve fitting by LS";
  Plot(data_x, data_y, k, b, title);
}
