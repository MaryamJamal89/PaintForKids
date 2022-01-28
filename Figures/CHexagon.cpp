#include "CHexagon.h"
#include<fstream>

// Define Infinite (Using INT_MAX caused overflow problems)
#define INF 10000

int CHexagon::HexCnt = 0;  //static variable to determine the number of objects

CHexagon::CHexagon(){}

CHexagon::CHexagon(Point C, int len, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = C;
	length = len;
	HexCnt++;
}

void CHexagon::DrawMe(GUI* pOut) const
{
	//Call Output::DrawHex to draw a Hexagon on the screen	
	pOut->DrawHex(Center, length, FigGfxInfo, Selected);
}

// save figure in the file
void CHexagon::Save(ofstream& file, GUI* pGUI)
{
	file << "HEX " << ID << " " << Center.x << " " << Center.y << " " << length << " " << pGUI->ColorToString(FigGfxInfo.DrawClr) << " ";

	if (FigGfxInfo.isFilled == true)
	{
		file << pGUI->ColorToString(FigGfxInfo.FillClr) << endl;
	}
	else
	{
		file << "NO_FILL" << endl;
	}
}

void CHexagon::Load(ifstream& loadedFile, GUI* pGUI)
{
	string drawColor, fillColor;
	loadedFile >> ID >> Center.x >> Center.y >> P.x >> P.y >> drawColor >> fillColor;
	FigGfxInfo.DrawClr = pGUI->StringToColor(drawColor);
	if (fillColor == "NO_FILL")
	{
		FigGfxInfo.isFilled = false;
	}
	else
	{
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr = pGUI->StringToColor(fillColor);
	}
	CHexagon::SetSelected(false);
}


// https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/?ref=gcse
// Given three collinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool CHexagon::onSegment(Point p, Point q, Point r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;
	return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int CHexagon::orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; // collinear
	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// The function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool CHexagon::doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and p2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}


// Returns true if the point p lies inside the polygon[] with n vertices
bool CHexagon::isInside(Point polygon[], int n, Point p)
{
	// There must be at least 3 vertices in polygon[]
	if (n < 3) return false;

	// Create a point for line segment from p to infinite
	Point extreme = { INF, p.y };

	// Count intersections of the above line with sides of polygon
	int count = 0, i = 0;
	do
	{
		int next = (i + 1) % n;

		// Check if the line segment from 'p' to 'extreme' intersects
		// with the line segment from 'polygon[i]' to 'polygon[next]'
		if (doIntersect(polygon[i], polygon[next], p, extreme))
		{
			// If the point 'p' is collinear with line segment 'i-next',
			// then check if it lies on segment. If it lies, return true,
			// otherwise false
			if (orientation(polygon[i], p, polygon[next]) == 0)
				return onSegment(polygon[i], p, polygon[next]);

			count++;
		}
		i = next;
	} while (i != 0);

	// Return true if count is odd, false otherwise
	return count & 1; // Same as (count%2 == 1)
}

 //InFig return boolian to check point inside Figure 
bool CHexagon::InFig(int x, int y)
{
	int d = length;

	Point point1;
	point1.x = Center.x - d;
	point1.y = Center.y;
	Point point2;
	point2.x = Center.x - d / 2;
	point2.y = Center.y - (d - d / 20 * 3);
	Point point3;
	point3.x = Center.x + d / 2;
	point3.y = Center.y - (d - d / 20 * 3);
	Point point4;
	point4.x = Center.x + d;
	point4.y = Center.y;
	Point point5;
	point5.x = Center.x + d / 2;
	point5.y = Center.y + (d - d / 20 * 3);
	Point point6;
	point6.x = Center.x - d / 2;
	point6.y = Center.y + (d - d / 20 * 3);

	Point points[] = { point1, point2, point3, point4,point5,point6 };
	return isInside(points, 6, {x,y});
}

// Print to return all info about figure
void CHexagon::PrintInfo(GUI* pGUI)
{
	string id = to_string(ID);
	string x = to_string(Center.x);
	string y = to_string(Center.y);

	string fillingColor;
	if (FigGfxInfo.isFilled)
	{
		fillingColor = pGUI->ColorToString(FigGfxInfo.FillClr);
	}
	else
	{
		fillingColor = "NO_FILL";
	}
	pGUI->PrintMessage("Hexagon / ID: " + id + " Center: (" + x + ", " + y + ") / Drawing Color:" + pGUI->ColorToString(FigGfxInfo.DrawClr) + " / Filling Color: " + fillingColor);
}
