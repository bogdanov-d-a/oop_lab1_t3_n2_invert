#include "stdafx.h"
#include "MatrixSquare3.h"

CMatrixSquare3::CMatrixSquare3()
{
	for (size_t row = 0; row < SIZE; ++row)
	{
		for (size_t column = 0; column < SIZE; ++column)
		{
			m_data[row][column] = 0;
		}
	}
}

bool CMatrixSquare3::CheckCoords(size_t row, size_t column)
{
	return (row < SIZE && column < SIZE);
}

CMatrixSquare3::Value CMatrixSquare3::GetDeterminant() const
{
	return (m_data[0][0] * GetMinor(0, 0) - m_data[0][1] * GetMinor(0, 1) + m_data[0][2] * GetMinor(0, 2));
}

CMatrixSquare3 CMatrixSquare3::GetAdjugate() const
{
	CMatrixSquare3 adj;

	for (size_t row = 0; row < SIZE; ++row)
	{
		for (size_t column = 0; column < SIZE; ++column)
		{
			adj.m_data[row][column] = GetCofactor(column, row);
		}
	}

	return adj;
}

int CMatrixSquare3::GetCofactorSign(size_t row, size_t column)
{
	if ((row + column) % 2 == 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

CMatrixSquare2 CMatrixSquare3::GetMinorMatrix(size_t row, size_t column) const
{
	assert(CheckCoords(row, column));
	CMatrixSquare2 result;

	for (size_t targetRow = 0; targetRow < SIZE - 1; ++targetRow)
	{
		size_t sourceRow = targetRow;
		if (targetRow >= row)
		{
			++sourceRow;
		}

		for (size_t targetColumn = 0; targetColumn < SIZE - 1; ++targetColumn)
		{
			size_t sourceColumn = targetColumn;
			if (targetColumn >= column)
			{
				++sourceColumn;
			}

			result.SetValue(targetRow, targetColumn, m_data[sourceRow][sourceColumn]);
		}
	}

	return result;
}

CMatrixSquare3::Value CMatrixSquare3::GetMinor(size_t row, size_t column) const
{
	return GetMinorMatrix(row, column).GetDeterminant();
}

CMatrixSquare3::Value CMatrixSquare3::GetCofactor(size_t row, size_t column) const
{
	return (GetCofactorSign(row, column) * GetMinor(row, column));
}

void CMatrixSquare3::DivideMatrixValues(Value divisor)
{
	assert(divisor != 0);

	for (size_t row = 0; row < SIZE; ++row)
	{
		for (size_t column = 0; column < SIZE; ++column)
		{
			m_data[row][column] /= divisor;
		}
	}
}

CMatrixSquare3 CMatrixSquare3::GetInvertedMatrix() const
{
	assert(!IsSingular());
	CMatrixSquare3 result = GetAdjugate();
	result.DivideMatrixValues(GetDeterminant());
	return result;
}

bool CMatrixSquare3::IsSingular() const
{
	return (GetDeterminant() == 0);
}

void CMatrixSquare3::SetValue(size_t row, size_t column, Value value)
{
	assert(CheckCoords(row, column));
	m_data[row][column] = value;
}

CMatrixSquare3::Value CMatrixSquare3::GetValue(size_t row, size_t column) const
{
	assert(CheckCoords(row, column));
	return m_data[row][column];
}
