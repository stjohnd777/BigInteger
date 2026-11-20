#include "packed_decimal.h"

#include <stdexcept>

std::vector<std::uint8_t> encodeSequence(const std::string &sequence) {
    std::vector<std::uint8_t> encoded;
    encoded.reserve(sequence.size() / 2 + sequence.size() % 2);
    for (std::size_t i = 0; i < sequence.size(); i += 2) {
        if (sequence[i] < '0' || sequence[i] > '9' ||
            (i + 1 < sequence.size() && (sequence[i + 1] < '0' || sequence[i + 1] > '9'))) {
            throw std::invalid_argument("packed decimal requires digits");
        }
        const auto first = static_cast<std::uint8_t>(sequence[i] - '0');
        const auto second = i + 1 < sequence.size() ? static_cast<std::uint8_t>(sequence[i + 1] - '0') : 0;
        encoded.push_back(static_cast<std::uint8_t>((first << 4) | second));
    }
    return encoded;
}

std::string decodeSequence(const std::vector<std::uint8_t> &encoded, std::size_t digitCount) {
    if (encoded.size() != digitCount / 2 + digitCount % 2)
        throw std::invalid_argument("packed decimal length does not match");

    std::string decoded;
    decoded.reserve(digitCount);
    for (std::size_t i = 0; i < encoded.size(); ++i) {
        const auto first = encoded[i] >> 4;
        const auto second = encoded[i] & 0x0f;
        if (first > 9 || second > 9 ||
            (i + 1 == encoded.size() && digitCount % 2 != 0 && second != 0))
            throw std::invalid_argument("invalid packed decimal digit or padding");
        decoded.push_back(static_cast<char>('0' + first));
        if (decoded.size() < digitCount) decoded.push_back(static_cast<char>('0' + second));
    }
    return decoded;
}
