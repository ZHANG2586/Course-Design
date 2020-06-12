#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <io.h>
#include "./View/Main_Menu.h"
#include "./View/Account_UI.h"
int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    Account_Srv_InitSys();
    if(!SysLogin()) {
		printf("\n�Բ�������Ȩ��¼��ϵͳ�밴������˳�......\n");
		getchar();
		exit(0);
    }
    system("cls");
    hello();
    Main_Menu();
    return EXIT_SUCCESS;
}
