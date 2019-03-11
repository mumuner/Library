//三个链表（书 读者 预约）输出到文件和从文件读的代码加上预约模块的代码写了就行了。
//借书模块
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "library.h"
bookList bookinput();
readerList readerinput();
appointmentList queue(); 
void isbn(appointmentList head,readerList q);
void yuyueoutput(appointmentList head);
//借书：首先先判断这个成员的已经借了多少书，如果已经借了两本不能再借书，如果少于两本可以借书，然后输入图书编号，如果flag=0，则成功借走，否则如果flag=1，
//并且将此节点插入到isbn码链表中 
//输入其isbn码，首先遍历isbn链，然后再进行头插法，插入节点。

//还书：通过输入图书编号，然后修改flag，然后再遍历isbn链表，把链表后面的元素的信息比如成员编号查找到，并且删除此节点，通过成员编号再遍历找到并且
//保存成员节点，然后遍历图书链表，通过isbn码，找到flag=0的图书，并保存该图书节点，并且修改flag = 1，然后将这个节点添加到成员节点中。 
//如果还书后的isbn码所对应的链为空了，则删除此isbn节点 
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
			printf("成员查找成功\n");
			break;
		}
		p = p->next;
	}
	char id[30];
	scanf("%s",id);
	if(!strcmp(p->borrow->no,id)){
		printf("图书borrow查找成功\n");
		p->num = p->num-1; 
		p->borrow->flag = 0;
		if(p->borrow->remainTime < 0){
			printf("需要支付罚款\n");
			printf("支付金额：%d \n",(p->borrow->remainTime)*(-2)); 
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
		if(isp->info->renext == NULL){				//如果还书后，isbn节点后为空，则删去此节点，并且遍历图书修改flag 和 num 
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
			free(p->borrow);   //删除此节点； 
		} 
		else{										//否则先找到isbn链最后的节点，并且将其no找到，利用no遍历找到成员，并且修改他的信息,不用修改图书flag 
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
		printf("图书borrow2查找成功\n");
		p->num = p->num-1; 
		p->borrownext->flag = 0;
		if(p->borrownext->remainTime < 0){
			printf("需要支付罚款\n");
			printf("支付金额：%d \n",(p->borrownext->remainTime)*(-2)); 
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
		if(isp1->info->renext == NULL){				//如果还书后，isbn节点后为空，则删去此节点，并且遍历图书修改flag 和 num 
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
			free(p->borrow);   //删除此节点； 
		} 
		else{										//否则先找到isbn链最后的节点，并且将其no找到，利用no遍历找到成员，并且修改他的信息,不用修改图书flag 
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
		printf("查找失败\n");
	}
} 
void borrow(){        //这个函数有瑕疵，因为有好多要改的地方，因为没法引用已有链表，我在函数里添加了好几个，还要删去 
	readerList head , p; 
	appointmentList ishead , isp;
	head = readerinput();
	char id[30];
	scanf("%s",id);
	p = head->next;
	while(p){
		if(!strcmp(id,p->no)){
			if(p->num == 2){
				printf("你已经超出借书上限.\n");
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
				printf("可以借阅\n");
				if(p->num == 2){
					printf("你已超出借书上限借书失败\n"); 
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
				printf("需要预约\n"); 
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
			printf("预约成功\n");
			break;
		}
		else{
			p = p->renext ;
		}
	}
	
}
readerList readerinput() { //成员读入 
	FILE *fp;
	readerList p;
	readerList head;
	head = (readerList)malloc(sizeof(reader));
	if ((fp = fopen("成员.txt", "r")) != NULL) {
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
bookList bookinput() { //图书读入 
	FILE *fp;
	bookList head;
	head = (bookList)malloc(sizeof(book));
	bookList p;
	if ((fp = fopen("图书.txt", "r")) != NULL) {
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
void yuyueoutput(appointmentList head){  //每次输出后，都要再进行读入 
	FILE *fp;
	readerList ren , pre;
	appointmentList p;
	p = head->renext;
	if((fp = fopen("测试.txt", "w")) != NULL){
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
	if((fp = fopen("预约.txt","r")) != NULL){
		p = (appointmentList)malloc(sizeof(appointment));
		head->renext = p;
		p->renext = NULL;
		p->info = (readerList)malloc(sizeof(reader)); //相当于头指针 
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
