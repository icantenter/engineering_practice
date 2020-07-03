#pragma once
#include <iostream>
#include <string>
enum error_index
{
    ERROR_ARGUMENT = 0,
    ERROR_FILE_OPERATION = 1,
    ERROR_ACCESS_DENIED = 2,
};

static const std::string error_msgs[] = { // error messages
    "invalid argument", "file operation not permitted", "access denied"};