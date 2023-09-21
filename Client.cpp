
#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <iostream>

#pragma warning(disable : 4996)

SOCKET Connection;

//! ������� ��������� ��������� �� �������
void ClienHandler() {
	char msg[256]; // ��� �������� ���������
	while (true) {
		recv(Connection, msg, sizeof(msg), NULL);
		std::cout << msg << std::endl;
	}
}

int main(int atgc, char* argv[])
{
	WSAData wsadata; //! ��������� WSAData
	WORD DLLVersion = MAKEWORD(2, 1); //! ������������� ������ ���������� winsock ��� �������� ����������
	if (WSAStartup(DLLVersion, &wsadata) != 0) { //! ���� �������� �� ����, �� ���������� ��������� �������
		std::cout << "Error" << std::endl; // �������� ����������
		exit(1);
	}

	//! ��������� ���������� �� ������ ������
	SOCKADDR_IN addr; // ��������� SOCKADDR ������������� ��� �������� ������. ��� �������� ���������� SOCKADDR_IN
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // sin_addr - ��������� SOCKADDR_IN, ������� ������ ����� (� ����� ������ ����� ����)
	addr.sin_port = htons(1111); // ���� ��� ������������� ��������� ������������ �������
	addr.sin_family = AF_INET; // sin_family (AF_INET - ������������ ��������� �������� ����������)

	//! ����� ������� ����� ����� ��� ���������� � ��������
	Connection = socket(AF_INET, SOCK_STREAM, NULL);

	//�������� �������������� � �������
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server" << std::endl;
		return 1;
	}
	std::cout << "Connected!!!" << std::endl;

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClienHandler, NULL, NULL, NULL);

	char msg1[256];
	while (true) {
		// ��������� ������� ���������� � ���������� � ����������
		std::cin.getline(msg1, sizeof(msg1));
		send(Connection, msg1, sizeof(msg1), NULL);
		Sleep(10);
	}

	system("pause");

	return 0;
}