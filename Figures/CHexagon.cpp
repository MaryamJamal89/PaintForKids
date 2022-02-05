#include "CHexagon.h"
#include<fstream>
#include <iostream>

// Define Infinite (Using INT_MAX caused overflow problems)
#define INF 10000

int CHexagon::HexCnt = 0;  //static variable to determine the number of objects

CHexagon::CHexagon()
{
	HexCnt++;
}

CHexagon::CHexagon(int Xarr[], int Yarr[], Point C, int len, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Center = C;
	length = len;
	for (int i = 0; i < 6; i++)
	{
		Xpoints[i] = Xarr[i];
		Ypoints[i] = Yarr[i];
	}
	HexCnt++;
}

CHexagon::~CHexagon() {
	HexCnt--;
}

void CHexagon::DrawMe(GUI* pOut) const
{
	//Call Output::DrawHex to draw a Hexagon on the screen	
	pOut->DrawHex(Xpoints, Ypoints, FigGfxInfo, Selected);
}

// figure Name
string CHexagon::FigureName()
{
	return "Hexagon";
}

// save figure in the file
void CHexagon::Save(ofstream& file, GUI* pGUI)
{
	file << "HEX " << ID << " " << Center.x << " " << Center.y << " " << length << " ";

	for (int i = 0; i < 6; i++) {
		file << Xpoints[i] << " " << Ypoints[i] << " ";
	}

	file << pGUI->ColorToString(FigGfxInfo.DrawClr) << " ";

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
	loadedFile >> ID >> Center.x >> Center.y >> length;
	for (int i = 0; i < 6; i++) {
		loadedFile >> Xpoints[i] >> Ypoints[i];
	}
	loadedFile >> drawColor >> fillColor;
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
	Point points[6];
	for (int i = 0; i < 6; i++)
	{
		points[i].x = Xpoints[i];
		points[i].y = Ypoints[i];
	}

	return isInside(points, 6, { x, y });
}

// Print to return all info about figure
void CHexagon::PrintInfo(GUI* pGUI)
{
	string id = to_string(ID);
	string x = to_string(Center.x);
	string y = to_string(Center.y);
	string len = to_string(length);

	string fillingColor;
	if (FigGfxInfo.isFilled)
	{
		fillingColor = pGUI->ColorToString(FigGfxInfo.FillClr);
	}
	else
	{
		fillingColor = "NO_FILL";
	}
	pGUI->PrintMessage("Hexagon / ID: " + id + " / Center: (" + x + ", " + y + ") / Length: " + len + " / Drawing Color:" + pGUI->ColorToString(FigGfxInfo.DrawClr) + " / Filling Color: " + fillingColor);
}

// take a copy of pointer obj without Refernce
CHexagon* CHexagon::CloneFig()
{
	//HexCnt++;
	return new CHexagon(*this);
}


int CHexagon::GetCount()
{
	return HexCnt;
}

void CHexagon::IncCount()
{
	HexCnt++;
}

int CHexagon::Resize(double scale)
{
	 length *= scale;

	int xpoints[6];
	int ypoints[6];

	xpoints[0] = Center.x - length;
	ypoints[0] = Center.y;
	xpoints[1] = Center.x - length / 2;
	ypoints[1] = Center.y - (length - length / 20 * 3);
	xpoints[2] = Center.x + length / 2;
	ypoints[2] = Center.y - (length - length / 20 * 3);
	xpoints[3] = Center.x + length;
	ypoints[3] = Center.y;
	xpoints[4] = Center.x + length / 2;
	ypoints[4] = Center.y + (length - length / 20 * 3);
	xpoints[5] = Center.x - length / 2;
	ypoints[5] = Center.y + (length - length / 20 * 3);


	for (int i = 0; i < 6; i++)
	{
		if (ypoints[i]  < UI.ToolBarHeight || ypoints[i] >= (UI.height - UI.StatusBarHeight))
		{
			return 1;
		}
	}

	for (int i = 0; i < 6; i++) {

		Xpoints[i] = xpoints[i];
		Ypoints[i] = ypoints[i];
	}

	return 0;
}

