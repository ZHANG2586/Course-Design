#ifndef SCHEDULE_H_
#define SCHEDULE_H_
#include "Play.h"


//��������
// ʱ��ṹ�嶨�����£�
// ���ͱ�ʶ��ttms_time_t
// �������ƣ�ttms_time_t
// ���Ͷ��壺
typedef struct {
    int hour;
    int minute;
    int second;
}ttms_time_t;


//�ݳ��ƻ��������͵Ķ������£�
//�������� ��schedule_t.
//���Ͷ��壺
typedef struct {
    int id;             //�ݳ��ƻ�ID
    int play_id;        //��ӳ��ĿID
    int studio_id;      //�ݳ���ID
    ttms_date_t date;   //��ӳ����
    ttms_time_t time;   //��ӳʱ��
    int seat_count;     //��λ��
}schedule_t;


//�ݳ��ƻ������ڵ�Ķ������£�
//���ͱ�ʶ ��TTMS_SDS_Schedule_ListNode.
//��������: schedule_node_t��schedule_list_t
//���Ͷ��壺
typedef struct schedule_node {
        schedule_t data;
        struct schedule_node * next;
        struct schedule_node * prev;
}schedule_node_t, *schedule_list_t;


//��ʶ�� ��TTMS_SCU_Play_Srv_FetchByPlay
//�������ܣ����ݲ����еľ�ĿID�ţ�������þ�Ŀ��ص��ݳ��ƻ���
int Schedule_Srv_FetchByPlay(schedule_list_t list, int play_id);


//��ʶ�� ��TTMS_SCU_Schedule_Srv_Add
//�������ܣ�������data��Ϊʵ�ε��ó־û���洢���ݳ��ƻ������������־û��㺯���ķ���ֵ���ݸ�����㺯��
int Schedule_Srv_Add(schedule_t * data);


//��ʶ�� ��TTMS_SCU_Schedule_Srv_Mod
//�������ܣ��ò���data�е��ݳ��ƻ�������Ϊʵ�Σ�ͨ�����ó־û��㺯�����޸��ļ���¼�ľɵ��ݳ��ƻ���Ϣ��
int Schedule_Srv_Modify(const schedule_t *data);


//��ʶ�� ��TTMS_SCU_Schedule_Srv_DelByID
//�������� �����ݲ���id��¼���ݳ��ƻ�ID�ţ����ó־û��㺯��ɾ����Ӧ���ݳ��ƻ���
int Schedule_Srv_DeleteByID(int id);


//��ȡ�����ݳ��ƻ���Ϣ��������
int Schedule_Srv_FetchAll(schedule_list_t list);


//ͨ�����ƻ�ȡ��Ŀ��Ϣ
int Play_Srv_FetchByName(play_list_t list,char condt[]);

int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount);

#endif // SCHEDULE_H_
