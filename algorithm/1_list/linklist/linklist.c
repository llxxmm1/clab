#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define N 10
typedef struct member_list_s {
    int num;    /* ��� */
    struct list_head list;
} member_list_t;

member_list_t member_list;

static int init(void);
static void destroy(void);

void main() {
   init();

   destroy();
}

static int init(void)
{
    //��ʼ��ͷ���
    member_list_t *listnode; //ÿ������������ʱ���õ�ָ��
    struct list_head * pos;
    member_list_t *p;
    int i;

    printf("init member list...\n");
    INIT_LIST_HEAD(&member_list.list);

    //����N����㣬���μ��뵽������
    for (i=0; i<N; i++) {
        listnode = (member_list_t *)malloc(sizeof(member_list_t));
        listnode->num = i+1;
        list_add_tail(&listnode->list, &member_list.list);
        printf("Node %d has added to member list...\n", i+1);
    }
    
    //��������
    i = 1;
    list_for_each(pos, &member_list.list) {
        p = list_entry(pos, member_list_t, list);
        printf("Node %d's data: %d\n", i, p->num);
        i++;
    }
    
    return 0;
}

static void destroy(void)
{
    struct list_head *pos, *n;
    member_list_t *p;
    int i;

    //����ɾ��N�����
    i = 1;
    list_for_each_safe(pos, n, &member_list.list) {
        //Ϊ�˰�ȫɾ���������еı���
        list_del(pos); //��������ɾ����ǰ���
        p = list_entry(pos, member_list_t, list); 
        //�õ���ǰ���ݽ����׵�ַ����ָ��
        free(p); //�ͷŸ����ݽ����ռ�ռ�
        printf("Node %d has removed from the doublelist...\n", i++);
    }
    printf("destroy member list...\n");
}

