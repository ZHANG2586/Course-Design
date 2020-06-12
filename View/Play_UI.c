/*Description : Ʊ�����ҳ���ͷ�ļ�*/

#include "../View/Play_UI.h"
#include "Schedule_UI.h"

#include "../Common/List.h"

#include "../Service/Play.h"
#include "../Service/Schedule.h"



static const int PLAY_PAGE_SIZE = 5;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
��ʶ����TTMS_SCU_Studio_UI_MgtEnt
�������ܣ�������Ŀ���档
����˵�����ޡ�
�� �� ֵ���ޡ�
*/

void Play_UI_MgtEntry(void)
{
	int i, id;
	char choice;

   // schedule_list_t new_schedule;

	play_list_t head;
	play_node_t *pos;
	Pagination_t paging;

	List_Init(head, play_node_t);
	paging.offset = 0;
	paging.pageSize = PLAY_PAGE_SIZE;

	paging.totalRecords = Play_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
	do{
			printf("\n==================================================================================================\n");
			printf("***************************************** �� Ŀ �� �� ********************************************\n\n\n");
			printf("%4s %10s %10s %10s %10s %14s %8s\n\n\n", "��Ŀ���", "��Ŀ����",
							"��Ʒ����","��Ŀʱ��","��ӳ����","��������","Ʊ��");
			printf("--------------------------------------------------------------------------------------------------\n\n\n");
			//
			Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i){
				printf("%4d %10s %10s %10d ", pos->data.id,
						pos->data.name, pos->data.area, pos->data.duration);
				printf("%10.4d/%.2d/%.2d  %8.4d/%.2d/%.2d  %4d\n\n\n",pos->data.start_date.year,pos->data.start_date.month,pos->data.start_date.day,pos->data.offline_date.year,pos->data.offline_date.month,pos->data.offline_date.day,pos->data.price);
			}
			printf("~~~~~~~~~~~~~~~~~~~~~~~~ ��ҳ��:%2d ~~~~~~~~~~~~~~~~~~~~~~~~~~~ ��ǰҳ %2d/%2d ~~~~~~~~~~~~~~~~~~~~~~\n\n",
					paging.totalRecords, Pageing_CurPage(paging),
					Pageing_TotalPages(paging));
			printf("**************************************************************************************************\n");
			printf("P  ��һҳ  |  N ��һҳ  |  A  ����  |  D  ɾ��  |  U  �޸�  |  S  ��ѯ��Ŀ�ݳ��ƻ�  |  R  �����ϲ�");
			printf("\n==================================================================================================\n");
			printf("����������ѡ��:");
			fflush(stdin);
			scanf("%c", &choice);
			getchar();

			fflush(stdin);
			switch (choice) {
			case 's':
			case 'S':
				printf("�������Ŀ���:");
				scanf("%d", &id);
				system("cls");
				 while(!Play_Srv_FetchByID( id , &head->data))
                {
                    printf("�����ڸþ�Ŀ,����������:\n");
                    scanf("%d",&id);
                }

                Schedule_UI_MgtEntry(id);
                paging.totalRecords = Play_Srv_FetchAll(head);
                List_Paging(head, paging, play_node_t);
				break;
			case 'a':
			case 'A':
				if (Play_UI_Add()) 				//���Ӿ�Ŀ
				{
					paging.totalRecords = Play_Srv_FetchAll(head);
					Paging_Locate_LastPage(head, paging, play_node_t);
				}
				break;
			case 'd':
			case 'D':
				printf("�������Ŀ���:");
				scanf("%d", &id);
				if (Play_UI_Delete(id)) 		//ɾ����Ŀ
				{
					paging.totalRecords = Play_Srv_FetchAll(head);
					List_Paging(head, paging, play_node_t);
				}
				break;
			case 'u':
			case 'U':
				printf("�������Ŀ���:");
				scanf("%d", &id);
				if (Play_UI_Modify(id)) 		//�޸ľ�Ŀ
				{
					paging.totalRecords = Play_Srv_FetchAll(head);
					List_Paging(head, paging, play_node_t);
				}
				break;
			case 'p':
			case 'P':
				if (!Pageing_IsFirstPage(paging)) 	//��һҳ
				{
					Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
				}
				break;
			case 'n':
			case 'N':
				if (!Pageing_IsLastPage(paging)) 	//��һҳ
				{
					Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
				}
				break;
			}

		} while (choice != 'r' && choice != 'R');
		system("cls");
		//�ͷ�����
		List_Destroy(head, play_node_t);
}

/*
��ʶ����TTMS_SCU_Studio_UI_Add
�������ܣ������¾�Ŀ���溯����
����˵������
�� �� ֵ�����Σ����� 1 ��ʾ�����¾�Ŀ�ɹ�����1 ���������¾�Ŀʧ��
*/
int Play_UI_Add(void)
{
	play_t temp;
	int k;

	char choice;
	int newCount=0;
	do {
		printf("\n==================================================================================================\n");
		printf("*************************************  �� �� �� �� �� Ŀ  ****************************************\n");
		printf("--------------------------------------------------------------------------------------------------\n\n\n");
		printf("��Ŀ����:\n");
		fflush(stdin);
//		gets(rec.name);
		scanf("%s",temp.name);
        /*while(strcmp(temp.name)>20)
        {
            printf("���볬��!����������");
            scanf("%s",temp.name);
        }*/
		printf("��Ŀ����:(1.��Ӱ  2.���  3.���ֻ�)\n");
		scanf("%d",&k);
        int r=(play_type_t)k;
		switch (r) {
			case 1: puts("movie"); break;
			case 2: puts("opera"); break;
			case 3: puts("concert"); break;
		}
		printf("��Ʒ����:\n");
		scanf("%s",temp.area);
		printf("��Ŀ�ּ�:(1.��ͯ 2.������ 3.����)\n");
        scanf("%d",&k);
        temp.rating=(play_rating_t)k;
		switch (temp.rating) {
			case 1: puts("Child"); break;
			case 2: puts("Teenage"); break;
			case 3: puts("Adult"); break;
		}
		printf("��Ŀʱ��:\n");
		scanf("%d",&temp.duration);
		printf("��ӳ����(****/**/**):\n");
		scanf("%d/%d/%d",&temp.start_date.year,&temp.start_date.month,&temp.start_date.day);
		printf("��������(****/**/**):\n");
		scanf("%d/%d/%d",&temp.offline_date.year,&temp.offline_date.month,&temp.offline_date.day);
		printf("Ʊ��:\n");
		scanf("%d",&temp.price);
		printf("\n\n\n");
		printf("==================================================================================================\n");

		if (Play_Srv_Add(&temp)) {
			newCount ++;
			printf("�µľ�Ŀ���ӳɹ�!\n");
		}
		else
			printf("�µľ�Ŀ����ʧ��!\n");
		printf("--------------------------------------------------------------------------------------------------\n");
		printf("A ��������, R ����:");
		getchar();
		fflush(stdin);
		scanf("%c", &choice);
	} while ('a' == choice || 'A' == choice);
	system("cls");
	return newCount;
}


/*
��ʶ����TTMS_SCU_Play_UI_Mod
�������ܣ������޸�ϵͳ���ִ��һ����Ŀ���ݡ�
����˵����idΪ���ͣ�����Ҫ�޸ĵľ�ĿID��
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ��޸��˾�Ŀ�ı�־��
*/
int Play_UI_Modify(int id)
{
	play_t rec;

	int rtn = 0;
    int k;

	/*Load record*/
	if (!Play_Srv_FetchByID(id, &rec)) {
		printf("���ݳ���������!\n�밴 [Enter] ����!\n");
		getchar();
		return 0;
	}

	printf("\n==================================================================================================\n");
	printf("***************************************  �� �� �� Ŀ �� Ϣ  **************************************\n");
	printf("--------------------------------------------------------------------------------------------------\n\n\n");
	printf("��Ŀ���:%d\n", rec.id);
	printf("�µľ�Ŀ����[��ǰ������:%s]:", rec.name);
	fflush(stdin);

//	gets(rec.name);
	scanf("%s",rec.name);

	printf("��Ŀ����:(1.��Ӱ  2.���  3.���ֻ�)\n");
	scanf("%d",&k);
	rec.type=(play_type_t)k;
	switch (rec.type) {
		case 1: puts("movie"); break;
		case 2: puts("opera"); break;
		case 3: puts("concert"); break;
	}
	printf("��Ʒ����:\n");
	scanf("%s",rec.area);
	printf("��Ŀ�ּ�:(1.��ͯ 2.������ 3.����)\n");
	scanf("%d",&k);
	int r=(play_rating_t)k;
	switch (r) {
		case 1: puts("Child"); break;
		case 2: puts("Teenage"); break;
		case 3: puts("Adult"); break;
	}
	printf("��Ŀʱ��:\n");
	scanf("%d",&rec.duration);
	printf("��ӳ����(****/**/**):\n");
	scanf("%d/%d/%d",&rec.start_date.year,&rec.start_date.month,&rec.start_date.day);
	printf("��������(****/**/**):\n");
	scanf("%d/%d/%d",&rec.offline_date.year,&rec.offline_date.month,&rec.offline_date.day);
	printf("Ʊ��:\n");
	scanf("%d",&rec.price);
	printf("\n\n\n");
	printf("--------------------------------------------------------------------------------------------------\n");

	if (Play_Srv_Modify(&rec)) {
		rtn = 1;
		printf("�þ�Ŀ�޸ĳɹ�!\n�밴 [Enter] ����!\n");
	}
	else
		printf("�þ�Ŀ�޸�ʧ��!\n�밴 [Enter] ����!\n");
	fflush(stdin);
	getchar();
	system("cls");
	return rtn;
}

/*
��ʶ����TTMS_SCU_Play_UI_Del
�������ܣ�����ɾ��ϵͳ���ִ��һ����Ŀ���ݡ�
����˵����idΪ���ͣ�����Ҫɾ�����ݳ���ID��
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ���˾�Ŀ�ı�־��
*/
int Play_UI_Delete(int id)
{
	int rtn = 0;

	if (Play_Srv_DeletByID(id)) {
		//ҵ���߼��㺯������ֵΪ��0����ʾɾ���ɹ�������ֵΪ 1 ��
		printf("�þ�Ŀɾ���ɹ�!\n�밴 [Enter] ����!\n");
		rtn = 1;
	}
	else {
		printf("�þ�Ŀɾ��ʧ��!\n�밴 [Enter] ����!\n");
	}

	getchar();
	return rtn;
}


/*
��ʶ����TTMS_SCU_Play_UI_Qry
�������ܣ���ѯ��Ŀ�ɹ�.
����˵����idΪ���ͣ���ʾ�����ҵľ�ĿID��
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ������˾�Ŀ�ı�־��
*/
int Play_UI_Query(int id)
{
	int rtn = 0;
	play_t rec;

	if(Play_Srv_FetchByID(id,&rec))
	{
	    printf("\n==================================================================================================\n");
        printf("*************************************** �� �� �� Ŀ �� �� ****************************************\n\n\n");
        printf("%4s %10s %10s %10s %10s %14s %8s\n\n", "��Ŀ���", "��Ŀ����",
                        "��Ʒ����","��Ŀʱ��","��ӳ����","��������","Ʊ��");
          printf("%4d %10s %10s %10d ", rec.id,
						rec.name,rec.area,rec.duration);
				printf("%10.4d/%.2d/%.2d  %8.4d/%.2d/%.2d  %4d\n\n\n",rec.start_date.year,rec.start_date.month,rec.start_date.day,
           rec.offline_date.year,rec.offline_date.month,rec.offline_date.day,rec.price);
        printf("--------------------------------------------------------------------------------------------------\n");
        printf("**************************************************************************************************\n");
        printf("\n==================================================================================================\n");
		printf("�þ�Ŀ��ѯ�ɹ�!\n�밴 [Enter] ����!\n");
		rtn=1;
	}
	else
		printf("�þ�Ŀ��ѯʧ��!\n�밴 [Enter] ����!\n");

    getchar();
	getchar();
	system("cls");
	return rtn;
}
