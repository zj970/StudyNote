/**************************************************************************
 * This is a Socket case,implemented based on TCP web chat program.
 * 
 * The application is the server side.
 * 
 * author: zj970
 * 
 * data: 2022/07/09 21：14
****************************************************************************/
#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)
#include <winsock.h>
#pragma comment(lib, "ws2_32.lib") 
#elif defined(__linux__) || defined(__unix__)
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define CLOSE_SOCKET close
#define SOCKET_ERROR (-1)
#else
#error "Unsupported platform"
#endif
#define PORT 8888  
                               
int main(){
    char Sendbuf[100];                              
    char Receivebuf[100];                           
    int SendLen;                                    
    int ReceiveLen;                                 
    int Length;                                     

    SOCKET socket_server;                           
    SOCKET socket_receive;                         

    SOCKADDR_IN Server_address;                     
    SOCKADDR_IN Client_address;                    

    WORD wVersionRequested;                        
    WSADATA wsaData;                                
    int error;                                      

    wVersionRequested = MAKEWORD(2,2);

    error = WSAStartup(wVersionRequested,&wsaData);
    
    if (error != 0)
    {
        printf("loading Socket error... \n");
        return 0;                                   
    }
    
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        WSACleanup();                           
        return 0;                                
    }
    Server_address.sin_family = AF_INET;  
    Server_address.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    Server_address.sin_port = htons(PORT);
    socket_server = socket(AF_INET,SOCK_STREAM,0);

    if (bind(socket_server,(SOCKADDR*)&Server_address,sizeof(SOCKADDR)))
    {
        printf("Scoket bind fail... \n");
    }

    if (listen(socket_server,5) < 0)
    {
        printf("Socket listen fail...\n");
    }

    /*Receive connectiond*/
    Length = sizeof(SOCKADDR);
    socket_receive = accept(socket_server,(SOCKADDR*)&Client_address,&Length);
    if (socket_receive == SOCKET_ERROR)
    {
        printf("Socket receive fail ...\n");
    }
    
    /*chat*/
    while (1)
    {
        ReceiveLen = recv(socket_receive,Receivebuf,100,0);
        if (ReceiveLen < 0)
        {
            printf("Receive fail to Client ... \n");
            printf("Exit ... \n");
            return 0;
        }
        else
        {
            printf("Clinet say: %s \n",Receivebuf);
        }

        printf("Please enter message:");
        scanf("%s",Sendbuf);
        SendLen = send(socket_receive,Sendbuf,100,0);
        if (SendLen < 0)
        {
            printf("Send message fail ... \n");
        }
    }
    WSACleanup();
    return 0;   
}  
