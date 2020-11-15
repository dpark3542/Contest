#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#include "../tasks/A.cpp"

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

  int get_memory_size() {
    std::ifstream proc;
    proc.open("/proc/" + std::to_string(getpid()) + "/status");
    std::string s = "", t;
    while (s != "VmPeak:") {
      proc >> s;
    }
    proc >> s;
    return std::stoi(s);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::vector<jhelper::Test> tests = {
    {"1", "1", true, true},{"2", "2", true, true},{"4", "3", true, true},
  };
  bool allOK = true;
  int testID = 0;
  std::cout << std::fixed;
  double maxTime = 0.0;
  int maxMemory = 0;
  for(const jhelper::Test& test : tests) {
    std::cout << "Test #" << testID++ << std::endl;
    if (!test.active) {
      std::cout << "SKIPPED\n" << std::endl;
      continue;
    }
    int fd[2];
    if (pipe(fd) < 0) {
      std::cerr << "Pipe failed." << std::endl;
      return 1;
    }
    pid_t pid = fork();
    if (pid == 0) {
      // child
      close(fd[0]);

      // run test
      std::stringstream in(test.input);
      std::ostringstream out;
      int mem_start = jhelper::get_memory_size();
      std::clock_t time_start = std::clock();
      A solver;
      solver.solve(in, out);
      std::clock_t time_finish = std::clock();
      int mem_end = jhelper::get_memory_size();

      // parse output
      double time = double(time_finish - time_start) / CLOCKS_PER_SEC;
      int memory = mem_end - mem_start;
      bool result = true;
      if (test.has_output) {
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
          std::cout << "Input: " << std::endl;
          std::cout << test.input << std::endl;
          std::cout << "Expected output: " << std::endl;
          std::cout << test.output << std::endl;
          std::cout << "Actual output: " << std::endl;
          std::cout << out.str() << std::endl;
          std::cout << "Result: Wrong Answer" << std::endl;
          std::cout << msg << std::endl;
        }
      }
      else {
        std::cout << "Actual output: \n" << out.str() << std::endl;
      }
      std::cout.precision(2);
      std::cout << "Time: " << time << " s." << std::endl;
      std::cout << "Memory: " << memory << " kB.\n" << std::endl;
      std::cout.precision(6);

      // write and close
      write(fd[1], &result, sizeof(bool));
      write(fd[1], &time, sizeof(double));
      write(fd[1], &memory, sizeof(int));
      close(fd[1]);
      return 0;
    }
    else if (pid < 0) {
      // error
      std::cerr << "Fork failed." << std::endl;
      return -1;
    }
    // parent
//    std::cerr << "PID: " << pid << std::endl;
    close(fd[1]);
    // TODO: kill child after timer
    if (wait(NULL) == -1) {
      std::cerr << "Child process error." << std::endl;
    }
    bool result;
    double time;
    int memory;
    read(fd[0], &result, sizeof(bool));
    read(fd[0], &time, sizeof(double));
    read(fd[0], &memory, sizeof(int));
    close(fd[0]);
    allOK &= result;
    maxTime = time > maxTime ? time : maxTime;
    maxMemory = memory > maxMemory ? memory : maxMemory;
  }
  if (allOK) {
    std::cout << "All OK" << std::endl;
  }
  else {
    std::cout << "Some cases failed" << std::endl;
  }
  std::cout.precision(2);
  std::cout << "Max time: " << maxTime << " s." << std::endl;
  std::cout << "Max memory: " << maxMemory << " kB." << std::endl;
  return 0;
}