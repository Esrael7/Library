/*
ͼ�����ϵͳ
*/
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
//---Moudle
typedef struct PriBook{
char name[20];
char author[20];
}Book;	//������
typedef struct PriBookClass{
	int id;	//���
	char name[20];
	char author[20];
	int totalMemory;
	int currentMemory;
	struct PriBookClass *next;	//ֻ����һ���ڵ�
}BookClass;
typedef struct PriLibrary{
	int totalMemory;
	int currentMemory;
	int numOfBookClass;	//�������
	BookClass *headBookClass;	//ͷ�ڵ�
}Library;
typedef struct PriReader{
	int id;
	char name[20];
	//ɢ�б�->�������
	struct PriReader *next;
}Reader;
typedef struct PriReaderSet{
	int amount;
	Reader *headReader;		//ͷ�ڵ�
}ReaderSet;
typedef struct PriRecord {
	char time[20];	//����ʱ��
	char limitedTime[20];	//�黹����
	Reader reader;
	BookClass bookClass;
	int amount;	//ͼ������
	int action;
	struct PriRecord *next;
}Record;
typedef struct PriRecordSet{
	int amount;	//��¼����
	Record *headRecord;	//ͷ�ڵ�
}RecordSet;
typedef struct PriSearchNode {
	int id;
	char name[20];
	char author[20];
	BookClass *bookClass;
}SearchNode;
typedef struct PriSearchList {
	SearchNode searchNode[1000];
	int amount;
}SearchList;
//Control
//--------------------------------------------------------------
Book createBook(char *name, char *author) {
	Book book;
	strcpy(book.name,name);
	strcpy(book.author,author);
	return book;
}
//--------------------------------------------------------------
/*��ʼ��һ����*/
BookClass *createBookClass(char *name,char *author) {
	BookClass* bookClass;
	bookClass = (BookClass *)malloc(sizeof(BookClass));
	bookClass->id = -1;	//��û�з������
	strcpy(bookClass->name,name);
	strcpy(bookClass->author,author);
	bookClass->totalMemory = 0;
	bookClass->currentMemory = 0;
	bookClass->next = NULL;
	return bookClass;
}
/*����鼮*/
void priAddBooks(BookClass *bookClass,int amount) {
	bookClass->totalMemory += amount;
	bookClass->currentMemory += amount;
}
/*ɾ���鼮*/
void priDeleteBooks(BookClass *bookClass, int amount) {
	if (amount > bookClass->totalMemory) {
		bookClass->totalMemory = 0;
	}
	else {
		bookClass->totalMemory -= amount;
	}
	if (amount > bookClass->currentMemory) {
		bookClass->currentMemory = 0;
	}
	else {
		bookClass->currentMemory -= amount;
	}
}
/*����鼮*/
void priClear(BookClass *bookClass) {
	BookClass *tempBook;
	tempBook = bookClass;
	bookClass = bookClass->next;
	free(tempBook);	//�ͷ��ڴ�
}
/*����*/
void priBor(BookClass *bookClass,int *amount) {
	if (bookClass->currentMemory < *amount) {
		*amount = bookClass->currentMemory;
		bookClass->currentMemory = 0;
	}
	else {
		bookClass->currentMemory -= *amount;
	}
}
/*����*/
void priRet(BookClass *bookClass, int amount) {
	bookClass->currentMemory += amount;
}
/*�޸��鼮��Ϣ*/
void priModifyBookClass(BookClass *bookClass,char *name,char *author) {
	strcpy(bookClass->name, name);
	strcpy(bookClass->author,author);
}
/*��ѯ�鼮������Ϣ*/
void priQueryBookClass(BookClass bookClass, int *totalMemory, int *currentMemory) {
	*totalMemory = bookClass.totalMemory;
	*currentMemory = bookClass.currentMemory;
}
//--------------------------------------------------------------
/*ReaderSet*/
/*���������б�*/
ReaderSet createReaderSet() {
	ReaderSet readerSet;
	readerSet.amount = 0;
	readerSet.headReader = NULL;
}
/*��Ӷ���*/
void addReader(ReaderSet *readerSet,char *name) {
	Reader *reader;
	reader = (Reader*)malloc(sizeof(Reader));
	reader->id = readerSet->amount;
	strcpy(reader->name,name);
	reader->next = readerSet->headReader;
	readerSet->headReader = reader;
}
//--------------------------------------------------------------
/*RecordSet*/
/*����*/
RecordSet createRecordSet() {
	RecordSet recordSet;
	recordSet.amount = 0;
	recordSet.headRecord = NULL;
	return recordSet;
}
/*��Ӽ�¼*/
void addRecord(BookClass bookClass, Reader reader, int amount, int action) {
	Record *record;
	record = (Record*)malloc(sizeof(Record));
	record->amount = amount;
	record->bookClass = bookClass;
	record->reader = reader;
	record->time = ;
	record->limitedTime = ;
	record->action = action;
}
//--------------------------------------------------------------
/*SearchList*/
/*Ϊͼ�鴴��һ�����Լ�����*/
SearchList createSearchList(Library library) {
	SearchList searchList;
	searchList.amount = library.numOfBookClass;	//��ȡ���������
	int i = 0;
	while (library.headBookClass) {
		searchList.searchNode[i].id = library.headBookClass->id;
		strcpy(searchList.searchNode[i].name, library.headBookClass->name);
		strcpy(searchList.searchNode[i].author, library.headBookClass->author);
		searchList.searchNode[i].bookClass = library.headBookClass;
		i++;
		library.headBookClass = library.headBookClass->next;	//ָ����һ���ڵ�
	}
	return searchList;
}
/*���ֲ���*/
int search(SearchList searchList,int index[1000],char *key) {
	char id[10];
	int sign = 0;
	for (int i = 0; i < searchList.amount; i++) {
		itoa(searchList.searchNode[i].id, id, 10);
		if (strcmp(id, key) ||
			strcpy(searchList.searchNode[i].name, key) ||
			strcpy(searchList.searchNode[i].author, key)) {	//ƥ��
			index[sign] = i;
			sign++;
		}
	}
	return sign;	
}
//--------------------------------------------------------------
/*Library*/
/*����*/
Library createLibrary() {
	Library library;
	library.currentMemory = 0;
	library.numOfBookClass = 0;
	library.totalMemory = 0;
	library.headBookClass = NULL;
}
/*�ۺϲ�ѯ*/
BookClass **queryLibrary(Library library,char* key) {
	SearchList searchList;
	searchList = createSearchList(library);	//��ü������Ա�
	BookClass *bookClasses[1000];	//�����ҵ���bookClass
	int index[1000];
	int length = search(searchList,index, key);
	for (int i = 0; i < length; i++) {
		bookClasses[i] = searchList.searchNode[index[i]].bookClass;
	}
	return bookClasses;
}
/*ID��ѯ*/
BookClass *queryLibraryById(Library library, int id) {
	BookClass *bookClass = NULL; 
	SearchList searchList;
	searchList = createSearchList(library);
	for (int i = 0; i < searchList.amount; i++) {
		if (id = searchList.searchNode[i].id) {
			bookClass = searchList.searchNode[i].bookClass;
			break;
		}
	}
	return bookClass;
}
/*����*/
int addBooks(Library *library, int id,char *name,char *author,int amount) {
	BookClass *bookClass;
	BookClass *temp;
	bookClass = queryLibraryById(*library,id);
	if (bookClass == NULL) {	//δ���ҵ�
		bookClass = createBookClass(name,author);	//�Ѿ����ٿռ�
		bookClass->id = library->numOfBookClass;
		library->numOfBookClass++;
		library->headBookClass = temp;
		library->headBookClass = bookClass;
		bookClass->next = temp;
	}
	else {	//ͼ������ж�Ӧ����
		priAddBooks(bookClass, amount);
	}
	return bookClass->id;
}
/*ɾ��*/
void deleteBooks(Library *library, int id, int amount) {
	BookClass *bookClass;
	bookClass = queryLibraryById(*library,id);
	if (bookClass) {
		priDeleteBooks(bookClass, amount);
	}
}
/*���*/
void clearBooks(Library *library, int id) {
	BookClass *bookClass;
	bookClass = queryLibraryById(*library,id);
	priClear(bookClass);
}
/*�޸�*/
void modifyBooks(Library *library,int id,char *name,char *author) {
	BookClass *bookClass;
	bookClass = queryLibraryById(*library,id);
	priModifyBookClass(bookClass,name,author);
}
/*����*/
int borBooks(Library *library, int id, int amount) {
	BookClass *bookClass;
	bookClass = queryLibraryById(*library,id);
	if (bookClass) {
		priBor(bookClass, &amount);
	}
	else {
		amount = 0;
	}
	return amount;	//�����������������
}
/*����*/
void retBooks(Library *library, int id, int amount) {
	BookClass *bookClass;
	bookClass = queryLibraryById(*library,id);
	if (bookClass) {
		priRet(bookClass,amount);
	}
	else {	//δ�ҵ�ͼ��
		//���ɢ�б�����
	}
}