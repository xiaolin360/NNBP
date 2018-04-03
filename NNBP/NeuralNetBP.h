#pragma once
#ifndef _NEURALNETBP_H
#define _NEURALNETBP_H

////XOR2
//#define IN_COUT			2     //��������ά��
//#define OUT_COUT		1     //�������ά��
//#define IMPLY_NUM		1     //���������
//
//#define SampleTrain		4		//ѵ���������� ��0-127��128������ȫ���μ�ѵ��
//#define SampleTest		4		//������������ ��0-127��128������ȫ���μӲ���
//
//#define NN_ImplyCout	4		//������ڵ���
//#define NN_Rate			0.5		//ѧϰ����
//#define NN_Error		0.001   //���ȿ��Ʋ���
//#define NN_LOOP			100000   //���ѭ������

/* �����ñ���
	����ά���ı�ʱ���ı�IN_COUT��ֵ����
	ͬʱ��Ҫ�޸�SampleTrain��SampleTest��NN_ImplyCout��ֵ��
	������ȡ��
	SampleTrain = 2^IN_COUT
	SampleTest  = 2^IN_COUT
	NN_ImplyCout  = ��2-4�� * IN_COUT
*/

//XOR7
#define IN_COUT			7     //��������ά��
#define OUT_COUT		1     //�������ά��
#define IMPLY_NUM		1     //���������

#define SampleTrain		128		//ѵ���������� ��0-127��128������ȫ���μ�ѵ��
#define SampleTest		128		//������������ ��0-127��128������ȫ���μӲ���

#define NN_ImplyCout	25		//������ڵ���
#define NN_Rate			0.4		//ѧϰ����
#define NN_Error		0.001   //���ȿ��Ʋ���
#define NN_LOOP			100000   //���ѭ������


typedef struct {       //bp�˹�������ṹ
	int h;             //ʵ��ʹ������ڵ���
	double v[IN_COUT][50];   //���ز�Ȩ����i,����ڵ��������Ϊ50
	double w[50][OUT_COUT];   //�����Ȩ����
	double a;          //ѧϰ��
	double b;          //���ȿ��Ʋ���
	int LoopCout;      //���ѭ������
	int LoopItera;     //ʵ��ѭ������
	double Error[NN_LOOP];	//���
} bp_nn;


int InitBp(bp_nn *bp); //��ʼ��bp����
int TrainBp(bp_nn *bp, int x[SampleTrain][IN_COUT], int y[SampleTrain][OUT_COUT]); //ѵ��bp���磬����Ϊx���������Ϊy
int UseBp(bp_nn *bp, int Input[IN_COUT], double Output[OUT_COUT]);		 //ʹ��bp����
double TestBp(bp_nn *bp, int x[SampleTest][IN_COUT], int y[SampleTest][OUT_COUT]);//����bp����

#endif
