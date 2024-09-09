
#include<iostream>
#include<unistd.h>
#include "main.h"
#include<cstring>
#include<Cfunc.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int socket_file_descriptor, connection;
struct sockaddr_in serveraddress, client;
char message[MESSAGE_LENGTH];


int main(){
    // Создадим сокет
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_file_descriptor == -1){
        std::cout << "Сбой при созданиий сокета!" << std::endl;
        exit(1);
    }

    // Установим адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr(SERVER);
    // Зададим номер порта
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Установим соединение с сервером
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if(connection == -1){
        std::cout << "Сбой при установке соединения с сервером!" << std::endl;
        exit(1);
    }

    int stage = 1;
    // Взаимодействие с сервером
    while(1)
    {
        if (stage == 0)
        {
            std::cout << "Соединение с сервером разорвано!" << std::endl;
            break;
        }

        mygetline(message, stage, !(stage >= 5 && stage <= 7)); //ввод сoобщения (0-1-й байт - это stage)
        //Посылаем на сервер
        ssize_t bytes = write(socket_file_descriptor, message, sizeof(message)); //послали на сервер
        if(bytes <= 0)
        {
            stage = 0; //Если передали 0 байт, значит пересылка не состоялась
            continue;
        }
        //Поллучает ответ с сервера
        memset(message,0,sizeof(message));
        read(socket_file_descriptor, message, sizeof(message)); // получили ответ от сервера с результатом в 0-м байте

        if (stage == 1) //Логин
        {
            if (message[0] == '1') stage = 2; //есть такой логин - переход на ввод пароля
            else
            {
                std::string ch = choice("Нет такого логина! Повторить логин-1, регистрация нового пользователя-3, выход-0", "130");
                if(ch == "1") continue;
                else if (ch == "3") stage = 3; //на регистрацию
                else if (ch == "0") stage = 0; //на выход
            }
        }
        else if (stage == 2) //Пароль
        {
            if (message[0] == '1') stage = 5;
            else
            {
                std::string ch = choice("Ошибка в пароле! Повторить пароль-1, возврат на ввод логина-2, регистр. нового пользователя-3, выход-0", "1230");
                if(ch == "1") continue;
                else if (ch == "2") stage = 1; //на ввод логина
                else if (ch == "3") stage = 3; //на регистрацию
                else if (ch == "0") stage = 0; //на выход
            }

        }
        else if (stage == 3) //Новый логин для регистрации
        {
            if (message[0] == '1') stage = 4; //новый логин введен правильно (нет такого в user)
            else
            {
                std::string ch = choice("Такой логин уже есть! Повторить ввод нового логина-1, выход-0", "10");
                if(ch == "1") continue;
                else if (ch == "0") stage = 0; //на выход
            }
        }
        else if (stage == 4) //Новый пароль для регистрации
        {
            if (message[0] == '1') //пароль введен правильно (не пустой)
            {
                std::string ch = choice("Регистрация завершена! Войти (авторизоваться)-1, регистрация нового-3, выход-0", "130");
                if (ch == "1") stage = 1;
                else if (ch == "3") continue;
                else if (ch == "0") stage = 0;
            }
            else
            {
                std::string ch = choice("Пароль не может быть пустым! Повторить ввод-1, выход-0", "10");
                if (ch == "1") continue;
                else if (ch == "0") stage = 0;
            }
        }
        else if (stage == 5) //Пакет сообщений от авторизованного клиента
        {
            std::string messageStr = std::string(message);
            std::cout << messageStr.substr(1) << std::endl;
            if (message[0] == '0') stage = 6;
        }
        else if (stage == 6) //Конец пакета сообщений от авторизованного клиента
        {
            std::string ch = choice("Послать сообщение-1, авторизация (новый вход)-2, регистр. нового-3, выход-0", "1230");
            if (ch == "0") stage = 0;
            else if(ch == "2") stage = 1;
            else if (ch == "3") stage = 3;
            else
            {
                stage = 7; //на отображение пользователей
            }
        }
        else if (stage == 7) //Пакет пользователей
        {
            std::string messageStr = std::string(message);
            std::cout << messageStr.substr(1) << std::endl;
            if (message[0] == '0') stage = 8;
        }
        else if (stage == 8) //ввод ID пользвателя
        {
            if (message[0] == '1') stage = 9; //ID пользвателя введен правильно
        }
        else if (stage == 9) //сообщение ввели
        {
            if (message[0] == '0') stage = 0;
            else stage = 5;
        }

    }
    // закрываем сокет, завершаем соединение
    close(socket_file_descriptor);
    return 0;
}
