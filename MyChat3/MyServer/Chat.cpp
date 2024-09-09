#include "Chat.h"
#include <vector>
#include <memory>
#include "User.h"
#include "Msg.h"

extern std::vector<User> users;
extern std::vector<Msg> msgs;

 Chat::Chat()
 {
     users.emplace_back(0,"All","1");
     _userIdMax = 0; //0-зарезервировано для выдачи всем
     _msgIdMax = -1;
 }


 int Chat::findUserLogin(std::string login)
 {
     int id = -1;
     for (unsigned int i = 0; i < users.size(); ++i)
     {
         if (users[i].getLogin() == login)
         {
             id = users[i].getId();
             break;
         }
     }
     return id;
 }


 void Chat::addUser(std::string login, std::string password)
{
    std::unique_ptr<User> u = std::make_unique<User>(++_userIdMax, login, password);
    users.push_back(*u);
}

int Chat::findUserIdByLoginPassword(std::string login, std::string password)
{
    int id = -1;
    for (unsigned int i = 0; i < users.size(); ++i)
    {
        if (users[i].getLogin() == login && users[i].getPsw() == password)
        {
            id = users[i].getId();
            break;
        }
    }
    return id;
}

std::string Chat::findUserNameByUserId(int idUser)
{
    std::string name;
    for (unsigned int i = 0; i < users.size(); ++i)
    {
        if (users[i].getId() == idUser)
        {
            name = users[i].getLogin();
            break;
        }
    }
    return name;
}




std::vector<std::string> Chat::showUsers()
{
    std::vector<std::string> result;

    result.emplace_back("--- ID  Login пользователя -----------");

    if (users.size() > 1)
    {
        for (unsigned int i = 1; i < users.size(); ++i)
        {
            result.emplace_back(users[i].showUser());
        }
    }
    result.emplace_back("------------------------------------");
    return result;
}

void Chat::sendMsg(int userId,int userIdTo, std::string message)
{
    std::string userName = findUserNameByUserId(userId);
    std::unique_ptr<Msg> m = std::make_unique<Msg>(++_msgIdMax, userId, userIdTo, message);
    msgs.push_back(*m);
}

std::vector<std::string> Chat::showMsgs(int userId)
{
    std::vector<std::string> result;
    std::string userLogin = findUserNameByUserId(userId);
    result.emplace_back("******** " + userLogin + ": принятые сообщения *******");
    for (unsigned int i = 0; i < msgs.size(); ++i)
    {
        if (msgs[i].getIdTo() == 0 || msgs[i].getIdTo() == userId) result.emplace_back(msgs[i].showMsg());
    }
    std::string s(37+userLogin.length(), '*');
    result.emplace_back(s);
    return result;
}

