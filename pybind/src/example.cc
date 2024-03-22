
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <string>
#include <vector>


namespace py = pybind11;

int add(int i, int j) { return i + j; }

std::string sum(std::vector<int> d) {
  int sum = 0;
  for (auto& i : d) sum += i;

  return std::to_string(sum);
}

// ref unuse in py
void reftest_int(int& d) { d *= 2; }

py::tuple tuple_test(std::vector<int>& d) {
  d.push_back(777);
  d.push_back(778);
  return py::make_tuple(true, d);
}

PYBIND11_MODULE(example, m) {
  m.doc() = "pybind11 example plugin";  // optional module docstring

  m.def("add", &add, "A function that adds two numbers");
  m.def("sum", &sum, "A function that sum");
  m.def("tuple_test", &tuple_test, "A function that tuple_test ret (bool,list)");
    m.def("reftest_int", &reftest_int, "A function that reftest_int");
}