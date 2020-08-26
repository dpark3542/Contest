#include "../tasks/TaskE.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>

namespace jhelper {

struct Test {
  std::string input;
  std::string output;
  bool active;
  bool has_output;
};

std::vector<std::vector<std::string>> tokenize(std::string s) {
  std::vector<std::vector<std::string>> v;
  std::stringstream ss(s);
  for (std::string line; std::getline(ss, line); ) {
    std::vector<std::string> w;
    std::istringstream iss(line);
    for (std::string token; iss >> token; ) {
      w.push_back(token);
    }
    if (!w.empty()) {
      v.push_back(w);
    }
  }
  return v;
}

bool check(std::string expected, std::string actual) {
  while(!expected.empty() && isspace(*--expected.end()))
    expected.erase(--expected.end());
  while(!actual.empty() && isspace(*--actual.end()))
    actual.erase(--actual.end());
  return expected == actual;
}

} // namespace jhelper

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::vector<jhelper::Test> tests = {
    {"4\n1 4 1 1\n", "2\n", true, true},{"5\n1 0 1 0 1\n", "3\n", true, true},
  };
  bool allOK = true;
  int testID = 0;
  std::cout << std::fixed;
  double maxTime = 0.0;
  for(const jhelper::Test& test: tests ) {
    std::cout << "Test #" << ++testID << std::endl;
    if (test.active) {
      std::cout << "Input: \n" << test.input << std::endl;
      if (test.has_output) {
        std::cout << "Expected output: \n" << test.output << std::endl;
      }
      else {
        std::cout << "Expected output: \n" << "N/A" << std::endl;
      }
      std::stringstream in(test.input);
      std::ostringstream out;
      std::clock_t start = std::clock();
      TaskE solver;
      solver.solve(in, out);
      std::clock_t finish = std::clock();
      double currentTime = double(finish - start) / CLOCKS_PER_SEC;
      maxTime = currentTime > maxTime ? currentTime : maxTime;
      std::cout << "Actual output: \n" << out.str() << std::endl;
      if (test.has_output) {
//        bool result = jhelper::check(test.output, out.str());
        bool result = true;
        std::string msg;
        std::vector<std::vector<std::string>> a = jhelper::tokenize(test.output), b = jhelper::tokenize(out.str());
        if (a.size() != b.size()) {
          result = false;
          msg = "Expected " + std::to_string(a.size()) + " lines, found " + std::to_string(b.size()) + " lines.";
        }
        for (int i = 0; result && i < a.size(); i++) {
          if (a[i].size() != b[i].size()) {
            result = false;
            msg = "Line " + std::to_string(i + 1) + ": expected " + std::to_string(a[i].size()) + " tokens, found " + std::to_string(b[i].size()) + " tokens.";
            break;
          }
          for (int j = 0; j < a[i].size(); j++) {
            if (a[i][j] != b[i][j]) {
              result = false;
              msg = "Line " + std::to_string(i + 1) + ", token " + std::to_string(j + 1) + ": expected '" + a[i][j] + "', found '" + b[i][j] + "'.";
              break;
            }
          }
        }
        if (result) {
          std::cout << "Result: OK" << std::endl;
        }
        else {
          std::cout << "Result: Wrong Answer" << std::endl;
          std::cout << msg << std::endl;
        }
        allOK = allOK && result;
      }
      std::cout << "Time: " << currentTime << "s." << std::endl;
    }
    else {
      std::cout << "SKIPPED\n";
    }

    std::cout << std::endl;
  }
  if(allOK) {
    std::cout << "All OK" << std::endl;
  }
  else {
    std::cout << "Some cases failed" << std::endl;
  }
  std::cout << "Maximal time: " << maxTime << "s." << std::endl;
  return 0;
}