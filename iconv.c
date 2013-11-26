#include <stdio.h>
#include <stdlib.h>
#include <iconv.h>
#include <string.h>
#define OUTLEN 255

int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen);
int u2g(char *inbuf,int inlen,char *outbuf,int outlen);
int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen);


int main()
{
    char *in_utf8 = "正在安装123";
    char *in_gb2312 = "你好，123请问";
    char utf8_out[OUTLEN];
    char gb2312_out[OUTLEN];
    int rc;

    printf("in_utf8= %s length=%ld\n", in_utf8, strlen(in_utf8));
    printf("in_gb2312=%s length=%ld\n", in_gb2312, strlen(in_gb2312));

    /*unicode码转为gb2312码*/
   rc = u2g(in_utf8,strlen(in_utf8),utf8_out,OUTLEN);
   printf("unicode-->gb2312 utf8_out=%s length=%ld\n", utf8_out, strlen(utf8_out));
    //gb2312码转为unicode码
    
    rc = g2u(in_gb2312,strlen(in_gb2312),gb2312_out,OUTLEN);
    printf("gb2312-->unicode gb2312_out=%s length=%ld\n",gb2312_out, strlen(gb2312_out));

    return 0;
}

    /*代码转换:从一种编码转为另一种编码*/
    int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen)
    {
        iconv_t cd;
        iconv_t rc;
        char **pin = &inbuf;
        char **pout = &outbuf;
    
        rc = iconv_open(to_charset,from_charset);
        if (rc==0) return -1;
        memset(outbuf,0,outlen);
        if (iconv(rc,pin,(size_t *)&inlen,pout,(size_t *)&outlen)==-1) return -1;
        iconv_close(rc);
        return 0;
    }

    /*UNICODE码转为GB2312码*/
    int u2g(char *inbuf,int inlen,char *outbuf,int outlen)
    {
        return code_convert("utf-8","gb2312",inbuf,inlen,outbuf,outlen);
    }
    /*GB2312码转为UNICODE码*/
    int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
    {
        return code_convert("gb2312","utf-8",inbuf,inlen,outbuf,outlen);
    }
