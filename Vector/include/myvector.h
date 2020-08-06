// An std::vector like container for a learning processes
// base source: https://lokiastari.com/blog/2016/03/12/vector-resize/index.html

#include <cstddef>
#include <iostream>
#include <cstddef>
#include <algorithm>

template <typename T>
class MyVector 
{
	std::size_t m_capacity;
	std::size_t m_length;
	T* m_buffer;

public:
	MyVector(int capacity = 10)
		: m_capacity(capacity)
		, m_length(0)
		, m_buffer(static_cast<T*>(::operator new(sizeof(T) * capacity)))
	{
		std::cout << "! constructed !" << std::endl;
	}
	~MyVector()
	{
		for (int loop = 0; loop < m_length; ++loop) 
		{
			m_buffer[m_length - 1 - loop].~T();
		}
		::operator delete(m_buffer);
		std::cout << "! destructed !" << std::endl;
	}
	MyVector(MyVector const& copy)
		: m_capacity(copy.m_length)
		, m_length(0)
		, m_buffer(static_cast<T*>(::operator new(sizeof(T) * m_capacity)))
	{
		try {
			for (int loop = 0; loop < copy.m_length; ++loop) 
			{
				push_back(copy.m_buffer[loop]);
			}
		} catch (...) {
			for (int loop = 0; loop < m_length; ++loop) {
				m_buffer[m_length - 1 - loop].~T();
			}
			::operator delete(m_buffer);
			throw;
		}
		std::cout << "! constructed !" << std::endl;
	}
	MyVector(MyVector&& move) noexcept
		: m_capacity(0)
		, m_length(0)
		, m_buffer(nullptr)
	{
		move.swap(*this);
	}
	MyVector& operator=(MyVector const& copy)
	{
		// Copy and Swap idiom
		MyVector<T> tmp(copy);
		tmp.swap(*this);
		return *this;
	}
	MyVector& operator=(MyVector&& move) noexcept
	{
		move.swap(*this);
		return *this;
	}

	// Modifiers
	// No-throw guarantee swap
	void swap(MyVector& other) noexcept
	{
		using std::swap;
		swap(m_capacity, other.m_capacity);
		swap(m_length, other.m_length);
		swap(m_buffer, other.m_buffer);
	}
	void push_back(T const& value)
	{
		resizeIfRequire();
		pushBackInternal(value);
	}
	void pop_back()
	{
		--m_length;
		m_buffer[m_length].~T();
	}
	void clear() noexcept
	{
		for (int loop = 0; loop < m_length; ++loop)
		{
			m_buffer[m_length - 1 - loop].~T();
		}
		m_length = 0;
	}
	void resize(std::size_t new_size)
	{
		if (new_size > m_length)
		{
			try
			{
				for (int loop = m_length; loop < new_size; ++loop)
				{
					T tmp = {};
					push_back(tmp);
				}
			}
			catch (...)
			{
				for (int loop = 0; loop < m_length; ++loop)
				{
					m_buffer[m_length - 1 - loop].~T();
				}
				::operator delete(m_buffer);
				throw;
			}
		}
		else if (new_size < m_length)
		{
			for (int loop = m_length; loop > new_size; --loop)
			{
				m_buffer[m_length - 1 - loop].~T();
				m_length--;
			}
		}
	}
	//void erase(const size_t& pos)
	
	// Capacity
	std::size_t capacity() const noexcept
	{
		return m_capacity;
	}
	std::size_t size() const { return m_length; }
	void reserve(std::size_t capacityUpperBound)
	{
		if (capacityUpperBound > m_capacity)
			reserveCapacity(capacityUpperBound);
	}

	// Element access
	T& operator[](std::size_t index) { return m_buffer[index]; }
	T const& operator[](std::size_t index) const { return m_buffer[index]; }

private:

	// Memory allocation area
	void resizeIfRequire()
	{
		if (m_length == m_capacity) 
		{
			std::cout << "resize" << std::endl;
			std::size_t newCapacity = std::max(2.0, m_capacity * 1.5);
			reserveCapacity(newCapacity);
		}
	}
	void pushBackInternal(T const& value)
	{
		new (m_buffer + m_length) T(value);
		++m_length;
	}
	void reserveCapacity(std::size_t newCapacity)
	{
		MyVector<T> tmpBuffer(newCapacity);
		std::for_each(m_buffer, m_buffer + m_length, [&tmpBuffer](T const& v) { tmpBuffer.pushBackInternal(v); });

		tmpBuffer.swap(*this);
	}
};