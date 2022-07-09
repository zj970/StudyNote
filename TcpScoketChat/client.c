/**************************************************************************
 * This is a Socket case,implemented based on TCP web chat program.
 * 
 * The application is the client side.
 * 
 * author: zj970
 * 
 * data: 2022/07/09 21：14
****************************************************************************/
#include <stdio.h>
#include <winsock.h>                                
#define PORT 8888                                 

int main(){
    char Sendbuf[100];                              
    char Receivebuf[100];                           
    int SendLen;                                    
    int ReceiveLen;                                 
    int Length;                                     

    SOCKET socket_send;                                                 

    SOCKADDR_IN Server_address;                                 

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
    Server_address.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    Server_address.sin_port = htons(PORT);
    socket_send = socket(AF_INET,SOCK_STREAM,0);

    if (connect(socket_send,(SOCKADDR*)&Server_address,sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        printf("Scoket bind fail... \n");
    }
    
   /*chat*/
    while (1)
    {
        printf("Please enter message: ");
        scanf("%s",Sendbuf);
        SendLen = send(socket_send,Sendbuf,100,0);
        if (SendLen < 0)
        {
            printf("Send message fail ... \n");
        }
        ReceiveLen = recv(socket_send,Receivebuf,100,0);
        if (ReceiveLen < 0)
        {
            printf("Receive fail to Client ... \n");
            printf("Exit ... \n");
            return 0;
        }
        else
        {
            printf("Server say: %s \n",Receivebuf);
        }
    }
    
    closesocket(socket_send);
    WSACleanup();
    return 0;   
}  
