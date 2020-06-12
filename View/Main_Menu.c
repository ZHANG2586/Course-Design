#include "./Main_Menu.h"
#include "Sale_UI.h"
#include "../Service/Account.h"
#include "Account_UI.h"
#include "../View/Play_UI.h"
#include "../View/Studio_UI.h"
#include <stdio.h>
#include "Schedule_UI.h"
#include <windows.h>

//ϵͳ���˵�
void Main_Menu(void) {
	char choice;
	do {
		printf("\n\n==================================================================================================\n");
		printf("**************************************** ��ԺƱ�����ϵͳ ****************************************\n\n");
		printf("                    [S] ��Ժ����.");
		printf("                            [P] ��Ŀ����.\n\n");
		printf("                    [T] ��Ʊ.");
		printf("                                [R] ��Ʊ.\n\n");
		printf("                    [Q] ��ѯ��Ŀ");
		printf("                             [N] Ʊ����ѯ.\n\n");
		printf("                    [W] ά����������.");
		printf("                        [A] �˻�����.\n\n");
		printf("                                          [E] �˳�.");
		printf("\n==================================================================================================\n\n\n");
		printf("����������ѡ��:");
		fflush(stdin);
		choice = getchar();
		system("cls");
		switch (choice) {
		case 'S':
		case 's':

		    if(gl_CurUser.type == USR_ADMIN)
                Studio_UI_MgtEntry();
            else
            {
                printf("����Ȩ���ʴ˹��ܣ�\n�밴��������أ�\n");
                getchar();
                getchar();
            }
			break;
        case 'P':
		case 'p':
            if(gl_CurUser.type == USR_ADMIN || gl_CurUser.type == USR_MANG)
                Play_UI_MgtEntry();
            else
            {
                printf("����Ȩ���ʴ˹��ܣ�\n�밴��������أ�\n");
                getchar();
                getchar();
            }
			break;
		case 'Q':
		case 'q':
            if(gl_CurUser.type == USR_ADMIN || gl_CurUser.type == USR_MANG || gl_CurUser.type == USR_CLERK)
                Queries_Menu();
            else
            {
                printf("����Ȩ���ʴ˹��ܣ�\n�밴��������أ�\n");
                getchar();
                getchar();
            }
			break;
		case 'T':
		case 't':
            if(gl_CurUser.type == USR_ADMIN || gl_CurUser.type == USR_CLERK)
                Sale_UI_MgtEntry();
            else
            {
                printf("����Ȩ���ʴ˹��ܣ�\n�밴��������أ�\n");
                getchar();
                getchar();
            }
			break;
		case 'R':
		case 'r':
            if(gl_CurUser.type == USR_ADMIN || gl_CurUser.type == USR_CLERK)
                Sale_UI_ReturnTicket();
            else
            {
                printf("����Ȩ���ʴ˹��ܣ�\n�밴��������أ�\n");
                getchar();
                getchar();
            }
			break;
		case 'N':
		case 'n':
            if(gl_CurUser.type == USR_ADMIN || gl_CurUser.type == USR_MANG || gl_CurUser.type == USR_CLERK)
                SalesAnalysis_UI_MgtEntry();
            else
            {
                printf("����Ȩ���ʴ˹��ܣ�\n�밴��������أ�\n");
                getchar();
                getchar();
            }
			break;
        case 'W':
		case 'w':
		    if(gl_CurUser.type == USR_ADMIN || gl_CurUser.type == USR_MANG || gl_CurUser.type == USR_CLERK)
                MaiAccount_UI_MgtEntry();
            else
            {
                printf("����Ȩ���ʴ˹��ܣ�\n�밴��������أ�\n");
                getchar();
                getchar();
            }
            break;
		case 'A':
		case 'a':
		    if(gl_CurUser.type == USR_ADMIN)
                Account_UI_MgtEntry();
            else
            {
                printf("����Ȩ���ʴ˹��ܣ�\n�밴��������أ�\n");
                getchar();
                getchar();
            }
			break;
		}
	} while ('E' != choice && 'e' != choice);
}

void hello(){
	printf("                               ---  ��  ӭ  ��  ��  Ʊ  ��  ��  ��  ϵ  ͳ  ---\n");
	system("color 0E");
	char s[104];
	memset(s,' ',101);
	s [0] = '[';
	s[101] = ']';
	s[102] = '\0';
	printf("\n\n\n\n");
	for(int i = 1;i < 101;i++)
	{

		s[i] = '=';
		printf("%s�Ѽ���%d%%]\r",s,i);
		fflush(stdout);
		Sleep(20);
	}
}

