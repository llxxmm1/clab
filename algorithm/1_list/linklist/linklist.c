#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define N 10
typedef struct member_list_s {
    int num;    /* 编号 */
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
    //初始化头结点
    member_list_t *listnode; //每次申请链表结点时所用的指针
    struct list_head * pos;
    member_list_t *p;
    int i;

    printf("init member list...\n");
    INIT_LIST_HEAD(&member_list.list);

    //建立N个结点，依次加入到链表当中
    for (i=0; i<N; i++) {
        listnode = (member_list_t *)malloc(sizeof(member_list_t));
        listnode->num = i+1;
        list_add_tail(&listnode->list, &member_list.list);
        printf("Node %d has added to member list...\n", i+1);
    }
    
    //遍历链表
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

    //依次删除N个结点
    i = 1;
    list_for_each_safe(pos, n, &member_list.list) {
        //为了安全删除结点而进行的遍历
        list_del(pos); //从链表中删除当前结点
        p = list_entry(pos, member_list_t, list); 
        //得到当前数据结点的首地址，即指针
        free(p); //释放该数据结点所占空间
        printf("Node %d has removed from the doublelist...\n", i++);
    }
    printf("destroy member list...\n");
}

