/**
 * @file   bool_matrix.hpp
 * @author Benjamin Negrevergne <benjamin@neb.dyn.cs.kuleuven.be>
 * @date   Sat Feb  9 15:31:10 2013
 *
 * @brief  Convinience boolean matrix class for gradual itemset mining.
 *
 *
 */

// bool_matrix.hpp
// Made by Benjamin Negrevergne
// Started on

#ifndef _BOOL_MATRIX_HPP_
#define _BOOL_MATRIX_HPP_

#include <vector>
#include <iostream>

/* NOTE: TODO std::vector<bool> are now standard containers with one byte
   elements, this should be replaced by a bitwise implementation for more efficiency*/

/* Square Bool Matrix */

/**
 * @class BoolMatrix
 *
 * @brief Convinience boolean matrix class for gradual itemset mining.
 *
 * Boolean Square Matrix.
 *
 */
// class BoolMatrix : public std::vector<bool> {

// private:
//   int N;

// public:
//   /**
//    * Create a new boolean matrix of size NxN
//    * @param n num of rows or num of cols.
//    * @param fill the matrix with this value.
//    */
//   inline BoolMatrix(int N = 0, bool fill = false):
//     std::vector<bool>(N*N, fill), N(N){
//   }

//   /**
//    * \brief Copy constructor.
//    */
//   inline BoolMatrix(const BoolMatrix &other):
//     std::vector<bool>(other), N(other.N){
//   }

//   /**
//    * \brief Assignment operator.
//    */
//   inline BoolMatrix &operator=(const BoolMatrix &other){
//     std::copy(other.begin(), other.end(), this->begin());
//     N=other.N;
//     return *this;
//   }

//   /**
//    * \brief Assignment operator.
//    */
//   inline BoolMatrix &bitwise_and(const BoolMatrix &other){
//     assert(get_size() == other.get_size());
//     for(int i = 0; i < N; i++){
//       //TODO improve efficiency!
//       bool b = (*this)[i];
// 	b &= other[i];
//       (*this)[i] = b;
//     }
//     return *this;
//   }

//   inline void set_N(int n) {N=n;}

//   /**
//    * \brief Return the size of the matrix. (sqrt of the #of element.)
//    */
//   inline int get_size() const {return N;}

//   /**
//    * \brief Set matrix value [\col, \row] to \v.
//    */
//   inline void set_value(int col, int row, bool v){
//     assert(col < N && row < N);
//     (*this)[col*N+row] = v;
//   }

//   /**
//    * \brief Return matrix value at [\col, \row].
//    */
//   inline bool get_value(int col, int row) const {
//     assert(col < N && row < N);
//     return (*this)[col*N+row];
//   }

//   /**
//    * \brief Return true if no bit is set in Row \row.
//    */
//   inline bool null_row_p(int row) const {
//     assert(row < N);
//     int range_start = N * row;
//     int range_end = N * (row+1);
//     for(int i = range_start; i < range_end; i++)
//       if((*this)[i]) return false;
//     return true;
//   }

// };

class BoolMatrix : public std::vector<bool>
{
private:
  int N;
  std::vector<std::string> columnNames;
  std::unordered_map<std::string, int> columnIndices;

public:
  inline BoolMatrix(int N = 0, bool fill = false) : std::vector<bool>(N * N, fill), N(N)
  {
    for (int i = 0; i < N; i++)
    {
      columnNames.push_back(std::to_string(i));
    }
    set_column_names(columnNames);
  }

  inline BoolMatrix(const BoolMatrix &other) : std::vector<bool>(other), N(other.N),
                                               columnNames(other.columnNames),
                                               columnIndices(other.columnIndices)
  {
  }

  inline bool operator==(const BoolMatrix &op1) const
  {
    if (N == op1.N && columnNames == op1.columnNames){
      for (int i = 0; i < N; ++i)
      {
        for (const auto &col : columnNames)
        {
          if (get_value(columnIndices.at(col), i) != op1.get_value(op1.columnIndices.at(col), i))
          {
            return false;
          }
        }
      }
      return true;
    }
    return false;
  }

  inline void set_column_names(const std::vector<std::string> &names)
  {
    columnNames = names;
    columnIndices.clear();
    for (int i = 0; i < N; ++i)
    {
      columnIndices[names[i]] = i;
    }
  }
  //   inline BoolMatrix &operator=(const BoolMatrix &other){
  //     std::copy(other.begin(), other.end(), this->begin());
  //     N=other.N;
  //     return *this;
  //   }

  inline BoolMatrix &operator=(const BoolMatrix &other)
  {
    std::vector<bool>::operator=(other);
    N = other.N;
    columnNames = other.columnNames;
    columnIndices = other.columnIndices;
    // auto columns_names = get_column_names();
    // for (int i = 0; i < columns_names.size(); i++)
    // {
    //   std::cout << columns_names[i] << " ";
    // }

    // std::cout << std::endl;

    // for (int r = 0; r < get_size(); r++)
    // {
    //   for (int c = 0; c < get_size(); c++)
    //   {
    //     std::cout << get_value(c, r) << " ";
    //   }
    //   std::cout << std::endl;
    // }
    // std::cout << std::endl;
    return *this;
  }

  inline BoolMatrix &bitwise_and_v2(const BoolMatrix &other)
  {
    assert(get_size() == other.get_size());
    for (int i = 0; i < N; i++)
    {
      // TODO improve efficiency!
      bool b = (*this)[i];
      b &= other[i];
      (*this)[i] = b;
    }
    return *this;
  }
  inline BoolMatrix bitwise_and(const BoolMatrix &other) 
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

    for (int i = 0; i < newSize; ++i)
    {
      for (int j = 0; j < newSize; ++j)
      {
        const auto &col = sharedColumns[j];
        const auto &indices = columnMapping[col];
        bool value = get_value(indices.first, i) && other.get_value(indices.second, i);
        // std::cout << "before choc" << std::endl;
        (*this)[i * newSize + j] = value;
        // std::cout << "end choc" << std::endl;
      }
    }
    set_N(newSize);
    (*this).set_column_names(sharedColumns);
    // for (int i = 0; i < newSize; i++)
    // {
    //   // TODO improve efficiency!
    //   const auto &col = sharedColumns[i];
    //   const auto &indices = columnMapping[col];
    //   bool b = (*this)[indices.first];
    //   b &= other[indices.second];
    //   result[i] = b;
    // }
    // set_column_names(result.get_column_names());

    return (*this);
  }

  inline void deleteRowAndColumn(int i)
  {

    if (i < 0 || i >= N)
    {
      return ;
    }

    std::vector<std::string> columnNames = get_column_names();
    columnNames.erase(std::find(columnNames.begin(), columnNames.end(), columnNames[i]));
    

    int newRow = 0;
    for (int row = 0; row < N; ++row)
    {
      if (row == i)
        continue;

      int newCol = 0;
      for (int col = 0; col < N; ++col)
      {
        if (col == i)
          continue;
        set_value(newCol, newRow, get_value(col, row));
        ++newCol;
      }
      ++newRow;
    }
    set_N(N-1);
    set_column_names(columnNames);
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

inline void printMatrix(const BoolMatrix &matrix)
{
  auto columns_names = matrix.get_column_names();
  for (int i = 0; i < columns_names.size(); i++)
  {
    std::cout << columns_names[i] << " ";
  }

  std::cout << std::endl;

  for (int r = 0; r < matrix.get_size(); ++r)
  {
    for (int c = 0; c < matrix.get_size(); ++c)
    {
      std::cout << matrix.get_value(c, r) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

#endif /* _BOOL_MATRIX_HPP_ */
