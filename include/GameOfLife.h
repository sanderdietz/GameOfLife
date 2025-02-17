#pragma once

#include "Grid.h"
#include "Settings.h"
#include <GLFW/glfw3.h>

class GameOfLife
{
private:
    GLFWwindow* m_window;
    float m_cellWidth;
    float m_cellHeight;
    Grid m_grid;
    double m_speed;

public:
    GameOfLife();
    GameOfLife(const Settings& settings);
    ~GameOfLife() { glfwTerminate(); }

    void drawCell(float x, float y);
    void loop();
};
