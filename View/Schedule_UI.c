#include "../View/Schedule_UI.h"
#include "../View/Seat_UI.h"
#include "../View/Ticket_UI.h"

#include "../Common/List.h"

#include "../Service/Schedule.h"
#include "../Service/Studio.h"
#include "../Service/Play.h"
#include "../Service/Schedule.h"
#include "../Service/Seat.h"
#include "../Service/Ticket.h"

#include "../Persistence/Studio_Persist.h"
#include "../Persistence/Play_Persist.h"

static const int SCHEDULE_PAGE_SIZE = 5;

#include <stdio.h>


//��ʶ�� ��TTMS_SCU_Schedule_UI_MgtEnt
//��������:Schedule_UI_MgtEntry
//�������� ����ʾ��ID��Ϊplay_id�ľ�Ŀ������������ݳ��ƻ������ṩ��ɾ���ݳ��ƻ����ܡ�
void Schedule_UI_MgtEntry(int play_id)
{
    int i, id;
	char choice;

    schedule_t *temp;
	schedule_list_t head;
	schedule_node_t *pos;
	Pagination_t paging;
	temp = (schedule_t*)malloc(sizeof(schedule_t));

	List_Init(head, schedule_node_t);
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	//��������
	paging.totalRecords = Schedule_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

    //�ж������ݳ��ƻ��еľ�ĿID�У��Ƿ��д���������ID
    //���������ʾ�ݳ��ƻ�
    //�������û����þ�Ŀ��ص��ݳ��ƻ�


	do {
		printf(
				"\n=================================================================================================\n");
		printf(
				"**************************************** �� �� �� �� �� �� **************************************\n\n");
		printf("%5s  %10s  %10s  %10s  %10s  %8s\n\n", "�ݳ��ƻ����", "��ӳ��Ŀ���", "�ݳ������",
				"��ӳ����", "��ӳʱ��" , "��λ��");
		printf( "-------------------------------------------------------------------------------------------------\n");
		//��ʾ����
		Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i){
		    if(pos->data.play_id == play_id){
                printf("%5d  %10d  %10d ", pos->data.id,pos->data.play_id,pos->data.studio_id);
                printf("%12.4d/%.2d/%.2d  ",pos->data.date.year,pos->data.date.month,pos->data.date.day);
                printf("%8.2d:%.2d:%.2d  ",pos->data.time.hour,pos->data.time.minute,pos->data.time.second);
                printf("%d\n\n",pos->data.seat_count);
		    }
		}
		printf("~~~~~~~~~~~~~~~~~~~~~~~ ��ҳ��:%2d ~~~~~~~~~~~~~~~~~~~~~~~~~~ ��ǰҳ %2d/%2d ~~~~~~~~~~~~~~~~~~~~~~~\n\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("*************************************************************************************************\n");
		printf("\n   P  ��һҳ  |  N  ��һҳ  |  A  ����  |  D  ɾ��  |  U  �޸�  |  T  ��ѯ�ݳ�Ʊ  |  R  �����ϲ�\n");
		printf("\n=================================================================================================\n");
		printf("����������ѡ��:");
		fflush(stdin);
		scanf("%c", &choice);
		getchar();

		switch (choice) {
		case 'a':
		case 'A':
		    if(head == NULL)
                    printf("head== NULL\n");
			if (Schedule_UI_Add(play_id)) //�����ӳɹ����������һҳ��ʾ
			{
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, schedule_node_t);
			}
            else{
                printf("����ʧ��!\n");
            }
            break;
		case 'd':
		case 'D':
			printf("�������ݳ��ƻ����:");
			scanf("%d", &id);
            while(!Schedule_Srv_FetchByID(id , temp))
            {
                printf("�����ڸ��ݳ��ƻ�,����������:\n");
                scanf("%d",&id);
            }
			if (Schedule_UI_Delete(id)) {	    //������������
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				List_Paging(head, paging, schedule_node_t);
			}
			break;
		case 'u':
		case 'U':
			printf("�������ݳ��ƻ����:");
			scanf("%d", &id);
			while(!Schedule_Srv_FetchByID(id , temp))
            {
                printf("�����ڸ��ݳ��ƻ�,����������:\n");
                scanf("%d",&id);
            }
			if (Schedule_UI_Modify(id)) {	        //������������
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				List_Paging(head, paging, schedule_node_t);
			}
			break;
		case 't':
		case 'T':
			printf("�������ݳ��ƻ����:");
			scanf("%d", &id);
			system("cls");
			while(!Schedule_Srv_FetchByID(id , temp))
            {
                printf("�����ڸ��ݳ��ƻ�,����������:\n");
                scanf("%d",&id);
            }
			if(Schedule_Srv_FetchByID(id , temp))
			{
			    Ticket_UI_MgtEntry(id);
			    paging.totalRecords = Schedule_Srv_FetchAll(head);
                List_Paging(head, paging, schedule_node_t);
			}
			else
            {
                printf("û���ҵ���Ӧ���ݳ��ƻ�!\n�밴 [Enter] ����!\n");
                getchar();
                getchar();
            }
			break;
		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
	system("cls");
	//�ͷ������ռ�
	List_Destroy(head, schedule_node_t);
}


//��ʶ�� ��TTMS_SCU_Schedule_UI_Add
//�������ƣ�Schedule_UI_Add
//�������ܣ����ռ���������ݳ��ƻ���Ϣ��ͨ������ҵ���߼��㺯���������ݳ��ƻ���
int Schedule_UI_Add(int play_id)
{
    schedule_t rec;
    schedule_list_t new_schedule;

    play_t *new_play;
    studio_t *new_studio;

    new_studio = (studio_t *)malloc(sizeof(studio_t));
    new_play =  ( play_t *)malloc(sizeof(play_t));
   // new_schedule = (schedule_list_t)malloc(sizeof(schedule_node_t));
    //new_schedule = (schedule_list_t)malloc(sizeof(schedule_node_t));

	int newRecCount = 0;
	char choice;

	do {
		printf("\n=================================================================================================\n");
		printf("************************************  �� �� �� �� �� �� �� ��  ***********************************\n");
		printf("--------------------------------------------------------------------------------------------------\n\n\n");
		//fflush(stdin);

        //��ĿID��ֵ���ݳ��ƻ����Ŀ��ID
		rec.play_id = play_id;

		if(Play_Srv_FetchByID(play_id, new_play) && !Schedule_Srv_FetchByPlay( new_schedule , play_id))
        printf("������⣬����Ϊ�þ�Ŀ�����ݳ��ƻ�!\n");

        printf("�������ݳ������:\n");
        scanf("%d",&rec.studio_id);
        Studio_Srv_FetchByID( rec.studio_id , new_studio);
        while(!Studio_Srv_FetchByID( rec.studio_id , new_studio))
        {
            printf("�����ڸ��ݳ���!\n");
            printf("����������:\n");
            scanf("%d",&rec.studio_id);
        }

        if(Play_Srv_FetchByID( play_id , new_play))         //�������ž�Ŀ����ӳ���ڸ�ֵ���ݳ��ƻ�������
        {
           rec.date.year=new_play->start_date.year;
           rec.date.month=new_play->start_date.month;
           rec.date.day=new_play->start_date.day;
        }


        printf("�������ӳʱ��(*:*:*):\n");
        scanf("%d:%d:%d",&rec.time.hour,&rec.time.minute,&rec.time.second);

        rec.seat_count = new_studio->seatsCount;


        printf("\n\n�µ��ݳ��ƻ���������:\n");
        printf("�ݳ���ID : %d\n",rec.studio_id);
        printf("��ĿID : %d\n",rec.play_id);
        printf("��ӳ����: %d/%d/%d\n",rec.date.year,rec.date.month,rec.date.day);
        printf("��ӳʱ��: %d:%d:%d\n",rec.time.hour,rec.time.minute,rec.time.second);
        printf("��λ��:%d\n",rec.seat_count);
		printf("=================================================================================================\n");

		if (Schedule_Srv_Add(&rec)) {
			newRecCount += 1;
			printf("�µ��ݳ��ƻ����ӳɹ�!\n");
		} else
			printf("�µ��ݳ��ƻ�����ʧ��!\n");
        printf("\n\n\n");
		printf("-------------------------------------------------------------------------------------------------\n");
		printf("A ��������, R ����:");
		fflush(stdin);
		scanf("%c", &choice);
		getchar();
	} while ('a' == choice || 'A' == choice);
	free(new_studio);
	free(new_play);
	free(new_schedule);

	return newRecCount;

}



//��ʶ�� ��TTMS_SCU_Schedule_UI_Mod
//�������� �������ݳ��ƻ���IDֵ������ҵ���߼��㺯���޸��ݳ��ƻ����ݡ�
int Schedule_UI_Modify(int id)
{
    schedule_t rec;

    studio_t *change_studio;
    play_t *change_play;
    change_studio = (studio_t *)malloc(sizeof(studio_t));
    change_play = (play_t *)malloc(sizeof(play_t));

	int rtn = 0;
    int rmn=0;

    //����ID��ȡ�ݳ��ƻ�
	Schedule_Srv_FetchByID(id, &rec);

    printf("\n\n��ǰ���ݳ��ƻ�\n");
    printf("�ݳ���ID : %d\n",rec.studio_id);
    printf("��ĿID : %d\n",rec.play_id);
    printf("��ӳ����: %d/%d/%d\n",rec.date.year,rec.date.month,rec.date.day);
    printf("��ӳʱ��: %d:%d:%d\n",rec.time.hour,rec.time.minute,rec.time.second);
    printf("��λ��:%d\n",rec.seat_count);
    printf("�밴 [Enter] ����!\n");
	getchar();
	getchar();

	printf("\n=================================================================================================\n");
	printf("************************************  �� �� �� �� �� �� �� Ϣ  **********************************\n");
	printf("-------------------------------------------------------------------------------------------------\n\n\n");
	printf("��Ŀ���:%d\n", rec.play_id);
	fflush(stdin);

    printf("�����µ��ݳ����ı��:\n");
    scanf("%d",&rec.studio_id);
    while(!Studio_Srv_FetchByID( rec.studio_id , change_studio))
    {
        printf("�����ڸ��ݳ���,����������:\n");
        scanf("%d",&rec.studio_id);
    }

    //�޸ľ�Ŀ��ӳ���ڣ�����ֵ���ݳ��ƻ�
    Play_Srv_FetchByID( rec.play_id , change_play);

    printf("�������µ���ӳ����:\n");
    scanf("%d/%d/%d",&change_play->start_date.year,&change_play->start_date.month,&change_play->start_date.day);
    printf("�������µ���������:\n");
    scanf("%d/%d/%d",&change_play->offline_date.year,&change_play->offline_date.month,&change_play->offline_date.day);
    rec.date.year = change_play->start_date.year;
    rec.date.month = change_play->start_date.month;
    rec.date.day = change_play->start_date.day;

    //�ı��ݳ��ƻ���ͬʱ�ı��Ŀ�����ӳ����
    if (Play_Srv_Modify(change_play)) {
        rmn = 1;
		printf("�þ�Ŀ�޸ĳɹ�!\n�밴 [Enter] ����!\n");
	}
	else{
		printf("�þ�Ŀ�޸�ʧ��!\n�밴 [Enter] ����!\n");
		return rmn;
	}

    rec.seat_count = change_studio->seatsCount;         //������λ
    printf("\n\n\n");
    printf("=================================================================================================\n");


	if (Schedule_Srv_Modify(&rec)) {
		rtn = 1;
		printf("���ݳ��ƻ��޸ĳɹ�!\n�밴 [Enter] ����!\n");
	}
	else{
		printf("���ݳ��ƻ��޸�ʧ��!\n�밴 [Enter] ����!\n");
		getchar();
	}
	fflush(stdin);
	getchar();
    printf("--------------------------------------------------------------------------------------------------\n");
	return rtn;
}


//��ʶ�� ����ʶ�� ��TTMS_SCU_Schedule_UI_Del;
//�������ܣ� ���ݲ����е��ݳ��ƻ�ID�ţ�ͨ������ҵ���߼��㺯��������ɾ���ݳ��ƻ���
int Schedule_UI_Delete(int id)
{
    int rtn = 0;

	if (Schedule_Srv_DeleteByID(id)) {
		printf("���ݳ��ƻ�ɾ���ɹ�!\n�밴 [Enter] ����!\n");
		rtn = 1;
	} else {
		printf("���ݳ��ƻ�ɾ��ʧ��!\n�밴 [Enter] ����!\n");
	}

	getchar();
	return rtn;
}


/*
��ʶ����TTMS_SCU_Schedule_UI_ListAll
�������ܣ����б���ʽ��ʾ���е��ݳ��ƻ����б��Ϸ���ʾ��ͷ��Ϣ����ͷ�·���ʾ�������ݳ��ƻ��е�һҳ����Ϣ���б��·���ʾ��ѯ���ܡ�
����˵������
�� �� ֵ����
*/
void Schedule_UI_ListAll(void)
{
	int i;
	char choice;

	schedule_list_t head;
	schedule_node_t *p;

	Pagination_t paging;

	List_Init(head,schedule_node_t);

	paging.offset = 0;
	paging.pageSize =5;


	paging.totalRecords = Schedule_Srv_FetchAll(head);
	Paging_Locate_FirstPage( head , paging );

	do{
		printf("\n=================================================================================================\n");
		printf("                                        �� �� �� �� �� ��\n");
		printf("\n-------------------------------------------------------------------------------------------------\n\n\n");
		printf("\t  %5s%5s%8s%10s%10s%10s\n", "�ƻ�",   "��Ŀ", "�ݳ���","��ӳ����","��ӳʱ��","��λ��");


        Paging_ViewPage_ForEach(head, paging, schedule_node_t, p, i)
        {
		printf("\t   %2d   %2d\t%2d",p->data.id,p->data.play_id,p->data.studio_id);
		printf(" %4d-%02d-%02d ",p->data.date.year, p->data.date.month, p->data.date.day);
		printf("%2d:%02d:%02d ",p->data.time.hour,p->data.time.minute,p->data.time.second);
		printf(" %5d\n",p->data.seat_count);
		}


		printf("\n~~~~~~~~~~~~~~~~~~~~~~ ��ҳ��:%2d ~~~~~~~~~~~~~~~~~~~~~~~~~ ��ǰҳ %2d/%2d ~~~~~~~~~~~~~~~~~~~~~~\n\n\n",
				paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
		printf("\n*************************************************************************************************" );
		printf("\n            [P]��ҳ          |           [N]��ҳ          |           [R]����\n\n");
		printf("\n=================================================================================================\n");
		printf("��ѡ��:");

		choice = getchar();

		switch(choice){
		case 'p':
		case 'P':
            if (!Pageing_IsFirstPage(paging)) {
                Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
            }
            break;
        case 'n':
        case 'N':
            if (!Pageing_IsLastPage(paging)) {
                Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
            }
            break;
        }
    }while (choice != 'r' && choice != 'R');
    //�ͷ������ռ�
    List_Destroy(head, schedule_node_t);
}




/*
��ʶ����TTMS_SCU_Schedule_UI_Query
�������ܣ���ʾ������������ݳ��ƻ���Ϣ��
����˵����play_name �ַ���ָ�룬��ʾ����ȡ�ݳ��ƻ��ľ�Ŀ���ơ�
�� �� ֵ�����Σ���ȡ���ݳ��ƻ�������
*/
int Schedule_UI_Query(char play_name[])
{
    play_list_t list_p;
    schedule_list_t list_s;

    list_p = (play_list_t)malloc(sizeof(play_node_t));
    list_s = (schedule_list_t)malloc(sizeof(schedule_node_t));

    if(!Play_Srv_FetchByName(list_p,play_name))
    {
        printf("δ�ҵ���ӰƬ\n");
        getchar();
        return 0;
    }

    if(!Schedule_Srv_FetchByPlay(list_s , list_p->data.id))
    {
        printf("δ�ҵ���Ӧ���ݳ��ƻ�!\n");
        getchar();
        return 0;
    }
    printf("\n=================================================================================================\n");
    printf("************************************** �� �� �� �� �� �� ****************************************\n\n");
    printf("%5s  %10s  %10s  %10s  %10s  %8s\n\n", "�ݳ��ƻ����", "��ӳ��Ŀ���", "�ݳ������",
				"��ӳ����", "��ӳʱ��" , "��λ��");
    printf("-------------------------------------------------------------------------------------------------\n\n\n");
    printf("%5d  %10d  %10d ", list_s->data.id,list_s->data.play_id,list_s->data.studio_id);
    printf("%12.4d/%.2d/%.2d  ",list_s->data.date.year,list_s->data.date.month,list_s->data.date.day);
    printf("%8.2d:%.2d:%.2d  ",list_s->data.time.hour,list_s->data.time.minute,list_s->data.time.second);
    printf("%d\n\n\n",list_s->data.seat_count);
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("\n=================================================================================================\n");
    free(list_p);
    free(list_s);
    return 1;
}
 void Queries_Menu() {
    int i;
	char choice;

    schedule_t *temp;
    play_t * play_temp;
    studio_t * studio_temp;
	schedule_list_t head;
	schedule_node_t *pos;

	Pagination_t paging;
	temp = (schedule_t*)malloc(sizeof(schedule_t));
    play_temp = (play_t * )malloc(sizeof(play_t));
    studio_temp = (studio_t *)malloc(sizeof(studio_t));

	List_Init(head, schedule_node_t);
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	//��������
	paging.totalRecords = Schedule_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

    //�ж������ݳ��ƻ��еľ�ĿID�У��Ƿ��д���������ID
    //���������ʾ�ݳ��ƻ�
    //�������û����þ�Ŀ��ص��ݳ��ƻ�


	do {
		printf(
				"\n=================================================================================================\n");
		printf(
				"***************************************** �� ʾ �� Ŀ *******************************************\n\n");
		printf( "%5s  %10s  %10s  %10s  %10s  %8s\n\n", "��ӳ��Ŀ����", "�ݳ�������",
				"��ӳ����", "��ӳʱ��" , "��������", "�۸�");
		printf( "-------------------------------------------------------------------------------------------------\n\n\n");
		//��ʾ����
		Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i){
            Play_Perst_SelectByID( pos->data.play_id , play_temp);
            Studio_Perst_SelectByID(pos->data.studio_id, studio_temp );

            printf("%5s ",play_temp->name);
            printf("%12s ",studio_temp->name);
            printf("%10.4d/%.2d/%.2d  ",pos->data.date.year,pos->data.date.month,pos->data.date.day);
            printf("%6.2d:%.2d:%.2d  ",pos->data.time.hour,pos->data.time.minute,pos->data.time.second);
            printf("%6.4d/%.2d/%.2d  ",play_temp->offline_date.year,play_temp->offline_date.month,play_temp->offline_date.day);
            printf("%d\n\n\n",play_temp->price);

		}
		printf("\n~~~~~~~~~~~~~~~~~~~~~~ ��ҳ��:%2d ~~~~~~~~~~~~~~~~~~~~~~~~ ��ǰҳ %2d/%2d ~~~~~~~~~~~~~~~~~~~~~~~\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("*************************************************************************************************\n");
		printf("          P    |   ��һҳ    |    N    ��һҳ    |     R    �����ϲ�");
		printf("\n=================================================================================================\n");
		printf("����������ѡ��:");
		fflush(stdin);
		scanf("%c", &choice);
		getchar();

		switch (choice) {
		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
	system("cls");
	free(temp);
	free(play_temp);
	free(studio_temp);
	//�ͷ������ռ�
	List_Destroy(head, schedule_node_t);

 }


