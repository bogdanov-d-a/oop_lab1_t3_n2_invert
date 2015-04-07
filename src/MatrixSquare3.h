#pragma once

#include "MatrixSquare2.h"

class CMatrixSquare3
{
public:
	typedef double Value;

	CMatrixSquare3();
	CMatrixSquare3 GetInvertedMatrix() const;
	bool IsSingular() const;
	void SetValue(size_t row, size_t column, Value value);
	Value GetValue(size_t row, size_t column) const;

private:
	static const size_t SIZE = 3;
	Value m_data[SIZE][SIZE];

	Value GetDeterminant() const;
	CMatrixSquare3 GetAdjugate() const;
	CMatrixSquare2 GetMinorMatrix(size_t row, size_t column) const;
	Value GetMinor(size_t row, size_t column) const;
	Value GetCofactor(size_t row, size_t column) const;
	void DivideMatrixValues(Value divisor);

	static bool CheckCoords(size_t row, size_t column);
	static int GetCofactorSign(size_t row, size_t column);
};
