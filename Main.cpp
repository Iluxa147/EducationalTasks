#include <iostream>
#include <set>
#include <vector>
#include <cassert>

#include "Algorithms.h"
#include "LinearAlgebra.h"
#include "IPVector.h"
#include "MemoryManagement.h"
#include "Stuff.h"

#include "vld.h" //Visual Leak Detector

//#define StringDevider //devide your string with any symbol

#ifdef VectorStructExample

/*void ShowV(IPVector<int>& v)
{
	//std::cout << std::endl;
	std::cout << "&buff_: " << &v[0] << std::endl;
	for (size_t i = 0; i < v.getSize(); ++i)
	{
		std::cout << i << "    val: " << v[i] << "  &: "<< &v[i] << std::endl;
	}
	std::cout << "Size: " << v.getSize() << std::endl;
	std::cout << "Capacity: " << v.getCapacity() << std::endl;
	std::cout << std::endl;
}*/

struct President
{
	std::string name;
	std::string country;
	int year;

	President() {}
	President(std::string p_name, std::string p_country, int p_year)
		: name(std::move(p_name)), country(std::move(p_country)), year(p_year)
	{
		std::cout << "I am being constructed.\n";
	}
	President(President&& other)
		: name(std::move(other.name)), country(std::move(other.country)), year(other.year)
	{
		std::cout << "I am being moved.\n";
	}
	President& operator=(const President& other) = default;
};
#endif VectorStructExample

int main(int argc, char** argv)
{
#ifdef StringReverse
	std::string str = "ABCDE";
	StrReverseChar(str);
	StrReverseXOR(str);
	std::cout << str << std::endl;
#endif StringReverse

#ifdef MegreSort

	int A[] = { 5, 2, 4, 6, 1, 3, 2, 6 };
	constexpr unsigned int arrayLength = sizeof(A) / sizeof(int);

	MergeSort(A, 1, arrayLength);

	for (size_t i = 0; i < arrayLength; ++i)
	{
		std::cout << A[i] << ' ';
	}

#endif MegreSort

#ifdef MinMaxSimultaneously

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> dst(INT_MIN, INT_MAX);
	constexpr unsigned int arrSize = 100u;
	int min, max;
	int arr[arrSize];

	SimultaneouslyMinMax(arr, arrSize);

#endif MinMaxSimultaneously

#ifdef InsertionSort

	int arr[] = { 5, 2, 4, 6, 1, 3, 2, 6 };
	constexpr unsigned int arrayLength = sizeof(arr) / sizeof(int);

	SortInsertion(arr, arrayLength);

	for (size_t i = 0; i < arrayLength; ++i)
	{
		std::cout << arr[i] << ' ';
	}

#endif InsertionSort

#ifdef StringDevider
	std::string myString, tmpString;
	std::vector<std::string> subStrings;
	char devider, tmpItem;

	std::cout << "Print some string: " << std::endl;
	getline(std::cin, myString);
	std::cout << "Print single char devider: " << std::endl;
	std::cin >> devider;

	tmpItem = devider;
	for (const auto &i : myString)
	{
		if (i != devider)
		{
			tmpString += i;
			tmpItem = i;
		}
		else
		{
			if (tmpItem != devider)
			{
				subStrings.push_back(tmpString);
				tmpString = "";
				tmpItem = i;
			}
		}
	}

	//if it's the last tmpString without key (end of entered string)
	if (tmpString != "")
	{
		subStrings.push_back(tmpString);
	}

	for (const auto &n : subStrings)
	{
		std::cout << n << std::endl;
	}
#endif StringDevider

#ifdef BezierFindCoords 
	int x1, y1; //start point
	int x2, y2; //reference point
	int x3, y3; //end point
	std::map<float, int> tBySinglePointCoord;
	std::set<int> initSingleCoords;
	bool isVertical;
	bool isHorizontal;
	bool isPoint;

	std::cout << "Print 3 point's coords in Xn Yn format from start to end and press <Enter>: " << std::endl;
	std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	std::cout << std::endl;

	isVertical = (x1 == x2 && x2 == x3);
	isHorizontal = (y1 == y2 && y2 == y3);
	isPoint = (isVertical && isHorizontal && x1 == y1);

	//if curve is the vertical line
	if (isVertical)
	{
		initSingleCoords.emplace(y1);
		initSingleCoords.emplace(y2);
		initSingleCoords.emplace(y3);
		auto itYStart = initSingleCoords.cbegin();
		auto itYLast = initSingleCoords.crbegin();

		for (int i = *itYStart; i <= *itYLast; ++i)
		{
			std::cout << "x = " << x1 << " y = " << i << std::endl;
		}
	}

	//if curve is the horizontal line
	else if (isHorizontal)
	{
		initSingleCoords.emplace(x1);
		initSingleCoords.emplace(x2);
		initSingleCoords.emplace(x3);
		auto itXStart = initSingleCoords.cbegin();
		auto itXLast = initSingleCoords.crbegin();

		for (int i = *itXStart; i <= *itXLast; ++i)
		{
			std::cout << "x = " << i << " y = " << y1 << std::endl;
		}
	}

	//if curve is the point
	else if (isPoint)
	{
		std::cout << "x = " << x1 << " y = " << y1 << std::endl;
	}

	//regular curve
	else
	{
		//sort unique x coords to find x-range
		initSingleCoords.emplace(x1);
		initSingleCoords.emplace(x2);
		initSingleCoords.emplace(x3);
		auto itXStart = initSingleCoords.cbegin();
		auto itXLast = initSingleCoords.crbegin();

		// for all suggested int x curves points. If x is not on curve, it will be no t values for that coord
		for (int i = *itXStart; i <= *itXLast; ++i)
		{
			SetTAndCoordPair(x1, x2, x3, i, tBySinglePointCoord);
		}
		// for all finded valid t values
		for (const auto &n : tBySinglePointCoord)
		{
			std::cout << "x = " << n.second << " y = " << GetPointSingleCoord(y1, y2, y3, n.first) << std::endl << std::endl;
		}
	}
#endif BezierFindCoords

#ifdef PlacementNew
	PlacementExample();
#endif PlacementNew


#ifdef VectorStructExample

	/*auto ii = log((double)20.0f);
	auto iii = log(2.0f);
	size_t Log = ceil(log((double)20.0f) / log(2.0f));
	auto zzz = (1 << Log);
	IPVector<bool> vvvv11(2);

	std::vector<int> stdV(20);

	stdV.resize(30);

	stdV.pop_back();
	stdV.resize(5);
	stdV.shrink_to_fit();

	stdV.resize(100);
	auto ggg = stdV[99];
	stdV.push_back(3);
	stdV.reserve(5);
	stdV.pop_back();*/

	///T IPVector
	IPVector<int> vec1 = { 1,2 };
	assert(vec1.getSize() == 2 && vec1.getCapacity() == 2);			//initializer list
	
	vec1.resize(30);
	vec1[0] = 5;
	vec1[29] = 99;
	vec1[1] = 1;
	assert(vec1.getSize() == 30 &&
		vec1.getCapacity() == 30 &&
		vec1[0] == 5 && vec1[1] == 1 && vec1[29] == 99 &&
		&vec1.back() - &vec1.front() + 1 == vec1.getSize());		//resize to bigger

	vec1.popBack();
	assert(vec1.getSize() == 29 && vec1.getCapacity() == 30);		//popBack

	vec1.shrinkToFit();
	assert(vec1.getSize() == 29 && vec1.getCapacity() == 29 &&
		vec1[0] == 5);												//shrinkToFit


	vec1.pushBack(5);
	assert(vec1.getSize() == 30 && vec1.getCapacity() == 43 &&
		vec1.back() == 5 &&
		& vec1.back() - &vec1.front() + 1 == vec1.getSize());		//resize to less

	vec1.clear();

	IPVector<int> vec2(IPVector<int>(2)); //TODO no move constructor cuz compiler optimization?
	
	vec2 = IPVector<int>(2);										
	assert(vec2.getSize() == 2 && vec2.getCapacity() == 2);			//=&& operator

	vec1 = vec2;
	assert(vec1.getSize() == 2 && vec1.getCapacity() == 2);			//copy constructor


	///bool IPVector
	IPVector<bool> vecBool1(2);


	vecBool1[0] = 1;

	IPVector<bool>::ShowV(vecBool1);


#endif VectorStructExample






	std::cout << '\n';
	system("pause");
	return 0;
}