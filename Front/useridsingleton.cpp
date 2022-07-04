#include "useridsingleton.h"

UserIdSingleton* UserIdSingleton::userId{nullptr};

std::mutex UserIdSingleton::mutex;


UserIdSingleton *UserIdSingleton::GetInstance(const std::string& value)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (userId == nullptr)
    {
        userId = new UserIdSingleton(value);
    }
    return userId;
}

