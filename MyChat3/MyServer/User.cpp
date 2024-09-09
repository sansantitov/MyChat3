#include "User.h"

User::User()
{

	_id = -1;
	_login = "";
	_psw = "";
}


User::User(int id, std::string login, std::string psw)
{
	_id = id;
	_login = login;
	_psw = psw;
}


void User::setUser(int id, std::string login, std::string psw)
{
	_id = id;
	_login = login;
	_psw = psw;
}

std::string User::showUser()
{
    const std::string str = "     " + std::to_string( _id) + "  " + _login;
    return str;
}

int User::getId()
{
    return _id;
}

std::string User::getLogin()
{
    return _login;
}

std::string User::getPsw()
{
    return _psw;
}

