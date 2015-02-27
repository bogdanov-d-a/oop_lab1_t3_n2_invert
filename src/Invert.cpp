// Invert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MatrixSquare3.h"

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc == 2)
	{
		CMatrixSquare3 srcMatrix;

		if (srcMatrix.ReadFromFile(argv[1]))
		{
			if (!srcMatrix.IsSingular())
			{
				srcMatrix.GetInvertedMatrix().Print();
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
