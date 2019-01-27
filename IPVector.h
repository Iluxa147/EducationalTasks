#pragma once
// TODO capacity_(size*2)?
#define DebugException(msg) _CrtDbgReportW(_CRT_ASSERT, __FILEW__, __LINE__, NULL, L"%ls", msg);

template <typename T>
class IPVector
{
public:
	typedef T* Iterator;
	
	IPVector(size_t size);
	IPVector(const IPVector<T>& v);
	IPVector(IPVector<T>&& v);

	~IPVector() { free(buff_); };
	
	Iterator begin() { return buff_; };
	Iterator end() { return buff_ + size_; };
	
	size_t getSize() const { return size_; };
	size_t getCapacity() const { return capacity_; };
	bool isEmpty() const { return size_ == 0; };
	T& front() { return *begin(); };
	T& back() { return *(end() - 1); };
	void pushBack(const T &val);
	void clear();

	T& operator [] (size_t pos) const;
	IPVector & operator = (IPVector&& v);
	
private:
	T* buff_;
	size_t size_;
	size_t capacity_;
};

template<typename T>
inline IPVector<T>::IPVector(size_t size) : size_(size), capacity_(size*2)
{
	buff_ = (T*)std::calloc(capacity_, sizeof(T));
}

template<typename T>
inline IPVector<T>::IPVector(const IPVector<T>& v) : size_(v.size_), capacity_(v.capacity_)
{
	buff_ = (T*)malloc(sizeof(T)*v.size_);
	for (size_t i = 0; i < v.size_; ++i)
	{
		buff_[i] = v.buff_[i];
	}
}

template<typename T>
inline IPVector<T>::IPVector(IPVector<T>&& v): size_(v.size_), capacity_(v.capacity_), buff_(v.buff_)
{
	v.clear();
}

template<typename T>
inline void IPVector<T>::pushBack(const T & val)
{
	if (size_ == capacity_)
	{
		capacity_ = size_ * 2;
		buff_ = (T*)realloc()
			
	}
	else
	{
		buff_[size_++] = val;
	}
}

template<typename T>
inline void IPVector<T>::clear()
{
	buff_ = nullptr; // TODO free?
	size_ = 0;
	capacity_ = 0;
}

template<typename T>
inline T & IPVector<T>::operator[](size_t index) const
{
	if (size_ <= index) //error reporter
	{
		throw DebugException(L"vector subscript out of range");
	}
	return buff_[index];
}

template<typename T>
inline IPVector<T> & IPVector<T>::operator=(IPVector&& v)
{
	free(buff_);
	size_(v.size_);
	capacity_(v.capacity_);
	buff_(v.buff);

	v.clear();

	return *this;
}