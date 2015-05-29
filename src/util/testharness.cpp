#include "util/testharness.h"

#include <stdio.h>

#include <vector>

namespace tools {
namespace test {

namespace {
struct Test {
  const char* base;
  const char* name;
  void (*func)();
};
std::vector<Test>* tests;
} //namespace

bool RegisterTest(const char* base, const char* name, void (*func)()) {
  if (tests == NULL) {
    tests = new std::vector<Test>;
  }
  Test t;
  t.base = base;
  t.name = name;
  t.func = func;
  tests->push_back(t);
  return true;
}

int RunAllTests() {
  int num = 0;
  if (tests != NULL) {
    for (std::size_t i = 0; i < tests->size(); ++i) {
      const Test& t = (*tests)[i];
      fprintf(stderr, " ---- Test %s.%s\n", t.base, t.name);
      (*t.func)();
      ++num;
    }
  }
  fprintf(stderr, " ==== PASSED %d tests\n", num);
  if (tests != NULL) {
    delete tests;
    tests = NULL;
  }
  return 0;
}

} //namespace test
} //namespace tools
