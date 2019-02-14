//placeholders are for experiments

#ifdef Placeholder
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <chrono>
#include <random>
#include <memory>
#include <set>
#include <map>

#include "vld.h"

#define MergeSortTmpl
#define Debug


#ifdef MergeSortTmpl

void Merge(int* A, unsigned int l, unsigned int m, unsigned int r)
{
	unsigned int n1 = m - l + 1;
	unsigned int n2 = r - m;

	//std::vector<int> L(n1+1);
	//std::vector<int> R(n2+1);

	int *L = new int[n1 + 1];
	int *R = new int[n2 + 1];

	std::cout << "++++++++++++++" << std::endl;
	std::cout << "&A" << &A << std::endl;
	std::cout << "p " << l << ' ' << std::endl;
	std::cout << "q " << m << ' ' << std::endl;
	std::cout << "r " << r << ' ' << std::endl;
	std::cout << "n1 " << n1 << ' ' << std::endl;
	std::cout << "n2 " << n2 << ' ' << std::endl;
	//std::cout << "L size " << L.size() << ' ' << std::endl;
	//std::cout << "R size " << R.size() << ' ' << std::endl;
	std::cout << '\n' << std::endl;

	std::cout << "First Filling: " << std::endl;
	for (size_t i = 0; i < n1; ++i)
	{
		L[i] = A[l + i - 1]; // 1st invariant: at index 1 in L write an A[1]
		std::cout << "L[" << i << "] " << L[i] << "   " << "A[l + i] " << "A[" << (l + i - 1) << "] " << A[l + i - 1] << std::endl;

	}

	for (size_t i = 0; i < n2; ++i)
	{
		//R[i] = A[m + i + 1];
		//std::cout << "R[" << i << "] " << R[i] << "   " << "A[m + i + 1] " << "A[" << m + i + 1 << "] " << A[m + i + 1] << std::endl;

		R[i] = A[m + i];
		std::cout << "R[" << i << "] " << R[i] << "   " << "A[m + i + 1] " << "A[" << (m + i) << "] " << A[m + i] << std::endl;

	}

	//signal values in the end
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;

	unsigned int i = 0;
	unsigned int j = 0;

#ifdef Debug
	std::cout << '\n' << std::endl;
	std::cout << "After INT_MAX: " << std::endl;

	for (size_t i = 0; i <= n1; ++i)
	{
		std::cout << "L[" << i << "] " << L[i] << ' ';
	}
	std::cout << '\n' << std::endl;

	for (size_t i = 0; i <= n2; ++i)
	{
		std::cout << "R[" << i << "] " << R[i] << ' ';
	}
	std::cout << '\n' << std::endl;
#endif //Debug

	std::cout << "Filling A: " << std::endl;

	for (size_t k = l - 1; k < r; ++k)
	{
		//std::cout << k << std::endl;

		if (L[i] <= R[j])
		{
			A[k] = L[i];
			std::cout << "L[" << i << "] " << L[i] << ' ' << "A[" << k << "] " << A[k] << std::endl;
			++i;
		}
		else
		{
			A[k] = R[j];
			std::cout << "R[" << j << "] " << R[j] << ' ' << "A[" << k << "] " << A[k] << ' ' << std::endl;
			++j;
		}
	}

	std::cout << '\n' << std::endl;
	std::cout << "Before OUT:" << std::endl;

	/*std::cout << "A " << std::endl;
	for (auto const&n : A)
	{
	std::cout << n << ' ';
	}*/
	std::cout << '\n';
	std::cout << "L " << std::endl;
	for (size_t k = 0; k < i; ++k)
	{
		std::cout << L[k] << ' ';
	}

	std::cout << '\n' << "R " << std::endl;
	for (size_t k = 0; k < j; ++k)
	{
		std::cout << R[k] << ' ';
	}
	std::cout << '\n' << std::endl;

	delete[] L;
	delete[] R;
}

void MergeSort(int* A, unsigned int start, unsigned int end)
{

	if (start < end)
	{
		unsigned int mid = (start + end) / 2;
		//std::cout << q << std::endl;
		MergeSort(A, start, mid);
		MergeSort(A, mid + 1, end);
		Merge(A, start, mid, end);
	}

}

#endif //MergeSortTmpl

int main(int argc, char** argv)
{
	//int *zz = new int(1);
#ifdef MergeSortTmpl

	//std::vector<int> A{ 2, 4, 5, 7, 1, 2, 3, 6 };

	//std::vector<int> A{ 5,2,4,6,1,3,2,6 };

	int A[] = { 5, 2, 4, 6, 1, 3, 2, 6, 0 };
	constexpr unsigned int arrayLength = sizeof(A) / sizeof(int);

	//std::cout << "&A" << &A << std::endl;

	//unsigned int arrayLength = A.size();

	/*unsigned int p = 1;
	unsigned int q = 4;
	unsigned int r = A.size();
	Merge(A, p, q, r);*/

	MergeSort(A, 1, arrayLength);

	std::cout << '\n' << std::endl;

#ifdef Debug
	for (const auto &n : A)
	{
		std::cout << n << ' ';
	}

	std::cout << '\n' << std::endl;
#endif //Debug

#endif //MergeSortTmpl

	system("pause");
	return 0;
}




#endif //Placeholder

#ifdef oldVec
template<typename T>
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
#endif //oldVec
