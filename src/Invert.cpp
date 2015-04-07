// Invert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MatrixSquare3.h"

#define MATRIX_SIZE 3

bool ReadMatrix(const char fileName[], CMatrixSquare3 &outMatrix)
{
	FILE *f;

	if (fopen_s(&f, fileName, "r") == 0)
	{
		for (size_t row = 0; row < MATRIX_SIZE; ++row)
		{
			for (size_t column = 0; column < MATRIX_SIZE; ++column)
			{
				CMatrixSquare3::Value tmpValue;
				int readFieldCnt = fscanf_s(f, "%lf", &tmpValue);
				assert(readFieldCnt == 1);
				outMatrix.SetValue(row, column, tmpValue);
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

void PrintMatrix(CMatrixSquare3 const& matrix)
{
	for (size_t row = 0; row < MATRIX_SIZE; ++row)
	{
		for (size_t column = 0; column < MATRIX_SIZE; ++column)
		{
			printf("%0.3lf", matrix.GetValue(row, column));
			if (column != MATRIX_SIZE - 1)
			{
				printf("\t");
			}
		}
		printf("\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc == 2)
	{
		CMatrixSquare3 srcMatrix;

		if (ReadMatrix(argv[1], srcMatrix))
		{
			if (!srcMatrix.IsSingular())
			{
				PrintMatrix(srcMatrix.GetInvertedMatrix());
			}
			else
			{
				puts("Singular matrix can't be inverted");
			}

			return 0;
		}
		else
		{
			puts("Input data reading error");
			return 1;
		}
	}
	else
	{
		assert(argc > 0);
		printf("Usage: %s <matrix file>\n", argv[0]);
		return 2;
	}
}
