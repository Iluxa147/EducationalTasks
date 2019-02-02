#pragma once
#define VectorStructExample

//TODO move method realization inside class
//TODO new capacity (size_+ size_/2) ?
#define DebugException(msg) _CrtDbgReportW(_CRT_ASSERT, __FILEW__, __LINE__, NULL, L"%ls", msg);
#define Debug

#ifdef VectorStructExample
template <typename T>
class IPVector
{
public:
	typedef T* Iterator;
	Iterator begin() { return buff_; };
	Iterator end() { return buff_ + size_; };

	explicit IPVector(size_t size);
	IPVector(std::initializer_list<T> lst);
	explicit IPVector(const IPVector<T>& v);
	IPVector(IPVector<T>&& v);

	~IPVector() { delete[] buff_; };
		
	size_t getSize() const { return size_; };
	size_t getCapacity() const { return capacity_; };
	bool isEmpty() const { return size_ == 0; };
	T& front() { return *begin(); };
	T& back() { return *(end() - 1); };
	void shrinkToFit() { capacity_ = size_; };
	void pushBack(const T &val);
	void popBack();
	void clear();
	void resize(size_t newSize);
	void reserve(size_t newCapacity);

	T& operator [] (size_t pos) const;
	IPVector<T> operator = (const IPVector<T>& v);
	IPVector<T> & operator = (IPVector<T>&& v);

private:
	T* buff_;
	size_t size_;
	size_t capacity_;
};

template<typename T>
inline IPVector<T>::IPVector(size_t size) : size_(size), capacity_(size)
{
	buff_ = new T[capacity_];
	//buff_ = (T*)std::calloc(capacity_, sizeof(T));
}

template<typename T>
inline IPVector<T>::IPVector(std::initializer_list<T> lst) : size_(lst.size()), capacity_(lst.size()), buff_(new T[lst.size()]) //TODO rewrite this constructor
{
#ifdef Debug
	std::cout << "initializer_list constructor" << std::endl;
#endif Debug
	
	int i = 0; // :-))))))
	for (auto const &n : lst)
	{
		buff_[i] = n;
		++i;
	}
}


template<typename T>
inline IPVector<T>::IPVector(const IPVector<T>& v) : size_(v.size_), capacity_(v.capacity_)
{
#ifdef Debug
	std::cout << "COPY constructor" << std::endl;
#endif Debug

	buff_ = new T[v.capacity_];
	for (size_t i = 0; i < v.size_; ++i)
	{
		buff_[i] = v.buff_[i];
	}
}

template<typename T>
inline IPVector<T>::IPVector(IPVector<T>&& v): size_(v.size_), capacity_(v.capacity_), buff_(v.buff_)
{
#ifdef Debug
	std::cout << "MOVE constructor" << std::endl;
#endif Debug
	
	v.size_ = 0;
	v.capacity_ = 0;
	v.buff_ = nullptr;
}

template<typename T>
inline void IPVector<T>::pushBack(const T & val)
{
#ifdef Debug
	std::cout << "pushBack" << std::endl;
#endif Debug

	if (size_ < capacity_)
	{
		buff_[size_++] = val;
	}
	else
	{
		size_t tmpSize = size_;
		resize(size_+ size_/2);
		buff_[tmpSize] = val;
	}
}

template<typename T>
inline void IPVector<T>::popBack()
{
#ifdef Debug
	std::cout << "popBack" << std::endl;
#endif Debug

	if (size_==0) //error reporter
	{
		throw DebugException(L"vector is empty");
	}
	else
	{
		--size_;
	}
}

template<typename T>
inline void IPVector<T>::clear()
{
#ifdef Debug
	std::cout << "clear" << std::endl;
#endif Debug

	size_ = 0;
	capacity_ = 0;
	delete[] buff_;
}

template<typename T>
inline void IPVector<T>::resize(size_t newSize)
{
	if (newSize != size_)
	{
#ifdef Debug
		std::cout << "resize" << std::endl;
#endif Debug

		reserve(newSize);
		size_ = newSize;
	}
}

template<typename T>
inline void IPVector<T>::reserve(size_t newCapacity)
{
	if (newCapacity > capacity_)
	{
#ifdef Debug
		std::cout << "reserve" << std::endl;
#endif Debug
		std::cout << "buff_: " << buff_ << std::endl;
		T* tmpBuff = new T[newCapacity];
		tmpBuff = new (buff_) T[newCapacity];
		std::cout << "tmpBuff: " << tmpBuff << std::endl;
		buff_ = tmpBuff;
		std::cout << "buff_: " << buff_ << std::endl;
	}
}

template<typename T>
inline T & IPVector<T>::operator[](size_t index) const
{
	if (size_ <= index) //error reporter
	{
		throw DebugException(L"vector index is out of range");
	}
	return buff_[index];
}

template<typename T>
inline IPVector<T> IPVector<T>::operator=(const IPVector<T>& v)
{
#ifdef Debug
	std::cout << "= operator" << std::endl;
#endif Debug

	return IPVector<T>(v);
}

template<typename T>
inline IPVector<T> & IPVector<T>::operator=(IPVector&& v)
{
#ifdef Debug
	std::cout << "= && operator" << std::endl;
#endif Debug
	buff_ = v.buff_;
	size_ = v.size_;
	capacity_ = v.capacity_;

	v.size_ = 0;
	v.capacity_ = 0;
	v.buff_ = nullptr;

	return *this;
}

#endif VectorStructExample

