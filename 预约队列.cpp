//ԤԼ���е�������������⡣һ�ǵ�һ����ֻ��һ��ԤԼʱ����Ϣ�޷������
//���ǵ�ԤԼ������Ϣ�����δ�ͷŽ�㣬������ǰһ������nextδ�ó�NULL��
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "library.h"
void yuyueoutput(appointmentList head){  //ÿ������󣬶�Ҫ�ٽ��ж��� 
	FILE *fp;
	readerList ren , pre;
	appointmentList p;
	p = head->renext;
	if((fp = fopen("����.txt", "w")) != NULL){
		while(p){
			fprintf(fp,"%s\n",p->ISBN);
			if(p->info->renext){
				while(1){
					ren = p->info->renext;
					if(ren->renext == NULL) {
						fprintf(fp,"%d %s %s %s %d %d \n", ren->identity, ren->name, ren->no, ren->school, ren->level, ren->num);
						free(ren);
						p->info->renext = NULL;
						break;
					}
					else {
						while(ren->renext){
							pre = ren;
							ren = ren->renext;
						}  
					}
					fprintf(fp,"%d %s %s %s %d %d \n", ren->identity, ren->name, ren->no, ren->school, ren->level, ren->num);
					free(ren);
					pre->renext = NULL;
				}
			}
			p = p->renext;
		}
	}
	fclose(fp); 
} 

appointmentList queue(){
	FILE *fp;
	appointmentList p,head;
	char judge[30];
	head = (appointmentList)malloc(sizeof(appointment));
	if((fp = fopen("ԤԼ.txt","r")) != NULL){
		p = (appointmentList)malloc(sizeof(appointment));
		head->renext = p;
		p->renext = NULL;
		p->info = (readerList)malloc(sizeof(reader)); //�൱��ͷָ�� 
		p->info->renext = NULL;
		//p->info->next = NULL;
		fscanf(fp,"%s",p->ISBN) ;
		while(1){
			if(fscanf(fp,"%s",judge)>0){
				if(atoi(judge)==1||atoi(judge)==2){
					readerList child;
					child = (readerList)malloc(sizeof(reader));
					if(p->info->renext == NULL){
						child->renext = NULL;
						child->next = NULL;
						p->info->renext = child;
					}
					else {
						child->renext = p->info->renext;
						child->next = NULL;
						p->info->renext = child;
					}
					child->identity = atoi(judge);
					fscanf(fp,"%s",child->name);
					fscanf(fp,"%s",child->no);	
					fscanf(fp,"%s",child->school);
					fscanf(fp,"%d",&child->level);
					fscanf(fp,"%d",&child->num);
				}
				else {
					p = (appointmentList)malloc(sizeof(appointment));
					p->renext = head->renext;
					p->info = (readerList)malloc(sizeof(reader)); 
					p->info->renext = NULL;
					p->info->next = NULL;
					head->renext = p;
					strcpy(p->ISBN,judge);
				}
			}
			else break;
		}
	}
	fclose(fp);
	return head;
}
