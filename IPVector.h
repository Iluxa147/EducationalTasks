//TODO new capacity (size_+ size_/2) ?
//TODO <bool> blocksCount to separate function?
#pragma once
#ifdef _DEBUG
#define DebugException(msg) _CrtDbgReportW(_CRT_ASSERT, __FILEW__, __LINE__, NULL, L"%ls", msg);
#define Debug
#endif //_DEBUG

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
#endif //Debug
	};
	explicit IPVector(size_t size) : size_(size), capacity_(size), buff_(new T[capacity_])
	{
#ifdef Debug
		std::cout << "size_t constructor " << size_ << " " << capacity_ << " "<< buff_ <<std::endl;
#endif //Debug
	};
	explicit IPVector(const IPVector<T>& v) : size_(v.size_), capacity_(v.capacity_), buff_(new T[v.capacity_]) //explicit copy constructor?
	{
#ifdef Debug
		std::cout << "COPY constructor" << std::endl;
#endif //Debug
		for (size_t i = 0; i < v.size_; ++i)
		{
			buff_[i] = v.buff_[i];
		}
	};
	IPVector(IPVector<T>&& v) noexcept : size_(v.size_), capacity_(v.capacity_), buff_(v.buff_)
	{
#ifdef Debug
		std::cout << "MOVE constructor" << std::endl;
#endif //Debug
		v.size_ = 0;
		v.capacity_ = 0;
		v.buff_ = nullptr;
	};
	IPVector(std::initializer_list<T> lst) : size_(lst.size()), capacity_(lst.size()), buff_(new T[lst.size()])
	{
#ifdef Debug
		std::cout << "initializer_list constructor" << std::endl;
#endif //Debug
		std::copy(lst.begin(), lst.end(), buff_);
	};

	~IPVector() {
#ifdef Debug
		std::cout << "~ " << size_ <<" " <<  capacity_  << " " << buff_ << std::endl;
#endif //Debug
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
#endif //Debug
		if (size_ < capacity_)
		{
			T* tmpBuff = new T[size_];
			for (size_t i = 0; i < size_; ++i)
			{
				tmpBuff[i] = buff_[i];
			}
			delete[] buff_;
			buff_ = tmpBuff;
			capacity_ = size_;
		}
	};
	void pushBack(const T &val)
	{
#ifdef Debug
		std::cout << "& pushBack" << std::endl;
#endif //Debug
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
#endif //Debug
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
#endif //Debug
		size_ = 0;
		capacity_ = 0;
		delete[] buff_;
		buff_ = nullptr;
	};
	void resize(size_t newSize)
	{
		if (newSize != size_)
		{
#ifdef Debug
			std::cout << "resize" << std::endl;
#endif //Debug
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
#endif //Debug
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

	template<class... Args>
	void emplaceBack(Args&&... args) //TODO WIP
	{
#ifdef Debug
		std::cout << "emplaceBack" << std::endl;
#endif //Debug
		if (size_ >= capacity_)
		{
			reserve(size_ + size_ / 2);
		}
		new(&buff_[size_++]) T(std::forward<Args>(args)...);
	};

	IPVector<T>& operator = (const IPVector<T>& v)
	{
#ifdef Debug
		std::cout << "= operator" << std::endl;
#endif //Debug
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
		delete[] buff_;
		size_ = v.size_;
		capacity_ = v.capacity_;
		buff_ = tmpBuff;
		return *this;
	};
	IPVector<T>& operator = (IPVector<T>&& v) noexcept
	{
#ifdef Debug
		std::cout << "= && operator" << std::endl;
#endif //Debug
		delete[] buff_;
		buff_ = v.buff_;
		size_ = v.size_;
		capacity_ = v.capacity_;

		v.size_ = 0;
		v.capacity_ = 0;
		v.buff_ = nullptr;

		return *this;
	};
	T& operator [] (size_t index) const
	{
#ifdef Debug
		if (size_ <= index) //error reporter
		{
			throw DebugException(L"vector index is out of range");
		}
#endif //Debug
		return buff_[index];
	};
	
	static void ShowVectorElements(IPVector<T>& v)
	{
		//std::cout << std::endl;
		std::cout << "&buff_: " << &v[0] << std::endl;
		for (size_t i = 0; i < v.getSize(); ++i)
		{
			std::cout << i << "    val: " << v[i] << "  &: " << &v[i] << std::endl;
		}
		std::cout << "Size: " << v.getSize() << std::endl;
		std::cout << "Capacity: " << v.getCapacity() << std::endl;
		std::cout << std::endl;
	}

private:
	size_t size_;
	size_t capacity_;
	T* buff_;
};

template<>
class IPVector<bool>
{
	struct BitHelper
	{
	public:
		explicit BitHelper(unsigned int* container, unsigned int index) : container_(container), index_(index) {};

		void operator = (const bool val)
		{
			val ? *container_ |= 1u << index_ : *container_ &= ~(1u << index_); //1u is a mask like 0x00000001u
		}

		operator bool() const
		{
			return (*container_ >> index_) & 1u;
		}
		/*unsigned int& operator[](size_t index)
		{
			return *container_;
		}*/

	private:
		unsigned int* container_;
		unsigned int index_;
	};

public:
	static constexpr unsigned int blockSize_ = 32u; //minimum memory block size in bits. sizeof(unsigned int)*8 = 32

public:
	typedef unsigned int* Iterator; //a pointer to a container where the certain bit is
	Iterator begin() { return buff_; };
	Iterator end() { return buff_ + size_ / blockSize_; };

	explicit IPVector() : size_(0), capacity_(0), buff_(nullptr)
	{
#ifdef Debug
		std::cout << "default constructor" << std::endl;
#endif //Debug
	};
	explicit IPVector(unsigned int size) : size_(size)
	{
		if (size <= blockSize_)
		{
			//buff_ = (unsigned int*)std::malloc(sizeof(unsigned int));
			buff_ = new unsigned int[1]();
			capacity_ = blockSize_; // = 32 (in bits)
		}
		else
		{
			//buff_ = (unsigned int*)std::malloc(sizeof(unsigned int)* std::ceil(size / 32));
			//unsigned int blocksCount = std::ceil(static_cast<float>(size) / static_cast<float>(blockSize_));
			unsigned int blocksCount = size / blockSize_ + 1;
			buff_ = new unsigned int[blocksCount]();
			capacity_ = blocksCount*blockSize_;
		}
#ifdef Debug
		std::cout << "bool size_t constructor " << size_ << " " << capacity_ << " " << buff_ << " " << &buff_[0] << std::endl;
#endif //Debug
	};
	explicit IPVector(const IPVector<bool>& v) : size_(v.size_), capacity_(v.capacity_), buff_(new unsigned int[v.capacity_/blockSize_]) //explicit copy constructor?
	{
#ifdef Debug
		std::cout << "bool COPY constructor" << std::endl;
#endif //Debug
		for (size_t i = 0; i < v.size_; ++i)
		{
			buff_[i] = v.buff_[i];
		}
	};
	IPVector(IPVector<bool>&& v) noexcept : size_(v.size_), capacity_(v.capacity_), buff_(v.buff_)
	{
#ifdef Debug
		std::cout << "bool MOVE constructor" << std::endl;
#endif //Debug
		v.size_ = 0;
		v.capacity_ = 0;
		v.buff_ = nullptr;
	};

	const unsigned int* getBlockAddress(const unsigned int index) const { return &buff_[index / blockSize_]; };
	size_t getSize() const { return size_; };
	size_t getCapacity() const { return capacity_; };
	bool isEmpty() const { return size_ == 0; };
	bool front() { return BitHelper(begin(), 0); };
	bool back() { return BitHelper(end(), size_/blockSize_-1); };

	void shrinkToFit()
	{
#ifdef Debug
		std::cout << "shrinkToFit" << std::endl;
#endif //Debug
		unsigned int blocksCount = size_ / blockSize_ + 1;

		if (size_ < capacity_)
		{
			unsigned int* tmpBuff = new unsigned int[blocksCount];
			for (size_t i = 0; i < size_; ++i)
			{
				tmpBuff[i] = buff_[i];
			}
			delete[] buff_;
			buff_ = tmpBuff;
			capacity_ = size_ / blockSize_ + 1;
		}
	};
	void pushBack(const bool &val)
	{
#ifdef Debug
		std::cout << "bool pushBack" << std::endl;
#endif //Debug
		if (size_ == 0)
		{
			reserve(1);
		}
		else if (size_ == capacity_)
		{
			reserve(size_ + size_ / 2);
		}
		BitHelper(end(), size_++ / blockSize_ - 1) = val;
	};

	void popBack()
	{
		std::cout << "bool popBack" << std::endl;
		if (size_ == 0) //error reporter
		{
#ifdef Debug
			throw DebugException(L"vector is empty");
#endif //Debug
		}
		else
		{
			--size_;
		}
	};
	void clear()
	{
#ifdef Debug
		std::cout << "bool clear" << std::endl;
#endif //Debug
		size_ = 0;
		capacity_ = 0;
		delete[] buff_;
		buff_ = nullptr;
	};
	void resize(size_t newSize)
	{
		if (newSize != size_)
		{
#ifdef Debug
			std::cout << "bool resize" << std::endl;
#endif //Debug
			reserve(newSize);
			size_ = newSize;
		}
	};
	void reserve(size_t newCapacity)
	{
		if (newCapacity > capacity_)
		{
#ifdef Debug
			std::cout << "bool reserve" << std::endl;
#endif //Debug
			unsigned int blocksCount = newCapacity / blockSize_ + 1;

			unsigned int* tmpBuff = new unsigned int[blocksCount];
			for (size_t i = 0; i < blocksCount; ++i)
			{
				tmpBuff[i] = buff_[i];
			}
			delete[] buff_;
			buff_ = tmpBuff;
			capacity_ = newCapacity;
		}
	};

	IPVector<bool>& operator = (const IPVector<bool>& v)
	{
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
		auto blocksCount = v.size_ / blockSize_ + 1;
		unsigned int* tmpBuff = new unsigned int[blocksCount];
		for (size_t i = 0; i < blocksCount; ++i)
		{
			tmpBuff[i] = v.buff_[i];
		}
		if (buff_ != nullptr)
		{
			delete[] buff_;
		}
		size_ = v.size_;
		capacity_ = v.capacity_;
		buff_ = tmpBuff;
		return *this;
	}
	IPVector<bool>& operator = (IPVector<bool>&& v) noexcept
	{
#ifdef Debug
		std::cout << "bool = && operator" << std::endl;
#endif //Debug
		if (buff_ != nullptr)
		{
			delete[] buff_;
		}
		buff_ = v.buff_;
		size_ = v.size_;
		capacity_ = v.capacity_;

		v.size_ = 0;
		v.capacity_ = 0;
		v.buff_ = nullptr;

		return *this;

	}
	BitHelper operator[] (size_t index) const
	{
		/* *buff_ |= 1u << index;
		unsigned int mask = 1 << index;
		unsigned int masked = *buff_ & mask;
		unsigned int bit = masked >> index;
		bool boolBit = static_cast<bool>(bit);
		unsigned int blockNumber = std::ceil(static_cast<float>(index+1) / static_cast<float>(blockSize_));

		std::cout << "operator[] " << &buff_[index / blockSize_] << " " << buff_[index / blockSize_] << std::endl;
		std::cout << sizeof(BitHelper) << std::endl;*/
		return BitHelper(&buff_[index / blockSize_], index);
	};


	~IPVector() {
#ifdef Debug
		std::cout << "~bool " << size_ << " " << capacity_ << " " << buff_ << " " << buff_[0] << std::endl;
#endif //Debug
		//std::free(buff_); };
		delete[] buff_; };

	static void ShowVectorElements(const IPVector<bool>& v)
	{
		std::cout << "&buff_: " << v.getBlockAddress(0) << std::endl;

		for (size_t i = 0; i < v.getSize(); ++i)
		{
			std::cout << i << "    val: " << v[i] << "  &: " << v.getBlockAddress(i) << std::endl;
		}
		std::cout << "Size: " << v.getSize() << std::endl;
		std::cout << "Capacity: " << v.getCapacity() << std::endl;
		std::cout << std::endl;
	}

private:
	unsigned int size_;			//in bits
	unsigned int capacity_;		//in bits
	unsigned int* buff_;		//min block size is sizeof(unsigned int) = 8 bytes = 32bits
};
#endif //VectorStructExample

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
