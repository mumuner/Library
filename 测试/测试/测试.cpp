// 测试.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//三个链表（书 读者 预约）输出到文件和从文件读的代码加上预约模块的代码写了就行了。
/*typedef struct book{//图书信息
char no[_SIZE];//图书编号
char ISBN[_SIZE];//ISBN
char name[_SIZE];//书名
char author[_SIZE];//作者
char press[_SIZE];//出版社
char info[_SIZE];//简介
char bTime[_SIZE];//购买时间
int borrowTimes;//借出次数
int flag;//是否借出,0为未借出,其他为借书者编号
int remainTime;//剩余时间剩余（申请后赋值）   初始为20天？？？？
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
	if ((fp = fopen("图书.txt", "r")) != NULL) {
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
