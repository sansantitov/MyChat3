#include "main.h"
#include "Cfunc.h"
#include <iostream>
#include <cstring>

std::string choice(std::string str, std::string choices)
{
    const char *array = choices.c_str();
    std::string choice = " ";
    while (!(choice.length() == 1 && strchr(array, choice[0])))
    {
        std::cout << str << std::endl;
        getline(std::cin, choice);
    }
    return choice;
}

void mygetline(char* message, int stage, bool isInput)
{
    std::string cc = "";
    if (isInput)
    {
        if (stage == 1) std::cout << "Логин (выход-0): " << std::endl;
        else if (stage == 2) std::cout << "Пароль: " << std::endl;
        else if (stage == 3) std::cout << "Новый логин: " << std::endl;
        else if (stage == 4) std::cout << "Новый пароль: " << std::endl;
        else if (stage == 5) std::cout << "Пакет принятых сообщений" << std::endl;
        else if (stage == 6) std::cout << "Конец пакета принятых сообщений" << std::endl;
        else if (stage == 7) std::cout << "Пакет пользователей" << std::endl;
        else if (stage == 8) std::cout << "Кому послать (ID user) 0-всем: " << std::endl;
        else if (stage == 9) std::cout << "Сообщение (выход-0):" << std::endl;
        getline(std::cin, cc);
    }
    memset(message,0,MESSAGE_LENGTH);
    cc = std::to_string(stage/10)+std::to_string(stage%10) + cc;
    int n = cc.length();
    const char* cstr = cc.c_str();
    std::strncpy(message, cstr, n);
}

bool is_number(const std::string& s) 
{ 
    return !s.empty() && (s.find_first_not_of("0123456789") == s.npos); 
}
