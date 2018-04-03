/*
Referrence:
BP�˹�����������㷨C����ʵ�֡�ת��
http://blog.163.com/mthupc_0725/blog/static/28935506200942811235114/
*/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#define OUT_COUT	2     //�������ά��
#define IN_COUT		3      //��������ά��
#define COUT		6     //��������

typedef struct {       //bp�˹�������ṹ
	int h;             //ʵ��ʹ������ڵ���
	double v[IN_COUT][50];   //���ز�Ȩ����i,����ڵ��������Ϊ50
	double w[50][OUT_COUT];   //�����Ȩ����
	double a;          //ѧϰ��
	double b;          //���ȿ��Ʋ���
	int LoopCout;      //���ѭ������
} bp_nn;

double fnet(double net) { //Sigmoid����,�����缤���
	return 1.0 / (1 + exp(-net));
}


int InitBp(bp_nn *bp) { //��ʼ��bp����

	//����������ڵ����������Ϊ50
	(*bp).h = 2;
	//������ѧϰ��
	(*bp).a = 0.1;    //(*bp).aΪdouble�����ݣ����Ա�����lf
	//�����뾫�ȿ��Ʋ���
	(*bp).b = 0.001;
	//���������ѭ������
	(*bp).LoopCout = 1000;

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



int TrainBp(bp_nn *bp, float x[COUT][IN_COUT], int y[COUT][OUT_COUT]) {
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
		for (i = 0; i < COUT; i++) {
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
			for (j = 0; j < IN_COUT; j++)
				for (k = 0; k < h; k++)
					v[j][k] = v[j][k] + a * x[i][j] * ChgH[k];
		}
		if (n % 10 == 0)
			printf("��� : %f\n", e);
	}
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
	printf("bp����ѵ��������\n");

	return 1;
}


int UseBp(bp_nn *bp, float Input[IN_COUT], float Output[OUT_COUT]) {    //ʹ��bp����
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
	printf("���Ϊ��   ");
	for (i = 0; i < OUT_COUT; i++)
	{
		printf("%.3f ", O2[i]);
		Output[i] = O2[i];
	}
		
	printf("\n");


	return 1;
}


int main_BP3()
{
	float x[COUT][IN_COUT] = { 
	{ 0.8,0.5,0 },
	{ 0.9,0.7,0.3 },
	{ 1,0.8,0.5 },
	{ 0,0.2,0.3 },
	{ 0.2,0.1,1.3 },
	{ 0.2,0.7,0.8 } }; //ѵ������
	int y[COUT][OUT_COUT] = { 
	{ 0,1 },
	{ 0,1 },
	{ 0,1 },
	{ 1,0 },
	{ 1,0 },
	{ 1,0 } };          //�������
	bp_nn bp;

	float Input[IN_COUT] = { 0.2,0.4,0.5 };
	float Output[OUT_COUT];

	InitBp(&bp);                    //��ʼ��bp����ṹ
	TrainBp(&bp, x, y);             //ѵ��bp������

	UseBp(&bp, Input, Output);                     //����bp������

	while (1);

	return 1;
}

