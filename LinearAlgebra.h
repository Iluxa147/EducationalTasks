#pragma once
#include <map>

//#define BezierFindCoords //input - 3 'int' coords to create bezier. Output - all bezier coords intercted withs all 'int' at bezier scope

#ifdef BezierFindCoords 
bool isTValid(const float &t)
{
	return t >= 0 && t <= 1;
}

void SetTAndCoordPair(const float pSingleCoord1, const float pSingleCoord2, const float pSingleCoord3, const float pSingleCoordI, std::map<float, int> &tBySinglePointCoord)
{
	float t; //t value is on [0; 1] section (normalized curve coords)
	if (pSingleCoord1 == pSingleCoord2 && pSingleCoord1 != pSingleCoord3)
	{
		t = sqrtf((pSingleCoordI - pSingleCoord1) / (pSingleCoord3 - pSingleCoord2));
		if (isTValid(t))
		{
			tBySinglePointCoord.emplace(t, pSingleCoordI);
		}
	}

	else if (pSingleCoord1 - 2 * pSingleCoord2 + pSingleCoord3 == 0 && pSingleCoord1 != pSingleCoord2)
	{
		t = (pSingleCoordI - pSingleCoord1) / (2 * (pSingleCoord2 - pSingleCoord1));
		if (isTValid(t))
		{
			tBySinglePointCoord.emplace(t, pSingleCoordI);
		}
	}

	else if (pSingleCoord1 - 2 * pSingleCoord2 + pSingleCoord3 != 0)
	{
		t = (pSingleCoord1 - pSingleCoord2 + sqrtf((pSingleCoord1 - 2 * pSingleCoord2 + pSingleCoord3)*pSingleCoordI + powf(pSingleCoord2, 2) - pSingleCoord1 * pSingleCoord3)) / (pSingleCoord1 - 2 * pSingleCoord2 + pSingleCoord3);
		if (isTValid(t))
		{
			tBySinglePointCoord.emplace(t, pSingleCoordI);
		}
		t = (pSingleCoord1 - pSingleCoord2 - sqrtf((pSingleCoord1 - 2 * pSingleCoord2 + pSingleCoord3)*pSingleCoordI + powf(pSingleCoord2, 2) - pSingleCoord1 * pSingleCoord3)) / (pSingleCoord1 - 2 * pSingleCoord2 + pSingleCoord3);
		if (isTValid(t))
		{
			tBySinglePointCoord.emplace(t, pSingleCoordI);
		}
	}
}

float GetPointSingleCoord(const float pCoord1, const float pCoord2, const float pCoord3, const float t)
{
	return powf((1 - t), 2)*pCoord1 + 2 * t*(1 - t)*pCoord2 + powf(t, 2)*pCoord3;
}

#endif BezierFindCoords
