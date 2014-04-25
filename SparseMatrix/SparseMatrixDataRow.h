#pragma once
#include "SuperLU_4.3\SRC\slu_ddefs.h"

// wrapper class for matrix data store in row order
class SparseMatrixDataRow {
	friend class SparseMatrixData; 

	// data
	SuperMatrix* supermatrix;

	// getters
	NRformat* getData() { return (NRformat*) supermatrix->Store; }
	const NRformat* getData() const { return (NRformat*) supermatrix->Store; }
	inline double* nzvel(){  return (double*) getData()->nzval; }
	inline int*    colinx(){ return getData()->colind; }
	inline int*    rowptr(){ return getData()->rowptr; }
public:
	inline const int&    nnz()   const { return getData()->nnz; }
	inline double* const nzvel() const { return (double*) getData()->nzval; }
	inline int* const    colinx() const { return getData()->colind; }
	inline int* const    rowptr() const { return getData()->rowptr; }
	inline const SuperMatrix* getSuperMatrix() const { return supermatrix; }

private:

	// constructors & destructors
	SparseMatrixDataRow( int rows, int cols, double nzval[], int colidx[], int rowptr[], int N ); 
	SparseMatrixDataRow( int rows, int cols, const double non_zero_value[], 
		const int col_index[], const int row_pointer[], int N ); 
	~SparseMatrixDataRow(); 
}; 