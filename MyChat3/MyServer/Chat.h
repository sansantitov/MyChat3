#pragma once
#include <iostream>
#include <vector>

class Chat
{
public:
    Chat(); //конструктор
    int findUserLogin(std::string login); //поиск ID пользователя по логину
    void addUser(std::string login, std::string password); //добавление пользователя
    int findUserIdByLoginPassword(std::string login, std::string password); //поиск ID пользователя по логину-паролю
    std::string findUserNameByUserId(int userId);  //поиск имени пользователя по ID пользователя
    std::vector<std::string> showUsers(); //отображение пользователей
    std::vector<std::string> showMsgs(int idUser); //отображение сообщений для текущего пользоваеля
    void sendMsg(int userId, int userIdTo, std::string message); //запись сообщения для "пересылки"
    int getUserIdLogin(); //получение ID текущего пользователя

private:
    int _userIdMax; //максимальное (последнее) значение ID зарегистрированного пользователя
    int _msgIdMax; //максимальное (последнее) значение ID записанного сообщения
};

