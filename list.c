#include <stdlib.h>
#include <string.h>

typedef struct listElmt_ 
{
    void *data;
    struct ListElmt_ *next;
} ListElmt;

typedef struct List_
{
    int size;
    ListElmt *head;
    ListElmt *tail;
} List;

void list_init(List *list);
void list_destroy(List *list);
int list_ins_next(List *list, ListElmt *element, const void *data);
int list_rem_next(List *list, ListElmt *element, void **data);

#define LIST_SIZE(list)     ((list)->size)
#define LIST_HEAD(list)     ((list)->head)
#define LIST_TAIL(list)     ((list)->tail)
#define LIST_IS_HEAD(list, element)     ((element) == (list)->head ? 1 : 0)
#define LIST_IS_TAIL(list, element)     ((element)->next == NULL ? 1 : 0)
#define LIST_DATA(element)    ((element)->data)
#define LIST_NEXT(element)    ((element)->next)

void list_init(List *list)
{
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

void list_destory(List *list)
{

}

int list_ins_next(List *list, ListElmt *element, const void *data)
{
    ListElmt *new_node = (ListElmt *)malloc(sizeof(ListElmt));
    new_node->data = data;

    //链表为空
    if (NULL == (list)->head) {
        //当插入第一个的时候，既是头也是尾
        (list)->head = new_node;
        (list)->tail = new_node;
        new_node->next = NULL;

        return 0;
    }
    
    //链表不为空，没指定插入位置，插入尾部
    if (NULL == element) {
        (list)->tail->next = new_node;
        new_node->next     = NULL;
        (list)->tail       = new_node;

        return 0;
    }

    ListElmt *position = list->head;
    while (position->next) {
        if (position->data == data) {
            if (list->tail == position) {
                new_node->next = NULL;
                list->tail = new_node;
            } else {
                new_node->next = position->next;
            }
            position->next = new_node;

            return 0;
        }
        position = position->next;
    }

    return -1;
}


int list_rem_next(List *list, ListElmt *element, void **data)
{
    ListElmt *position = list->head;
    
    //没传入element，直接删除链表尾元素
    if (NULL == element) {
        data = &list->tail->data;
        free(list->tail);
        
        while (position->next) {
            position = position->next;
        }
        list->tail = position;

        return 0;
    }

    while (position) {
        if (position->data == element->data) {
            
        }
    }
}

int main()
{
    List *list;
    
    list = (List *)malloc(sizeof(List));
    list_init(list);

    return 0;
}
