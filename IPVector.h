#pragma once
// TODO new capacity (size_+ size_/2) ?
#define DebugException(msg) _CrtDbgReportW(_CRT_ASSERT, __FILEW__, __LINE__, NULL, L"%ls", msg);
#define Debug

template <typename T>
class IPVector
{
public:
	typedef T* Iterator;
	
	IPVector(size_t size);
	IPVector(const IPVector<T>& v);
	IPVector(IPVector<T>&& v);

	~IPVector() { delete[] buff_; /*free(buff_);*/ };
	
	Iterator begin() { return buff_; };
	Iterator end() { return buff_ + size_; };
	
	size_t getSize() const { return size_; };
	size_t getCapacity() const { return capacity_; };
	bool isEmpty() const { return size_ == 0; };
	T& front() { return *begin(); };
	T& back() { return *(end() - 1); };
	void pushBack(const T &val);
	void popBack();
	void clear();
	void resize(size_t newSize);
	void reserve(size_t newCapacity);

	T& operator [] (size_t pos) const;
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

	v.clear();
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
	buff_ = nullptr; // TODO free/delete for buff_?
	size_ = 0;
	capacity_ = 0;
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

		//tmpBuff = (T*)realloc(buff_, sizeof(T) * newCapacity);

		T* tmpBuff = new T[newCapacity];
		for (size_t i = 0; i < size_; ++i)
		{
			tmpBuff[i] = buff_[i];
		}
		delete[] buff_;
		buff_ = tmpBuff;
		capacity_ = newCapacity;
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
inline IPVector<T> & IPVector<T>::operator=(IPVector&& v)
{
#ifdef Debug
	std::cout << "= && operator" << std::endl;
#endif Debug

	delete[] buff_;
	size_ = v.size_;
	capacity_ = v.capacity_;
	buff_ = v.buff_;

	v.clear();

	return *this;
}