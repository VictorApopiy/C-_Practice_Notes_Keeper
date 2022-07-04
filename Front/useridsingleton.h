#ifndef USERIDSINGLETON_H
#define USERIDSINGLETON_H
#include <iostream>
#include <mutex>
#include <thread>

class UserIdSingleton
{
private:
    static UserIdSingleton * userId;
    static std::mutex mutex;

protected:
    UserIdSingleton(const std::string value): value_(value)
    {
    }
    ~UserIdSingleton() {}
    std::string value_;

public:

    UserIdSingleton(UserIdSingleton &other) = delete;

    void operator=(const UserIdSingleton &) = delete;

    static UserIdSingleton *GetInstance(const std::string& value);

    std::string value() const{
        return value_;
    }
};
#endif // USERIDSINGLETON_H
