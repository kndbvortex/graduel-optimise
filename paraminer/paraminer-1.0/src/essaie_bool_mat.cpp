#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

class BoolMatrix : public std::vector<bool>
{
private:
    int N;
    std::vector<std::string> columnNames;
    std::unordered_map<std::string, int> columnIndices;

public:
    inline BoolMatrix(int N = 0, bool fill = false) : std::vector<bool>(N * N, fill), N(N)
    {
        for(int i=1; i<=N; i++){
            columnNames.push_back(to_string(i));
            columnIndices[to_string(i)] = i-1;
        }
    }

    inline BoolMatrix(const BoolMatrix &other) : std::vector<bool>(other), N(other.N),
                                                 columnNames(other.columnNames),
                                                 columnIndices(other.columnIndices)
    {
    }

    inline BoolMatrix &operator=(const BoolMatrix &other)
    {
        std::vector<bool>::operator=(other);
        N = other.N;
        columnNames = other.columnNames;
        columnIndices = other.columnIndices;
        return *this;
    }

    inline void set_column_names(const std::vector<std::string> &names)
    {
        N = names.size();
        this->resize(N * N);
        columnNames = names;
        columnIndices.clear();
        for (int i = 0; i < N; ++i)
        {
            columnIndices[names[i]] = i;
        }
    }

    inline BoolMatrix bitwise_and(const BoolMatrix &other) const
    {
        std::vector<std::string> sharedColumns;
        std::unordered_map<std::string, std::pair<int, int>> columnMapping;

        // Determine the shared columns
        for (const auto &col : columnNames)
        {
            if (other.columnIndices.count(col))
            {
                sharedColumns.push_back(col);
                columnMapping[col] = {columnIndices.at(col), other.columnIndices.at(col)};
            }
        }

        int newSize = sharedColumns.size();
        BoolMatrix result(newSize, false);
        result.set_column_names(sharedColumns);

        for (int i = 0; i < newSize; ++i)
        {
            for (int j = 0; j < newSize; ++j)
            {
                const auto &col = sharedColumns[j];
                const auto &indices = columnMapping[col];
                bool value = get_value(indices.first, i) && other.get_value(indices.second, i);
                result.set_value(j, i, value);
            }
        }

        return result;
    }
    inline void set_N(int n)
    {
        N = n;
        this->resize(N * N);
    }

    inline int get_size() const { return N; }

    inline void set_value(int col, int row, bool v)
    {
        assert(col < N && row < N);
        (*this)[row * N + col] = v;
    }

    inline bool get_value(int col, int row) const
    {
        assert(col < N && row < N);
        return (*this)[row * N + col];
    }

    inline bool null_row_p(int row) const
    {
        assert(row < N);
        int range_start = N * row;
        int range_end = N * (row + 1);
        for (int i = range_start; i < range_end; i++)
            if ((*this)[i])
                return false;
        return true;
    }

    inline const std::vector<std::string> &get_column_names() const
    {
        return columnNames;
    }
};

void printMatrix(const BoolMatrix &matrix, int rows, int cols)
{
    auto columns_names = matrix.get_column_names(); 
    for (int i = 0; i < columns_names.size(); i++)
    {
        cout <<  columns_names[i] << " ";
    }

    cout << endl;
    
    
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

int main() {
    BoolMatrix m1(3, false);
    // m1.set_column_names({"A", "B", "C"});
    m1.set_value(0, 0, true);
    m1.set_value(1, 1, true);
    m1.set_value(1, 0, true);
    m1.set_value(1, 2, true);
    m1.set_value(2, 2, true);

    printMatrix(m1, 3, 3);

    BoolMatrix m2(3, false);
    // m2.set_column_names({"B", "C", "D"});
    m2.set_value(0, 0, true);
    m2.set_value(1, 1, true);
    m2.set_value(2, 2, true);

    printMatrix(m2, 3, 3);

    cout << "OKK" << endl;
    BoolMatrix result = m1.bitwise_and(m2);

    cout << "Result matrix columns: " << endl;
    printMatrix(result, result.get_size(), result.get_size());

    // for (const auto& col : result.get_column_names()) {
    //     cout << col << " ";
    // }
    // cout << endl;

    // // Print the result matrix
    // for (int i = 0; i < result.get_size(); ++i) {
    //     for (int j = 0; j < result.get_size(); ++j) {
    //         cout << result.get_value(j, i) << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}