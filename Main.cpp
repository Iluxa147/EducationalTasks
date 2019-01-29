#include <iostream>
#include <set>
#include <vector>

#include "Algorithms.h"
#include "LinearAlgebra.h"
#include "IPVector.h"

#include "vld.h"

//#define StringDevider //devide your string with any symbol

void ShowV(IPVector<int>& v)
{
	//std::cout << std::endl;

	for (size_t i = 0; i < v.getSize(); ++i)
	{
		std::cout << i << "     " << v[i] << std::endl;
	}
	std::cout << "Size: " << v.getSize() << std::endl;
	std::cout << "Capacity: " << v.getCapacity() << std::endl;
	std::cout << std::endl;

}

int main(int argc, char** argv)
{
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

	auto ii = log((double)20);
	auto iii = log(2.0);


	size_t Log = ceil(log((double)20) / log(2.0));
	auto zzz = (1 << Log);


	std::vector<int> stdV(20);
	stdV.resize(30);



	stdV.pop_back();
	//stdV[2] = 4;
	//stdV[9] = 50;

	//int zz = stdV[2];

	stdV.resize(5);
	stdV.resize(100);
	auto ggg = stdV[99];
	stdV.push_back(3);
	stdV.reserve(5);
	stdV.pop_back();
	//auto gg = stdV.back();
	//auto fff = stdV.max_size();


	IPVector<int> v11 = { 1,2 };
	IPVector<int> v(20);


	v[0] = 0;

	v.resize(5);
	v.back() = 4;

	ShowV(v);

	v.pushBack(5);
	ShowV(v);
	v.popBack();
	//v.resize(100);
	ShowV(v);

	v.resize(30);
	ShowV(v);


	v.pushBack(5);
	ShowV(v);
	v.clear();

	//v.reserve(150);
	//v.pushBack(3);

	//v.pushBack(2);
	//auto fff = v[99];

	






	//IPVector<int> v4(IPVector<int>(2)); //TODO not a move constructor ?
	
	IPVector<int> v4(std::move(v)); //Move constructor
	v4 = IPVector<int>(2);		//=&& operator



	v = v4;




	std::cout << '\n';
	system("pause");
	return 0;
}