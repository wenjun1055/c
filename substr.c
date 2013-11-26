#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void  getSubStr(char *str,char *substr,int start,int end);
void getStr(char *str,char *substr,int start,int end);
int startposizition(char *str,int start);
int endposizition(char *str,int end);


int main()
{
    char str[500]="你好啊kkkk131你0啊3黑KKK乎fds乎好fdsa看到发 你埃弗fasf顿阿发fds生飞洒大法舒服阿飞多少";
    char substr[200];
    memset(substr,0,sizeof(substr));

    getSubStr(str,substr,0,5);
    printf("%s\n",substr);

    getSubStr(str,substr,5,11);
    printf("%s\n",substr);

    getSubStr(str,substr,11,13);
    printf("%s\n",substr);

    getSubStr(str,substr,13,17);
    printf("%s\n",substr);
    
    getSubStr(str,substr,17,30);
    printf("%s\n",substr);

    getSubStr(str,substr,30,50);
    printf("%s\n",substr);
    return 0;
}


/*
*  getsubstr此函数为截取中文函数，当一个字串过长，分段截取中，汉字占双字节，而字符为单字节
*  参数说明
*  str      传入字串
*  substr   返回子串
*  start    取值开始位置
*  end      取值结束位置
*   示例
*   char str[500]="你好啊kkkk131你0啊3黑KKK乎fds乎好fdsa看到发 你埃弗fasf顿阿发fds生飞洒大法舒服阿飞多少";
*   char substr[200];
*   memset(substr,0,sizeof(substr));
*   getSubStr(str,substr,0,5);getSubStr(str,substr,6,11);...
*/

void  getSubStr(char *str,char *substr,int start,int end)
{
    start = startposizition(str,start);
    end   = endposizition(str,end);
    getStr(str,substr,start,end);   
}


void getStr(char *str,char *substr,int start,int end)
{
    char temp[200];
    int  i=0;
    memset(temp,0,sizeof(temp));

    for(start;start<=end;start++)
    {
        temp[i]=str[start];
        i++;
    }
    temp[i]='\0';
    strcpy(substr,temp);
}


/*判断末端取值位置*/
int endposizition(char *str,int end)
{
    int i=0;            //用于计数
    int posizition=0;   //还回位置
    int tempposi=end; 
    while(str[tempposi]<0)
    {
        i++;
        tempposi--;
    }

    if(i%2==0 && i!=0)
            posizition=end; 
    else
            posizition=end-1;   
    return posizition;
}


/*判断开始取值位置*/
int startposizition(char *str,int start)
{
    int i=0;            //用于计数
    int posizition=0;   //还回位置
    int tempposi=start;  
    while(str[tempposi]<0)
    {
        i++;
        tempposi--;
    }

    if(i%2==0 && i!=0)
            posizition=start+1; 
    else 
            posizition=start;   
    return posizition;
}


