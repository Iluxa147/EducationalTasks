#include <iostream>
#include <set>
#include <vector>
#include <cassert>

#include "Algorithms.h"
#include "LinearAlgebra.h"
#include "IPVector.h"
#include "MemoryManagement.h"
#include "Stuff.h"
#include "IPSharedPtr.h"
#include "factory.h"

#include "vld.h" //Visual Leak Detector

#include <memory>

#include "factory.h"

//#define StringDevider //devide your string with any symbol

int main(int argc, char** argv)
{



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
#endif //StringDevider

#ifdef MegreSort

	int A[] = { 5, 2, 4, 6, 1, 3, 2, 6 };
	constexpr unsigned int arrayLength = sizeof(A) / sizeof(int);

	MergeSort(A, 1, arrayLength);

	for (size_t i = 0; i < arrayLength; ++i)
	{
		std::cout << A[i] << ' ';
	}

#endif //MegreSort

#ifdef MinMaxSimultaneously

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> dst(INT_MIN, INT_MAX);
	constexpr unsigned int arrSize = 100u;
	int min, max;
	int arr[arrSize];

	SimultaneouslyMinMax(arr, arrSize);

#endif //MinMaxSimultaneously

#ifdef InsertionSort

	int arr[] = { 5, 2, 4, 6, 1, 3, 2, 6 };
	constexpr unsigned int arrayLength = sizeof(arr) / sizeof(int);

	SortInsertion(arr, arrayLength);

	for (size_t i = 0; i < arrayLength; ++i)
	{
		std::cout << arr[i] << ' ';
	}

#endif //InsertionSort

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
#endif //BezierFindCoords

#ifdef VectorStructExample

	std::vector<int> v(2);
	v.resize(20);
	v.resize(5);

	v.shrink_to_fit();
	v.emplace_back();

	std::vector<bool> b1(2);
	b1[0] = 1;
	auto fdfd = b1.front();
	auto sa = b1.begin();

	///T IPVector
	//initializer list
	auto initList = []()
	{
		IPVector<int> vec1 = { 1,2 };
		assert(vec1.getSize() == 2 && vec1.getCapacity() == 2);
	};
	initList();

	//resize to bigger
	auto resizeToBigger = []()
	{
		IPVector<int> vec1 = { 1,2 };
		vec1[0] = 5;
		vec1[1] = 1;
		vec1.resize(30);
		vec1[29] = 99;
		assert(vec1.getSize() == 30 &&
			vec1.getCapacity() == 30 &&
			vec1[0] == 5 && vec1[1] == 1 && vec1[29] == 99 &&
			&vec1.back() - &vec1.front() + 1 == vec1.getSize());
	};
	resizeToBigger();

	//resize to less
	auto resizeToLess = []()
	{
		IPVector<int> vec1(30);
		vec1.resize(5);
		vec1[0] = 5;
		vec1.popBack();
		assert(vec1.getSize() == 4 && vec1.getCapacity() == 30 &&
			vec1[0] == 5 &&
			& vec1.back() - &vec1.front() + 1 == vec1.getSize());
	};
	resizeToLess();

	//popBack
	auto popBack = []()
	{
		IPVector<int> vec1(30);
		vec1[0] = 1;
		vec1.popBack();
		assert(vec1.getSize() == 29 && vec1.getCapacity() == 30 &&
			vec1[0] == 1);
	};
	popBack();

	//shrinkToFit
	auto shrink = []()
	{
		IPVector<int> vec1(30);
		vec1[0] = 1;
		vec1.popBack();
		vec1.shrinkToFit();
		assert(vec1.getSize() == 29 && vec1.getCapacity() == 29 &&
			vec1[0] == 1);
	};
	shrink();

	//copyMoveSemantics
	auto copyMoveSemantics = []()
	{
 		IPVector<int> vec1(30);
		vec1[0] = 1;
		vec1.clear();
		IPVector<int> vec2(IPVector<int>(2)); //TODO no move constructor cuz compiler optimization?

		vec2 = IPVector<int>(2);
		assert(vec2.getSize() == 2 && vec2.getCapacity() == 2);			//=&& operator

		vec1.pushBack(5);
		vec2[1] = 5;
		vec1 = vec2;
		assert(vec1.getSize() == 2 && vec1.getCapacity() == 2 &&
			vec1[1] == 5);												//= operator
	};
	copyMoveSemantics();

	//copyMoveSemantics
	auto emplace = []()
	{
		IPVector<int> vec1(5);
		vec1.emplaceBack();
	};
	emplace();

	///bool IPVector
	IPVector<bool> vecBool1(33);
	
	vecBool1[0] = true;
	vecBool1[1] = true;
	vecBool1[32] = true;
	IPVector<bool>::ShowVectorElements(vecBool1);
	vecBool1.pushBack(0);
	vecBool1.pushBack(1);
	vecBool1.popBack();

	auto hjdf = vecBool1.front();
	auto hjdfff = vecBool1.back();

	IPVector<bool> vecBool2(IPVector<bool>(2));
	
	vecBool2 = vecBool1;
	assert(vecBool2.getSize() == 34 && vecBool2.getCapacity() == 64 &&
		vecBool2[0] == true && vecBool2[32] == true);				//= operator

	
	//IPVector<bool>::ShowVectorElements(vecBool1);


#endif //VectorStructExample

#ifdef IPSharedPtrExample

	FStream fStream("test.txt");
	


	std::cout << '\n';

	IPSharedPtr<int> p1 (new int(5));
	IPSharedPtr<int> p2;
	bool jsks = p1;
	p2 = p1;

	//std::cout << "val: " << *p1 << " &: " << &p1 << " data&: " << p1.getRawPtr() << '\n';
	std::cout << "val: " << *p2 << " &: " << &p2 << " data&: " << p2.getRawPtr() << '\n';
	
	auto fdfhhsd(p1);

	std::cout << '\n';

	IPSharedPtr<int> p3(new int(6));
	IPSharedPtr<int> p4;

	p4 = p3;

	std::cout << "val: " << *p3 << " &: " << &p3 << '\n';
	std::cout << "val: " << *p4 << " &: " << &p4 << '\n';

	auto fdfggsd(p3);


	std::cout << '\n';
	
	std::shared_ptr<int> sp1 (new int(5));
	std::shared_ptr<int> sp2;
	//sp2 = sp1;

	sp2 = std::move(sp1);

	auto fdfd = sp1;

	//std::cout << "val: " << *sp1 << " &: " << &sp1 << " data&: " << sp1 << '\n';
	std::cout << "val: " << *sp2 << " &: " << &sp2 << " data&: " << sp2 << '\n';


	std::shared_ptr<int> sp3(new int(6));
	std::shared_ptr<int> sp4;
	sp4 = sp3;

	auto fdfsdsd = sp3;

	std::cout << "val: " << *sp3 << " &: " << &sp3 << " data&: " << sp3 << '\n';
	std::cout << "val: " << *sp4 << " &: " << &sp4 << " data&: " << sp4 << '\n';
	
	
#endif //IPSharedPtrExample



	std::cout << '\n';
	system("pause");
	return 0;
}