#include "ls_test.h"

int main(int argc, char **argv) {
  std::vector<double> data_x, data_y;
  int data_num = 20;
  GenerateData(data_num, data_x, data_y);
  LeastSquares(data_x, data_y, data_num);
  return 0;
}