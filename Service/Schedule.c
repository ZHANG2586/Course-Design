#include "Schedule.h"

#include "../Persistence/Schedule_Persist.h"
#include "../Persistence/EntityKey_Persist.h"
#include "../Persistence/Play_Persist.h"

#include "../Common/List.h"

#include <stdio.h>


//��ʶ�� ��TTMS_SCU_Play_Srv_FetchByPlay
//�������ܣ����ݲ����еľ�ĿID�ţ�������þ�Ŀ��ص��ݳ��ƻ���
int Schedule_Srv_FetchByPlay(schedule_list_t list, int play_id) {
    return Schedule_Perst_SelectByPlay(list, play_id);
}


//��ʶ�� ��TTMS_SCU_Schedule_Srv_Add
//�������ܣ�������data��Ϊʵ�ε��ó־û���洢���ݳ��ƻ������������־û��㺯���ķ���ֵ���ݸ�����㺯��
int Schedule_Srv_Add(schedule_t * data) {
    return Schedule_Perst_Insert(data);
}


//��ʶ�� ��TTMS_SCU_Schedule_Srv_Mod
//�������ܣ��ò���data�е��ݳ��ƻ�������Ϊʵ�Σ�ͨ�����ó־û��㺯�����޸��ļ���¼�ľɵ��ݳ��ƻ���Ϣ��
int Schedule_Srv_Modify(const schedule_t *data) {
    return Schedule_Perst_Update(data);
}


//��ʶ�� ��TTMS_SCU_Schedule_Srv_DelByID
//�������� �����ݲ���id��¼���ݳ��ƻ�ID�ţ����ó־û��㺯��ɾ����Ӧ���ݳ��ƻ���
int Schedule_Srv_DeleteByID(int id) {
    return Schedule_Perst_RemByID(id);
}

//��ʶ�� ��TTMS_SCU_Schedule_Srv_FetchAll
//�������ܣ� ��ȡȫ���ݳ��ƻ�
int Schedule_Srv_FetchAll(schedule_list_t list)
{
    return Schedule_Perst_SelectAll(list);
}

//��ʶ�� ��TTMS_SCU_Schedule_Srv_FetchByName
//�������ܣ� �������ƻ�ȡ��Ŀ
int Play_Srv_FetchByName(play_list_t list,char condt[])
{
    return Play_Perst_SelectByName(list , condt);
}

int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount)
{
    int value = 0;          //�洢Ʊ��
    int sold = 0;           //�洢��Ч��Ʊ����
    schedule_list_t list;
    schedule_node_t *p;
    *soldCount = 0;

    int flag;

    List_Init(list,schedule_node_t);
    flag=Schedule_Perst_SelectByPlay(list, play_id);              //�����ݳ��ƻ�����list
    //printf("%d\n\n\n",Schedule_Perst_SelectByPlay(list, play_id));
    List_ForEach(list,p) {
        if(flag==1)
            break;
        printf("%d\n",p->data.id);
        value += Ticket_Srv_StatRevSchID(p->data.id,&sold);
        *soldCount = *soldCount+sold;
        flag--;
    }

    //��������
    List_Destroy(list,schedule_node_t);

    return value;
}


