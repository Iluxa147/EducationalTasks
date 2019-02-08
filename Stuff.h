#pragma once
#include <string>

//#define StringReverse

#ifdef StringReverse
void StrReverseChar(std::string& src)
{
	int n = src.length();
	for (size_t i = 0; i < n / 2; ++i)
	{
		std::swap(src[i], src[n - i - 1]);
	}
}

void StrReverseXOR(std::string& src)
{
	int first = 0;
	int n = src.length()-1;
	while (first < n)
	{
		src[first] ^= src[n];
		src[n] ^= src[first];
		src[first] ^= src[n];
		++first;
		--n;
	}
}
#endif StringReverse