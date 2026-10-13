#ifndef CONSOLE_COLOR_HPP
#define CONSOLE_COLOR_HPP

// Code for painting in the console
// specifically for unix based systems

#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <vector>

class Console {
public:
  Console() {
    struct winsize w;
    ioctl(1, TIOCGWINSZ, &w);
    height = w.ws_row;
    width = w.ws_col;
    buffer.resize(height, std::vector<std::string>(width, "\u2588"));
    coloring.resize(height, std::vector<std::string>(width));
  }

  void render() {
    for (size_t i = 0; i < buffer.size(); i++) {
      for (size_t j = 0; j < buffer[i].size(); j++) {
        if (coloring[i][j] != "")
          std::cout << coloring[i][j];
        std::cout << buffer[i][j];
        if (coloring[i][j] != "")
          std::cout << "\033[0m";
      }
      if (i + 1 < buffer.size())
        std::cout << '\n';
    }
  }

  void paint(int starting_r, int starting_c, std::string s,
             std::string color = "") {
    if (s.size() + starting_c >= static_cast<size_t>(width)) {
      s = s.substr(0, width - starting_c);
    }
    for (size_t i = 0; i < s.size(); i++) {
      coloring[starting_r][i + starting_c] = color;
      buffer[starting_r][i + starting_c] = std::string(1, s[i]);
    }
  }

  void color(int r, int c, std::string color) { coloring[r][c] = color; }

  int getWidth() { return width; }
  int getHeight() { return height; }
  std::vector<std::vector<std::string>> buffer;

private:
  int width, height;
  std::vector<std::vector<std::string>> coloring;
};

#endif
