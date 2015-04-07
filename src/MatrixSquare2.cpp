#include "stdafx.h"
#include "MatrixSquare2.h"

CMatrixSquare2::CMatrixSquare2()
{
	for (size_t row = 0; row < SIZE; ++row)
	{
		for (size_t column = 0; column < SIZE; ++column)
		{
			m_data[row][column] = 0;
		}
	}
}

void CMatrixSquare2::SetValue(size_t row, size_t column, Value value)
{
	assert(CheckCoords(row, column));
	m_data[row][column] = value;
}

bool CMatrixSquare2::CheckCoords(size_t row, size_t column)
{
	return (row < SIZE && column < SIZE);
}

CMatrixSquare2::Value CMatrixSquare2::GetDeterminant() const
{
	return (m_data[0][0] * m_data[1][1] - m_data[0][1] * m_data[1][0]);
}
