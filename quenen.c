/**
 *  简单队列，从头插入，从尾取
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct queue_element_
{
    char *data;
    struct queue_element_ *next;
    struct queue_element_ *last;
} queue_element;

typedef struct queue_list_
{
    int size;
    queue_element *head;
    queue_element *tail;
} queue_list;

void queue_init(queue_list *queue)
{
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
}

int queue_insert(queue_list *queue, char *str)
{
    queue_element *new_node = (queue_element *)malloc(sizeof(queue_element));
    if (!new_node) {
        return -1;
    }
    new_node->data = strdup(str);
    new_node->last = NULL;

    //队列为空
    if (0 == queue->size
            && NULL == queue->head
            && NULL == queue->tail) {

        new_node->next = NULL;

        (queue->size)++;
        queue->head = new_node;
        queue->tail = new_node;

        return 0;
    }

    //队列不为空
    (queue->size)++;
    queue->head->last = new_node;
    new_node->next = queue->head;
    queue->head = new_node;

    return 0;
}

int queue_get(queue_list *queue, char **str)
{
    if (0 == queue->size) {
        str = NULL;
        return -1;
    }

    queue_element *tail = queue->tail;

    *str = tail->data;

    if (1 == queue->size) {
        queue->head = NULL;
        queue->tail = NULL;
    } else {
        tail->last->next = NULL;
        queue->tail = tail->last;
    }

    free(tail);
    (queue->size)--;

    return 0;
}

void queue_apply(queue_list *queue)
{
    queue_element *p = queue->head;

    if (queue->size ==0) {
        printf("this queue size is 0\n");
        exit(-1);
    }

    while (p) {
        printf("%s\n", p->data);

        p = p->next;
    }
    printf("\n");
}

int main()
{
    queue_list *queue;
    char *data;

    queue = (queue_list *)malloc(sizeof(queue));
    queue_init(queue);

    queue_insert(queue, "hello");
    queue_insert(queue, "my");
    queue_insert(queue, "name");
    queue_insert(queue, "is");
    queue_insert(queue, "hua");
    queue_insert(queue, "sheng");
    queue_insert(queue, "!");
    queue_insert(queue, "你");
    queue_insert(queue, "是");
    queue_insert(queue, "谁？");

    queue_apply(queue);

    while (queue->size) {
        queue_get(queue, &data);
        printf("%s\n", data);
        free(data);
    }

    free(queue);
}
