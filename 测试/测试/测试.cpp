// ����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
//���������� ���� ԤԼ��������ļ��ʹ��ļ����Ĵ������ԤԼģ��Ĵ���д�˾����ˡ�
/*typedef struct book{//ͼ����Ϣ
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
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "library.h"
int main() {
	FILE *fp;
	bookList head, p;
	head = (bookList)malloc(sizeof(book));
	if ((fp = fopen("ͼ��.txt", "r")) != NULL) {
		p = (bookList)malloc(sizeof(book));
		head->next = p;
		p->next = NULL;
		while (fscanf(fp, "%s %s %s %s %s %s %s %s %d %d", &p->no, &p->ISBN, &p->name, &p->author, &p->press, &p->info, &p->bTime, &p->borrowTimes, &p->flag, &p->remainTime)) {
			p = (bookList)malloc(sizeof(book));
			p->next = head->next;
			head->next = p;
		}
		head->next = p->next;
	}
	p = head->next;
	while (p) {
		printf("%s %s %s %s %s %s %s %s %d %d\n", p->no, p->ISBN, p->name, p->author, p->press, p->info, p->bTime, p->borrowTimes, p->flag, p->remainTime);
		p = p->next;
	}
	return 0;
}
