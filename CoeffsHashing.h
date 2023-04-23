#pragma once
#include <iostream>

class CoeffsHashing
{
	public:
		static double getDist(double key);
	private:
		static int sign(double x);
		static int hash(double v);
};