#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 1000
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include"MoudleAndControl.h"
int main() {
	system("title Library");
	system("color 03");
	int index;
	Library library = createLibrary();
	RecordSet recordSet = createRecordSet();
	ReaderSet readerSet = createReaderSet();
	char path[3][20] = {"library.txt","records.txt","readers.txt"};
	printf("�����ļ���....\n");
	load(path[0],path[1],path[2],&library,&readerSet,&recordSet);
	system("cls");
	printf("�����ļ��ɹ�\n");
	printf("ͼ���Ŀǰ����%d���飬����%d���飬����%d����\n",library.numOfBookClass,
		library.totalMemory,
		library.currentMemory);
	printf("1.��ѯ�����Ϣ\n");
	printf("2.����\n");
	printf("3.����\n");
	printf("4.�������֤��\n");
	printf("5.�޸Ķ�����Ϣ\n");
	printf("6.�ɱ����\n");
	printf("7.������\n");
	printf("8.����\n");
	printf("9.�˳�\n");
	printf("���������ֽ�����Ӧ���ܣ�");
	while (scanf("%d", &index) == 1) {
		if (index == 1) {	//�ۺϲ�ѯ����
			system("cls");
			BookClass *bookClasses[MAX_SIZE];
			char info[20];
			printf("������ͼ������ֻ������ߣ�");
			scanf("%s", info);
			int length = queryLibrary(library, bookClasses, info);
			//printf("%d\n",length);
			if (length == 0) {
				printf("�޴���\n");
			}
			else {
				printf("���\t����\t����\t�ܿ���\t������\n");
				for (int i = 0; i < length; i++) {
					printf("%d\t%s\t%s\t%d\t%d\n",
						bookClasses[i]->id,
						bookClasses[i]->name,
						bookClasses[i]->author,
						bookClasses[i]->totalMemory,
						bookClasses[i]->currentMemory);
				}
			}
		}
		if (index == 2) {
			int bookId, readerId, amount;
			printf("��������Ľ���֤�ţ�\n");
			scanf("%d", &readerId);
			if (searchReader(readerSet, readerId) == NULL) {
				printf("����֤�Ŵ���\n");
			}
			else {
				printf("����������Լ�������");
				scanf("%d %d", &bookId, &amount);
				amount = Borrow(&library, &readerSet, &recordSet, readerId, bookId, amount);
				printf("������� %d ����\n", amount);
			}
		}
		if (index == 3) {
			int bookId, readerId, amount;
			printf("��������Ľ���֤�š���ź�����\n");
			scanf("%d %d %d", &readerId, &bookId, &amount);
			if (searchReader(readerSet, readerId) == NULL) {
				printf("����֤�Ŵ���\n");
			}
			else {
				amount = Return(&library, &readerSet, &recordSet, readerId, bookId, amount);
				printf("�㻹�� %d ����\n", amount);
			}
		}
		if (index == 4) {
			printf("����������֣�");
			char name[20];
			scanf("%s", name);
			printf("��Ľ���֤��Ϊ��%d \n", addReader(&readerSet, name));
		}
		if (index == 5) {
			int readerId;
			char name[20];
			printf("��������Ľ���֤��\n");
			scanf("%d",&readerId);
			if (searchReader(readerSet, readerId) == NULL) {
				printf("����֤�Ŵ���\n");
			}
			else {
				printf("�������������\n");
				scanf("%s",name);
				printf("�޸ĳɹ�\n");
			}
		}
		if (index == 6) {	//�ɱ����
			system("cls");
			char name[20];
			char author[20];
			int amount;
			printf("������ͼ�����֡������Լ�����\n");
			scanf("%s %s %d",name,author,&amount);
			addBooks(&library,name,author,amount);
			//system("cls");
			printf("���ɹ�\n");
		} 
		if (index == 7) {	//������	
			int id;
			printf("����������ţ�");
			scanf("%d",&id);
			clearBooks(&library,id);
		}
		if (index == 8) {
		}
		if (index == 9) {
			save(path[0], path[1], path[2],library,readerSet,recordSet);
			exit(0);
		}
		//system("cls");
		printf("1.��ѯ�����Ϣ\n");
		printf("���������ֽ�����Ӧ���ܣ�");
	}
	getchar();
	return 0;
}


