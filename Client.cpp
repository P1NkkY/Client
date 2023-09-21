
#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <iostream>

#pragma warning(disable : 4996)

SOCKET Connection;

//! Функция принимает сообщение от сервера
void ClienHandler() {
	char msg[256]; // Для хранения сообщения
	while (true) {
		recv(Connection, msg, sizeof(msg), NULL);
		std::cout << msg << std::endl;
	}
}

int main(int atgc, char* argv[])
{
	WSAData wsadata; //! Структура WSAData
	WORD DLLVersion = MAKEWORD(2, 1); //! Запрашиваемая версия библиотеки winsock для загрузки библиотеки
	if (WSAStartup(DLLVersion, &wsadata) != 0) { //! Если вернулся не ноль, то библиотека загружена неверно
		std::cout << "Error" << std::endl; // Загрузка библиотеки
		exit(1);
	}

	//! Заполняем информацию об адресе сокета
	SOCKADDR_IN addr; // Структура SOCKADDR предназначена для хранения адреса. Для интернет протоколов SOCKADDR_IN
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // sin_addr - структура SOCKADDR_IN, которая хранит адрес (в нашем случае локал хост)
	addr.sin_port = htons(1111); // Порт для идентификации программы поступающими данными
	addr.sin_family = AF_INET; // sin_family (AF_INET - используется семейство интернет протоколов)

	//! Нужно создать новый сокет для соединения с сервером
	Connection = socket(AF_INET, SOCK_STREAM, NULL);

	//Пытаемся присоединиться к серверу
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server" << std::endl;
		return 1;
	}
	std::cout << "Connected!!!" << std::endl;

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClienHandler, NULL, NULL, NULL);

	char msg1[256];
	while (true) {
		// Считываем символы записанные и записываем в переменную
		std::cin.getline(msg1, sizeof(msg1));
		send(Connection, msg1, sizeof(msg1), NULL);
		Sleep(10);
	}

	system("pause");

	return 0;
}