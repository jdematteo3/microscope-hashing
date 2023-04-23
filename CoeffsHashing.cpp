#include "CoeffsHashing.h"
#include <iostream>
#include "Data.h"

int  CoeffsHashing::sign(double x) {
	if (x > 0)
		return 1;
	else if (x < 0)
		return -1;
	else
		return 0;
}
double CoeffsHashing::getDist(double key) 
{
	int index = hash(key);
	double c[4] = { voltToDist::coeffs[index][0],
						voltToDist::coeffs[index][1], 
						voltToDist::coeffs[index][2],
						voltToDist::coeffs[index][3] };

	return c[0] * pow(key - voltToDist::breaks[index], 3) 
		+ c[1] * pow(key - voltToDist::breaks[index], 2)
		+ c[2] * pow(key - voltToDist::breaks[index], 1) +
		c[3];

}

int CoeffsHashing::hash(double v)
{
	int curInd = (int)(-23.3083 * pow(v, 8) + 466.1509 * pow(v, 7) +
		-3982.1476 * pow(v, 6) + 18919.2055 * pow(v, 5) +
		-54416.7628 * pow(v, 4) + 96397.9527 * pow(v, 3) +
		-102360.6215 * pow(v, 2) + 62611.00495 * v + -17801.55039);

	//if out of range, set index to min/max
	if (curInd < 0)
		return 0;
	if (curInd > 5806)
		return 5806;

	//-1 means guess is under, 1 means guess is over
	int underover = sign(voltToDist::breaks[curInd] - v);
	int underoverPrev = underover;

	bool switched = 0; //flips to 1 if underover has switched signs

	while (!switched) {
		if (underover > 0) //if above
			curInd--; //go down 1 spot
		if (underover < 0) //if below
			curInd++; //move up 1 spot
		if (underover == 0) //if equal
			return curInd;

		//if out of range, set index to min/max
		if (curInd < 0)
			return 0;
		if (curInd > 5806)
			return 5806;
		
		underover = sign(voltToDist::breaks[curInd] - v);

		if (underoverPrev != underover)
			return curInd;

		underoverPrev = underover;
	}

}
