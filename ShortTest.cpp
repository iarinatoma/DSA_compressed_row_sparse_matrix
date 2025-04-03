#include <iostream>
#include <assert.h>
#include "Matrix.h"
using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
}

void testMultiply() {
	Matrix m1(2, 2);
	m1.modify(0, 0, 1);
	m1.modify(0, 1, 2);
	m1.modify(1, 0, 3);
	m1.modify(1, 1, 4);

	Matrix m2(2, 2);
	m2.modify(0, 0, 5);
	m2.modify(0, 1, 6);
	m2.modify(1, 0, 7);
	m2.modify(1, 1, 8);

	Matrix result = m1.multiply(m2);

	assert(result.element(0, 0) == 19); // 1*5 + 2*7 = 19
	assert(result.element(0, 1) == 22); // 1*6 + 2*8 = 22
	assert(result.element(1, 0) == 43); // 3*5 + 4*7 = 43
	assert(result.element(1, 1) == 50); // 3*6 + 4*8 = 50

	// Dacă testul trece fără erori, afișăm un mesaj de succes
	cout << "TEST MULTIPLY" << endl;
}
