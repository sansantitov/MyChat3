#include "Msg.h"
#include "Sfunc.h"
#include <iostream>
#include <ctime>
#include <chrono>


Msg::Msg()
{
     _id = 0;
    _datetime = getTime();
	_message = "";
	_idFrom = 0;
    _idTo = 0;
		
	
}

Msg::Msg(int id, int idFrom, int idTo, std::string message)
{
	
	_id = id;
    _datetime = getTime();
	_message = message;
	_idFrom = idFrom;
    _idTo = idTo;
}

std::string Msg::showMsg()
{
	if (!_message.empty())
	{
        std::string dtStr = _datetime;
        const std::string str = dtStr+": " + _message;
        //std::cout << str;
        return str;
	}
    return "";
}

std::string Msg::getTime()
{
   auto end = std::chrono::system_clock::now();
   std::time_t end_time = std::chrono::system_clock::to_time_t(end);
   std::string ends = std::ctime(&end_time);
   return ends.substr(0,19);
}

int Msg::getIdTo()
{
    return _idTo;
}

std::string Msg::getMessage()
{
    return _message;
}


