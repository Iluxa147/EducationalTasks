#pragma once
#include <iostream>
#include <string>
#include <random>

//#define InsertionSort //n^2
//#define MegreSort //nlog(n)
//#define MinMaxSimultaneously //n

#ifdef MegreSort
void Merge(int* A, unsigned int p, unsigned int q, unsigned int r)
{
	unsigned int n1 = q - p + 1;
	unsigned int n2 = r - q;

	int *L = new int[n1 + 1];
	int *R = new int[n2 + 1];

	for (size_t i = 0; i < n1; ++i)
	{
		L[i] = A[p + i - 1];
	}

	for (size_t i = 0; i < n2; ++i)
	{
		R[i] = A[q + i];
	}

	//signal values in the end
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;

	unsigned int i = 0;
	unsigned int j = 0;

	for (size_t k = p - 1; k < r; ++k)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			++i;
		}
		else
		{
			A[k] = R[j];
			++j;
		}
	}

	delete[] L;
	delete[] R;
}

void MergeSort(int* A, unsigned int p, unsigned int r)
{
	if (p < r)
	{
		unsigned int q = (p + r) / 2;
		MergeSort(A, p, q);
		MergeSort(A, q + 1, r);
		Merge(A, p, q, r);
	}
}
#endif MegreSort

#ifdef MinMaxSimultaneously

void SimultaneouslyMinMax(int *arr, const unsigned int arrSize)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> dst(INT_MIN, INT_MAX);
	int min, max;
	long long sum = 0;
	double average;

	//fill array with random numbers
	for (size_t i = 0; i < arrSize; ++i)
	{
		arr[i] = dst(rng);
	}

	//1st part: single comparison, cos array elements count is even
	size_t i = 0;
	if (arr[i] < arr[i + 1])
	{
		min = arr[i];
		max = arr[i + 1];
	}
	else
	{
		min = arr[i + 1];
		max = arr[i];
	}
	sum += static_cast<long long>(arr[i]) + static_cast<long long>(arr[i + 1]);

	//2nd part to achieve 3(n-2)/2 number of operations inside for loop
	for (i = 2; i < arrSize; i += 2)
	{
		if (arr[i] < arr[i + 1])
		{
			if (arr[i] < min)
			{
				min = arr[i];
			}
			if (arr[i + 1] > max)
			{
				max = arr[i + 1];
			}
		}
		else
		{
			if (arr[i + 1] < min)
			{
				min = arr[i + 1];
			}
			if (arr[i] > max)
			{
				max = arr[i];
			}
		}
		sum += static_cast<long long>(arr[i]) + static_cast<long long>(arr[i + 1]);
	}

	average = static_cast<double>(sum) / arrSize;

	std::cout.precision(12);
	std::cout << "MAX = " << max << std::endl;
	std::cout << "MIN = " << min << std::endl;
	std::cout << "AVER = " << average << std::endl;
	std::cout.precision(8);
}
#endif MinMaxSimultaneously

#ifdef InsertionSort

void SortInsertion(int *arr, const unsigned int arrSize)
{
	for (size_t i = 1; i < arrSize; ++i)
	{
		for (size_t j = i; j > 0 && arr[j-1]>arr[j]; --j)
		{
			std::swap(arr[j - 1], arr[j]);
		}
	}
}

#endif InsertionSort