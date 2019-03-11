//三个链表（书 读者 预约）输出到文件和从文件读的代码加上预约模块的代码写了就行了。
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "library.h"
void yuyueoutput(appointmentList head) {  //每次输出后，都要再进行读入 
	FILE *fp;
	readerList ren;
	appointmentList p;
	p = head->renext;
	if ((fp = fopen("测试.txt", "w+")) != NULL) {
		while (p) {
			//fprintf(fp, "%s\n", p->ISBN);
			if (p->info->next) {
				while (1) {
					ren = p->info->next;
					if (ren == NULL) break;
					while (ren->next) {
						ren = ren->next;
					}
					fprintf(fp, "%d %s %s %s %d %d \n", ren->identity, ren->name, ren->no, ren->school, ren->level, ren->num);
					ren = NULL;
				}
			}
			p = p->renext;
		}
	}
	fclose(fp);
}
int main() {
	FILE *fp;
	appointmentList p, head;
	char judge[30];
	head = (appointmentList)malloc(sizeof(appointment));
	if ((fp = fopen("预约.txt", "r")) != NULL) {
		p = (appointmentList)malloc(sizeof(appointment));
		head->renext = p;
		p->renext = NULL;
		p->info = (readerList)malloc(sizeof(reader)); //相当于头指针 
		p->info->next = NULL;
		while (1) {
			if (fscanf(fp, "%s", judge)>0) {
				if (atoi(judge) == 1 || atoi(judge) == 2) {
					readerList child;
					child = (readerList)malloc(sizeof(reader));
					if (p->info->next == NULL) {
						child->next = NULL;
						child->next = p->info->next;
						p->info->next = child;
					}
					else {
						child->next = p->info->next;
						p->info->next = child;
					}
					child->identity = atoi(judge);
					fscanf(fp, "%s", child->name);
					fscanf(fp, "%s", child->no);
					fscanf(fp, "%s", child->school);
					fscanf(fp, "%d", &child->level);
					fscanf(fp, "%d", &child->num);
				}
				else {
					strcpy(p->ISBN, judge);
					p = (appointmentList)malloc(sizeof(appointment));
					p->renext = head->renext;
					p->info = (readerList)malloc(sizeof(reader));
					p->info->next = NULL;
					head->renext = p;
				}
			}
			else break;
		}
		head->renext = p->renext;
	}
	yuyueoutput(head);
	fclose(fp);
	return 0;
}