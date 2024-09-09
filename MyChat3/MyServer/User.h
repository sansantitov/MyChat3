#pragma once
#include <string>

class User
{
public:
    User(); //конструктор
    User(int id, std::string login, std::string psw); //конструктор с установкой свойств
    void setUser(int id, std::string login, std::string psw); //установка свойств
    std::string showUser(); //отображение информации о пользователе

    int getId(); //получение ID пользователя
    std::string getLogin(); //получение логина пользователя
    std::string getPsw(); //получение пароля пользователя
private:
    int _id; //ID пользователя
    std::string _login; //логин
    std::string _psw; //пароль
};

