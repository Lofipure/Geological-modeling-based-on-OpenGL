#ifndef _TIN_H_
#define _TIN_H_

#include <vector>
#include <cmath>
#include <iostream>
#include "Line.h"
#include "Tri.h"
#include "Point.h"

#include <cstdlib>
#include <ctime>

class TIN
{
public:
	std::vector<Point> pointList;
	std::vector<Line> lineList;
	std::vector<Tri> triList;

public:
	double angle(Line line, long p);
	long Max(Line line, std::vector<long> usableList);
	double F(Line line, long p3);
	double distance(long p1, long p2);

	void createPoint(int n);
	void createTin();
	void writeFile();

public:
	TIN() = default;
};
#endif // !_TIN_H_
