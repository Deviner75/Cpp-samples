// file mymatrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <functional>

template <typename T>
class MyMatrix
{
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;
    using iterator = typename std::vector<value_type>::iterator;
    using const_iterator = typename std::vector<value_type>::const_iterator;
    using size_type = std::size_t;

private:
    size_type m_rows;
    size_type m_cols;
    std::vector<value_type> m_buffer;

public:
    MyMatrix(size_type dimx = 3, size_type dimy = 3)
        : m_rows(dimx)
        , m_cols(dimy)
        , m_buffer(dimx* dimy)
    {}
    // Copy constructor
    MyMatrix(MyMatrix const& copy)
        : m_rows(copy.m_rows)
        , m_cols(copy.m_cols)
        , m_buffer(copy.m_buffer)
    {}
    // Move constructor
    MyMatrix(MyMatrix&& move) noexcept
    {
        *this = std::move(move);
    }
    explicit MyMatrix<T>(iterator begin, iterator end, size_type dimx, size_type dimy)
        : m_rows(dimx)
        , m_cols(dimy)
        , m_buffer(std::distance(begin, end))
    {
        std::copy(begin, end, m_buffer.begin());
    }
    // Copy assignment
    MyMatrix& operator=(MyMatrix const& copy)
    {
        // Copy and Swap idiom
        MyMatrix tmp(copy);
        tmp.swap(*this);
        return *this;
    }
    // Move assignment
    MyMatrix& operator=(MyMatrix&& move) noexcept
    {
        move.swap(*this);
        return *this;
    }

    // Iterators
    iterator       begin() { return m_buffer.begin(); }
    const_iterator begin()  const { return m_buffer.begin(); }
    const_iterator cbegin() const { return begin(); }

    iterator       end() { return m_buffer.end(); }
    const_iterator end()    const { return m_buffer.end(); }
    const_iterator cend()   const { return end(); }

    // Access operators with validation
    reference operator()(const size_type x, const size_type y)
    {
        size_type index = m_cols * x + y;
        assert(index < m_buffer.size() && "Index is out of range");
        return m_buffer[index];
    }
    const_reference operator()(const size_type x, const size_type y) const
    {
        size_type index = m_cols * x + y;
        assert(index < m_buffer.size() && "Index is out of range");
        return m_buffer[index];
    }
    reference operator[](size_type index)
    {
        assert(index < m_buffer.size() && "Index is out of range");
        return m_buffer[index];
    }
    const_reference operator[](size_type index) const
    {
        assert(index < m_buffer.size() && "Index is out of range");
        return m_buffer[index];
    }

    // Mutating functions
    void ident()
    {
        assert(m_rows == m_cols && "Matrix must be square!");
        for (size_type x = 0; x < m_rows; ++x) {
            for (size_type y = 0; y < m_cols; ++y)
                m_buffer[m_cols * x + y] = static_cast<T>(x == y); // CORRECT ?
        }
    }
    void fillRand()
    {
        std::generate(m_buffer.begin(), m_buffer.end(), []() {return std::rand() % 10; });
    }
    void swap(MyMatrix<value_type>& other) noexcept
    {
        using std::swap;
        swap(this->m_rows, other.m_rows);
        swap(this->m_cols, other.m_cols);
        swap(this->m_buffer, other.m_buffer);
    }

    // Inspecting functions
    size_type rows() const
    { return m_rows; }
    size_type cols() const
    { return m_cols; }

    // Matrix mathematical operations
    template<class U>
    MyMatrix& operator+=(MyMatrix<U> const& mtx)
    {
        if (m_rows != mtx.rows() || m_cols != mtx.cols())
            throw std::invalid_argument("Matrix dimension must be the same.");
        std::transform(m_buffer.begin(), m_buffer.end(), mtx.begin(), m_buffer.begin(), std::plus<>{});
        return *this;
    }
    template<class U>
    MyMatrix& operator-=(MyMatrix<U> const& mtx)
    {
        if (m_rows != mtx.rows() || m_cols != mtx.cols())
            throw std::invalid_argument("Matrix dimension must be the same.");
        std::transform(m_buffer.begin(), m_buffer.end(), mtx.begin(), m_buffer.begin(), std::minus<>{});
        return *this;
    }
    MyMatrix  operator*(MyMatrix const& mtx) const
    {
        MyMatrix<T> tmp(*this);
        return tmp *= mtx;
    }
    MyMatrix  operator*=(MyMatrix const& mtx)
    {
        assert(m_cols == mtx.m_rows && "Invalid Matrix demensions.");
        MyMatrix<value_type> result(m_rows, mtx.m_cols);

        for (size_type r = 0; r < m_rows; r++) {
            for (size_type c = 0; c < mtx.m_cols; c++) {
                for (size_type i = 0; i < m_cols; i++) {
                    result.m_buffer[mtx.m_cols * r + c] += m_buffer[m_cols * r + i] * mtx.m_buffer[mtx.m_cols * i + c];
                }
            }
        }
        return result;
    }

    // Comparision
    bool operator==(MyMatrix const& mtx) const noexcept
    {
        return m_rows == mtx.m_rows && m_cols == mtx.m_cols && m_buffer == mtx.m_buffer;
    }
    bool operator!=(MyMatrix const& mtx) const noexcept { return !(*this == mtx); }

    // Matrix scalar operations
    MyMatrix& operator+(const T& value)
    {
        std::transform(m_buffer.begin(), m_buffer.end(), m_buffer.begin(), [&value](const T index) {return index + value; });
        return *this;
    }
    MyMatrix& operator-(const T& value)
    {
        std::transform(m_buffer.begin(), m_buffer.end(), m_buffer.begin(), [&value](const T index) {return index - value; });
        return *this;
    }
    MyMatrix& operator*(const T& value)
    {
        std::transform(m_buffer.begin(), m_buffer.end(), m_buffer.begin(), [&value](T index) {return index * value; });
        return *this;
    }
    MyMatrix& operator/(const T& value)
    {
        std::transform(m_buffer.begin(), m_buffer.end(), m_buffer.begin(), [&value](T index) {return index / value; });
        return *this;
    }

    // Unary operators
    MyMatrix operator-() const
    {
        MyMatrix result(*this);
        std::transform(result.begin(), result.end(), result.begin(), std::negate<>{});
        return result;
    }
    MyMatrix operator+() const
    {
        MyMatrix result(*this);
        std::transform(result.begin(), result.end(), result.begin(), std::abs<>{});
        return result;
    }
};

// << overload doesn't use private members, hence friend was useless
template <typename T>
std::ostream& operator<<(std::ostream& out, MyMatrix<T> const& mtx)
{
    std::size_t rows = mtx.rows();
    std::size_t cols = mtx.cols();

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            out << mtx(i, j) << ' ';
        }
        out << "\n";
    }
    return out;
}
template <typename T>
MyMatrix<T> transpose(MyMatrix<T> const& mtx)
{
    std::size_t rows = mtx.rows();
    std::size_t cols = mtx.cols();

    MyMatrix<T> result(cols, rows);

    for (std::size_t r = 0; r < rows * cols; r++) {
        std::size_t i = r / rows;
        std::size_t j = r % rows;
        result[r] = mtx[cols * j + i];
    }

    return result;
}
template <typename T>
MyMatrix<T> inverse(MyMatrix<T> const& mtx)
{
    MyMatrix<T> result(mtx);

    std::transform(result.begin(), result.end(), result.begin(), [](const T index) {return 1 / index; });

    return result;
}
template <typename T>
MyMatrix<T> symmetric(MyMatrix<T> const& mtx)
{
    assert(mtx.cols() == mtx.rows() && "Invalid Matrix demensions.");
    MyMatrix<T> result(mtx);
    return mtx * transpose(mtx);
}
#endif // MATRIX_H

// Matrix mathematical operations
template <typename T, typename U>
MyMatrix<T>  operator+(MyMatrix<T> mtx1, MyMatrix<U> const& mtx2)
{
    return mtx1 += mtx2;
}
template <typename T, typename U>
MyMatrix<T>  operator-(MyMatrix<T> mtx1, MyMatrix<U> const& mtx2)
{
    return mtx1 -= mtx2;
}