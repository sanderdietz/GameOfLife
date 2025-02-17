#include "GameOfLife.h"

#include <iostream>

GameOfLife::GameOfLife()
    : m_window(nullptr), m_cellWidth(0), m_cellHeight(0), m_grid(), m_speed(0.0)
{
}

GameOfLife::GameOfLife(const Settings& settings)
    : m_speed(settings.speed)
{
    m_speed = settings.speed;

    // GLFW initialization
    if (!glfwInit())
        std::cout << "Error: GLFW not initialized" << std::endl;

    m_window = glfwCreateWindow(settings.resolutionWidth, settings.resolutionHeight, "GameOfLife", nullptr, nullptr);
    if (!m_window)
    {
        glfwTerminate();
        std::cout << "Error: no window created" << std::endl;
    }

    glfwMakeContextCurrent(m_window);
    glfwSetWindowAttrib(m_window, GLFW_RESIZABLE, GLFW_FALSE);

    // Define the number of rows and columns
    int windowWidth, windowHeight;
    glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
    int cellSizePixel = windowHeight / settings.rows;
    int cols = windowWidth / cellSizePixel;
    m_cellHeight = 2.0f / settings.rows;
    m_cellWidth = 2.0f / cols;

    // Define grid of zeros
    m_grid = Grid(settings.rows, cols);
    m_grid.setRandom();
}

void GameOfLife::drawCell(float x, float y)
{
    glBegin(GL_TRIANGLES);

    glVertex2f(x, y);
    glVertex2f(x + m_cellWidth, y);
    glVertex2f(x, y + m_cellHeight);

    glVertex2f(x + m_cellWidth, y);
    glVertex2f(x, y + m_cellHeight);
    glVertex2f(x + m_cellWidth, y + m_cellHeight);

    glEnd();
}

void GameOfLife::loop()
{
    double lastFrame = glfwGetTime();
    
    // Main loop
    while (!glfwWindowShouldClose(m_window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        double currentFrame = glfwGetTime();
        if (currentFrame - lastFrame > m_speed)
        {
            lastFrame = currentFrame;
            m_grid = m_grid.getNextGrid();
        }

        for (int i = 0; i < m_grid.getRows(); i++)
        {
            float y = -1.0f + (float)(2 * i) / (float)(m_grid.getRows());
            for (int j = 0; j < m_grid.getCols(); j++)
            {
                float x = -1.0f + (float)(2 * j) / (float)(m_grid.getCols());
                if (m_grid.getCell(i, j))
                    drawCell(x, y);
            }
        }

        glfwSwapBuffers(m_window);

        glfwPollEvents();
    }
}
