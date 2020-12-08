#include "single_thread_tcp_server.h"
#include <algorithm> 


void handle_connection(SOCKET socket, sockaddr_in* addr) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char* str_in_addr = inet_ntoa(addr->sin_addr);
    printf("[%s]>>%s\n", str_in_addr, "Establish new connection");
    while (true) {
        char buffer[256] = "";
        int key;
        int rc = recv(socket, buffer, sizeof(buffer), 0);
        int r_c = recv(socket, (char*)&key, sizeof(key), 0);
        if (rc > 0 || r_c > 0) {
            printf("[%s]:%s\n", str_in_addr, buffer);
            printf("[%s]:%d\n", str_in_addr, key);
        }
        else {
            break;
        }

        int i = 0, j = 0;
        char ABC[] = { 'À','Á','Â','Ã','Ä','Å','Æ','Ç','È',
                'É','Ê','Ë','Ì','Í','Î','Ï','Ð','Ñ',
                'Ò','Ó','Ô','Õ','Ö','×','Ø','Ù','Ú',
                'Û','Ü','Ý','Þ','ß','_','.',',','0',
                '1','2','3','4','5','6','7','8','9' };

        char* begin = ABC;
        char* end = ABC + sizeof(ABC);
        for (; buffer[i]; ++i)
        {
            char* ch = std::find(begin, end, buffer[i]);
            if (ch != end) buffer[i] = *(begin + (ch - begin + key) % sizeof(ABC));
        }

        int sd = send(socket, buffer, sizeof(buffer), 0);
        if (sd > 0) {
            printf("[%s]:%s\n", "MESS", buffer);
        }
        else {
            break;
        }

    }


    close_socket(socket);
    printf("[%s]>>%s", str_in_addr, "Close incomming connection");
}