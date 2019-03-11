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
void returnbook(readerList head,appointmentList ishead,bookList bookhead){
	readerList p , zip , zip1;
	appointmentList isp ,preisp ,isp1 ,preisp1 ;
	bookList bokp , bokp1;
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
		preisp = ishead;
		isp = ishead->renext;
		while(isp){
			if(!strcmp(isp->ISBN,p->borrow->ISBN)){
				break;
			}
			preisp = isp;
			isp = isp->renext;
		}
		if(isp->info->renext == NULL){				//如果还书后，isbn节点后为空，则删去此节点，并且遍历图书修改flag 和 num 
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
			free(p->borrow);   //删除此节点； 
		} 
		else{										//否则先找到isbn链最后的节点，并且将其no找到，利用no遍历找到成员，并且修改他的信息,不用修改图书flag 
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
		printf("图书borrow2查找成功\n");
		p->num = p->num-1; 
		p->borrownext->flag = 0;
		if(p->borrownext->remainTime < 0){
			printf("需要支付罚款\n");
			printf("支付金额：%d \n",(p->borrownext->remainTime)*(-2)); 
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
		if(isp1->info->renext == NULL){				//如果还书后，isbn节点后为空，则删去此节点，并且遍历图书修改flag 和 num 
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
			free(p->borrow);   //删除此节点； 
		} 
		else{										//否则先找到isbn链最后的节点，并且将其no找到，利用no遍历找到成员，并且修改他的信息,不用修改图书flag 
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
					bokp->remainTime = 20;      //???????在哪里确定修改    ，都改好了 
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
		printf("查找失败\n");
	}
} 
void borrow(readerList head,appointmentList ishead,bookList header){        //这个函数有瑕疵，因为有好多要改的地方，因为没法引用已有链表，我在函数里添加了好几个，还要删去 
	readerList  p; 
	appointmentList isp;
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
	bookList q;
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
					isp = (appointmentList)malloc(sizeof(appointment));
					isp->info = (readerList)malloc(sizeof(reader));
					isp->info->renext = NULL;
					strcpy(isp->ISBN,q->ISBN);
					isp->renext = ishead->renext ;
					ishead->renext = isp;
					q->flag = 1;
					q->remainTime = 20;
					printf("借阅成功\n");
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
					printf("借阅成功\n");
			}
			else{
				printf("需要预约\n"); 
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
			printf("预约成功\n");
			break;
		}
		else{
			p = p->renext ;
		}
	}
	
}
