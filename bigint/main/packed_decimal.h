#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

std::vector<std::uint8_t> encodeSequence(const std::string &sequence);
std::string decodeSequence(const std::vector<std::uint8_t> &encoded, std::size_t digitCount);
