#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

int main(int argc, char **argv)
{
    char api[100] = "http://m.baidu.com/news?tn=bdapitext&src=";
    CURL *handle;
    CURLcode flag;
    size_t len;
    int socket;

    if (argc != 2) {
        printf("Please input news url\r\n");
        return 0;
    }
    
    strcat(api, *(argv+1));
    
    handle = curl_easy_init();
    if (NULL == handle) {
        printf("curl_easy_init failed\r\n");
        return 0;
    }
    curl_easy_setopt(handle, CURLOPT_URL, api);
    curl_easy_setopt(handle, CURLOPT_HEADER, 1);
    //curl_easy_setopt(handle, CURLOPT_CONNECT_ONLY, 1);

    flag = curl_easy_perform(handle);
    if (CURLE_OK != flag) {
        printf("curl_easy_perform failed!\r\n");
        curl_easy_cleanup(handle);
        return 0;
    }

    curl_easy_cleanup(handle);
    return 0;
}
