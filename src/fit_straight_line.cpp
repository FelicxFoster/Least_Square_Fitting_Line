#include "fit_straight_line.h"

int main(int argc, char **argv) {
  double k = 0.0;
  double b = 0.0;
  int data_num = 20;
  ceres::Problem problem;
  std::vector<double> data_x, data_y;

  GenerateData(data_num, data_x, data_y);

  for (int i = 0; i < data_x.size(); ++i) {
    problem.AddResidualBlock(
        new ceres::AutoDiffCostFunction<ExponentialResidual, 1, 1, 1>(
            new ExponentialResidual(data_x[i], data_y[i])),
        NULL, &k, &b);
  }
  // 配置求解器
  ceres::Solver::Options options;
  options.max_num_iterations = 20;
  options.linear_solver_type = ceres::DENSE_QR;
  options.minimizer_progress_to_stdout = true;

  ceres::Solver::Summary summary;
  ceres::Solve(options, &problem, &summary);  // 优化

  // 输出结果
  std::cout << "k: " << k << " b: " << b << "\n";
  // AX + BY + C = 0
  std::cout << "Direction Vector   (B,-A): (" << -1 << "," << -k << ")\n";
  std::cout << "Normal Vector      (A,B): (" << k << "," << -1 << ")\n";

  // 画图
  const char *title = "curve fitting by ceres";
  Plot(data_x, data_y, k, b, title);
  return 0;
}
