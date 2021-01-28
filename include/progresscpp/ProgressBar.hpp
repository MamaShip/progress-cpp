#pragma once
#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H
#include <chrono>
#include <iostream>

namespace progresscpp {
class ProgressBar {
private:
  unsigned int ticks = 0;

  const unsigned int total_ticks;
  const unsigned int bar_width;
  const char complete_char = '=';
  const char incomplete_char = ' ';
  const std::chrono::steady_clock::time_point start_time =
      std::chrono::steady_clock::now();

public:
  ProgressBar(unsigned int total, unsigned int width, char complete,
              char incomplete)
      : total_ticks{total}, bar_width{width}, complete_char{complete},
        incomplete_char{incomplete} {}

  ProgressBar(unsigned int total, unsigned int width)
      : total_ticks{total}, bar_width{width} {}

  unsigned int operator++() { return ++ticks; }

  void display() const {
    float progress = (float)ticks / total_ticks;
    int pos = (int)(bar_width * progress);

    std::chrono::steady_clock::time_point now =
        std::chrono::steady_clock::now();
    auto time_elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time)
            .count();

    std::cout << "[\033[32m"; // \033[32m  --> ANSI转义序列，设置字体为绿色

    for (unsigned int i = 0; i < bar_width; ++i) {
      if (i < pos)
        std::cout << complete_char;
      else if (i == pos)
        std::cout << ">";
      else
        std::cout << incomplete_char;
    }
    std::cout << "\033[0m] " // \033[0m  --> ANSI转义序列，关闭所有属性
              << int(progress * 100.0) << "% " << float(time_elapsed) / 1000.0
              << "s\r";
    std::cout.flush();
  }

  void done() const {
    display();
    std::cout << std::endl;
  }
};
} // namespace progresscpp
#endif // PROGRESS_BAR_H
/*
使用方法：
// initialize the bar
progresscpp::ProgressBar progressBar(max_idx, bar_len);

for (int i = 0; i < max_idx; i++){
    // record the tick
    ++progressBar;
    // display the bar
    progressBar.display();
}
// tell the bar to finish
progressBar.done();
*/