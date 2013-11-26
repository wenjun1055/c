#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>

#define BUF_LEN 1028
#define SERVER_PORT 8080

//定义好的html页面，实际情况下web server基本是从本地文件系统读取html文件 
const static char http_error_hdr[] = "HTTP/1.1 404 Not Found\r\nContent-type: text/html\r\n\r\n";
const static char http_html_hdr[] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
const static char http_index_html[] = 
"<html><head><title>Congrats!</title></head>"
"<body><h1>Welcome to our HTTP server demo!</h1>"
"<p>This is a just small test page.</body></html>";

//解析到HTTP请求的文件后，发送本地文件系统中的文件
//这里，我们处理对index文件的请求，发送我们预定好的html文件
//呵呵，一切从简！ 
int http_send_file(char *filename, int sockfd)
{
    if(!strcmp(filename, "/")){
        //通过write函数发送http响应报文；报文包括HTTP响应头和响应内容--HTML文件 
        write(sockfd, http_html_hdr, strlen(http_html_hdr));
        write(sockfd, http_index_html, strlen(http_index_html));
    }
    else{
         // 文件未找到情况下发送404error响应 
        printf("%s:file not find!\n",filename);
        write(sockfd, http_error_hdr, strlen(http_error_hdr));
    }
  return 0;
}

//HTTP请求解析 
void serve(int sockfd){
    char buf[BUF_LEN];
    read(sockfd, buf, BUF_LEN);
    if(!strncmp(buf, "GET", 3)){
        char *file = buf + 4;
        char *space = strchr(file, ' ');
        *space = '\0';
        http_send_file(file, sockfd);
    }
    else{
         //其他HTTP请求处理，如POST，HEAD等 。这里我们只处理GET 
        printf("unsupported request!\n");
        return;
    }
}

int main(){
    int sockfd,err,newfd;
    struct sockaddr_in addr;
    //建立TCP套接字 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("socket creation failed!\n");
        return 0;
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    //这里要注意，端口号一定要使用htons先转化为网络字节序，否则绑定的实际端口
    //可能和你需要的不同 
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in))){
        perror("socket binding failed!\n");
        return 0;
    }
    listen(sockfd, 128);
    for(;;){
        //不间断接收HTTP请求并处理，这里使用单线程，在实际情况下考虑到效率一般多线程 
        newfd = accept(sockfd, NULL, NULL);
        serve(newfd);
        close(newfd);
    }

    return 0;
}