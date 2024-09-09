#pragma once

#include <string>
//#include <vector>

std::string choice(std::string, std::string); //выбор в терминале символа с проверкой
bool is_number(const std::string&); //проверка стринга на цифру
void mygetline(char* message, int stage, bool idInput);
//void mygetlineWithoutInput(char* message, int stage);
