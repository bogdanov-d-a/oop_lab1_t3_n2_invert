#include "stdafx.h"
#include "Matrix.h"

CMatrix::CMatrix(index_t size)
{
	assert(size > 0);
	assert(size <= MAX_SIZE);
	m_size = size;

	for (index_t row = 0; row < m_size; ++row)
	{
		for (index_t column = 0; column < m_size; ++column)
		{
			m_data[row][column] = 0;
		}
	}
}

void CMatrix::SetValue(index_t row, index_t column, value_t value)
{
	assert(CheckCoords(row, column));
	m_data[row][column] = value;
}

CMatrix::value_t CMatrix::GetValue(index_t row, index_t column) const
{
	assert(CheckCoords(row, column));
	return m_data[row][column];
}

bool CMatrix::CheckCoords(index_t row, index_t column) const
{
	return (row < m_size && column < m_size);
}

CMatrix::value_t CMatrix::GetDeterminant() const
{
	switch (m_size)
	{
	case 2:
		return (m_data[0][0] * m_data[1][1] - m_data[0][1] * m_data[1][0]);
	case 3:
		return (m_data[0][0] * GetMinor(0, 0) - m_data[0][1] * GetMinor(0, 1) + m_data[0][2] * GetMinor(0, 2));
	default:
		assert(false);
		return 0;
	}
}

void CMatrix::GetAdjugate(CMatrix ** outMatrixPtr) const
{
	*outMatrixPtr = new CMatrix(m_size);

	for (index_t row = 0; row < m_size; ++row)
	{
		for (index_t column = 0; column < m_size; ++column)
		{
			(*outMatrixPtr)->SetValue(row, column, GetCofactor(column, row));
		}
	}
}

int CMatrix::GetCofactorSign(index_t row, index_t column)
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

void CMatrix::GetCutMatrix(index_t cutRow, index_t cutColumn, CMatrix ** outMatrixPtr) const
{
	assert(CheckCoords(cutRow, cutColumn));
	assert(m_size > 1);
	
	*outMatrixPtr = new CMatrix(m_size - 1);

	for (index_t targetRow = 0; targetRow < m_size - 1; ++targetRow)
	{
		index_t sourceRow = targetRow;
		if (targetRow >= cutRow)
		{
			++sourceRow;
		}

		for (index_t targetColumn = 0; targetColumn < m_size - 1; ++targetColumn)
		{
			index_t sourceColumn = targetColumn;
			if (targetColumn >= cutColumn)
			{
				++sourceColumn;
			}

			(*outMatrixPtr)->SetValue(targetRow, targetColumn, m_data[sourceRow][sourceColumn]);
		}
	}
}

CMatrix::value_t CMatrix::GetMinor(index_t row, index_t column) const
{
	CMatrix *tmpMatrix;
	GetCutMatrix(row, column, &tmpMatrix);
	value_t result = tmpMatrix->GetDeterminant();
	delete tmpMatrix;
	return result;
}

CMatrix::value_t CMatrix::GetCofactor(index_t row, index_t column) const
{
	return (GetCofactorSign(row, column) * GetMinor(row, column));
}

void CMatrix::Print() const
{
	for (CMatrix::index_t column = 0; column < m_size; ++column)
	{
		for (CMatrix::index_t row = 0; row < m_size; ++row)
		{
			printf("%lf", m_data[row][column]);
			if (row != m_size - 1)
			{
				printf("\t");
			}
		}
		printf("\n");
	}
}

void CMatrix::GetTransposedMatrix(CMatrix ** outMatrixPtr) const
{
	*outMatrixPtr = new CMatrix(m_size);

	for (index_t row = 0; row < m_size; ++row)
	{
		for (index_t column = 0; column < m_size; ++column)
		{
			(*outMatrixPtr)->SetValue(row, column, m_data[column][row]);
		}
	}
}

void CMatrix::DivideMatrixValues(value_t divisor)
{
	assert(divisor != 0);

	for (index_t row = 0; row < m_size; ++row)
	{
		for (index_t column = 0; column < m_size; ++column)
		{
			m_data[row][column] /= divisor;
		}
	}
}

void CMatrix::GetInvertedMatrix(CMatrix ** outMatrixPtr) const
{
	assert(!IsSingular());

	CMatrix *transposedMatrix;
	GetTransposedMatrix(&transposedMatrix);

	CMatrix *adjugateMatrix;
	transposedMatrix->GetAdjugate(&adjugateMatrix);

	delete transposedMatrix;
	adjugateMatrix->DivideMatrixValues(GetDeterminant());
	*outMatrixPtr = adjugateMatrix;
}

bool CMatrix::IsSingular() const
{
	return (GetDeterminant() == 0);
}
