#include <iostream>
#include <fstream>
#include <cmath>

double getSlope(int ax, int ay, int bx, int by) {
	double m = (double)(ay - by) / (double)(ax - bx);
	return m;
}

double getB(double m, int x, int y) {
	double b = (double)y - m*(double)x;
	return b;
}

/* ------------------------------------------------------------------------------
 * containsOrigin - Determine whether a triangle contains the origin, where a
 * triangle is denoted by it's three vertices.  This function is based on the
 * idea that the lines created by the edges of the triangle will intersect the
 * axes of the Cartesian coordinate plane under certain criteria if the
 * triangle is to contain the origin:
 *
 *   1. Once above the origin on the Y-Axis.  Once below the origin on the
 *   Y-Axis.  Once to the right of the origin on the X-Axis.  Once to the left
 *   of the origin on the X-Axis.  This is the most common case.
 *
 *   2. There are a total of more than 4 intersections with the X and Y axes.
 *   This is a much less common case that is still technically possible.  This
 *   can happen when a vertex of the triangle falls onto an axis.  You can
 *   imagine that a vertex is an intersection of two lines with an axis at the
 *   same point.  Triangle #431 is a prime example of this type.
 *
 */
bool containsOrigin(int ax, int ay, int bx, int by, int cx, int cy) {

	double m;
	double b;
	double xI;
	int maxX;
	int minX;
	int maxY;
	int minY;

	int px = 0;
	int py = 0;
	int nx = 0;
	int ny = 0;

	m = getSlope(ax, ay, bx, by);
	b = getB(m, ax, ay);
	minY = std::min(ay, by);
	maxY = std::max(ay, by);
	minX = std::min(ax, bx);
	maxX = std::max(ax, bx);
	xI = (-1*b/m);

	if (b <= maxY && b >= minY) {
		if (b < 0) {
			ny++;
		} else {
			py++;
		}
	}

	if (xI <= maxX && xI >= minX) {
		if (xI < 0) {
			nx++;
		} else {
			px++;
		}
	}

	m = getSlope(bx, by, cx, cy);
	b = getB(m, bx, by);
	minY = std::min(by, cy);
	maxY = std::max(by, cy);
	minX = std::min(bx, cx);
	maxX = std::max(bx, cx);
	xI = (-1*b/m);


	if (b <= maxY && b >= minY) {
		if (b < 0) {
			ny++;
		} else {
			py++;
		}
	}

	if (xI <= maxX && xI >= minX) {
		if (xI < 0) {
			nx++;
		} else {
			px++;
		}
	}

	m = getSlope(cx, cy, ax, ay);
	b = getB(m, cx, cy);
	minY = std::min(cy, ay);
	maxY = std::max(cy, ay);
	minX = std::min(cx, ax);
	maxX = std::max(cx, ax);
	xI = (-1*b/m);


	if (b <= maxY && b >= minY) {
		if (b < 0) {
			ny++;
		} else {
			py++;
		}
	}

	if (xI <= maxX && xI >= minX) {
		if (xI < 0) {
			nx++;
		} else {
			px++;
		}
	}

	if (py == 1 && ny == 1 && px == 1 && nx == 1) {
		return true;
	
	// This tricky case accounts for when a triangle vertex falls on an intercept.
	} else if (py+ny+px+nx > 4) {
		return true;

	} else {
		return false;
	}

}
int main() {

	int count = 0;

	std::ifstream i ("triangles.txt", std::ifstream::in);
	while (i.good() && !i.eof()) {

		char j;
		int ax;
		int ay;
		int bx;
		int by;
		int cx;
		int cy;

		i >> ax; if (i.eof()) break;
		i.get(j);if (i.eof()) break;
		i >> ay; if (i.eof()) break;
		i.get(j);if (i.eof()) break;
		i >> bx; if (i.eof()) break;
		i.get(j);if (i.eof()) break;
		i >> by; if (i.eof()) break;
		i.get(j);if (i.eof()) break;
		i >> cx; if (i.eof()) break;
		i.get(j);if (i.eof()) break;
		i >> cy; if (i.eof()) break;
		i.get(j);if (i.eof()) break;

		bool contains = containsOrigin(ax, ay, bx, by, cx, cy);

		if (contains) {
			count++;
		}
	}
	i.close();

	std::cout << count << std::endl;

	return 0;
}
