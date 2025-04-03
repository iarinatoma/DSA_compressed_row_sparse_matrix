#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

#include <utility>
using namespace std;

class Matrix {

private:
	int* rand_arr; // array principal, marcam incep. fiecarui rand. are lungine de randuri+1
	int* col_arr;
	TElem* val_arr;
	int nr_col, nr_rand, capacity, non_zero;

	void dublam_capacitatea();
	void micsoram_capacitatea();
	bool pozitie_valida(int i, int j) const;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	Matrix multiply(const Matrix& other) const;

	// destructor
	~Matrix();

};
