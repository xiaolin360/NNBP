#include <stdio.h>
#include "Sample.h"



//ѵ��������ʼ�� 
int SampleTrain_Init(int Sx[SampleTrain][IN_COUT], int Sy[SampleTrain][OUT_COUT])
{
	int i,j;
	int sum = 0;

	for (i = 0; i < SampleTrain; i++)
	{
		sum = 0;
		for (j = 0; j < IN_COUT; j++)
		{
			Sx[i][IN_COUT-j-1]= (i >> j) & 1;	//����ȡ����λ
			sum += Sx[i][IN_COUT - j - 1];
		}
		Sy[i][0] = sum % 2;	//ȡ����
	}
	return 1;
}


//����������ʼ�� 
int SampleTest_Init(int Sx[SampleTest][IN_COUT], int Sy[SampleTest][OUT_COUT])
{
	int i, j;
	int sum = 0;

	for (i = 0; i < SampleTest; i++)
	{
		sum = 0;
		for (j = 0; j < IN_COUT; j++)
		{
			Sx[i][IN_COUT - j - 1] = (i >> j) & 1;	//����ȡ����λ
			sum += Sx[i][IN_COUT - j - 1];
		}
		Sy[i][0] = sum % 2;	//ȡ����
	}
	return 1;
}




