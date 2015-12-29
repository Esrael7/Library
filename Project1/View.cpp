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
	system("cls");
	printf("->ͼ���Ŀǰ���� %d ���飬���� %d ���飬���� %d ����\n",
		library.numOfBookClass,
		library.totalMemory,
		library.currentMemory);
	printf("+------------------��ӭ����ͼ�����ϵͳ-------------------+\n"); 
	printf("|                                                         |\n");
	printf("|                        1.��ѯ                           |\n");
	printf("|                        2.����                           |\n");
	printf("|                        3.����                           |\n");
	printf("|                        4.�������֤                     |\n");
	printf("|                        5.�޸ĸ�����Ϣ                   |\n");
	printf("+---------------------------------------------------------+\n");
	printf("|                        6.�ɱ����                       |\n");
	printf("|                        7.������                       |\n");
	printf("|                        8.�鿴��¼                       |\n");
	printf("|                        9.�鿴����                       |\n");
	printf("|                        10.�˳�                          |\n");
	printf("+---------------------------------------------------------+\n");
	printf("|                  ������Ž����Ӧ����                   |\n");
	printf("+---------------------------------------------------------+\n");
	printf("->");
	while (scanf("%d", &index) == 1) {
		system("cls");
		if (index == 1) {	//�ۺϲ�ѯ����
			
			BookClass *bookClasses[MAX_SIZE];
			char info[20];
			printf("->������ͼ������ֻ������ߣ�\n->");
			scanf("%s", info);
			int length = queryLibrary(library, bookClasses, info);
			//printf("%d\n",length);
			if (length == 0) {
				system("cls");
				printf("->ͼ������޴���\n");
			}
			else {
				system("cls");
				printf("");
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
			printf("->��������Ľ���֤�ţ�\n->");
			scanf("%d", &readerId);
			system("cls");
			if (searchReader(readerSet, readerId) == NULL) {
				printf("->����֤�Ŵ���\n");
			}
			else {
				printf("->����������Լ�������\n->");
				scanf("%d %d", &bookId, &amount);
				amount = Borrow(&library, &readerSet, &recordSet, readerId, bookId, amount);
				system("cls");
				printf("->������� %d ���顣\n", amount);
			}
		}
		if (index == 3) {
			
			int bookId, readerId, amount;
			printf("->��������Ľ���֤�š���ź�������\n->");
			scanf("%d %d %d", &readerId, &bookId, &amount);
			system("cls");
			if (searchReader(readerSet, readerId) == NULL) {
				printf("->����֤�Ŵ���\n");
			}
			else {
				amount = Return(&library, &readerSet, &recordSet, readerId, bookId, amount);
				printf("->��黹�� %d ���顣\n", amount);
			}
		}
		if (index == 4) {
			
			printf("->����������֣�\n->");
			char name[20];
			scanf("%s", name);
			system("cls");
			printf("->��Ľ���֤��Ϊ��%d \n", addReader(&readerSet, name));
		}
		if (index == 5) {
			int readerId;
			char name[20];
			printf("->��������Ľ���֤�ţ�\n->");
			scanf("%d",&readerId);
			system("cls");
			if (searchReader(readerSet, readerId) == NULL) {
				printf("->����֤�Ŵ���\n");
			}
			else {
				printf("->�������������\n->");
				scanf("%s",name);
				alterReader(&readerSet,readerId,name);
				system("cls");
				printf("->�޸ĳɹ�\n");
			}
		}
		if (index == 6) {	//�ɱ����
			char name[20];
			char author[20];
			int amount;
			printf("->������ͼ�����֡������Լ�������->\n");
			scanf("%s %s %d",name,author,&amount);
			addBooks(&library,name,author,amount);
			system("cls");
			printf("->���ɹ�\n");
		} 
		if (index == 7) {	//������	
			int id;
			printf("->����������ţ�\n->");
			scanf("%d",&id);
			clearBooks(&library,id);
		}
		if (index == 8) {
			showRecord(recordSet);
		}
		if (index == 9) {
			showReaders(readerSet);
		}
		if (index == 10) {
			save(path[0], path[1], path[2], library, readerSet, recordSet);
			printf("->����ɹ���\n");
			system("cls");
			printf("->��л���ʹ�á�\n");
			printf("->by ����");
			Sleep(1000);
			exit(0);
		}
		int non;
		printf("->�����������ַ��������档\n->");
		scanf("%d",&non);
		system("cls");
		printf("->ͼ���Ŀǰ���� %d ���飬���� %d ���飬���� %d ����\n",
			library.numOfBookClass,
			library.totalMemory,
			library.currentMemory);
		printf("+---------------------------------------------------------+\n");
		printf("|                        1.��ѯ                           |\n");
		printf("|                        2.����                           |\n");
		printf("|                        3.����                           |\n");
		printf("|                        4.�������֤                     |\n");
		printf("|                        5.�޸ĸ�����Ϣ                   |\n");
		printf("+---------------------------------------------------------+\n");
		printf("|                        6.�ɱ����                       |\n");
		printf("|                        7.������                       |\n");
		printf("|                        8.�鿴��¼                       |\n");
		printf("|                        9.�鿴����                       |\n");
		printf("|                        10.�˳�                          |\n");
		printf("+---------------------------------------------------------+\n");
		printf("|                  ������Ž����Ӧ����                   |\n");
		printf("+---------------------------------------------------------+\n");
		printf("->");
	}
	
	return 0;
}


