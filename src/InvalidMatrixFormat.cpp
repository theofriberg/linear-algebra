#include "../include/InvalidMatrixFormat.hpp"

#include <string>

InvalidMatrixFormat::InvalidMatrixFormat(const std::string &message)
    : msg(message) {}

InvalidMatrixFormat::~InvalidMatrixFormat() noexcept = default;

const char *InvalidMatrixFormat::what() const noexcept
{
    return msg.c_str();
}
