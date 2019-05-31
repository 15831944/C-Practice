#include<stdio.h>
#include<iostream>
#include <winsock.h>
using namespace std;

#define DEFAULT_PORT 6000
#define MAX_SOCKET 10
#pragma comment (lib,"Ws2_32.lib")

void main() {
	//����socket��Դ
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (0 != err) {
		cout << "Init Failure!" << err << endl;
		return;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		cout << "Version Error~!" << endl;
	}

	//��ʼ��socket
	SOCKET socketServ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socketServ == INVALID_SOCKET) {
		cout << "Init Socket Error!" << endl;
	}

	//��
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons( DEFAULT_PORT);
	if(SOCKET_ERROR == bind(socketServ, (sockaddr*)&addrSrv, sizeof(sockaddr))){
		cout << "Bind Socket Error" << endl;
	}

	//����
	if (SOCKET_ERROR == listen(socketServ, MAX_SOCKET)) {
		cout << "Listen Socket Error" << endl;
	}

	//����
	SOCKADDR_IN addrClient;
	int len = sizeof(addrClient);
	while (1)
	{
		//��������
		SOCKET sockConnect= accept(socketServ, (sockaddr*)&addrClient, &len);

		//����
		/*char* buff = "welcome to connect me!";
		send(sockConnect, buff, strlen(buff) + 1, 0);*/
		
		char lpbuff[100];
		sprintf_s(lpbuff, "[%s],welcome!",inet_ntoa(addrClient.sin_addr));
		send(sockConnect, lpbuff, strlen(lpbuff) + 1, 0);

		//����
		char rcvBuff[100];
		recv(sockConnect, rcvBuff, sizeof(rcvBuff), 0);

		cout << inet_ntoa(addrClient.sin_addr)<< ":" << rcvBuff << endl;

		closesocket(sockConnect);
	}


	//�ͷ�socket��Դ
	WSACleanup();
	system("pause");
}