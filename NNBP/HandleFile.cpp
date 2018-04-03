
#include <stdio.h>
#include "HandleFile.h"


//���ֵ����
int WriteToFile_Error(bp_nn *bp,char fileName[])
{
	FILE *fp;
	int i;
	//fp = fopen("dataParity7.txt", "w");//���ļ��Ա�д������ 
	fp = fopen(fileName, "w");//���ļ��Ա�д������ 
	for (i = 0; i < (*bp).LoopItera; i++)
	{
		//�����д��fpָ����ļ�  
		fprintf(fp, "%f\n", (*bp).Error[i]);
	}
	fclose(fp);               //д����ϣ��ر��ļ� 

	return 1;
}

//����������
int WriteToFile_Accuracy(char fileName[], double Accuracy[],int length)
{
	FILE *fp;
	int i;
	//fp = fopen("dataParity7.txt", "w");//���ļ��Ա�д������ 
	fp = fopen(fileName, "w");//���ļ��Ա�д������ 
	int temp=sizeof(Accuracy) / sizeof(Accuracy[0]);
	for (i = 0; i < length; i++)
	{
		//�����д��fpָ����ļ�  
		fprintf(fp, "%f\n", Accuracy[i]);
	}
	fclose(fp);               //д����ϣ��ر��ļ� 

	return 1;
}


//��ȡ�ļ�
int ReadFile(bp_nn *bp, char fileName[])
{
	FILE *fp;
	int i;

	int b[2] = { 0 };

	fp = fopen(fileName, "r");//���ļ��Ա���ж�ȡ���� 
	for (i = 0; i < 2; i++)
	{
		//��fpָ����ļ��ж�ȡ10��������b����  
		fscanf(fp, "%d", &b[i]);
	}
	fclose(fp);        //��ȡ��ϣ��ر��ļ� 

	for (i = 0; i < 2; i++)
	{
		//�����fp�ļ���ȡ��10��������  
		printf("%d\n", b[i]);
	}

	int c = b[0] &( 1<<5 );
	int d = (b[0] >> (4 - 1)) & 1;
	int e = (b[0] >> (4 - 1)) ;
	int f = (11111 >> (4 - 1));

	printf("%d\n", c);
	printf("%d\n", d);

	return 1;
}




