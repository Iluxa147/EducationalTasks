#pragma once
#include <string>

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
	/*std::string str = "ABCDE";
	StrReverseChar(str);
	StrReverseXOR(str);
	std::cout << str << std::endl;*/
}

void RemoveDups(char *pStr)
{
	if (!pStr[0])
	{
		return;
	}
	unsigned int prev = 0u;
	for (unsigned int i = 1; pStr[i]; ++i)
	{
		if (pStr[i] != pStr[prev])
		{
			++prev;
			pStr[prev] = pStr[i];
		}
	}
	pStr[++prev] = '\0';

	///	char str[] = "AAA BBB ÀÀÀ";
	///RemoveDups(str);
}

void DecToBin(const int val)
{
	int j = 0;
	if (val == 0)
	{
		std::cout << 0;
		return;
	}

	int i = 31; //32-1
	while (!((val >> i) & 1u))
	{
		val >> i--;
		j++;
	}
	for (&i; i >= 0; --i)
	{
		std::cout << ((val >> i) & 1u);
		j++;
	}
	std::cout << ' '<<j;

	///DecToBin(INT_MIN);
}

class FStream
{
public:
	std::FILE *file;
	int position;

public:
	FStream(const char* filename) : file(nullptr), position(0)
	{
		file = std::fopen(filename, "rb");
	};


	~FStream() { fclose(file); };

};