#include "Grid.h"

#include <iostream>
#include <bitset>

Grid::Grid()
    : m_rows(0), m_cols(0), m_cells(nullptr)
{
}

Grid::Grid(int rows, int cols)
    : m_rows(rows), m_cols(cols), m_cells(new __uint128_t[cols])
{
    std::fill(m_cells, m_cells + cols, 0);
}

Grid::Grid(const Grid& other)
    : m_rows(other.getRows()), m_cols(other.getCols()), m_cells(new __uint128_t[m_cols])
{
    std::copy(other.m_cells, other.m_cells + m_cols, m_cells);
}

Grid::Grid(Grid&& other)
    : m_rows(other.getRows()), m_cols(other.getCols()), m_cells(other.m_cells)
{
    other.m_rows = 0;
    other.m_cols = 0;
    other.m_cells = nullptr;
}

Grid& Grid::operator=(const Grid& other)
{
    if (this != &other)
    {
        delete[] m_cells;
        m_rows = other.getRows();
        m_cols = other.getCols();
        m_cells = new __uint128_t[m_cols];
        std::copy(other.m_cells, other.m_cells + m_cols, m_cells);
    }
    return *this;
}

Grid& Grid::operator=(Grid&& other)
{
    if (this != &other)
    {
        delete[] m_cells;
        m_rows = other.getRows();
        m_cols = other.getCols();
        m_cells = other.m_cells;
        other.m_rows = 0;
        other.m_cols = 0;
        other.m_cells = nullptr;
    }
    return *this;
}

void Grid::log() const
{
    for (int j = 0; j < m_cols; j++)
        std::cout << std::bitset<128>(m_cells[j]) << std::endl;
}

void Grid::setRandom(int seed)
{
    srand(seed);
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            if (rand() % 100 < 50)
                setCell(i, j);
        }
    }
}

std::list<std::pair<int, int>> Grid::getNeighborsCoords(int i, int j) const
{
    std::list<std::pair<int, int>> neighbors;

    if (i > 0)
        neighbors.push_back(std::make_pair(i - 1, j));
    if (i < m_rows - 2)
        neighbors.push_back(std::make_pair(i + 1, j));
    if (j > 0)
        neighbors.push_back(std::make_pair(i, j - 1));
    if (j < m_cols - 2)
        neighbors.push_back(std::make_pair(i, j + 1));
    if (i > 0 && j > 0)
        neighbors.push_back(std::make_pair(i - 1, j - 1));
    if (i > 0 && j < m_cols - 2)
        neighbors.push_back(std::make_pair(i - 1, j + 1));
    if (i < m_rows - 2 && j > 0)
        neighbors.push_back(std::make_pair(i + 1, j - 1));
    if (i < m_rows - 2 && j < m_cols - 2)
        neighbors.push_back(std::make_pair(i + 1, j + 1));

    return neighbors;
}

Grid Grid::getNextGrid() const
{
    Grid nextGrid(m_rows, m_cols);
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            int numAliveNeighbors = 0;
            for (std::pair<int, int> neighborCoords : getNeighborsCoords(i, j))
            {
                if (getCell(neighborCoords.first, neighborCoords.second))
                    numAliveNeighbors++;
            }
            if (getCell(i, j) && (numAliveNeighbors == 2 || numAliveNeighbors == 3))
                nextGrid.setCell(i, j);
            if (!getCell(i, j) && numAliveNeighbors == 3)
                nextGrid.setCell(i, j);
        }
    }
    return nextGrid;
}
