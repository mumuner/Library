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
extern char bo[6][256];//图书信息的输入缓冲区 
extern int choice;
/*后续增加读者信息,查找信息等输入缓冲区*/

typedef struct book{//图书信息 
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

typedef struct reader{//读者信息 
	int identity;//身份,1为教师,2为学生 
	char name[_SIZE];//姓名 
	char no[_SIZE];//证件号 
	char school[_SIZE];//学院 
	int level;//诚信情况,0为最高,3为最低
	int num;//当前借阅数量 
	book* borrow;//该名读者借阅图书的信息 
	book* borrownext;//读者所借的下一本书的信息 
	reader* next;
	reader* renext;  //预约队列中的链
}reader, *readerList;

typedef struct appointment{//预约信息 
	char ISBN[_SIZE];//ISBN
	readerList info;//预约该书的读者信息 
	appointment *renext;
}appointment, *appointmentList;

//extern "C" _declspec (dllexport) void bookEntryDlg(char* noOfbook,char buffer[][256]);
//extern "C" _declspec (dllexport) void bookDlgn(bookList sptr, int * bookno, int * count, char t[]);
//extern "C" _declspec (dllexport) void bookEditDlg(char info[][256], char buffer[][256]);
//extern "C" _declspec (dllexport) void bookSearchDlg(bookList sptr);
//extern "C" _declspec (dllexport) void ReaderDlg(readerList &sptr, char t[]);
/*后续增加其他图形界面*/

extern void outputToScreen();
extern void initScreen();
#endif
