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
    ioctl(0, TIOCGWINSZ, &w);
    printf("lines %d\n", w.ws_row);
    printf("columns %d\n", w.ws_col);
    height = w.ws_row;
    width = w.ws_col;
    std::string test = "";
    for (int i = 0; i < width; i++) {
      test += ' ';
    }
    buffer.resize(height, test);
  }

  void render() {
    for (int i = 0; i < buffer.size(); i++)
      std::cout << buffer[i] << std::endl;
  }

  void paint(int starting_r, int starting_c, std::string s) {
    if (s.size() + starting_c >= width) {
      s = s.substr(width - starting_c);
    }
    for (int i = 0; i < s.size(); i++) {
      buffer[starting_r][i + starting_c] = s[i];
    }
  }

  int getWidth() { return width; }
  int getHeight() { return height; }

private:
  int width, height;
  std::vector<std::string> buffer;
};

#endif
