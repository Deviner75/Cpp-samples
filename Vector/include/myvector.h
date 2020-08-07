// An std::vector like container.
// Mainly done for learning processes of memory mangment and various semantics.
// Base source: https://lokiastari.com/blog/2016/03/12/vector-resize/index.html


#include <type_traits>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <iterator>

template<typename T>
class MyVector
{
public:
	using value_type = T;
	using reference = T&;
	using const_reference = T const&;
	using pointer = T*;
	using const_pointer = T const*;
	using iterator = T*;
	using const_iterator = T const*;
	using riterator = std::reverse_iterator<iterator>;
	using const_riterator = std::reverse_iterator<const_iterator>;
	using difference_type = std::ptrdiff_t;
	using size_type = std::size_t;

private:
	size_type       m_capacity;
	size_type       m_length;
	T* m_buffer;

	struct Deleter
	{
		void operator()(T* m_buffer) const
		{
			::operator delete(m_buffer);
		}
	};

public:
	MyVector(int capacity = 10)
		: m_capacity(capacity)
		, m_length(0)
		, m_buffer(static_cast<T*>(::operator new(sizeof(T)* capacity)))
	{}
	template<typename I>
	MyVector(I begin, I end)
		: m_capacity(std::distance(begin, end))
		, m_length(0)
		, m_buffer(static_cast<T*>(::operator new(sizeof(T)* m_capacity)))
	{
		for (auto loop = begin; loop != end; ++loop) {
			pushBackInternal(*loop);
		}
	}
	MyVector(std::initializer_list<T> const& list)
		: MyVector(std::begin(list), std::end(list))
	{}
	~MyVector()
	{
		std::unique_ptr<T, Deleter>     deleter(m_buffer, Deleter());
		clearElements();
	}
	MyVector(MyVector const& copy)
		: m_capacity(copy.m_length)
		, m_length(0)
		, m_buffer(static_cast<T*>(::operator new(sizeof(T)* m_capacity)))
	{
		try {
			for (int loop = 0; loop < copy.m_length; ++loop) {
				push_back(copy.m_buffer[loop]);
			}
		} catch (...) {
			std::unique_ptr<T, Deleter>     deleter(m_buffer, Deleter());
			clearElements();
			throw;
		}
	}
	MyVector& operator=(MyVector const& copy)
	{
		copyAssign(copy);
		return *this;
	}
	MyVector(MyVector&& move) noexcept
		: m_capacity(0)
		, m_length(0)
		, m_buffer(nullptr)
	{
		move.swap(*this);
	}
	MyVector& operator=(MyVector&& move) noexcept
	{
		move.swap(*this);
		return *this;
	}
	void swap(MyVector& other) noexcept
	{
		using std::swap;
		swap(m_capacity, other.m_capacity);
		swap(m_length, other.m_length);
		swap(m_buffer, other.m_buffer);
	}

	// Non-Mutating functions
	size_type           size() const { return m_length; }
	size_type           capacity() const { return m_capacity; }
	bool                empty() const { return m_length == 0; }

	// Validated element access
	reference           at(size_type index) { validateIndex(index); return m_buffer[index]; }
	const_reference     at(size_type index) const { validateIndex(index); return m_buffer[index]; }

	// Non-Validated element access
	reference           operator[](size_type index) { return m_buffer[index]; }
	const_reference     operator[](size_type index) const { return m_buffer[index]; }
	reference           front() { return m_buffer[0]; }
	const_reference     front() const { return m_buffer[0]; }
	reference           back() { return m_buffer[m_length - 1]; }
	const_reference     back() const { return m_buffer[m_length - 1]; }

	// Iterators
	iterator            begin() { return m_buffer; }
	riterator           rbegin() { return riterator(end()); }
	const_iterator      begin() const { return m_buffer; }
	const_riterator     rbegin() const { return const_riterator(end()); }

	iterator            end() { return m_buffer + m_length; }
	riterator           rend() { return riterator(begin()); }
	const_iterator      end() const { return m_buffer + m_length; }
	const_riterator     rend() const { return const_riterator(begin()); }

	const_iterator      cbegin() const { return begin(); }
	const_riterator     crbegin() const { return rbegin(); }
	const_iterator      cend() const { return end(); }
	const_riterator     crend() const { return rend(); }

	// Comparison
	bool operator!=(MyVector const& rhs) const { return !(*this == rhs); }
	bool operator==(MyVector const& rhs) const
	{
		return  (size() == rhs.size())
			&& std::equal(begin(), end(), rhs.begin());
	}

	// Mutating functions
	void push_back(value_type const& value)
	{
		resizeIfRequire();
		pushBackInternal(value);
	}
	void push_back(value_type&& value)
	{
		resizeIfRequire();
		moveBackInternal(std::move(value));
	}
	template<typename... Args>
	void emplace_back(Args&&... args)
	{
		resizeIfRequire();
		emplaceBackInternal(std::move(args)...);
	}
	void pop_back()
	{
		--m_length;
		m_buffer[m_length].~T();
	}
	void reserve(size_type capacityUpperBound)
	{
		if (capacityUpperBound > m_capacity) {
			reserveCapacity(capacityUpperBound);
		}
	}
private:
	void validateIndex(size_type index) const
	{
		if (index >= m_length) {
			throw std::out_of_range("Out of Range");
		}
	}
	void resizeIfRequire()
	{
		if (m_length == m_capacity) {
			size_type newCapacity = std::max(2.0, m_capacity * 1.5);
			reserveCapacity(newCapacity);
		}
	}
	void reserveCapacity(size_type newCapacity)
	{
		MyVector<T> tmpBuffer(newCapacity);
		simpleCopy(tmpBuffer);
		tmpBuffer.swap(*this);
	}

	// Adds new element to the end using placement new
	void pushBackInternal(T const& value)
	{
		new (m_buffer + m_length) T(value);
		++m_length;
	}
	// Move new element to the end using placement new
	void moveBackInternal(T&& value)
	{
		new (m_buffer + m_length) T(std::move(value));
		++m_length;
	}
	// Move a list of elements to the end using placement new
	template<typename... Args>
	void emplaceBackInternal(Args&&... args)
	{
		new (m_buffer + m_length) T(std::move(args)...);
		++m_length;
	}
	void simpleCopy(MyVector<T>& dst)
	{
		std::for_each(m_buffer, m_buffer + m_length,
					  [&dst](T const& v) {dst.pushBackInternal(v); }
		);
	}
	// Calls the destructor on all the members in reverse order
	void clearElements()
	{
		for (int loop = 0; loop < m_length; ++loop) {
			m_buffer[m_length - 1 - loop].~T();
		}
	}
	// Copy and Swap idiom
	void copyAssign(MyVector const& copy)
	{
		MyVector<T>  tmp(copy);
		tmp.swap(*this);
	}
};