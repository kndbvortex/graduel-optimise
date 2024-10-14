#include <vector>
#include <iostream>
#include "math.h"
using namespace std;

// Function to delete row and column i from the matrix
std::vector<int> deleteRowAndColumn(const std::vector<int> &matrix, int rows, int cols, int i)
{
    if (i < 0 || i >= rows || i >= cols || matrix.size() != rows * cols)
    {
        return matrix;
    }

    std::vector<int> result;
    for (int r = 0; r < rows; ++r)
    {
        if (r == i)
            continue;
        for (int c = 0; c < cols; ++c)
        {
            if (c == i)
                continue;
            result.push_back(matrix[r * cols + c]);
        }
    }

    return result;
}

// Function to sum elements of a particular row and column
int sumRowAndColumn(const std::vector<int> &matrix, int rows, int cols, int i)
{
    if (i < 0 || i >= rows || i >= cols || matrix.size() != rows * cols)
    {
        return 0;
    }

    int sum = 0;

    // Sum the row
    for (int c = 0; c < cols; ++c)
    {
        sum += matrix[i * cols + c];
    }

    // Sum the column (excluding the element already counted in the row)
    for (int r = 0; r < rows; ++r)
    {
        if (r != i)
        {
            sum += matrix[r * cols + i];
        }
    }

    return sum;
}

// Helper function to print the matrix
void printMatrix(const std::vector<int> &matrix, int rows, int cols)
{
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            std::cout << matrix[r * cols + c] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(){
    std::vector<int> m = {1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
    for (int i = 0; i < m.size(); i++)
    {
        m[i] = i;
    }
    printMatrix(m, 4, 4);


    std::cout << sumRowAndColumn(m, 4, 4, 0) << "......" << std::endl;

    m = deleteRowAndColumn(m, (int)sqrt(m.size()), (int)sqrt(m.size()), 1);
    printMatrix(m, (int)sqrt(m.size()), (int)sqrt(m.size()));
}
