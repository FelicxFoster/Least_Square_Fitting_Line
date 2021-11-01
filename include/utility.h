#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_plotter.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <opencv2/core/core.hpp>
#include <random>
#include <vector>

double uniform_rand(double lowerBndr, double upperBndr) {
  return lowerBndr +
         ((double)std::rand() / (RAND_MAX + 1.0)) * (upperBndr - lowerBndr);
}
double gauss_rand(double mean, double sigma) {
  double x, y, r2;
  do {
    x = -1.0 + 2.0 * uniform_rand(0.0, 1.0);
    y = -1.0 + 2.0 * uniform_rand(0.0, 1.0);
    r2 = x * x + y * y;
  } while (r2 > 1.0 || r2 == 0.0);
  return mean + sigma * y * std::sqrt(-2.0 * log(r2) / r2);
}

// 生成测试集
void GenerateData(int num, std::vector<double> &data_x,
                  std::vector<double> &data_y) {
  double m = 0.079;
  double c = 13.62;
  std::vector<double> y_true;
  for (int i = 0; i < num; i++) {
    data_x.push_back(i + 1);
  }
  cv::RNG rng;
  double w_sigma = 0.2;
  for (int i = 0; i < data_x.size(); i++) {
    double temp = m * data_x[i] + c;
    y_true.push_back(temp);
    // double noise = gauss_rand(0, 0.1);
    // data_y.push_back(temp + noise);
    data_y.push_back(temp + rng.gaussian(w_sigma));
  }
}

// 图形显示
void Plot(std::vector<double> data_x, std::vector<double> data_y, double m,
          double c, const char *title) {
  pcl::visualization::PCLPlotter *plot_(
      new pcl::visualization::PCLPlotter(title));
  plot_->setBackgroundColor(1, 1, 1);
  plot_->setTitle(title);

  std::vector<double> y_estimate_data;  // 估计数据
  std::vector<double> y_truth_date;     // 真实数据
  for (int i = 0; i < data_x.size(); i++) {
    double xi = data_x[i];
    double yi = m * xi + c;

    y_estimate_data.push_back(yi);

    y_truth_date.push_back(0.079 * xi + 13.62);
  }
  plot_->addPlotData(data_x, y_truth_date, "ground_truth", vtkChart::LINE);

  plot_->addPlotData(data_x, y_estimate_data, "estimation", vtkChart::LINE);

  plot_->addPlotData(data_x, data_y, "points", vtkChart::POINTS);

  plot_->plot();
}
