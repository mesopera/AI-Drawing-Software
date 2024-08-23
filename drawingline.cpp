#include <GLFW/glfw3.h>
#include <iostream>
#include "drawingline.h"
#include <vector>

// Variables to track mouse state
bool drawing = false;
double startX, startY, endX, endY;

// Vector to store all drawn lines
std::vector<Line> lines;

// Mouse button callback
void mouse_button(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            drawing = true;
            glfwGetCursorPos(window, &startX, &startY);
            std::cout << "Mouse pressed at: (" << startX << ", " << startY << ")\n";
        }
        else if (action == GLFW_RELEASE)
        {
            drawing = false;
            glfwGetCursorPos(window, &endX, &endY);
            std::cout << "Mouse released at: (" << endX << ", " << endY << ")\n";

            // Store the line in the vector
            lines.push_back({ static_cast<int>(startX), static_cast<int>(startY), static_cast<int>(endX), static_cast<int>(endY) });
        }
    }
}

// Cursor position callback (if you want to track cursor position while dragging)
void cursor_position(GLFWwindow* window, double xpos, double ypos)
{
    if (drawing)
    {
        endX = xpos;
        endY = ypos;
        std::cout << "Current cursor position: (" << xpos << ", " << ypos << ")\n";
    }
}

// Function to plot a single pixel using OpenGL
void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Bresenham's line drawing algorithm
void drawLineBresenham(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true)
    {
        plot(x1, y1); // Plot the current point

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

// Function to draw all stored lines
void drawStoredLines()
{
    glColor3f(1.0f, 0.0f, 1.0f); // Red color for the lines
    for (const Line& line : lines)
    {
        drawLineBresenham(line.x1, line.y1, line.x2, line.y2);
    }
}
