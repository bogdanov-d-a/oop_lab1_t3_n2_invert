#pragma once

class CMatrixSquare2
{
public:
	typedef uint8_t index_t;
	typedef double value_t;

	CMatrixSquare2();
	void SetValue(index_t row, index_t column, value_t value);
	value_t GetDeterminant() const;

protected:
	static const index_t SIZE = 2;
	value_t m_data[SIZE][SIZE];
	static bool CheckCoords(index_t row, index_t column);
};
