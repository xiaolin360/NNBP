
/*
Referrence:
BP�˹�����������㷨C����ʵ�֡�ת��
http://blog.163.com/mthupc_0725/blog/static/28935506200942811235114/
*/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include "NeuralNetBP.h"


//�����缤���
double fnet(double net) { 

	double temp=0;

	//Sigmoid����
	temp= 1.0 / (1 + exp(-net)); 

	return temp;

}

int InitBp(bp_nn *bp) { //��ʼ��bp����

	//����������ڵ����������Ϊ50
	(*bp).h = NN_ImplyCout;
	//������ѧϰ��
	(*bp).a = NN_Rate;    //(*bp).aΪdouble�����ݣ����Ա�����lf
	//�����뾫�ȿ��Ʋ���
	(*bp).b = NN_Error;
	//���������ѭ������
	(*bp).LoopCout = NN_LOOP;

	//�����������ʼ��Ȩֵ����
	int i, j;
	srand((unsigned)time(NULL));
	for (i = 0; i < IN_COUT; i++)
		for (j = 0; j < (*bp).h; j++)
			(*bp).v[i][j] = rand() / (double)(RAND_MAX);
	for (i = 0; i < (*bp).h; i++)
		for (j = 0; j < OUT_COUT; j++)
			(*bp).w[i][j] = rand() / (double)(RAND_MAX);

	return 1;
}

int TrainBp(bp_nn *bp, int x[SampleTrain][IN_COUT], int y[SampleTrain][OUT_COUT]) 
{
	//ѵ��bp���磬����Ϊx���������Ϊy
	double f = (*bp).b;                      //���ȿ��Ʋ���
	double a = (*bp).a;                      //ѧϰ��
	int h = (*bp).h;                         //����ڵ���
	double v[IN_COUT][50], w[50][OUT_COUT];  //Ȩ����
	double ChgH[50], ChgO[OUT_COUT];         //�޸�������
	double O1[50], O2[OUT_COUT];             //���������������
	int LoopCout = (*bp).LoopCout;           //���ѭ������
	int i, j, k, n;
	double temp;


	for (i = 0; i < IN_COUT; i++)            // ���ƽṹ���е�Ȩ���� 
		for (j = 0; j < h; j++)
			v[i][j] = (*bp).v[i][j];
	for (i = 0; i < h; i++)
		for (j = 0; j < OUT_COUT; j++)
			w[i][j] = (*bp).w[i][j];

	double e = f + 1;
	for (n = 0; e > f && n < LoopCout; n++)
	{ //��ÿ������ѵ������
		e = 0;
		for (i = 0; i < SampleTrain; i++)
		{
			for (k = 0; k < h; k++) {          //���������������
				temp = 0;
				for (j = 0; j < IN_COUT; j++)
					temp = temp + x[i][j] * v[j][k];
				O1[k] = fnet(temp);
			}
			for (k = 0; k < OUT_COUT; k++) { //����������������
				temp = 0;
				for (j = 0; j < h; j++)
					temp = temp + O1[j] * w[j][k];
				O2[k] = fnet(temp);
			}
			for (j = 0; j < OUT_COUT; j++)    //����������Ȩ�޸���    
				ChgO[j] = O2[j] * (1 - O2[j]) * (y[i][j] - O2[j]);
			for (j = 0; j < OUT_COUT; j++)   //����������
				e = e + (y[i][j] - O2[j]) * (y[i][j] - O2[j]);
			for (j = 0; j < h; j++) {         //��������Ȩ�޸���
				temp = 0;
				for (k = 0; k < OUT_COUT; k++)
					temp = temp + w[j][k] * ChgO[k];
				ChgH[j] = temp * O1[j] * (1 - O1[j]);
			}
			for (j = 0; j < h; j++)           //�޸������Ȩ����
				for (k = 0; k < OUT_COUT; k++)
					w[j][k] = w[j][k] + a * O1[j] * ChgO[k];
			for (j = 0; j < IN_COUT; j++)     //�޸�������Ȩ����
				for (k = 0; k < h; k++)
					v[j][k] = v[j][k] + a * x[i][j] * ChgH[k];
		}
		(*bp).Error[n] = e;		//��¼���

		if (n % 10 == 0)
		{
			printf("ѭ��������%d, ��� : %f\n",n,e);
		}
	}
	(*bp).LoopItera = n;		//ʵ��ѭ������

	printf("�ܹ�ѭ��������%d\n", n);
	printf("�����������Ȩ����\n");
	for (i = 0; i < IN_COUT; i++) {
		for (j = 0; j < h; j++)
			printf("%f    ", v[i][j]);
		printf("\n");
	}
	printf("������������Ȩ����\n");
	for (i = 0; i < h; i++) {
		for (j = 0; j < OUT_COUT; j++)
			printf("%f    ", w[i][j]);
		printf("\n");
	}
	for (i = 0; i < IN_COUT; i++)             //�ѽ�����ƻؽṹ�� 
		for (j = 0; j < h; j++)
			(*bp).v[i][j] = v[i][j];
	for (i = 0; i < h; i++)
		for (j = 0; j < OUT_COUT; j++)
			(*bp).w[i][j] = w[i][j];
	printf("bp����ѵ��������\n\n");

	return 1;
}


int UseBp(bp_nn *bp, int Input[IN_COUT], double Output[OUT_COUT]) {    //ʹ��bp����
	double O1[50];
	double O2[OUT_COUT]; //O1Ϊ�������,O2Ϊ��������
	int i, j;

	double temp;
	for (i = 0; i < (*bp).h; i++) {
		temp = 0;
		for (j = 0; j < IN_COUT; j++)
			temp += Input[j] * (*bp).v[j][i];
		O1[i] = fnet(temp);
	}
	for (i = 0; i < OUT_COUT; i++) {
		temp = 0;
		for (j = 0; j < (*bp).h; j++)
			temp += O1[j] * (*bp).w[j][i];
		O2[i] = fnet(temp);
	}
	//���ֵ
	for (i = 0; i < OUT_COUT; i++)
	{
		Output[i] = O2[i];
	}
	return 1;
}



double TestBp(bp_nn *bp, int x[SampleTest][IN_COUT], int y[SampleTest][OUT_COUT])
{    //ʹ��bp����

	int i, j;
	int Input[IN_COUT];
	double Output[OUT_COUT];	//�˴��������ʵ�ʼ������ ����Ϊdouble��
	int yMeasure[SampleTest];
	int CorrectN = 0;
	double Accuracy = 0;	//��ȷ��

	for (i = 0; i < SampleTest; i++)
	{
		for (j = 0; j < IN_COUT; j++)
		{
			Input[j] = x[i][j];
		}

		////��ʾ����ֵ
		//printf("����ֵΪ: ");
		//for (int k = 0; k < IN_COUT; k++)
		//{
		//	printf("%d ", Input[k]);
		//}
		//printf("\n");

		UseBp(bp, Input, Output);      //����bp�������Ӻ���

		////��ʾ���ֵ
		//printf("���ֵΪ: ");
		//for (int k = 0; k < OUT_COUT; k++)
		//{
		//	printf("%.3f ", Output[k]);
		//}
		//printf("\n");

		////��ʾ��ֵ
		//printf("��ֵΪ: ");
		//for (int k = 0; k < OUT_COUT; k++)
		//{
		//	printf("%d ", y[i][OUT_COUT - 1]);
		//}
		//printf("\n\n");

		//�������
		if (Output[OUT_COUT - 1] >= 0.5)
		{
			yMeasure[i] = 1;
		}
		else
		{
			yMeasure[i] = 0;
		}


		if (y[i][OUT_COUT - 1] == yMeasure[i])	//��ֵ=����ֵ
		{
			CorrectN++;
		}
	}

	Accuracy=CorrectN * 1.0 / SampleTest;	//������ȷ��
	//��ʾ���Խ��
	printf("n=7 ʱ��BPNN ���Խ��Ϊ��\n");
	printf("  ������������%d\n", SampleTest);
	printf("  ��ȷ��������%d\n", CorrectN);
	printf("  ��ȷ��Ϊ  ��%f\n", Accuracy);
	printf("\n\n");


	return Accuracy;

}


