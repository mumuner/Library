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
int main(){
	readerList head , p , zip , zip1;
	appointmentList ishead , ishead1, isp ,preisp ,isp1 ,preisp1 ;
	bookList bookhead , bokp , bookhead1, bokp1;
	head = readerinput();
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
		ishead = queue();
		preisp = ishead;
		isp = ishead->renext;
		while(isp->renext){
			if(!strcmp(isp->ISBN,p->borrow->ISBN)){
				break;
			}
			preisp = isp;
			isp = isp->renext;
		}
		if(isp->info->renext == NULL){				//��������isbn�ڵ��Ϊ�գ���ɾȥ�˽ڵ㣬���ұ���ͼ���޸�flag �� num 
			preisp->renext = isp->renext;
			free(isp); 
			bookhead =  bookinput();
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
			bookhead =  bookinput();
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
			printf("...............");
			while(zip){
				if(!strcmp(zip->no,childhead->no)){
					break;
				}
				zip = zip->next;
			}
			printf("%s\n",zip->name);
			printf("%s\n",zip->borrow->name);
			printf("%p\n",zip->borrownext->name);
			if(zip->borrow == NULL){
				zip->borrow = (bookList)malloc(sizeof(book));
				zip->borrow = p->borrow ;
				free(p->borrow) ;
				zip->num = 1 ;
				printf("chenggongle aaaaa\n");
			}
			else if(zip->borrownext == NULL){
				zip->borrownext = (bookList)malloc(sizeof(book));
				zip->borrownext = p->borrow;
				free(p->borrow);
				zip->num = 2;
				printf("chengongle bbbbbb\n");
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
		ishead1 = queue();
		preisp1 = ishead1;
		isp1 = ishead1->renext;
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
			bookhead1 =  bookinput();
			bokp1 = bookhead1->next;
			while(bokp1){
				if(!strcmp(bokp1->no,p->borrownext->no)){
					bokp1->flag = 0;
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
			bookhead1 =  bookinput();
			zip1 = head->next;
			bokp1 = bookhead1->next; 
			while(bokp1){
				if(!strcmp(bokp1->no,p->borrownext->no)){
					bokp1->borrowTimes++;
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
				zip1->borrow = p->borrownext ;
				free(p->borrownext) ;
				zip1->num = 1 ;
				printf("chenggongle aaaaa\n");
			}
			else if(zip1->borrownext == NULL){
				zip1->borrownext = (bookList)malloc(sizeof(book));
				zip1->borrownext = p->borrownext;
				free(p->borrownext);
				zip1->num = 2;
				printf("chengongle bbbbbb\n");
				yuyueoutput(ishead1);
			}
		}
	}
	else {
		printf("����ʧ��\n");
	}
} 
void borrow(){        //���������覴ã���Ϊ�кö�Ҫ�ĵĵط�����Ϊû�����������������ں���������˺ü�������Ҫɾȥ 
	readerList head , p; 
	appointmentList ishead , isp;
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
	bookList header , q;
	header = bookinput();
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
					ishead = queue();
					isp = (appointmentList)malloc(sizeof(appointment));
					isp->info = (readerList)malloc(sizeof(reader));
					isp->info->renext = NULL;
					strcpy(isp->ISBN,q->ISBN);
					isp->renext = ishead->renext ;
					ishead->renext = isp;
				} 
				else 
					p->borrow = q;
				 	ishead = queue();
					isp = (appointmentList)malloc(sizeof(appointment));
					isp->info = (readerList)malloc(sizeof(reader));
					isp->info->renext = NULL;
					strcpy(isp->ISBN,q->ISBN);
					isp->renext = ishead->renext ;
					ishead->renext = isp;
			}
			else{
				printf("��ҪԤԼ\n"); 
				ishead = queue();
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
			q->renext = p->info->renext;
			p->info->renext = q;
			printf("ԤԼ�ɹ�\n");
			break;
		}
		else{
			p = p->renext ;
		}
	}
	
}
readerList readerinput() { //��Ա���� 
	FILE *fp;
	readerList p;
	readerList head;
	head = (readerList)malloc(sizeof(reader));
	if ((fp = fopen("��Ա.txt", "r")) != NULL) {
		p = (readerList)malloc(sizeof(reader));
		head->next = p;
		p->next = NULL;
		while(fscanf(fp,"%d",&p->identity)>0){
			fscanf(fp,"%s",p->name);
			fscanf(fp,"%s",p->no);	
			fscanf(fp,"%s",p->school);
			fscanf(fp,"%d",&p->level);
			fscanf(fp,"%d",&p->num);
			if(p->num==1) {
				p->borrow = (bookList)malloc(sizeof(book));
				fscanf(fp,"%s",p->borrow->no);
				fscanf(fp,"%s",p->borrow->ISBN);
				fscanf(fp,"%s",p->borrow->name);	
				fscanf(fp,"%s",p->borrow->author);
				fscanf(fp,"%s",p->borrow->press);
				fscanf(fp,"%s",p->borrow->info);
				fscanf(fp,"%s",p->borrow->bTime);
				fscanf(fp,"%d",&p->borrow->borrowTimes);
				fscanf(fp,"%d",&p->borrow->flag);
				fscanf(fp,"%d",&p->borrow->remainTime);
				p->borrownext = NULL;
			}
			else if(p->num==2){
				p->borrow = (bookList)malloc(sizeof(book));
				p->borrownext = (bookList)malloc(sizeof(book));
				fscanf(fp,"%s",p->borrow->no);
				fscanf(fp,"%s",p->borrow->ISBN);
				fscanf(fp,"%s",p->borrow->name);	
				fscanf(fp,"%s",p->borrow->author);
				fscanf(fp,"%s",p->borrow->press);
				fscanf(fp,"%s",p->borrow->info);
				fscanf(fp,"%s",p->borrow->bTime);
				fscanf(fp,"%d",&p->borrow->borrowTimes);
				fscanf(fp,"%d",&p->borrow->flag);
				fscanf(fp,"%d",&p->borrow->remainTime);
				fscanf(fp,"%s",p->borrownext->no);
				fscanf(fp,"%s",p->borrownext->ISBN);
				fscanf(fp,"%s",p->borrownext->name);	
				fscanf(fp,"%s",p->borrownext->author);
				fscanf(fp,"%s",p->borrownext->press);
				fscanf(fp,"%s",p->borrownext->info);
				fscanf(fp,"%s",p->borrownext->bTime);
				fscanf(fp,"%d",&p->borrownext->borrowTimes);
				fscanf(fp,"%d",&p->borrownext->flag);
				fscanf(fp,"%d",&p->borrownext->remainTime);
			}
			else {
				p->borrow=NULL;
				p->borrownext=NULL;
			}
			p = (readerList)malloc(sizeof(reader));
			p->next = head->next;
			head->next = p;
		}
		head->next = p->next;
	}
	fclose(fp);
	return head;
}
bookList bookinput() { //ͼ����� 
	FILE *fp;
	bookList head;
	head = (bookList)malloc(sizeof(book));
	bookList p;
	if ((fp = fopen("ͼ��.txt", "r")) != NULL) {
		p = (bookList)malloc(sizeof(book));
		head->next = p;
		p->next = NULL;
		while(fscanf(fp,"%s",p->no)>0){
			fscanf(fp,"%s",p->ISBN);
			fscanf(fp,"%s",p->name);	
			fscanf(fp,"%s",p->author);
			fscanf(fp,"%s",p->press);
			fscanf(fp,"%s",p->info);
			fscanf(fp,"%s",p->bTime);
			fscanf(fp,"%d",&p->borrowTimes);
			fscanf(fp,"%d",&p->flag);
			fscanf(fp,"%d",&p->remainTime);
			p = (bookList)malloc(sizeof(book));
			p->next = head->next;
			head->next = p;
		}
		head->next = p->next;
	}
	return head;
}
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
						//child->next = NULL;
						p->info->renext = child;
					}
					else {
						child->renext = p->info->renext;
						//child->next = NULL;
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
					//p->info->next = NULL;
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
