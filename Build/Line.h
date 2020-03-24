#ifndef _LINE_H_
#define _LINE_H_

class Line
{
public:
	long p0, p1;
	int useCount;

	Line();
	bool friend operator==(Line line0, Line line1);
};
#endif // !_LINE_H_
