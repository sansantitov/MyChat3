#include "main.h"
#include "Sfunc.h"
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


bool is_number(const std::string& s) 
{ 
    return !s.empty() && (s.find_first_not_of("0123456789") == s.npos); 
}

std::string getStageStr(int stage)
{
    if (stage == 1) return "Логин";
    else if (stage == 2) return "Пароль";
    else if (stage == 3) return "Новый логин";
    else if (stage == 4) return "Новый пароль";
    else if (stage == 5) return "Пакет сообщений";
    else if (stage == 6) return "Конец пакета сообщений";
    else if (stage == 7) return "Пакет пользователей";
    else if (stage == 8) return "Ввод Id пользователя";
    else if (stage == 9) return "Сообщение";

    return "";
}

