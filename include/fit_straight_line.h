#include <ceres/ceres.h>

#include <chrono>
#include <iostream>

#include "utility.h"

struct ExponentialResidual {
  ExponentialResidual(double x, double y) : x_(x), y_(y) {}
  // 计算残差
  template <typename T>
  bool operator()(const T *const k, const T *const b, T *residual) const {
    // r = y - f(x)
    residual[0] = y_ - (k[0] * x_ + b[0]);
    return true;
  }

 private:
  const double x_;
  const double y_;
};
