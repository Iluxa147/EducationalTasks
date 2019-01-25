#pragma once

template <typename T>
class IPVector
{
public:
	IPVector(T);
	


	~IPVector();



	size_t size() const { return size_; };
	size_t capacity() const { return capacity_; };



	T& operator [] (size_t i) const;


private:
	int* begin_;
	size_t size_;
	size_t capacity_;
};

template<typename T>
inline IPVector<T>::IPVector(T size) : size_(size), capacity_(size*2)
{
	begin_ = (int*)std::calloc(size, sizeof(T));
}

template<typename T>
inline T & IPVector<T>::operator[](size_t i) const
{
	return *(begin_+i);
}

template<typename T>
inline IPVector<T>::~IPVector()
{
	free(begin_);
}
