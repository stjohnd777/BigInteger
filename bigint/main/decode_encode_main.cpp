//
// Created by overman on 4/7/2024.
//
#include <iostream>
#include <string>
#include <vector>
#include "packed_decimal.h"

int main() {
    std::string sequence = "89623754715371538751384651465871936986";
    auto encodedSequence = encodeSequence(sequence);

    // Display the encoded sequence
    std::cout << "Encoded sequence: ";
    for (auto c : encodedSequence) {
        std::cout << std::hex << (int)c << " ";
    }
    std::cout << std::endl;

    // Decode the encoded sequence
    std::string decodedSequence = decodeSequence(encodedSequence, sequence.size());
    std::cout << "Decoded sequence: " << decodedSequence << std::endl;

    return 0;
}
