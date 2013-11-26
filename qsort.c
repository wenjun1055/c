#include <stdio.h>

static int qsort_swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;

    return 0;
}

void qsort(int *base, int nmemb)
{
    int *begin_stack[10];
    int *end_stack[10];
    int *begin;
    int *end;
    int *seg1;
    int *seg2;
    int *seg2p;
    int loop;
    unsigned int offset;

    /* 使用栈而不是常见的递归实现 */
    begin_stack[0] = base;      //开始元素位置栈，入栈
    end_stack[0]   = base + (nmemb - 1) ;   //结束位置栈，入栈

    for (loop = 0; loop >= 0; --loop) {
        begin = begin_stack[loop];          //开始位置出栈
        end   = end_stack[loop];        //结束位置出栈

        while (begin < end) {
            offset = (end - begin) >> 1;        //取中间位置

            qsort_swap(begin, begin + offset);      //交换开始和中间的位置

            for (int i = 0; i < 8;i++) 
            {
                printf("%d ", base[i]);
            }
            printf("\n\n");


            seg1 = begin;
            seg2 = end;

            while (1) {
                for (; seg1 < seg2 && *begin < *seg1 ; seg1 += 1);

                for (; seg2 >= seg1 && *seg2 > *begin; seg2 -= 1);

                if (seg1 >= seg2)
                    break;

                qsort_swap(seg1, seg2);


                for (int i = 0; i < 8;i++) 
                {
                    printf("%d ", base[i]);
                }
                printf("\n\n");
            }

            qsort_swap(begin, seg2);


            for (int i = 0; i < 8;i++) 
            {
                printf("%d ", base[i]);
            }
            printf("\n\n");

            seg2p = seg2;

            if ((seg2p - begin) <= (end - seg2p)) {
                if (seg2p < end) {          //右侧入栈
                    begin_stack[loop] = seg2p + 1;
                    end_stack[loop++] = end;
                }
                end = seg2p;
            } else {
                if (seg2p > begin) {        // 左侧入栈
                    begin_stack[loop] = begin;
                    end_stack[loop++] = seg2p - 1;
                }        //end if
                begin = seg2p;
            }       //end if
        }           //end while


        for (int i = 0; i < 8;i++) 
        {
            printf("%d ", base[i]);
        }
        printf("\n\n");
    }                   //end for

}
int main(int argc, char *argv[])
{
    int a[10] = {14, 5, 7, 8, 2, 4, 55, 3};
    int i;

    printf("\n\n");
    for (i = 0; i < 8;i++) 
    {
        printf("%d ", a[i]);
    }
    printf("\n\n");

    qsort(a, 8);

    printf("\n\n");
    for (i = 0; i < 8;i++) 
    {
        printf("%d ", a[i]);
    } 
    printf("\n\n");

    return 0;
}
