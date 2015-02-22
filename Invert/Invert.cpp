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

		for (CMatrix::index_t column = 0; column < INPUT_MATRIX_SIZE; ++column)
		{
			for (CMatrix::index_t row = 0; row < INPUT_MATRIX_SIZE; ++row)
			{
				CMatrix::value_t tmpValue;
				int readFiledCnt = fscanf_s(f, "%lf", &tmpValue);
				assert(readFiledCnt == 1);
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
	CMatrix *srcMatrix;

	if (ReadMatrix("input.txt", &srcMatrix))
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
