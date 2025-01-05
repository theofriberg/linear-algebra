#pragma once

#include <exception>
#include <string>

class InvalidMatrixFormat : public std::exception
{
public:
    explicit InvalidMatrixFormat(const std::string &message);
    virtual ~InvalidMatrixFormat() noexcept;
    const char *what() const noexcept override;

private:
    std::string msg;
};