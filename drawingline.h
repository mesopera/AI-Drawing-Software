#ifndef DRAWING_H
#define DRAWING_H

#include <GLFW/glfw3.h>
#include <vector>

// Function prototypes
void mouse_button(GLFWwindow* window, int button, int action, int mods);
//void cursor_position(GLFWwindow* window, double xpos, double ypos);
void drawStoredLines();
void drawLineBresenham(int x1, int y1, int x2, int y2);
void plot(int x, int y);

// Structure to store line coordinates
struct Line
{
    int x1, y1, x2, y2;
};

extern std::vector<Line> lines; // Global vector to store all lines

#endif


