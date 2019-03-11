void readeroutput(readerList head){
	FILE *fp1; 
	readerList p;
	p = head->next;
	if ((fp1 = fopen("测试.txt", "w+")) != NULL){
		while(p){
			fprintf(fp1,"%d %s %s %s %d %d \n", p->identity, p->name, p->no, p->school, p->level, p->num);
			if(p->num==1){
				fprintf(fp1,"%s %s %s %s %s %s %s %d %d %d \n", p->borrow->no, p->borrow->ISBN, p->borrow->name, p->borrow->author, p->borrow->press, p->borrow->info, p->borrow->bTime,p->borrow->borrowTimes,p->borrow->flag,p->borrow->remainTime);
			}
			else if(p->num==2){
				fprintf(fp1,"%s %s %s %s %s %s %s %d %d %d \n", p->borrow->no, p->borrow->ISBN, p->borrow->name, p->borrow->author, p->borrow->press, p->borrow->info, p->borrow->bTime,p->borrow->borrowTimes,p->borrow->flag,p->borrow->remainTime);
				fprintf(fp1,"%s %s %s %s %s %s %s %d %d %d \n", p->borrownext->no, p->borrownext->ISBN, p->borrownext->name, p->borrownext->author, p->borrownext->press, p->borrownext->info, p->borrownext->bTime,p->borrownext->borrowTimes,p->borrownext->flag,p->borrownext->remainTime);
			}
			p = p->next;
		}
	}
	fclose(fp1);
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
				p->borrownext = NULL;                             //***********要改的 
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
