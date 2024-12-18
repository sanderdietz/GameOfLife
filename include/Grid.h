#pragma once

#include <list>

class Grid
{
private:
    int m_rows;
    int m_cols;
    __uint128_t* m_cells;

public:
    // Constructors
    Grid();
    Grid(int rows, int cols);
    Grid(const Grid& other);
    Grid(Grid&& other);
    ~Grid() { delete[] m_cells; }

    Grid& operator=(const Grid& other);
    Grid& operator=(Grid&& other);

    void log() const;
    int getRows() const { return m_rows; }
    int getCols() const { return m_cols; }
    void setCell(int i, int j) { m_cells[j] |= (__uint128_t)1 << i; }
    bool getCell(int i, int j) const { return m_cells[j] >> i & 1; }
    
    Grid getNextGrid() const;
    void setRandom(int seed = 0);

private:
    std::list<std::pair<int, int>> getNeighborsCoords(int i, int j) const;
};