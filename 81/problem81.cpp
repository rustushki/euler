#include <iostream>
#include <new>
#include <vector>
#include <fstream>
#include <cstdlib>

// H and W of the square matrix.
#define N 80


// Problem matrix.
std::vector< std::vector<unsigned int> > m;

// Store minimum computed paths in this matrix.
std::vector< std::vector<unsigned int> > s;

/*------------------------------------------------------------------------------
 * getMatrix - retrieve the matrix for problem 81.
 */
std::vector< std::vector<unsigned int> > getMatrix() {

	// Store the matrix here.
	std::vector< std::vector<unsigned int> > matrix;

	// Here's the expected file.
	std::ifstream fin("matrix.txt");

	// A row of the matrix.
	std::vector<unsigned int> row;

	// Read in N numbers from the file and push them in order onto the row.
	int x = 0;
	while (!fin.eof()) {

		unsigned int num;
		fin >> num;
		if (!fin.eof()) {
			row.push_back(num);

			// When you've read in N numbers, push the row into the matrix and
			// create a new row.
			if (x == N-1) {
				matrix.push_back(row);
				x = 0;
				row = std::vector<unsigned int>();
			} else {
				x++;
			}

			// Repeat.
		}
	}

	return matrix;
}

/*------------------------------------------------------------------------------
 * getEmptyMatrix - Get an NxN matrix where each value is initialized to 0.
 */
std::vector< std::vector<unsigned int> > getEmptyMatrix() {
	std::vector< std::vector<unsigned int> > matrix;

	for (int x = 0; x < N; x++) {
		matrix.push_back(std::vector<unsigned int>(N, 0));
	}

	return matrix;
}


/*------------------------------------------------------------------------------
 * setMinPath - Given a cell, set the minimum path from that cell to the cell
 * at N-1, N-1.  It's able to do so by assuming that the cell below and to the
 * right of the given cell have already had their minimum paths computed.
 *
 * If a cell below or to the right does not exist, it receives a value of
 * 0--which is always assumed to be an invalid path length.  This rule applies
 * to edges and the SE corner.
 */
void setMinPath(int x, int y) {

	// Determine the minimum path of the cell below. 0 if non-existent.
	int down = 0;
	if (y+1 <= N-1) {
		down = s[y+1][x];
	}

	// Determine the minimum path of the cell rightwards. 0 if non-existent.
	int right = 0;
	if (x+1 <= N-1) {
		right = s[y][x+1];
	}

	// If the cell below doesn't exist, use the cell rightwards.
	if (down == 0) {
		s[y][x] = m[y][x] + right;

	// If the cell to the right doesn't exist, use the cell below.
	} else if (right == 0) {
		s[y][x] = m[y][x] + down;

	// If the cell below has a smaller path than the cell rightwards, use that
	// path.
	} else if (down < right) {
		s[y][x] = m[y][x] + down;

	// If the cell rightwards has a smaller path than the cell rightwards, use
	// that path.
	} else {
		s[y][x] = m[y][x] + right;
	}

}

int main() {

	// Get the problem's matrix.
	m = getMatrix();

	// Get the empty matrix.
	s = getEmptyMatrix();

	// Iterate over the SW to NE diagonals starting with the one in cell N-1,
	// N-1. and ending in the one in cell 0,0.
	for (int diag = N*2; diag >= 1; diag--) {

		// Determine the first cell in the diagonal.
		int startX;
		int startY;
		if (diag > N) {
			startX = diag - N;
			startY = N;
		} else {
			startX = 1;
			startY = diag;
		}

		// Set x and y to the first cell of the diagonal.
		int x = startX;
		int y = startY;

		// Iterate over each cell in the diagonal.
		while (y >= startX) {

			// Determine the minimum path to (N-1, N-1) for the cell (x,y)
			setMinPath(x-1, y-1);

			// Move to the next cell in the diagonal.
			x++;
			y--;

		}

		// Next diagonal, please.
	}

	// The result is in cell (0,0).
	std::cout << s[0][0] << std::endl;

	return 0;
}
