//���������� ���� ԤԼ��������ļ��ʹ��ļ����Ĵ������ԤԼģ��Ĵ���д�˾����ˡ�
//����ģ��
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "library.h"
bookList bookinput();
readerList readerinput();
appointmentList queue(); 
void isbn(appointmentList head,readerList q);
void yuyueoutput(appointmentList head);
//���飺�������ж������Ա���Ѿ����˶����飬����Ѿ��������������ٽ��飬��������������Խ��飬Ȼ������ͼ���ţ����flag=0����ɹ����ߣ��������flag=1��
//���ҽ��˽ڵ���뵽isbn�������� 
//������isbn�룬���ȱ���isbn����Ȼ���ٽ���ͷ�巨������ڵ㡣

//���飺ͨ������ͼ���ţ�Ȼ���޸�flag��Ȼ���ٱ���isbn��������������Ԫ�ص���Ϣ�����Ա��Ų��ҵ�������ɾ���˽ڵ㣬ͨ����Ա����ٱ����ҵ�����
//�����Ա�ڵ㣬Ȼ�����ͼ������ͨ��isbn�룬�ҵ�flag=0��ͼ�飬�������ͼ��ڵ㣬�����޸�flag = 1��Ȼ������ڵ���ӵ���Ա�ڵ��С� 
//���������isbn������Ӧ����Ϊ���ˣ���ɾ����isbn�ڵ� 
void returnbook(readerList head,appointmentList ishead,bookList bookhead){
	readerList p , zip , zip1;
	appointmentList isp ,preisp ,isp1 ,preisp1 ;
	bookList bokp , bokp1;
	p = head->next;
	char memberno[30];
	scanf("%s",memberno);
	while(p){
		if(!strcmp(memberno,p->no)){
			printf("��Ա���ҳɹ�\n");
			break;
		}
		p = p->next;
	}
	char id[30];
	scanf("%s",id);
	if(!strcmp(p->borrow->no,id)){
		printf("ͼ��borrow���ҳɹ�\n");
		p->num = p->num-1; 
		p->borrow->flag = 0;
		if(p->borrow->remainTime < 0){
			printf("��Ҫ֧������\n");
			printf("֧����%d \n",(p->borrow->remainTime)*(-2)); 
		} 
		preisp = ishead;
		isp = ishead->renext;
		while(isp){
			if(!strcmp(isp->ISBN,p->borrow->ISBN)){
				break;
			}
			preisp = isp;
			isp = isp->renext;
		}
		if(isp->info->renext == NULL){				//��������isbn�ڵ��Ϊ�գ���ɾȥ�˽ڵ㣬���ұ���ͼ���޸�flag �� num 
			preisp->renext = isp->renext;
			free(isp); 
			bokp = bookhead->next;
			while(bokp){
				if(!strcmp(bokp->no,p->borrow->no)){
					bokp->flag = 0;
					bokp->borrowTimes = bokp->borrowTimes+1;
					bokp->remainTime = 20;
					break;
				}
				bokp = bokp->next;
			}
			free(p->borrow);   //ɾ���˽ڵ㣻 
		} 
		else{										//�������ҵ�isbn�����Ľڵ㣬���ҽ���no�ҵ�������no�����ҵ���Ա�������޸�������Ϣ,�����޸�ͼ��flag 
			readerList childhead;
			childhead = isp->info->renext;
			while(childhead->renext){
				childhead = childhead->renext;
			}
			zip = head->next;
			bokp = bookhead->next; 
			while(bokp){
				if(!strcmp(bokp->no,p->borrow->no)){
					bokp->borrowTimes++;
					bokp->remainTime = 20;
					break;
				}
				bokp = bokp->next;
			}
			while(zip){
				if(!strcmp(zip->no,childhead->no)){
					break;
				}
				zip = zip->next;
			}
			if(zip->borrow == NULL){
				zip->borrow = (bookList)malloc(sizeof(book));
				*(zip->borrow)= *(p->borrow) ;
				free(p->borrow) ;
				if(p->borrownext){
					*(p->borrow) = *(p->borrownext);
					free(p->borrownext);
					p->borrownext = NULL; 
				}
				else{
					p->borrow = NULL;
				}
				zip->num = 1 ;
			}
			else if(zip->borrownext == NULL){
				zip->borrownext= (bookList)malloc(sizeof(book));
				*(zip->borrownext) = *(p->borrow);
				free(p->borrow);
				if(p->borrownext){
					*(p->borrow) = *(p->borrownext);
					free(p->borrownext);
					p->borrownext = NULL; 
				}
				else{
					p->borrow = NULL;
				}
				p->borrow = NULL;
				zip->num = 2;
			}
		}
	}
   else if(!strcmp(p->borrownext->no,id)){
		printf("ͼ��borrow2���ҳɹ�\n");
		p->num = p->num-1; 
		p->borrownext->flag = 0;
		if(p->borrownext->remainTime < 0){
			printf("��Ҫ֧������\n");
			printf("֧����%d \n",(p->borrownext->remainTime)*(-2)); 
		} 
		preisp1 = ishead;
		isp1 = ishead->renext;
		while(isp1->renext){
			if(!strcmp(isp1->ISBN,p->borrownext->ISBN)){
				break;
			}
			preisp1 = isp1;
			isp1 = isp1->renext;
		}
		if(isp1->info->renext == NULL){				//��������isbn�ڵ��Ϊ�գ���ɾȥ�˽ڵ㣬���ұ���ͼ���޸�flag �� num 
			preisp1->renext = isp1->renext;
			free(isp1); 
			bokp1 = bookhead->next;
			while(bokp1){
				if(!strcmp(bokp1->no,p->borrownext->no)){
					bokp1->flag = 0;
					bokp->remainTime = 20;
					bokp1->borrowTimes++;
					break;
				}
				bokp1 = bokp1->next;
			}
			free(p->borrow);   //ɾ���˽ڵ㣻 
		} 
		else{										//�������ҵ�isbn�����Ľڵ㣬���ҽ���no�ҵ�������no�����ҵ���Ա�������޸�������Ϣ,�����޸�ͼ��flag 
			readerList childhead;
			childhead = isp1->info->renext;
			while(childhead->renext){
				childhead = childhead->renext;
			}
			zip1 = head->next;
			bokp1 = bookhead->next; 
			while(bokp1){
				if(!strcmp(bokp1->no,p->borrownext->no)){
					bokp1->borrowTimes++;
					bokp->remainTime = 20;      //???????������ȷ���޸�    �����ĺ��� 
					break;
				}
				bokp1 = bokp1->next;
			}
			while(zip1){
				if(!strcmp(zip1->no,childhead->no)){
					break;
				}
				zip1 = zip1->next;
			}
			if(zip1->borrow == NULL){
				zip1->borrow = (bookList)malloc(sizeof(book));
				*(zip1->borrow) = *(p->borrownext);
				free(p->borrownext) ;
				if(p->borrownext){
					*(p->borrow) = *(p->borrownext);
					free(p->borrownext);
					p->borrownext = NULL; 
				}
				else{
					p->borrow = NULL;
				}
				zip1->num = 1 ;
			}
			else if(zip1->borrownext == NULL){
				zip1->borrownext = (bookList)malloc(sizeof(book));
				*(zip1->borrownext)= *(p->borrownext);
				free(p->borrownext);
				if(p->borrownext){
					*(p->borrow) = *(p->borrownext);
					free(p->borrownext);
					p->borrownext = NULL; 
				}
				else{
					p->borrow = NULL;
				}
				zip1->num = 2;
			}
		}
	}
	else {
		printf("����ʧ��\n");
	}
} 
void borrow(readerList head,appointmentList ishead,bookList header){        //���������覴ã���Ϊ�кö�Ҫ�ĵĵط�����Ϊû�����������������ں���������˺ü�������Ҫɾȥ 
	readerList  p; 
	appointmentList isp;
	head = readerinput();
	char id[30];
	scanf("%s",id);
	p = head->next;
	while(p){
		if(!strcmp(id,p->no)){
			if(p->num == 2){
				printf("���Ѿ�������������.\n");
			}
			break;
		}
		else{
			p = p->next;
		} 
	}
	bookList q;
	char bianhao[30];
	scanf("%s",bianhao);
	q = header ->next;
	while(q){
		if(!strcmp(bianhao,q->no)){
			if(q->flag == 0){
				printf("���Խ���\n");
				if(p->num == 2){
					printf("���ѳ����������޽���ʧ��\n"); 
				}
				else if(p->num == 1){
					p->borrownext = q;
					isp = (appointmentList)malloc(sizeof(appointment));
					isp->info = (readerList)malloc(sizeof(reader));
					isp->info->renext = NULL;
					strcpy(isp->ISBN,q->ISBN);
					isp->renext = ishead->renext ;
					ishead->renext = isp;
					q->flag = 1;
					q->remainTime = 20;
					printf("���ĳɹ�\n");
				} 
				else 
					p->borrow = q;
					isp = (appointmentList)malloc(sizeof(appointment));
					isp->info = (readerList)malloc(sizeof(reader));
					isp->info->renext = NULL;
					strcpy(isp->ISBN,q->ISBN);
					isp->renext = ishead->renext ;
					ishead->renext = isp;
					q->flag = 1;
					q->remainTime = 20;
					printf("���ĳɹ�\n");
			}
			else{
				printf("��ҪԤԼ\n"); 
				isbn(ishead,p);
			}
			break;	
		}
		else{
			q = q->next;
		}
	}
	
}
void isbn(appointmentList head,readerList q){
	char isb[30];
	appointmentList p;
	scanf("%s",isb);
	p = head->renext; 
	while(p){
		if(!strcmp(isb,p->ISBN)){
			if(p->info->renext = NULL){
				q->renext = NULL;
				p->info->renext = q;
			}
			else{
				q->renext = p->info->renext;
				p->info->renext = q;
			}
			printf("ԤԼ�ɹ�\n");
			break;
		}
		else{
			p = p->renext ;
		}
	}
	
}
