#pragma once

class CMatrix
{
public:
	typedef uint8_t index_t;
	typedef double value_t;

	CMatrix(index_t size);
	void SetValue(index_t row, index_t column, value_t value);
	value_t GetValue(index_t row, index_t column) const;
	value_t GetDeterminant() const;
	void GetAdjugate(CMatrix ** outMatrixPtr) const;
	void GetCutMatrix(index_t cutRow, index_t cutColumn, CMatrix ** outMatrixPtr) const;
	value_t GetMinor(index_t row, index_t column) const;
	value_t GetCofactor(index_t row, index_t column) const;
	void Print() const;
	void GetTransposedMatrix(CMatrix ** outMatrixPtr) const;
	void DivideMatrixValues(value_t divisor);
	void GetInvertedMatrix(CMatrix ** outMatrixPtr) const;
	bool IsSingular() const;
protected:
	static const index_t MAX_SIZE = 3;

	value_t m_data[MAX_SIZE][MAX_SIZE];
	index_t m_size;

	bool CheckCoords(index_t row, index_t column) const;
	static int GetCofactorSign(index_t row, index_t column);
};
