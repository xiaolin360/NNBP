#pragma once
#ifndef _HANDLEFILE_H
#define _HANDLEFILE_H

#include "NeuralNetBP.h"


//���ֵ����
int WriteToFile_Error(bp_nn *bp, char fileName[]);
//����������
int WriteToFile_Accuracy(char fileName[], double Accuracy[], int length);
//��ȡ�ļ�
int ReadFile(bp_nn *bp, char fileName[]);

#endif






