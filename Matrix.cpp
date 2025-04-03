#include <iostream>
#include "Matrix.h"
#include <exception>
#include <utility>
using namespace std;

//complexitate minima: theta(n)
//complexitate average: theta(n)
//complexitate maxima: theta(n)
Matrix::Matrix(int nrLines, int nrCols) {
	if (nrLines < 1 || nrCols <1)
          throw invalid_argument("nrLines and nrCols must be bigger than 0");
    this->nr_rand = nrLines;
    this->nr_col = nrCols;
    this->non_zero = 0;
    this->capacity = 10;

    this->rand_arr = new int[nr_rand + 1];
    this->col_arr = new int[capacity];
    this->val_arr = new TElem[capacity];

    for (int i = 0; i < nr_rand + 1; i++)
        this->rand_arr[i] = 0;
}

//complexitate minima: theta(n)
//complexitate average: theta(n)
//complexitate maxima: theta(n)
void Matrix::dublam_capacitatea() {
	int new_capacity =  capacity*2;

    int* new_col_arr = new int[new_capacity];
    TElem* new_val_arr = new TElem[new_capacity];

    for ( int i = 0; i < non_zero; i++){
    	new_col_arr[i] = col_arr[i];
        new_val_arr[i] = val_arr[i];
    }

    delete[] col_arr;
    delete[] val_arr;

    col_arr = new_col_arr;
    val_arr = new_val_arr;
    capacity = new_capacity;
}

//complexitate minima: theta(n)
//complexitate average: theta(n)
//complexitate maxima: theta(n)
void Matrix::micsoram_capacitatea() {
    if (non_zero < capacity / 4 && capacity > 10) {
    	int new_capacity = capacity / 2;

    	int* new_col_arr = new int[new_capacity];
    	TElem* new_val_arr = new TElem[new_capacity];

    	for ( int i = 0; i < non_zero; i++){
  	  		new_col_arr[i] = col_arr[i];
    	    new_val_arr[i] = val_arr[i];
    	}

    	delete[] col_arr;
    	delete[] val_arr;

    	col_arr = new_col_arr;
    	val_arr = new_val_arr;
    	capacity = new_capacity;
	}
}

//complexitate minima: theta(1)
//complexitate average: theta(1)
//complexitate maxima: theta(1)
bool Matrix::pozitie_valida(int i, int j) const {
    return (i >= 0 && i < nr_rand && j >= 0 && j < nr_col);
}

//complexitate minima: theta(1)
//complexitate average: theta(1)
//complexitate maxima: theta(1)
int Matrix::nrLines() const {
	return nr_rand;
}

//complexitate minima: theta(1)
//complexitate average: theta(1)
//complexitate maxima: theta(1)
int Matrix::nrColumns() const {
    return nr_col;
}

//complexitate minima: theta(1)
//complexitate average: theta(n)
//complexitate maxima: theta(n)
TElem Matrix::element(int i, int j) const {
	if ( not pozitie_valida(i,j) )
       throw out_of_range("Index out of range");

	// verific ca linia nu fie vida.
    if ( rand_arr[i+1] - rand_arr[i] == 0)
    	return NULL_TELEM;

	// trec cu un for prin col_arr dar numa de la randul respectiv
    for ( int k = rand_arr[i]; k < rand_arr[i+1]; k++)
        if ( col_arr[k] == j )	// verific sa am valoare pe coloana respectiva
              return val_arr[k];
    	return NULL_TELEM;
}


//complexitate minima: theta(1)
//complexitate average: theta(n)
//complexitate maxima: theta(n)
TElem Matrix::modify(int i, int j, TElem e) {
    int index, k;

	if ( not pozitie_valida(i,j) )
       throw out_of_range("Index out of range");


    // daca exista deja ceva in matrice inainte
	if ( element (i,j) != NULL_TELEM ){
    	TElem old_val = element (i,j);	// tin minte valoarea veche ca sa o pot retruna

        // imi tine minte unde am sa suprascriu/ de unde am sa suprascriu (sterg)
        for ( k = rand_arr[i]; k < rand_arr[i+1]; k++){ // trec cu un for prin col_arr sa gasesc pozitia coresp pt val_arr care trebe schimbata
            	if ( col_arr[k] == j ){
                	index = k;
                    break;
                }
        }

        // daca vreau sa schimb o val !0 cu o val !0
        if ( e != NULL_TELEM)
        	val_arr[index] = e;	// o schimb efectiv
        else {

            // suprasciu (sterg) de la pozitia aflata mai sus pana in capat
            for ( k = index; k < non_zero-1; k++ ) {
            	col_arr[k] = col_arr[k+1];
                val_arr[k] = val_arr[k+1];
            }

            // ma asigur ca golesc fix ultima pozitie din col_arr si val_arr
            col_arr[non_zero-1] = NULL_TELEM;
			val_arr[non_zero-1] = NULL_TELEM;

        	non_zero--;
            micsoram_capacitatea();

        	// micsoram rand_arr ul de la pozitia i+1
        	for ( k = i+1; k <= nr_rand; k++ )
            	rand_arr[k]-=1;
        }

        return old_val;	//	returnez valoarea veche
    }

	// acum incep cazurile in care nu exista nimic in matrice inainte
    else {
        // daca incerc sa bag pe nimic un nimic, nu se schimba nimic
    	if (e == NULL_TELEM)
    		return NULL_TELEM;

        // daca pe nimic bag ceva !0
    	else if ( e != NULL_TELEM){
			if ( non_zero == capacity )
				dublam_capacitatea();

            // insert_here ma va ajuita sa determin unde trebe inserat un elemenet in col_arr si val_arr
            int insert_here = rand_arr[i];
            while ( insert_here < rand_arr[i+1] && col_arr[insert_here] < j )
                insert_here++;

            // mutam elementele la dreapta sa cream spatiu
            for ( k = non_zero; k > insert_here; k-- ){
                col_arr[k] = col_arr[k-1];
                val_arr[k] = val_arr[k-1];
            }

            // inserarea efectiva plus non_zero++
            col_arr[insert_here] = j;
            val_arr[insert_here] = e;
            non_zero++;

            // marim rand_arr ul de la pozitia i+1
            for ( k = i+1; k <= nr_rand; k++ )
                rand_arr[k]++;
        }
    	// returnez mereu NULL_TELEM ca inainte nu era nimic acolo
        return NULL_TELEM;
    }
}

//complexitate minima: theta(n^2) --> daca cumva matricea are elemente numa pe diagonala principala
//complexitate average: theta(n^3)
//complexitate maxima: theta(n^3)
//pre:matricile sa poata fi inmultite
//post:multiply <- eine matrix die das Losung der multiplikation anderer zwei Matrizen ist
//throws: ein exception falls nr_col != other.nr_rand
Matrix Matrix::multiply(const Matrix& other) const{
	// Verificăm dacă dimensiunile sunt compatibile pentru înmulțire
	if (nr_col != other.nr_rand) {
		throw invalid_argument("Dimensiunile matricelor nu sunt compatibile pentru inmultire.");
	}

	// matrice de rezultate. dupa inmultuire
	Matrix result(nr_rand, other.nr_col);  // numărul de rânduri al primei matrice și numărul de coloane ale celei de-a doua

	for (int i = 0; i < nr_rand; ++i) {
		for (int j = 0; j < other.nr_col; ++j) {
			TElem sum = 0;
			for (int k = rand_arr[i]; k < rand_arr[i + 1]; ++k) { // parcurgem elementele nenule din rândul i
				int col = col_arr[k]; // col[0], col[1], ... -> Coloana din matricea originală
				TElem val = val_arr[k]; // val[0], val[1], ... -> Valoarea din matricea originală

				// Verificăm dacă elementul curent poate fi înmulțit cu un element corespunzător din a doua matrice
				TElem other_val = other.element(col, j);
				sum += val * other_val;
			}
			// Dacă suma nu este 0, atunci setăm elementul rezultat
			if (sum != NULL_TELEM) {
				result.modify(i, j, sum);
			}
		}
	}

	return result;
}
//complexitate minima: theta(1)
//complexitate average: theta(1)
//complexitate maxima: theta(1)
Matrix::~Matrix() {
    delete[] val_arr;
    delete[] col_arr;
    delete[] rand_arr;
}
