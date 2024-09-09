#pragma once
#include <iostream>

class Msg
{
public:
    Msg(); //конструктор сообщения
    Msg(int id, int idFrom, int idTo, std::string message); //конструктор с установкой значений
    std::string showMsg(); //отображение сообщения
    std::string getTime(); //выдача текущего времени
    int getIdTo(); //получение ID пользователя-адресата сообщения
    std::string getMessage(); //получения текста сообщения

private:
    int _id; //ID сообщения
    std::string _datetime; //время формирования сообщения
    std::string _message; //текст сообщения
    int _idFrom; //ID пользователя-источника сообщения (от кого)
    int _idTo; //ID пользователя-адресата сообщения (кому)
};

