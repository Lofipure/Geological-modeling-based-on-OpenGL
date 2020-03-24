#include "Line.h"

Line::Line()
{
	this->p0 = this->p1 = -1;
	this->useCount = 0;
}

bool operator==(Line line0, Line line1)
{
	if (line0.p0 == line1.p0 && line0.p1 == line1.p1)
	{
		return true;
	}

	if (line0.p0 == line1.p1 && line0.p1 == line1.p0)
	{
		return true;
	}

	return false;
}