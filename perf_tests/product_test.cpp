#include "math_lib/matrix/matrix.h"
#include <chrono>
#include <iostream>

int main()
{
  Matrix<float, 3000, 2000> A = loadtxt<float, 3000, 2000>("A.txt");
  Matrix<float, 2000, 3000> B = loadtxt<float, 2000, 3000>("B.txt");

  auto begin = std::chrono::high_resolution_clock::now();
  Matrix<float, 3000, 3000> AxB = A * B;
  auto end = std::chrono::high_resolution_clock::now();

  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin) << std::endl;
}
