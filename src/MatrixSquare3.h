#pragma once

#include "MatrixSquare2.h"

class CMatrixSquare3
{
public:
	typedef uint8_t index_t;
	typedef double value_t;

	CMatrixSquare3();
	value_t GetDeterminant() const;
	CMatrixSquare3 GetAdjugate() const;
	CMatrixSquare2 GetMinorMatrix(index_t row, index_t column) const;
	value_t GetMinor(index_t row, index_t column) const;
	value_t GetCofactor(index_t row, index_t column) const;
	void Print() const;
	void DivideMatrixValues(value_t divisor);
	CMatrixSquare3 GetInvertedMatrix() const;
	bool IsSingular() const;
	bool ReadFromFile(const char fileName[]);
protected:
	static const index_t SIZE = 3;
	value_t m_data[SIZE][SIZE];

	static bool CheckCoords(index_t row, index_t column);
	static int GetCofactorSign(index_t row, index_t column);
};
