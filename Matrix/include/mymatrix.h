// file mymatrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <functional>
#include <type_traits>

template<typename T>
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
		, m_buffer(dimx * dimy)
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
	// Initializer list constructor
	MyMatrix(size_type dimx, size_type dimy, std::initializer_list<T> init)
		: m_rows(dimx)
		, m_cols(dimy)
		, m_buffer(dimx * dimy)
	{
		const size_type minlen{ std::min(m_buffer.size(), init.size()) };
		std::copy_n(init.begin(), minlen, m_buffer.begin());
	}
	// Iterator constructor
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
		MyMatrix<value_type> tmp(copy);
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
		if (x >= m_rows || y >= m_cols)
			throw std::invalid_argument("The index is out of range.");
		return m_buffer[m_cols * x + y];
	}
	const_reference operator()(const size_type x, const size_type y) const
	{
		if (x >= m_rows || y >= m_cols)
			throw std::invalid_argument("The index is out of range.");
		return m_buffer[m_cols * x + y];
	}
	reference operator[](size_type index)
	{
		if (index > m_buffer.size())
			throw std::invalid_argument("The index is out of range.");
		return m_buffer[index];
	}
	const_reference operator[](size_type index) const
	{
		if (index > m_buffer.size())
			throw std::invalid_argument("The index is out of range.");
		return m_buffer[index];
	}

	// Mutating functions
	void ident()
	{
		if (m_rows != m_cols)
			throw std::invalid_argument("The matrix must be square!");
		for (size_type x = 0; x < m_rows; ++x) {
			for (size_type y = 0; y < m_cols; ++y)
				m_buffer[m_cols * x + y] = static_cast<T>(x == y);
		}
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
	size_type size() const
	{ return m_buffer.size(); }

	// Matrix mathematical operations
	template<class U>
	MyMatrix& operator+=(MyMatrix<U> const& mtx)
	{
		if (m_rows != mtx.rows() || m_cols != mtx.cols())
			throw std::invalid_argument("Matrices dimensions must match!");
		std::transform(m_buffer.begin(), m_buffer.end(), mtx.begin(), m_buffer.begin(), std::plus<>{});
		return *this;
	}
	template<class U>
	MyMatrix& operator-=(MyMatrix<U> const& mtx)
	{
		if (m_rows != mtx.rows() || m_cols != mtx.cols())
			throw std::invalid_argument("Matrices dimensions must match!");
		std::transform(m_buffer.begin(), m_buffer.end(), mtx.begin(), m_buffer.begin(), std::minus<>{});
		return *this;
	}
	template<class U>
	MyMatrix operator*=(MyMatrix<U> const& mtx)
	{
		if (m_cols != mtx.rows())
			throw std::invalid_argument("Invalid Matrix dimensions.");

		MyMatrix<value_type> result(m_rows, mtx.cols());

		for (size_type r = 0; r < m_rows; r++) {
			for (size_type c = 0; c < mtx.cols(); c++) {
				for (size_type i = 0; i < m_cols; i++) {
					result.m_buffer[mtx.cols() * r + c] += m_buffer[m_cols * r + i] * mtx[mtx.cols() * i + c];
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
	template<class U>
	MyMatrix& operator+=(const U& val)
	{
		std::for_each(m_buffer.begin(), m_buffer.end(), [val](T& item) { item += val; });
		return *this;
	}
	template<class U>
	MyMatrix& operator-=(const U& val)
	{
		std::for_each(m_buffer.begin(), m_buffer.end(), [val](T& item) { item -= val; });
		return *this;
	}
	template<class U>
	MyMatrix& operator*=(const U& val)
	{
		std::for_each(m_buffer.begin(), m_buffer.end(), [val](T& item) { item *= val; });
		return *this;
	}
	template<class U>
	MyMatrix& operator/=(const U& val)
	{
		std::for_each(m_buffer.begin(), m_buffer.end(), [val](T& item) { item /= val; });
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
		std::transform(result.begin(), result.end(), result.begin(), [](value_type c) { return std::abs(c); });
		return result;
	}
};

// Matrix operators
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

	std::transform(result.begin(), result.end(), result.begin(), [](const T index) {
		return (index != 0) ? 1 / index : 0; });

	return result;
}
template <typename T>
MyMatrix<T> symmetric(MyMatrix<T> const& mtx)
{
	if (mtx.cols() != mtx.rows())
		throw std::invalid_argument("The matrix must be square!");
	MyMatrix<T> result(mtx);
	return mtx * transpose(mtx);
}

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
template <typename T, typename U>
MyMatrix<T>  operator*(MyMatrix<T> mtx1, MyMatrix<U> const& mtx2)
{
	return mtx1 *= mtx2;
}

// Matrix scalar operations
template <typename T, typename U>
MyMatrix<T> operator+(MyMatrix<T> mtx, U const& value)
{
	return mtx += value;
}
template <typename T, typename U>
MyMatrix<T> operator-(MyMatrix<T> mtx, U const& value)
{
	return mtx -= value;
}
template <typename T, typename U>
MyMatrix<T> operator*(MyMatrix<T> mtx, U const& value)
{
	return mtx *= value;
}
template <typename T, typename U>
MyMatrix<T> operator/(MyMatrix<T> mtx, U const& value)
{
	return mtx /= value;
}

#endif // MATRIX_H