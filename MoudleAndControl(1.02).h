#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 1000
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<Windows.h>
/*MOUDLE*/
//-----------------------------ͼ���-------------------------
typedef struct PriBookClass 
{
	int id;	//���
	char name[20];//����
	char author[20];//����
	char publisher[20];//������
	int totalMemory;//���ڴ�
	int currentMemory;//��ǰ�ڴ�
	struct PriBookClass *next;
}BookClass;
typedef struct PriLibrary 
{//���������Ϣ
	int totalMemory;//������Ŀ
	int currentMemory;//��ǰ�鼮��Ŀ
	int numOfBookClass;//�鼮���
	BookClass *headBookClass;//�鼮ͷָ��	
}Library;
//-----------------------------�������-----------------------
typedef struct PriBorBook 
{	 //���ڱ�����߽�����鼮
	int id;//�����鼮���
	int amount;//�����鼮����
}BorBook;
typedef struct PriBorBookSet 
{
	BorBook *borBooks[MAX_SIZE];
	int amount;//���鼮���
}BorBookSet;
//-----------------------------������Ϣ-----------------------
typedef struct PriReader 
{
	int id;
	char name[20];
	BorBookSet borBookSet;
	struct PriReader *next;
}Reader;
typedef struct PriReaderSet 
{
	int amount;
	Reader *headReader;
}ReaderSet;
//-----------------------------�軹��¼-----------------------
typedef struct PriRecord 
{
	int readerId;//�����
	int bookId;//�鼮��
	int amount;	//ͼ������
	char time[30];	//����ʱ��
	char limitedTime[30];	//�黹����
	int action;//��ǰ��Ϊ
	struct PriRecord *next;
}Record;
typedef struct PriRecordSet 
{
	int amount;	//��¼����
	Record *headRecord;	//ͷ�ڵ�
}RecordSet;
//-----------------------------Id������-----------------------
typedef struct PriSearchListById 
{
	int id;
	BookClass *bookClass;
}SearchIdNode;
typedef struct PriSearchListByIdSet 
{
	SearchIdNode searchId[MAX_SIZE];
	int amount;
}SearchIdList;
//-----------------------------�ۺϼ�����-------------------
typedef struct PriSearchNode 
{
	char name[20];
	char author[20];
	char publisher[20];
	BookClass *bookClass;
}SearchNode;
typedef struct PriSearchList 
{
	SearchNode searchNode[MAX_SIZE];
	int amount;
}SearchList;
/*Control*/
//-----------------------------�������-----------------------
/*���Ҹ��������鼮*/
 BorBook *searchBorBook(BorBookSet borBookSet, int id) 
 {
	BorBook *borBook = NULL;
	for (int i = 0; i < borBookSet.amount; i++) 
	{
		if (id == borBookSet.borBooks[i]->id) 
		{
			borBook = borBookSet.borBooks[i];
		}
	}
	return borBook;
}
/*�������������鼮*/
int addNewBorBook(BorBookSet *borBookSet, int id, int amount) 
{
	if (borBookSet->amount + 1 == MAX_SIZE) 
	{
		return 0;
	}
	else 
	{
		BorBook *borBook = (BorBook *)malloc(sizeof(BorBook));
		borBook->amount = amount;
		borBook->id = id;
		borBookSet->borBooks[borBookSet->amount] = borBook;	//ERROR
		borBookSet->amount++;
		return 1;
	}
}
//-----------------------------������Ϣ-----------------------
/*��ȡ�������ID*/
int getReaderMaxId(ReaderSet readerSet) 
{
	int maxId;
	if (readerSet.headReader) 
	{
		maxId = readerSet.headReader->id;
		while (readerSet.headReader) 
		{
			maxId = maxId > readerSet.headReader->id ?  maxId : readerSet.headReader->id;
			readerSet.headReader = readerSet.headReader->next;
		}
	}
	else 
	{
		maxId = 0;
	}
	return maxId;
}
/*���������б�*/
ReaderSet createReaderSet() 
{
	ReaderSet readerSet;
	readerSet.amount = 0;
	readerSet.headReader = NULL;
	return readerSet;
}
/*
���ܣ����Ӷ�����Ϣ
����ֵ������id
*/
int addReader(ReaderSet *readerSet,char *name) 
{
	Reader *reader;
	reader = (Reader *)malloc(sizeof(Reader));//����һ��������Ϣ�ڴ��
	reader->id = getReaderMaxId(*readerSet) + 1;	//ʹ��id��Ϊ����һ��
	strcpy(reader->name,name);//�洢��������
	reader->borBookSet.amount = 0;//��ʼ�������������
	reader->next = readerSet->headReader;//����ָ��ָ����һλ����
	readerSet->headReader = reader;
	readerSet->amount++;
	return reader->id;
}
/*��ʾ�����б�*/
void showReaders(ReaderSet readerSet) 
{
	void showReaderDetail(ReaderSet readerSet, int id);
	printf("->�����\t����\t�ѽ�����\t");
	printf("�鼮���\t�鼮��Ŀ\t\n");
	while (readerSet.headReader) 
	{

		printf("->%d\t\t%s\t%d\t\t",
			readerSet.headReader->id,
			readerSet.headReader->name,
			readerSet.headReader->borBookSet.amount);
		for (int i = 0; i < readerSet.headReader->borBookSet.amount; i++) 
		{
			printf("%d\t\t%d\t\t", readerSet.headReader->borBookSet.borBooks[i]->id,
				readerSet.headReader->borBookSet.borBooks[i]->amount);
		}
		printf("\n");
		readerSet.headReader = readerSet.headReader->next;
	}
}
/*��ʾ���߽�������*/
void showReaderDetail(ReaderSet readerSet,int id)
{
	Reader *searchReader(ReaderSet readerSet, int id);
	int i;
	Reader *reader = NULL;
	reader = searchReader(readerSet,id);
	printf("->�鼮���|�鼮��Ŀ\n");
	for (i = 0; i < reader->borBookSet.amount;i++)
		printf("%d\t|%d\n", reader->borBookSet.borBooks[i]->id, reader->borBookSet.borBooks[i]->amount);
}
/*
���ܣ�����id���Ҷ���
����ֵ������ָ��
*/
Reader *searchReader(ReaderSet readerSet, int id) 
{
	Reader *reader = NULL;
	while (readerSet.headReader) 
	{
		if (readerSet.headReader->id == id) 
		{
			reader = readerSet.headReader;
		}
		readerSet.headReader = readerSet.headReader->next;
	}
	return reader;
}
/*�޸Ķ�������*/
void alterReader(ReaderSet *readerSet, int id, char *name) 
{
	Reader *reader;
	reader = searchReader(*readerSet,id);
	printf("%d..woqu\n",readerSet->headReader->id);
	Sleep(5000);
	if (reader) 
	{
		strcpy(reader->name,name);
	}
	else 
	{
		printf("δ�ҵ��ö���\n");
	}
}
/*
���ܣ�ɾ������
����ֵ��0��������������
*/
int removeReader(ReaderSet *readerSet, int id)
{
	Reader *reader=readerSet->headReader;
	Reader *temp=readerSet->headReader;
	if (reader)
	{
		if(readerSet->headReader->id == id)//��ͷ�����д���
		{
			if(readerSet->headReader->borBookSet.amount > 0)
			{
				printf("�ö�������δ�黹�鼮���޷�ɾ��!\n");
				return 0;
			}
			readerSet->headReader = readerSet->headReader->next;
			free(temp);
			readerSet->amount -= 1; 
			printf("ɾ���ɹ�\n");
			return 0;
		}
		while(temp)
		{
			if(temp->id == id)
			{
				if(temp->borBookSet.amount > 0)
				{
					printf("�ö�������δ�黹�鼮���޷�ɾ��!\n");
					return 0;
				}
				reader->next = temp->next;
				free(temp);
				readerSet->amount -= 1;
				printf("ɾ���ɹ�\n");
				break;
			}
			else
			{
				reader = temp;
				temp = temp->next;
			}
		}
	}
	else
	{
		printf("��ǰ�����������Ϊ0.\n");
		Sleep(1000);
	}
	return 0;
}

/*
���ܣ�Ϊ������������鼮��������
����ֵ�������鼮��Ŀ
*/
int addBorBooks(ReaderSet *readerSet,int readerId,int bookId,int amount) 
{
	Reader *reader;
	BorBook *borBook;
	reader = searchReader(*readerSet,readerId);
	if (reader) 
	{
		borBook = searchBorBook(reader->borBookSet,bookId);
		if (borBook) 
		{	//�Ѿ����Ȿ��
			borBook->amount += amount;
		}
		else 
		{	//û���Ȿ��
			if (!addNewBorBook(&(reader->borBookSet),bookId,amount)) 
			{
				amount = 0;
			}
		}
	}
	return amount;
}
/*�Ӹ������ȡ�飬������*/
int deteleBorBook(ReaderSet *readerSet, int readerId, int bookId, int amount) 
{
	Reader *reader;
	BorBook *borBook;
	reader = searchReader(*readerSet, readerId);
	if (reader) 
	{
		borBook = searchBorBook(reader->borBookSet, bookId);
		if (borBook) 
		{
			amount = amount > borBook->amount ? borBook->amount : amount;	//�������鳬������
			borBook->amount -= amount;
			reader->borBookSet.amount -= 1;
		}
	}
	return amount;
}
//-----------------------------�軹��¼-----------------------
/*������¼��*/
RecordSet createRecordSet() 
{
	RecordSet recordSet;
	recordSet.amount = 0;
	recordSet.headRecord = NULL;
	return recordSet;
}
/*��Ӽ�¼*/
void addRecord(RecordSet *recordSet,int readerId,int bookId,int amount,int action) 
{
	Record *record = (Record *)malloc(sizeof(Record));
	record->readerId = readerId;
	record->bookId = bookId;
	record->amount = amount;
	record->action = action;
	time_t t;
	struct tm *timeinfo;
	t = time(NULL);
	char *time;
	time = ctime(&t);
	printf("%s\n",time);
	t += 2592000;
	timeinfo = localtime(&t);
	strcpy(record->time,time);
	if (action) 
	{	//����
		strcpy(record->limitedTime, asctime(timeinfo));
	}
	else 
	{	//����
		strcpy(record->limitedTime, time);
	}
	record->next = recordSet->headRecord;
	recordSet->headRecord = record;
	recordSet->amount++;
}
/*��ʾ��¼*/
void showRecord(RecordSet recordSet) 
{
	while (recordSet.headRecord) 
	{
		printf("->����֤�ţ�%d\t��ţ�%d\t������%d\n���ڣ�%s",
			recordSet.headRecord->readerId,
			recordSet.headRecord->bookId,
			recordSet.headRecord->amount,
			recordSet.headRecord->time);
		if (recordSet.headRecord->action == 1) 
		{
			printf("�������ڣ�%s", recordSet.headRecord->limitedTime);
			printf("����\n");
		}
		else 
		{
			printf("����\n");
		}
		recordSet.headRecord = recordSet.headRecord->next;
	}
}
//-----------------------------ID������-----------------------
/*����Id������
����ֵ��ID������ָ��
*/
SearchIdList CreateSearchIdList(Library library) 
{
	SearchIdList searchIdList;
	int i = 0;
	searchIdList.amount = library.numOfBookClass;//ID���������Ŀ�����鼮�����Ŀ
	while (library.headBookClass) 
	{
		searchIdList.searchId[i].id = library.headBookClass->id;
		searchIdList.searchId[i].bookClass = library.headBookClass;
		i++;
		library.headBookClass = library.headBookClass->next;//��������Ŀ������ID��������
	}
	return searchIdList;
}
/*
���ܣ�ͨ��Id��ѯ
����ֵ���鼮ָ��
*/
BookClass *searchById(SearchIdList searchIdList, int id) 
{
	BookClass *bookClass = NULL;
	for (int i = 0; i < searchIdList.amount; i++) 
	{
		if (id == searchIdList.searchId[i].id) 
		{
			bookClass = searchIdList.searchId[i].bookClass;
			break;
		}
	}
	return bookClass;
}
//-----------------------------�ۺϼ�����-------------------
/*�����ۺ�������*/
SearchList createSearchList(Library library) 
{
	SearchList searchList;
	searchList.amount = library.numOfBookClass;	//��ȡ���������
	int i = 0;
	while (library.headBookClass) 
	{
		strcpy(searchList.searchNode[i].name, library.headBookClass->name);
		strcpy(searchList.searchNode[i].author, library.headBookClass->author);
		strcpy(searchList.searchNode[i].publisher, library.headBookClass->publisher);
		searchList.searchNode[i].bookClass = library.headBookClass;
		i++;
		library.headBookClass = library.headBookClass->next;	//ָ����һ���ڵ�
	}
	return searchList;
}
/*�ۺϲ���*/
int search(SearchList searchList, int index[1000], char *key) 
{
	//char id[10];
	int sign = 0;
	for (int i = 0; i < searchList.amount; i++) 
	{
		if (strcmp(searchList.searchNode[i].name, key)  == 0||
			strcmp(searchList.searchNode[i].author, key) == 0 || 
			strcmp(searchList.searchNode[i].publisher,key) == 0) 
		{	//ƥ��
			index[sign] = i;
			sign++;
		}
	}
	return sign;
}
//-----------------------------ͼ���-------------------------
/*����*/
Library createLibrary() 
{
	Library library;
	library.currentMemory = 0;
	library.totalMemory = 0;
	library.numOfBookClass = 0;
	library.headBookClass = NULL;
	return library;
}
/*
���ܣ���ȡͼ������鼮���ID
����ֵ�����IDֵ
*/
int getBookClassMaxId(Library library) 
{
	int maxId = 0;
	while (library.headBookClass) 
	{
		maxId = maxId > library.headBookClass->id ? maxId : library.headBookClass->id;
		library.headBookClass = library.headBookClass->next;
	}
	return maxId;
}
/*�ۺϲ�ѯ*/
int queryLibrary(Library library, BookClass *bookClasses[MAX_SIZE], char* key) 
{
	SearchList searchList;
	searchList = createSearchList(library);	//��ü������Ա�
	int index[1000];
	int length = search(searchList, index, key);
	for (int i = 0; i < length; i++) 
	{
		bookClasses[i] = searchList.searchNode[index[i]].bookClass;
	}
	return length;
}
/*
���ܣ���ѯǰ���ڵ�
����ֵ��ǰ���ڵ�ֵ
*/
BookClass *findPreBookClass(Library library,int id) 
{
	BookClass *preBookClass = NULL,*bookClass;
	if (library.headBookClass) 
	{
		bookClass = library.headBookClass;
		while (bookClass && bookClass->id != id) 
		{
			preBookClass = bookClass;
			bookClass = bookClass->next;
		}
	}
	return preBookClass;
}
/*ID��ѯ*/
BookClass *queryLibraryById(Library library, int id) 
{
	BookClass *bookClass;
	SearchIdList searchIdList = CreateSearchIdList(library);
	bookClass = searchById(searchIdList, id);
	return bookClass;
}
/*�ɱ����*/
void addBooks(Library *library, char *name, char *author,char *publisher, int amount) 
{
	BookClass *bookClass = NULL;
	BookClass *temp = library->headBookClass;
	while (temp) 
	{
		if (strcmp(name, temp->name) == 0 && 
			strcmp(author,temp->author) == 0 && 
			strcmp(publisher,temp->publisher) == 0) 
		{
			bookClass = temp;
			break;
		}
		temp = temp->next;
	}
	if (!bookClass) 
	{	//������ͼ��ݲ�����
		bookClass = (BookClass*)malloc(sizeof(BookClass));
		strcpy(bookClass->name, name);
		strcpy(bookClass->author, author);
		strcpy(bookClass->publisher,publisher);
		bookClass->currentMemory = amount;
		bookClass->totalMemory = amount;
		bookClass->id = getBookClassMaxId(*library) + 1;//Ϊ��������id
		bookClass->next = library->headBookClass;
		library->headBookClass = bookClass;
		library->numOfBookClass++;
	}
	else 
	{
		bookClass->currentMemory += amount;
		bookClass->totalMemory += amount;
	}
	library->totalMemory += amount;//ͼ������鼮��Ŀ����
	library->currentMemory += amount;
}
/*��������*/
void clearBooks(Library *library, int id) 
{
	BookClass *preBookClass = NULL;
	BookClass *temp;
	if (library->headBookClass->id == id) 
	{	//ͷ�ڵ�
		temp = library->headBookClass;
		library->numOfBookClass--;
		library->currentMemory -= temp->currentMemory;
		library->totalMemory -= temp->totalMemory;
		library->headBookClass = library->headBookClass->next;
		free(temp);
		printf("->�����ϡ�\n");
	}
	else {	//���ܴ����ں����ڵ�
		preBookClass = findPreBookClass(*library, id);	//��ȡǰ���ڵ�
		if (preBookClass) 
		{		//�����Ȿ��
			temp = preBookClass->next;
			library->numOfBookClass--;
			library->currentMemory -= temp->currentMemory;
			library->totalMemory -= temp->totalMemory;
			preBookClass->next = temp->next;
			free(temp);
			printf("->�����ϡ�\n");
		}
		else 
		{
			printf("->�����ڴ��顣\n");
		}
	}
}
/*
���ܣ���ͼ��ݽ���
����ֵ����������
*/
int borrowBooks(Library *library, int id, int amount) 
{
	BookClass *bookClass;
	bookClass = queryLibraryById(*library, id);
	if (bookClass) 
	{
		amount = amount > bookClass->currentMemory ? bookClass->currentMemory : amount;
		bookClass->currentMemory -= amount;
		library->currentMemory -= amount;
	}
	else 
	{
		amount = 0;
	}
	return amount;
}
/*����*/
int returnBooks(Library *library, int id, int amount) 
{
	BookClass *bookClass = queryLibraryById(*library, id);
	if (bookClass) 
	{
		bookClass->currentMemory += amount;
		library->currentMemory += amount;
	}
	else 
	{
		amount = 0;
	}
	return amount;
}

void showAllBooks(Library *library)
{
	int num;
	BookClass *temp;
	temp = library->headBookClass;
	printf("->ͼ���Ŀǰ���� %d ���飬���� %d ���飬���� %d ����\n",library->numOfBookClass,library->totalMemory,library->currentMemory);
	printf("���\t|����\t\t   �鼮����Ŀ\t�����ִ���Ŀ\t\t\t\n");
	while(temp)
	{
		num = strlen(temp->name);
		if(num >= 14)
			printf("%d\t|%s\t%d\t\t%d\t\t\n",temp->id,temp->name,temp->totalMemory,temp->currentMemory);			
		else if(num>=8)
			printf("%d\t|%s\t\t%d\t\t%d\t\t\n",temp->id,temp->name,temp->totalMemory,temp->currentMemory);
		else 
			printf("%d\t|%s\t\t\t%d\t\t%d\t\t\n",temp->id,temp->name,temp->totalMemory,temp->currentMemory);
		temp = temp->next;
	}
}
//-----------------------------����--------------------------
/*���飬���ؽ������*/
int Borrow(Library *library, ReaderSet *readerSet, RecordSet *recordSet, int readerId, int bookId, int amount) 
{
	amount = borrowBooks(library, bookId, amount);	//��ͼ��ݽ���
	if (amount) 
	{
		int temp = amount;
		amount = addBorBooks(readerSet, readerId, bookId, amount);		//���˲ֿ������鼮
		if (amount) 
		{
			addRecord(recordSet, readerId, bookId, amount, 1);
		}
		else 
		{	//���˲ֿ��޷�����鼮�����鷵�زֿ�
			returnBooks(library, bookId, temp);
		}
	}
	printf("%d\n", amount);
	return amount;
}
//-----------------------------����--------------------------
/*���飬���ػ���ȥ������*/
int Return(Library *library, ReaderSet *readerSet, RecordSet *recordSet, int readerId, int bookId, int amount) 
{
	amount = deteleBorBook(readerSet, readerId, bookId, amount);	//�Ӹ���������Ƴ��鼮
	if (amount) 
	{
		int temp = amount;
		amount = returnBooks(library, bookId, amount);		//���鷵����ͼ���
		if (amount) 
		{
			addRecord(recordSet,readerId,bookId,amount,0);
		}
		else 
		{
			amount = addBorBooks(readerSet,readerId,bookId,temp);
		}
	}
	return amount;
}
/*�����ļ�*/
void load(char *path1, char *path2, char *path3, Library *library, ReaderSet *readerSet, RecordSet *recordSet) 
{
	BookClass *bookClass;
	Record *record;
	Reader *reader;
	FILE *file;
	file = fopen(path1,"r");
	if (file) 
	{
		fscanf(file,"%d\t%d\t%d\n",&library->currentMemory
			,&library->totalMemory,
			&library->numOfBookClass);
		for (int i = 0; i < library->numOfBookClass; i++) 
		{
			bookClass = (BookClass *)malloc(sizeof(BookClass));
			fscanf(file,"%d\t%s\t%s\t%s\t%d\t%d\n",
				&bookClass->id,
				bookClass->name,
				bookClass->author,
				bookClass->publisher,
				&bookClass->totalMemory,
				&bookClass->currentMemory);	//�����鼮��Ϣ
			bookClass->next = library->headBookClass;
			library->headBookClass = bookClass;
		}
		fclose(file);
	}
	file = fopen(path2, "r");
	if (file) 
	{
		fscanf(file,"%d\n",&recordSet->amount);
		for (int i = 0; i < recordSet->amount; i++) 
		{
			record = (Record *)malloc(sizeof(Record));
			fscanf(file,"%d%d%d",
				&record->readerId,
				&record->bookId,
				&record->amount);
			fgets(record->time,30,file);
			fgets(record->limitedTime, 30, file);
			fscanf(file,"%d",&record->action);
			record->next = recordSet->headRecord;
			recordSet->headRecord = record;
		}
		fclose(file);
	}
	file = fopen(path3,"r");	//��ʼ���������Ϣ
	if (file) 
	{
		fscanf(file,"%d\n",&readerSet->amount);
		for (int i = 0; i < readerSet->amount; i++) 
		{
			reader = (Reader *)malloc(sizeof(Reader));
			fscanf(file,"%d\t%s\t%d\t",&reader->id,reader->name,&reader->borBookSet.amount);
			//int a;
			for (int j = 0; j < reader->borBookSet.amount; j++) 
			{
				BorBook *borBook = (BorBook *)malloc(sizeof(BorBook));
				reader->borBookSet.borBooks[j] = borBook;
				fscanf(file, "%d\t%d\t", &borBook->id,
					&borBook->amount);
			}
			reader->next = readerSet->headReader;
			readerSet->headReader = reader;
		}
		fclose(file);
	}
}
/*����*/
void save(char *path1, char *path2, char *path3, Library library, ReaderSet readerSet, RecordSet recordSet) 
{
	FILE *file;
	file = fopen(path1,"w");//ͼ����ļ�����
	if (file) 
	{
		fprintf(file,"%d\t%d\t%d\n",library.currentMemory,
			library.totalMemory,library.numOfBookClass);
		while (library.headBookClass) 
		{
			fprintf(file,"%d\t%s\t%s\t%s\t%d\t%d\n", 
				library.headBookClass->id,
				library.headBookClass->name,
				library.headBookClass->author,
				library.headBookClass->publisher,
				library.headBookClass->totalMemory,
				library.headBookClass->currentMemory);
			library.headBookClass = library.headBookClass->next;
		}
		fclose(file);
	}
	file = fopen(path2,"w");//��¼�ļ�����
	if (file) 
	{
		fprintf(file,"%d\n",recordSet.amount);
		while (recordSet.headRecord) 
		{
			fprintf(file,"%d\t%d\t%d%s%s%d\n",
				recordSet.headRecord->readerId,
				recordSet.headRecord->bookId,
				recordSet.headRecord->amount,
				recordSet.headRecord->time,
				recordSet.headRecord->limitedTime,
				recordSet.headRecord->action);
			recordSet.headRecord = recordSet.headRecord->next;
		}
		fclose(file);
	}
	file = fopen(path3,"w");//�����ļ�����
	if (file) 
	{
		fprintf(file,"%d\n",readerSet.amount);
		while (readerSet.headReader) 
		{
			fprintf(file,"%d\t%s\t%d\t", 
				readerSet.headReader->id, 
				readerSet.headReader->name,
				readerSet.headReader->borBookSet.amount);
			for (int i = 0; i < readerSet.headReader->borBookSet.amount; i++) 
			{
				fprintf(file,"%d\t%d\t", readerSet.headReader->borBookSet.borBooks[i]->id,
					readerSet.headReader->borBookSet.borBooks[i]->amount);
			}
			fprintf(file,"\n");
			readerSet.headReader = readerSet.headReader->next;
		}
		fclose(file);
	}
}