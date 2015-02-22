// Invert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix.h"

const CMatrix::index_t INPUT_MATRIX_SIZE = 3;

bool ReadMatrix(const char fileName[], CMatrix ** outMatrixPtr)
{
	FILE *f;

	if (fopen_s(&f, fileName, "r") == 0)
	{
		*outMatrixPtr = new CMatrix(INPUT_MATRIX_SIZE);

		for (CMatrix::index_t row = 0; row < INPUT_MATRIX_SIZE; ++row)
		{
			for (CMatrix::index_t column = 0; column < INPUT_MATRIX_SIZE; ++column)
			{
				CMatrix::value_t tmpValue;
				int readFieldCnt = fscanf_s(f, "%lf", &tmpValue);
				assert(readFieldCnt == 1);
				(*outMatrixPtr)->SetValue(row, column, tmpValue);
			}
		}

		fclose(f);
		return true;
	}
	else
	{
		puts("Input file open error");
		return false;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc == 2)
	{
		CMatrix *srcMatrix;

		if (ReadMatrix(argv[1], &srcMatrix))
		{
			if (!srcMatrix->IsSingular())
			{
				CMatrix *invertedMatrix;
				srcMatrix->GetInvertedMatrix(&invertedMatrix);
				invertedMatrix->Print();
				delete invertedMatrix;
			}
			else
			{
				puts("Singular matrix can't be inverted");
			}

			delete srcMatrix;
			return 0;
		}
		else
		{
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
