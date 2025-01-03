#include <exception>
#include <string>

class InvalidMatrixFormat : public std::exception
{
public:
    explicit InvalidMatrixFormat(const std::string &message);
    const char *what() const noexcept override;

private:
    std::string msg;
};