bookList bookinput() { //Í¼Êé¶ÁÈë 
	FILE *fp;
	bookList head;
	head = (bookList)malloc(sizeof(book));
	bookList p;
	if ((fp = fopen("Í¼Êé.txt", "r")) != NULL) {
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
void bookoutput(bookList head){
	FILE *fp1; 
	bookList p;
	p = head->next;
	if ((fp1 = fopen("²âÊÔ.txt", "w+")) != NULL){
		while(p){
			fprintf(fp1,"%s %s %s %s %s %s %s %d %d %d \n", p->no, p->ISBN, p->name, p->author, p->press, p->info, p->bTime,p->borrowTimes,p->flag,p->remainTime);
			p = p->next;
		}
	}
}

