#pragma once
/*
represents memory different types of memory allocations
*/
//#include <iostream>


#define PlacementNew


#ifdef PlacementNew
void PlacementExample()
{
	const int Buf = 512;
	const int N = 5;
	char buffer[Buf];
	//int i;
	std::cout << "1st new and placement new" << std::endl;
	double *pd1, *pd2;
	pd1 = new double[N]; //new mem in heap for N doubles
	pd2 = new (buffer) double[N]; // placement new at buffer adress with [N] size
	for (size_t i = 0; i < N; ++i)
	{
		pd2[i] = pd1[i] = 1000 + 20.0*i;
	}
	std::cout << "Memory addresses: \n" << "heap: "<< pd1 << " static: " << (void*)buffer << std::endl;
	std::cout << "Memory contents: \n";
	for (size_t i = 0; i < N; ++i)
	{
		std::cout << pd1[i] << " at " << &pd1[i] << "; ";
		std::cout << pd2[i] << " at " << &pd2[i] << "; \n";
	}

	std::cout << "2nd new and placement new" << std::endl;
	double *pd3, *pd4;
	pd3 = new double[N]; //new mem in heap for N doubles
	pd4 = new (buffer) double[N]; // placement new at buffer adress with [N] size
	for (size_t i = 0; i < N; ++i)
	{
		pd4[i] = pd3[i] = 1000 + 40.0*i;
	}
	std::cout << "Memory contents: \n";
	for (size_t i = 0; i < N; ++i)
	{
		std::cout << pd3[i] << " at " << &pd3[i] << "; ";
		std::cout << pd4[i] << " at " << &pd4[i] << "; \n";
	}

	std::cout << "3rd new and placement new" << std::endl;
	delete[] pd1;
	pd1 = new double[N]; //new mem in heap for N doubles
	pd2 = new (buffer+N*sizeof(double)) double[N]; // placement new at buffer adress with [N] size
	for (size_t i = 0; i < N; ++i)
	{
		pd4[i] = pd3[i] = 1000 + 60.0*i;
	}
	std::cout << "Memory contents: \n";
	for (size_t i = 0; i < N; ++i)
	{
		std::cout << pd1[i] << " at " << &pd1[i] << "; ";
		std::cout << pd2[i] << " at " << &pd2[i] << "; \n";
	}
	delete[] pd1;
	delete[] pd3;
}


#endif PlacementNew