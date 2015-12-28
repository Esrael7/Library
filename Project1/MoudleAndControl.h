#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 1000
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<Windows.h>
/*MOUDLE*/
//-----------------------------ͼ���-------------------------
typedef struct PriBookClass {
	int id;	//���
	char name[20];
	char author[20];
	int totalMemory;
	int currentMemory;
	struct PriBookClass *next;
}BookClass;
typedef struct PriLibrary {
	int totalMemory;
	int currentMemory;
	int numOfBookClass;	
	BookClass *headBookClass;	
}Library;
//-----------------------------�������-----------------------
typedef struct PriBorBook {
	int id;
	int amount;
}BorBook;
typedef struct PriBorBookSet {
	BorBook *borBooks[MAX_SIZE];
	int amount;
}BorBookSet;
//-----------------------------������Ϣ-----------------------
typedef struct PriReader {
	int id;
	char name[20];
	BorBookSet borBookSet;
	struct PriReader *next;
}Reader;
typedef struct PriReaderSet {
	int amount;
	Reader *headReader;
}ReaderSet;
//-----------------------------�軹��¼-----------------------
typedef struct PriRecord {
	int readerId;
	int bookId;
	int amount;	//ͼ������
	char time[20];	//����ʱ��
	char limitedTime[20];	//�黹����
	int action;
	struct PriRecord *next;
}Record;
typedef struct PriRecordSet {
	int amount;	//��¼����
	Record *headRecord;	//ͷ�ڵ�
}RecordSet;
//-----------------------------Id������-----------------------
typedef struct PriSearchListById {
	int id;
	BookClass *bookClass;
}SearchIdNode;
typedef struct PriSearchListByIdSet {
	SearchIdNode searchId[MAX_SIZE];
	int amount;
}SearchIdList;
//-----------------------------�ۺϼ�����---------------------

/*Control*/
//-----------------------------������Ϣ-----------------------
/*���������б�*/
ReaderSet createReaderSet() {
	ReaderSet readerSet;
	readerSet.amount = 0;
	readerSet.headReader = NULL;
	return readerSet;
}
/*ע��,���ض���id*/
int addReader(ReaderSet *readerSet,char *name) {
	Reader *reader;
	reader = (Reader *)malloc(sizeof(Reader));
	reader->id = readerSet->amount;
	strcpy(reader->name,name);
	reader->borBookSet.amount = 0;
	reader->next = readerSet->headReader;
	readerSet->headReader = reader;
	readerSet->amount++;
	return readerSet->amount - 1;
}
/*����id���Ҷ���*/
Reader *searchReader(ReaderSet readerSet, int id) {
	Reader *reader = NULL;
	while (readerSet.headReader) {
		if (readerSet.headReader->id == id) {
			reader = readerSet.headReader;
		}
		readerSet.headReader = readerSet.headReader->next;
	}
	return reader;
}
/*�޸Ķ�������*/
void alterReader(ReaderSet *readerSet, int id, char *name) {
	Reader *reader;
	reader = searchReader(*readerSet,id);
	if (reader) {
		strcpy(reader->name,name);
	}
	else {
		printf("δ�ҵ���id\n");
	}
}
/*Ϊ������������鼮��������*/
int addBorBooks(ReaderSet *readerSet,int readerId,int bookId,int amount) {
	Reader *reader;
	BorBook *borBook;
	reader = searchReader(*readerSet,readerId);
	if (reader) {
		borBook = searchBorBook(reader->borBookSet,bookId);
		if (borBook) {	//�Ѿ����Ȿ��
			borBook->amount += amount;
		}
		else {	//û���Ȿ��
			if (!addNewBorBook(&(reader->borBookSet),bookId,amount)) {
				amount = 0;
			}
		}
	}
	return amount;
}
/*�Ӹ������ȡ�飬������*/
int deteleBorBook(ReaderSet *readerSet, int readerId, int bookId, int amount) {
	Reader *reader;
	BorBook *borBook;
	reader = searchReader(*readerSet, readerId);
	if (reader) {
		borBook = searchBorBook(reader->borBookSet, bookId);
		if (borBook) {
			amount = amount > borBook->amount ? borBook->amount : amount;	//�������鳬������
			borBook->amount -= amount;
		}
	}
	return amount;
}
//-----------------------------�軹��¼-----------------------
/*������¼��*/
RecordSet createRecordSet() {
	RecordSet recordSet;
	recordSet.amount = 0;
	recordSet.headRecord = NULL;
	return recordSet;
}
/*��Ӽ�¼*/
void addRecord(RecordSet *recordSet,int readerId,int bookId,int amount,int action) {
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
	t += 2592000;
	timeinfo = localtime(&t);
	strcpy(record->time,time);
	strcpy(record->limitedTime, asctime(timeinfo));
	record->next = recordSet->headRecord;
	recordSet->headRecord = record;
	recordSet->amount++;
}
//-----------------------------�������-----------------------
/*���Ҹ��������鼮*/
BorBook *searchBorBook(BorBookSet borBookSet,int id) {
	BorBook *borBook = NULL;
	for (int i = 0; i < borBookSet.amount; i++) {
		if (id == borBookSet.borBooks[i]->id) {
			borBook = borBookSet.borBooks[i];
		}
	}
	return borBook;
}
/*�������������鼮*/
int addNewBorBook(BorBookSet *borBookSet, int id, int amount) {
	if (borBookSet->amount + 1 == MAX_SIZE) {
		return 0;
	}
	else {
		BorBook *borBook = (BorBook *)malloc(sizeof(BorBook));
		borBook->amount = amount;
		borBook->id = id;
		borBookSet->borBooks[borBookSet->amount] = borBook;
		borBookSet->amount++;
		return 1;
	}
}
//-----------------------------ID������-----------------------
SearchIdList CreateSearchIdList(Library library) {
	SearchIdList searchIdList;
	int i = 0;
	searchIdList.amount = library.numOfBookClass;
	while (library.headBookClass) {
		searchIdList.searchId[i].id = library.headBookClass->id;
		searchIdList.searchId[i].bookClass = library.headBookClass;
		i++;
	}
	return searchIdList;
}
/*ͨ��Id��ѯ*/
BookClass *searchById(SearchIdList searchIdList, int id) {
	BookClass *bookClass = NULL;
	for (int i = 0; i < searchIdList.amount; i++) {
		if (id == searchIdList.searchId[i].id) {
			bookClass = searchIdList.searchId[i].bookClass;
			break;
		}
	}
	return bookClass;
}
//-----------------------------ͼ���-------------------------
/*����*/
Library createLibrary() {
	Library library;
	library.currentMemory = 0;
	library.totalMemory = 0;
	library.numOfBookClass = 0;
	library.headBookClass = NULL;
	return library;
}
/*�ۺϲ�ѯ*/

/*ID��ѯ*/
BookClass *queryLibraryById(Library library, int id) {
	BookClass *bookClass;
	SearchIdList searchIdList = CreateSearchIdList(library);
	bookClass = searchById(searchIdList, id);
	return bookClass;
}
/*�ɱ����*/
void addBooks(Library *library, char *name, char *author, int amount) {
	BookClass *bookClass = NULL;
	while (library->headBookClass) {
		if (strcmp(name, library->headBookClass->name) && strcmp(author, library->headBookClass->author)) {
			bookClass = library->headBookClass;
			break;
		}
		library->headBookClass = library->headBookClass->next;
	}
	if (bookClass) {
		bookClass->totalMemory += amount;
		bookClass->currentMemory += amount;
	}
	else {
		bookClass = (BookClass*)malloc(sizeof(BookClass));
		strcpy(bookClass->name, name);
		strcpy(bookClass->author, author);
		bookClass->currentMemory = amount;
		bookClass->totalMemory = amount;
		if (library->headBookClass) {
			bookClass->id = library->headBookClass->id + 1;
		}
		else {
			bookClass->id = 0;
		}
		bookClass->next = library->headBookClass;
		library->headBookClass = bookClass;
		library->numOfBookClass++;
	}
	library->totalMemory += amount;
	library->currentMemory += amount;
}
/*��������*/
void clearBooks(Library *library, int id) {
	BookClass *bookClass;
	BookClass *temp;
	bookClass = queryLibraryById(*library, id);
	if (bookClass) {
		library->numOfBookClass--;
		library->totalMemory -= bookClass->totalMemory;
		library->currentMemory -= bookClass->currentMemory;
		temp = bookClass;
		bookClass = bookClass->next;
		free(temp);
	}
}
/*����*/
int borrowBooks(Library *library, int id, int amount) {
	BookClass *bookClass;
	bookClass = queryLibraryById(*library, id);
	if (bookClass) {
		amount = amount > bookClass->currentMemory ? bookClass->currentMemory : amount;
		bookClass->currentMemory -= amount;
		library->currentMemory -= amount;
	}
	else {
		amount = 0;
	}
	return amount;
}
/*����*/
int returnBooks(Library *library, int id, int amount) {
	BookClass *bookClass = queryLibraryById(*library, id);
	if (bookClass) {
		bookClass->currentMemory += amount;
		library->currentMemory += amount;
	}
	else {
		amount = 0;
	}
	return amount;
}
//-----------------------------����--------------------------
/*���飬���ؽ������*/
int Borrow(Library *library, ReaderSet *readerSet, RecordSet *recordSet, int readerId, int bookId, int amount) {
	amount = borrowBooks(library, bookId, amount);	//��ͼ��ݽ���
	if (amount) {
		int temp = amount;
		amount = addBorBooks(readerSet, readerId, bookId, amount);		//���˲ֿ������鼮
		if (amount) {
			addRecord(recordSet, readerId, bookId, amount, 1);
		}
		else {	//���˲ֿ��޷�����鼮�����鷵�زֿ�
			returnBooks(library, bookId, temp);
		}
	}
	return 0;
}
//-----------------------------����--------------------------
/*���飬���ػ���ȥ������*/
int Return(Library *library, ReaderSet *readerSet, RecordSet *recordSet, int readerId, int bookId, int amount) {
	amount = deteleBorBook(readerSet, readerId, bookId, amount);	//�Ӹ���������Ƴ��鼮
	if (amount) {
		int temp = amount;
		amount = returnBooks(library, bookId, amount);		//���鷵����ͼ���
		if (amount) {
			addRecord(recordSet,readerId,bookId,amount,0);
		}
		else {
			amount = addBorBooks(readerSet,readerId,bookId,temp);
		}
	}
	return amount;
}
/*�����ļ�*/
void load(char *file, Library *library, ReaderSet *readerSet, RecordSet *recordSet) {

}
/*����*/
void save(char *file, Library *library, ReaderSet *readerSet, RecordSet *recordSet) {

}