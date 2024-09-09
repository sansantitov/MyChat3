#include<iostream>
#include<unistd.h>
#include<string.h>
#include <memory>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>

#include "main.h"
#include "User.h"
#include "Msg.h"
#include "Chat.h"
#include "Sfunc.h"



struct sockaddr_in serveraddress, client;
socklen_t length;
int sockert_file_descriptor, connection, bind_status, connection_status;
char message[MESSAGE_LENGTH];

std::vector <User> users{};
std::vector <Msg> msgs{};


int main()  {

    // Создадим сокет
    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(sockert_file_descriptor == -1){
        std::cout << "Сбой при создании сокета!" << std::endl;
        exit(1);
    }
    //
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Зададим номер порта для связи
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Привяжем сокет
    bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress,
    sizeof(serveraddress));
    if(bind_status == -1)  {
        std::cout << "Сбой при привязке сокета!" << std::endl;
        exit(1);
    }
    // Поставим сервер на прием данных
    connection_status = listen(sockert_file_descriptor, 5);
    if(connection_status == -1){
    std::cout << "Сервер не может прослушивать новые соединения!" << std::endl;
    exit(1);
    }  else  {
          std::cout << "Сервер прослушивает сообщения от клиента!" << std::endl;
    }
    length = sizeof(client);
    connection = accept(sockert_file_descriptor,(struct sockaddr*)&client, &length);
    if(connection == -1)  {
        std::cout << "Сервер не может принимать данные с клиента!" << std::endl;
        exit(1);
    }

    //Создадим Chat
    std::unique_ptr<Chat> chat = std::make_unique<Chat>();
    std::string login, pass; //для хранения текуших значений
    int idUser = 0;
    int idUserTo = 0;
    std::string idUserToStr;
    unsigned int currentRow = 0; //текущая строка пакета
    std::vector<std::string> msgs;
    std::vector<std::string> users;


    while(1){
        memset(message,0,MESSAGE_LENGTH);
        read(connection, message, sizeof(message)); //получили данные с клиента

        int stage = 10*(int(message[0]) - '0') + int(message[1]) - '0';
        std::string stageStr = getStageStr(stage);
        if (stage <= 0) //если в сообщении передали "0")
        {
            std::cout << "Клиент остановлен!" << std::endl;
            std::cout << "Сервер остановнен!" << std::endl;
            break;
        }
        //Отображаем stage, полученное от сервера
        char buffer[MESSAGE_LENGTH];
        strncpy(buffer, &message[2], MESSAGE_LENGTH-2); //сообщение очищеное (без stage)
        std::cout << "Принято:" << stageStr << " " <<  buffer << std::endl;
        char result = '0';
        std::string myMess;

        if (stage == 1) //логин
        {
            login.assign(buffer);
            idUser = chat->findUserLogin(login); //если ли такой user
            result = idUser > 0? '1' : '0';
        }
        else if (stage == 2) //пароль
        {
            pass.assign(buffer);
            if (pass == "") result = '0';
            else
            {
                idUser = chat->findUserIdByLoginPassword(login, pass); //если ли такой user
                result = idUser > 0? '1' : '0';
            }
        }
        else if (stage == 3) //новый логин
        {
            login.assign(buffer);
            login = (std::string)buffer;
            idUser = chat->findUserLogin(login); //если ли такой user
            result = idUser > 0? '0' : '1';
        }
        else if (stage == 4) //новый пароль
        {
            pass.assign(buffer);
            if (pass == "") result = '0';
            else
            {
                chat->addUser(login, pass);
                idUser = chat->findUserIdByLoginPassword(login, pass); //если ли такой user
                result = idUser > 0? '1' : '0';
            }
        }


        else if (stage == 5 || stage == 7) //пакет сообщений
        {

            if (currentRow == 0) msgs = stage == 5 ? chat->showMsgs(idUser) : chat->showUsers();
            if (msgs.size() > 0)
            {
                myMess = msgs[currentRow];
                if (currentRow < msgs.size()-1)
                {
                    result =  '1';
                    currentRow ++;
                }
                else
                {
                    result =  '0';
                    currentRow = 0;
                }
            }
        }
        else if (stage == 8) //ввод ID пользователя
        {
            idUserToStr.assign(buffer);
            if (!is_number(buffer)) result = '0';
            else
            {
                idUserTo = stoi(idUserToStr);
                if (idUserTo == 0) result = '1'; //послать всем
                else
                {
                    std::string nameTo = chat->findUserNameByUserId(idUserTo);
                    if (nameTo != "") result = '1';
                    else result = '0';
                }
            }
        }
        else if (stage == 9) //ввод сообщения
        {
            std::string mess = std::string(buffer);
            if (mess == "0") result = '0';
            else
            {
                chat->sendMsg(idUser, idUserTo, mess);
                result = '1';
            }
        }

        memset(message,0,MESSAGE_LENGTH); //очистили massage
        myMess = result + myMess;
        strncpy(message, myMess.c_str(), myMess.length());
        std::cout << "передан результат на клиент: " << result  << std::endl;
        //std::cout << message  << std::endl;
        ssize_t bytes = write(connection, message, sizeof(message)); //послали ответ клиенту
        // Если передали >= 0  байт, значит пересылка прошла успешно
        if(bytes < 0)  {
            std::cout << "Ответ от сервера клиенту по передался!" << std::endl;
            exit(1);
        }
    }
    // закрываем сокет, завершаем соединение
    close(sockert_file_descriptor);
    return 0;
}

