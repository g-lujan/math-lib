#include "math_lib/matrix/matrix.h"
#include <chrono>
#include <iostream>

int main()
{
  Matrix<float, 300, 200> A = loadtxt<float, 300, 200>("A.txt");
  Matrix<float, 200, 300> B = loadtxt<float, 200, 300>("B.txt");

  auto begin = std::chrono::high_resolution_clock::now();
  Matrix<float, 300, 300> AxB = A * B;
  auto end = std::chrono::high_resolution_clock::now();

  std::cout << AxB << std::endl;
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin) << std::endl;
}
