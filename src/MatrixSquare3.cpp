#include "stdafx.h"
#include "MatrixSquare3.h"

CMatrixSquare3::CMatrixSquare3()
{
	for (index_t row = 0; row < SIZE; ++row)
	{
		for (index_t column = 0; column < SIZE; ++column)
		{
			m_data[row][column] = 0;
		}
	}
}

bool CMatrixSquare3::CheckCoords(index_t row, index_t column)
{
	return (row < SIZE && column < SIZE);
}

CMatrixSquare3::value_t CMatrixSquare3::GetDeterminant() const
{
	return (m_data[0][0] * GetMinor(0, 0) - m_data[0][1] * GetMinor(0, 1) + m_data[0][2] * GetMinor(0, 2));
}

CMatrixSquare3 CMatrixSquare3::GetAdjugate() const
{
	CMatrixSquare3 adj;

	for (index_t row = 0; row < SIZE; ++row)
	{
		for (index_t column = 0; column < SIZE; ++column)
		{
			adj.m_data[row][column] = GetCofactor(column, row);
		}
	}

	return adj;
}

int CMatrixSquare3::GetCofactorSign(index_t row, index_t column)
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

CMatrixSquare2 CMatrixSquare3::GetMinorMatrix(index_t row, index_t column) const
{
	assert(CheckCoords(row, column));
	CMatrixSquare2 result;

	for (index_t targetRow = 0; targetRow < SIZE - 1; ++targetRow)
	{
		index_t sourceRow = targetRow;
		if (targetRow >= row)
		{
			++sourceRow;
		}

		for (index_t targetColumn = 0; targetColumn < SIZE - 1; ++targetColumn)
		{
			index_t sourceColumn = targetColumn;
			if (targetColumn >= column)
			{
				++sourceColumn;
			}

			result.SetValue(targetRow, targetColumn, m_data[sourceRow][sourceColumn]);
		}
	}

	return result;
}

CMatrixSquare3::value_t CMatrixSquare3::GetMinor(index_t row, index_t column) const
{
	return GetMinorMatrix(row, column).GetDeterminant();
}

CMatrixSquare3::value_t CMatrixSquare3::GetCofactor(index_t row, index_t column) const
{
	return (GetCofactorSign(row, column) * GetMinor(row, column));
}

void CMatrixSquare3::Print() const
{
	for (index_t row = 0; row < SIZE; ++row)
	{
		for (index_t column = 0; column < SIZE; ++column)
		{
			printf("%0.3lf", m_data[row][column]);
			if (column != SIZE - 1)
			{
				printf("\t");
			}
		}
		printf("\n");
	}
}

void CMatrixSquare3::DivideMatrixValues(value_t divisor)
{
	assert(divisor != 0);

	for (index_t row = 0; row < SIZE; ++row)
	{
		for (index_t column = 0; column < SIZE; ++column)
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

bool CMatrixSquare3::ReadFromFile(const char fileName[])
{
	FILE *f;

	if (fopen_s(&f, fileName, "r") == 0)
	{
		for (index_t row = 0; row < SIZE; ++row)
		{
			for (index_t column = 0; column < SIZE; ++column)
			{
				int readFieldCnt = fscanf_s(f, "%lf", &(m_data[row][column]));
				assert(readFieldCnt == 1);
			}
		}

		fclose(f);
		return true;
	}
	else
	{
		return false;
	}
}
