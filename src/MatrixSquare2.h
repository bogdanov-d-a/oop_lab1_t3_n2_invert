#pragma once

class CMatrixSquare2
{
public:
	typedef double Value;

	CMatrixSquare2();
	void SetValue(size_t row, size_t column, Value value);
	Value GetDeterminant() const;

private:
	static const size_t SIZE = 2;
	Value m_data[SIZE][SIZE];
	static bool CheckCoords(size_t row, size_t column);
};
