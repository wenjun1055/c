#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* struct */
typedef struct BiTreeNode_
{
    char   *data;
    struct BiTreeNode_ *left;
    struct BiTreeNode_ *right;
} BiTreeNode;

struct struct BiTree_
{
    int        size;
    BiTreeNode *root;
} BiTree;

/* define */
#define BITREE_SIZE(tree)       ((tree)->size)
#define BITREE_ROOT(tree)       ((tree)->root)
#define BITREE_IS_EOB(node)     (NULL == (node))
#define BITREE_IS_LEAF(node)    (NULL == (node)->left && NULL == (node)->right)
#define BITREE_DATA(node)       ((node)->data)
#define BITREE_LEFT(node)       ((node)->left)
#define BITREE_RIGHT(node)      ((node)->right)

/* interface */
void bitree_init(BiTree *tree);
void bitree_destory(BiTree *tree);
int bitree_insert_left(BiTree *tree, char *dest, const char *data);
int bitree_insert_right(BiTree *tree, char *dest, const char *data);
void bitree_remove_left(BiTree *tree, char *dest);
void bitree_remove_right(BiTree *tree, char *dest);
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const char *data);
int bitree_search(BiTree *tree, char *search, BiTreeNode **node);

/* start */

void bitree_init(BiTree *tree)
{
    tree->size = 0;
    tree->root = NULL;
}

void bitree_destory(BiTree *tree)
{
}

int bitree_search(BiTree *tree, char *search, BiTreeNode *node)
{
    //没有传入要搜寻的字符串，直接返回树根节点
    if (NULL == search) {
        *node = BITREE_ROOT(tree);

        return 0;
    }


}

int bitree_insert_left(BiTree *tree, char *dest, const char *data)
{
    
}
