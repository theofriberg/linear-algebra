#include <exception>
#include <string>

class InvalidMatrixFormat : public std::exception
{
public:
    explicit InvalidMatrixFormat(const std::string &message)
        : msg(message) {}

    const char *what() const noexcept override
    {
        return msg.c_str();
    }

private:
    std::string msg;
};