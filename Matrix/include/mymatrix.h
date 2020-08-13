#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

template <typename T>
class MyMatrix
{
public:
	using value_type = T;
	using reference = value_type&;
	using const_reference = value_type const&;
	using size_type = std::size_t;
	using iterator = typename std::vector<value_type>::iterator;
	using const_iterator = typename std::vector<value_type>::const_iterator;

private:
	size_type m_rows;
	size_type m_cols;
	std::vector<value_type> m_buffer;

public:
	MyMatrix(size_type dimx = 3, size_type dimy = 3)
		: m_rows(dimx)
		, m_cols(dimy)
	{
		m_buffer.resize(dimx * dimy);
	}
	MyMatrix(MyMatrix<value_type> const& copy)
		: m_rows(copy.m_rows)
		, m_cols(copy.m_cols)
		, m_buffer(copy.m_buffer)
	{}
	MyMatrix(MyMatrix<value_type>&& move) noexcept
	{ *this = std::move(move); }
	MyMatrix& operator=(MyMatrix<value_type> const& copy)
	{
		// Copy and Swap idiom
		MyMatrix<value_type> tmp(copy);
		tmp.swap(*this);
		return *this;
	}
	MyMatrix& operator=(MyMatrix<value_type>&& move) noexcept
	{
		move.swap(*this);
		return *this;
	}

	// Iterators
	iterator       begin() { return m_buffer.begin(); }
	const_iterator begin() const { return m_buffer.begin(); }
	const_iterator cbegin() const { return begin(); }

	iterator       end() { return m_buffer.end(); }
	const_iterator end() const { return m_buffer.end(); }
	const_iterator cend() const { return end(); }

	// Access operators with validation
	reference operator()(size_type x, size_type y)
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
	void fill(value_type value)
	{
		std::fill(m_buffer.begin(), m_buffer.end(), value);
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
	void print(std::ostream& out) const
	{
		for (size_t i(0); i < m_rows; i++) {
			for (size_t j(0); j < m_cols; j++) {
				out << m_buffer[m_cols * i + j] << ' ';
			}
			out << std::endl;
		}
	}

	// Matrix mathematical operations
	MyMatrix<T>  operator+(MyMatrix<T> const& mtx) const
	{
		MyMatrix<T> result(*this);
		return result += mtx;
	}
	MyMatrix<T>& operator+=(MyMatrix<T> const& mtx)
	{
		assert(m_rows == mtx.m_rows || m_cols == mtx.m_cols && "Matrix dimension must be the same.");
		std::transform(m_buffer.begin(), m_buffer.end(), mtx.m_buffer.begin(), m_buffer.begin(), std::plus<>{});
		return *this;
	}
	MyMatrix<T>  operator-(MyMatrix<T> const& mtx) const
	{
		MyMatrix<T> result(*this);
		return result -= mtx;
	}
	MyMatrix<T>& operator-=(MyMatrix<T> const& mtx)
	{
		assert(m_rows == mtx.m_rows || m_cols == mtx.m_cols && "Matrix dimension must be the same.");
		std::transform(m_buffer.begin(), m_buffer.end(), mtx.m_buffer.begin(), m_buffer.begin(), std::minus<>{});

		return *this;
	}
	MyMatrix<T>  operator*(MyMatrix<T> const& mtx) const
	{
		MyMatrix<T> tmp(*this);
		return tmp *= mtx;
	}
	MyMatrix<T>  operator*=(MyMatrix<T> const& mtx)
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
	bool operator==(MyMatrix<T> const& mtx) const noexcept
	{
		if (m_rows != mtx.m_rows || m_cols != mtx.m_cols)
			return false;

		std::for_each(m_buffer.cbegin(), m_buffer.cend(), [&](const size_type i) { return m_buffer[i] != mtx.m_buffer[i]; });

		return true;
	}
	bool operator!=(MyMatrix<T> const& mtx) const noexcept { return !(*this == mtx); }

	// Matrix/scalar operations
	MyMatrix<T>& operator+(const T& value)
	{
		std::transform(m_buffer.begin(), m_buffer.end(), m_buffer.begin(), [&value](const T index) {return index + value; });
		return *this;
	}
	MyMatrix<T>& operator-(const T& value)
	{
		std::transform(m_buffer.begin(), m_buffer.end(), m_buffer.begin(), [&value](const T index) {return index - value; });
		return *this;
	}
	MyMatrix<T>& operator*(const T& value)
	{
		std::transform(m_buffer.begin(), m_buffer.end(), m_buffer.begin(), [&value](T index) {return index * value; });
		return *this;
	}
	MyMatrix<T>& operator/(const T& value)
	{
		std::transform(m_buffer.begin(), m_buffer.end(), m_buffer.begin(), [&value](T index) {return index / value; });
		return *this;
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& out, MyMatrix<T> const& m)
{
	m.print(out);
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