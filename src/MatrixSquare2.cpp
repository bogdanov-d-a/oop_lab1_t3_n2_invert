#include "stdafx.h"
#include "MatrixSquare2.h"

CMatrixSquare2::CMatrixSquare2()
{
	for (index_t row = 0; row < SIZE; ++row)
	{
		for (index_t column = 0; column < SIZE; ++column)
		{
			m_data[row][column] = 0;
		}
	}
}

void CMatrixSquare2::SetValue(index_t row, index_t column, value_t value)
{
	assert(CheckCoords(row, column));
	m_data[row][column] = value;
}

bool CMatrixSquare2::CheckCoords(index_t row, index_t column)
{
	return (row < SIZE && column < SIZE);
}

CMatrixSquare2::value_t CMatrixSquare2::GetDeterminant() const
{
	return (m_data[0][0] * m_data[1][1] - m_data[0][1] * m_data[1][0]);
}
