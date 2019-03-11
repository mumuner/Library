#ifndef __library_h__
#define __library_h__

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include <ctime>

#define _SIZE 30
#define _CRT_SECURE_NO_WARNINGS
extern char bo[6][256];//ͼ����Ϣ�����뻺���� 
extern int choice;
/*�������Ӷ�����Ϣ,������Ϣ�����뻺����*/

typedef struct book{//ͼ����Ϣ 
	char no[_SIZE];//ͼ���� 
	char ISBN[_SIZE];//ISBN
	char name[_SIZE];//���� 
	char author[_SIZE];//���� 
	char press[_SIZE];//������ 
	char info[_SIZE];//��� 
	char bTime[_SIZE];//����ʱ��
	int borrowTimes;//�������
	int flag;//�Ƿ���,0Ϊδ���,����Ϊ�����߱�� 
	int remainTime;//ʣ��ʱ��ʣ�ࣨ�����ֵ��   ��ʼΪ20�죿������
	book* next;
}book, *bookList;

typedef struct reader{//������Ϣ 
	int identity;//���,1Ϊ��ʦ,2Ϊѧ�� 
	char name[_SIZE];//���� 
	char no[_SIZE];//֤���� 
	char school[_SIZE];//ѧԺ 
	int level;//�������,0Ϊ���,3Ϊ���
	int num;//��ǰ�������� 
	book* borrow;//�������߽���ͼ�����Ϣ 
	book* borrownext;//�����������һ�������Ϣ 
	reader* next;
	reader* renext;  //ԤԼ�����е���
}reader, *readerList;

typedef struct appointment{//ԤԼ��Ϣ 
	char ISBN[_SIZE];//ISBN
	readerList info;//ԤԼ����Ķ�����Ϣ 
	appointment *renext;
}appointment, *appointmentList;

//extern "C" _declspec (dllexport) void bookEntryDlg(char* noOfbook,char buffer[][256]);
//extern "C" _declspec (dllexport) void bookDlgn(bookList sptr, int * bookno, int * count, char t[]);
//extern "C" _declspec (dllexport) void bookEditDlg(char info[][256], char buffer[][256]);
//extern "C" _declspec (dllexport) void bookSearchDlg(bookList sptr);
//extern "C" _declspec (dllexport) void ReaderDlg(readerList &sptr, char t[]);
/*������������ͼ�ν���*/

extern void outputToScreen();
extern void initScreen();
#endif
