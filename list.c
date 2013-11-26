/**
 * 内存全部释放完了
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listElmt_ 
{
    int data;
    struct ListElmt *next;
} ListElmt;

typedef struct List_
{
    int size;
    ListElmt *head;
    ListElmt *tail;
} List;

void list_init(List *list);
void list_destroy(List *list);
int list_ins_next(List *list, int element, int data);
int list_rem_next(List *list, int element);

#define LIST_SIZE(list)     ((list)->size)
#define LIST_HEAD(list)     ((list)->head)
#define LIST_TAIL(list)     ((list)->tail)
#define LIST_IS_HEAD(list, element)     ((element) == (list)->head->data ? 1 : 0)
#define LIST_IS_TAIL(list, element)     ((element)->next == NULL ? 1 : 0)
#define LIST_NEXT(element)    ((element)->next)

void list_init(List *list)
{
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

void list_destory(List *list)
{
    ListElmt *position = list->head;
    while (list->head) {
        position = list->head;
        list->head = list->head->next;
        free(position);
    }
    free(list);

    return 0;
}

int list_ins_next(List *list, int element, int data)
{
    ListElmt *new_node = (ListElmt *)malloc(sizeof(ListElmt));
    new_node->data = data;

    //链表为空
    if (NULL == (list)->head) {
        //当插入第一个的时候，既是头也是尾
        (list)->head = new_node;
        (list)->tail = new_node;
        new_node->next = NULL;
        (list->size)++;
        return 0;
    }

    //链表不为空，没指定插入位置，插入头部
    if (-1 == element) {
        new_node->next = list->head;
        list->head = new_node;

        (list->size)++;
        return 0;
    }

    ListElmt *position = list->head;
    while (position) {
        if (position->data == element) {
            if (list->tail == position) {
                new_node->next = NULL;
                list->tail = new_node;
            } else {
                new_node->next = position->next;
            }
            position->next = new_node;

            (list->size)++;
            return 0;
        }
        position = position->next;
    }

    return -1;
}


int list_rem_next(List *list, int element)
{
    if (NULL == list->head) {
        return 0;
    }

    ListElmt *last = list->head;
    ListElmt *position = list->head;

    //没传入element，直接删除链表头元素
    if (-1 == element) {
        list->head = position->next;
        free(position);
        return 0;
    }

    while (position) {
        if (position->data == element) {
            if (list->head == position) {
                list->head = position->next;
            } else if (list->tail == position) {
                last->next = NULL;
                list->tail = last;
            } else {
                last->next = position->next;
            }

            free(position);

            return 0;
        }

        last     = position;
        position = position->next;
    }

    return -1;
}

void list_apply(List *list)
{
    ListElmt *position = list->head;

    while (position) {
        printf("%d\n", position->data);
        position = position->next;
    }
}

int main()
{
    List *list;

    list = (List *)malloc(sizeof(List));
    list_init(list);

    list_ins_next(list, -1, 1);
    list_ins_next(list, -1, 2);
    list_ins_next(list, -1, 3);
    list_ins_next(list, -1, 4);
    list_ins_next(list, 2, 5);
    list_ins_next(list, 3, 6);

    list_apply(list);

    list_rem_next(list, -1);
    list_rem_next(list, 2);
    list_rem_next(list, 5);

    list_apply(list);

    list_destory(list);

    return 0;
}
