//TODO new capacity (size_+ size_/2) ?
#pragma once
#ifdef _DEBUG
#define DebugException(msg) _CrtDbgReportW(_CRT_ASSERT, __FILEW__, __LINE__, NULL, L"%ls", msg);
#define Debug
#endif _DEBUG

#define VectorStructExample

#ifdef VectorStructExample
template <typename T>
class IPVector
{
public:
	typedef T* Iterator;
	Iterator begin() { return buff_; };
	Iterator end() { return buff_ + size_; };

	explicit IPVector() : size_(0), capacity_(0), buff_(nullptr)
	{
#ifdef Debug
		std::cout << "default constructor" << std::endl;
#endif Debug
	};
	explicit IPVector(size_t size) : size_(size), capacity_(size), buff_(new T[capacity_])
	{
#ifdef Debug
		std::cout << "size_t constructor " << size_ << " " << capacity_ << " "<< buff_ <<std::endl;
#endif Debug
	};
	IPVector(std::initializer_list<T> lst) : size_(lst.size()), capacity_(lst.size()), buff_(new T[lst.size()])
	{
#ifdef Debug
		std::cout << "initializer_list constructor" << std::endl;
#endif Debug
		std::copy(lst.begin(), lst.end(), buff_);
	};
	explicit IPVector(const IPVector<T>& v) : size_(v.size_), capacity_(v.capacity_), buff_(new T[v.capacity_]) //explicit copy constructor?
	{
#ifdef Debug
		std::cout << "COPY constructor" << std::endl;
#endif Debug
		for (size_t i = 0; i < v.size_; ++i)
		{
			buff_[i] = v.buff_[i];
		}
	};
	IPVector(IPVector<T>&& v) noexcept : size_(v.size_), capacity_(v.capacity_), buff_(v.buff_)
	{
#ifdef Debug
		std::cout << "MOVE constructor" << std::endl;
#endif Debug
		v.size_ = 0;
		v.capacity_ = 0;
		v.buff_ = nullptr;
	};

	~IPVector() {
#ifdef Debug
		std::cout << "~ " << size_ <<" " <<  capacity_  << " " << buff_ << std::endl;
#endif Debug
		delete[] buff_; };

	size_t getSize() const { return size_; };
	size_t getCapacity() const { return capacity_; };
	bool isEmpty() const { return size_ == 0; };
	T& front() { return *begin(); };
	T& back() { return *(end() - 1); };
	void shrinkToFit()
	{
#ifdef Debug
		std::cout << "shrinkToFit" << std::endl;
#endif Debug
		capacity_ = size_;
	};

	void pushBack(const T &val)
	{
#ifdef Debug
		std::cout << "& pushBack" << std::endl;
#endif Debug
		if (size_ == 0)
		{
			reserve(1);
		}
		else if (size_ == capacity_)
		{
			reserve(size_ + size_ / 2);
		}
		buff_[size_++] = val;
	};
	void popBack()
	{
		std::cout << "popBack" << std::endl;
		if (size_ == 0) //error reporter
		{
#ifdef Debug
			throw DebugException(L"vector is empty");
#endif Debug
		}
		else
		{
			--size_;
		}
	};
	void clear()
	{
#ifdef Debug
		std::cout << "clear" << std::endl;
#endif Debug
		size_ = 0;
		capacity_ = 0;
		delete[] buff_;
	};
	void resize(size_t newSize)
	{
		if (newSize != size_)
		{
#ifdef Debug
			std::cout << "resize" << std::endl;
#endif Debug
			reserve(newSize);
			size_ = newSize;
		}
	};
	void reserve(size_t newCapacity)
	{
		if (newCapacity > capacity_)
		{
#ifdef Debug
			std::cout << "reserve" << std::endl;
#endif Debug
			T* tmpBuff = new T[newCapacity];
			for (size_t i = 0; i < size_; ++i)
			{
				tmpBuff[i] = buff_[i];
			}
			delete[] buff_;
			buff_ = tmpBuff;
			capacity_ = newCapacity;
		}
	};

	template<class... Args> void emplaceBack(Args&&... args) //TODO WIP
	{
#ifdef Debug
		std::cout << "emplaceBack" << std::endl;
#endif Debug

		pushBack(T(std::forward<Args>(args)...));
	}; 

	T& operator [] (size_t index) const
	{
#ifdef Debug
		if (size_ <= index) //error reporter
		{
			throw DebugException(L"vector index is out of range");
		}
#endif Debug
		return buff_[index];
	};
	IPVector<T>& operator = (const IPVector<T>& v)
	{
#ifdef Debug
		std::cout << "= operator" << std::endl;
#endif Debug
		if (this == &v)
		{
			return *this;
		}
		if (v.size_ <= capacity_)
		{
			for (size_t i = 0; i < v.size_; ++i)
			{
				buff_[i] = v.buff_[i];
			}
			size_ = v.size_;
			return *this;
		}
		T* tmpBuff = new T[v.size_];
		for (size_t i = 0; i < v.size_; ++i)
		{
			tmpBuff[i] = v.buff_[i];
		}
		//delete[] buff_; //TODO ?
		size_ = v.size_;
		capacity_ = v.capacity_;
		buff_ = tmpBuff;
		return *this;
	};
	IPVector<T>& operator = (IPVector<T>&& v)
	{
#ifdef Debug
		std::cout << "= && operator" << std::endl;
#endif Debug
		delete[] buff_;
		buff_ = v.buff_;
		size_ = v.size_;
		capacity_ = v.capacity_;

		v.size_ = 0;
		v.capacity_ = 0;
		v.buff_ = nullptr;

		return *this;
	};

private:
	size_t size_;
	size_t capacity_;
	T* buff_;
};

template<>
class IPVector<bool>
{
public:
	explicit IPVector(unsigned int size) : size_(size)
	{
#ifdef Debug
		std::cout << "bool size_t constructor " << size_ << " " << capacity_ << " " << buff_ << std::endl;
#endif Debug

		if (size <= sizeof(unsigned int)*32)
		{
			buff_ = new unsigned int[size];
			capacity_ = size_;
		}
		else
		{
			buff_ = new unsigned int[size / 32];
			capacity_ = size / 32;
		}
	};
	explicit IPVector(const IPVector<bool>& v) : size_(v.size_), capacity_(v.capacity_), buff_(new unsigned int[v.capacity_]) //explicit copy constructor?
	{
#ifdef Debug
		std::cout << "bool COPY constructor" << std::endl;
#endif Debug
		for (size_t i = 0; i < v.size_; ++i)
		{
			buff_[i] = v.buff_[i];
		}
	};


	size_t getSize() const { return size_; };
	size_t getCapacity() const { return capacity_; };

	bool& operator[] (size_t index) const
	{

	}



	~IPVector() {
#ifdef Debug
		std::cout << "~bool " << size_ << " " << capacity_ << " " << buff_ << std::endl;
#endif Debug
		delete[] buff_; };

private:
	unsigned int size_;
	unsigned int capacity_;
	unsigned int* buff_;
};


#endif VectorStructExample

/*template<typename T>
inline IPVector<T>::IPVector(size_t size) : size_(size), capacity_(size), buff_(new T[capacity_])
{}

template<typename T>
inline IPVector<T>::IPVector(std::initializer_list<T> lst) : size_(lst.size()), capacity_(lst.size()), buff_(new T[lst.size()])
{
#ifdef Debug
	std::cout << "initializer_list constructor" << std::endl;
#endif Debug

	std::copy(lst.begin(), lst.end(), buff_);
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
inline IPVector<T>::IPVector(IPVector<T>&& v) noexcept: size_(v.size_), capacity_(v.capacity_), buff_(v.buff_)
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
*/
