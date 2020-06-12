#ifndef SCHEDULE_UI_H_
#define SCHEDULE_UI_H_



//��������:Schedule_UI_MgtEntry
//�������� ����ʾ��ID��Ϊplay_id�ľ�Ŀ������������ݳ��ƻ������ṩ��ɾ���ݳ��ƻ����ܡ�
void Schedule_UI_MgtEntry(int play_id);



//�������ƣ�Schedule_UI_Add
//�������ܣ����ռ���������ݳ��ƻ���Ϣ��ͨ������ҵ���߼��㺯���������ݳ��ƻ���
int Schedule_UI_Add(int play_id);



 //�������� �������ݳ��ƻ���IDֵ������ҵ���߼��㺯���޸��ݳ��ƻ����ݡ�
int Schedule_UI_Modify(int id);



//�������ܣ� ���ݲ����е��ݳ��ƻ�ID�ţ�ͨ������ҵ���߼��㺯��������ɾ���ݳ��ƻ���
int Schedule_UI_Delete(int id);


/*�����Ʋ��Ҿ�Ŀ��Ϣ*/
int Schedule_UI_Query(char * play_name);

/*��ʾ�����ݳ��ƻ�*/
void Schedule_UI_ListAll(void);

void Queries_Menu();


#endif // SCHEDULE_UI_H_
