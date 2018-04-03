#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>
#include "NeuralNetBP.h"
#include "HandleFile.h"
#include "Sample.h"


/*��ż���ж�
�� n ���������������� 1�������Ϊ 1���� n ����������ż���� 1�������Ϊ 0��
*/
int main()
{

	int TrainX[SampleTrain][IN_COUT];
	int TrainY[SampleTrain][OUT_COUT];
	int TestX[SampleTest][IN_COUT];
	int TestY[SampleTest][OUT_COUT];
	bp_nn bp;

	const int TrainTimes = 1;	//ѵ������
	double Accuracy[TrainTimes];//��ȷ��

	SampleTrain_Init(TrainX, TrainY);
	SampleTest_Init(TestX, TestY);

	//����ѵ��
	//InitBp(&bp);                    //��ʼ��bp����ṹ
	//TrainBp(&bp, TrainX, TrainY);   //ѵ��bp������
	//TestBp(&bp, TestX, TestY);       //����bp������

	//���ѵ��ȡƽ��ֵ
	for (int i = 0; i < TrainTimes;i++)
	{
		InitBp(&bp);                    //��ʼ��bp����ṹ
		TrainBp(&bp, TrainX, TrainY);   //ѵ��bp������
		Accuracy[i]=TestBp(&bp, TestX, TestY);       //����bp������
	}


	//��������
	WriteToFile_Error(&bp, "Data\\XOR7_Error.txt");	//�������һ�ε����
	WriteToFile_Accuracy("Data\\XOR7_Result.txt", Accuracy, TrainTimes);//�������е����н��

	system("pause");

	return 1;
}

