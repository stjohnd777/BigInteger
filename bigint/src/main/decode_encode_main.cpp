//
// Created by overman on 4/7/2024.
//
#include <iostream>
#include <string>
#include <vector>

// HEX: Base 16 0,1,2,3,4,5,6,7,8,9, A,B,C,D,E,F
std::vector<char> encodeSequence(const std::string& sequence) {
    std::vector<char> encoded;
    for (size_t i = 0; i < sequence.size(); i += 2) {
        char first = sequence[i] - '0';
        char second = (i + 1 < sequence.size()) ? sequence[i + 1] - '0' : 0; // If odd number of digits, pad with 0
        char combined = (first << 4) | second;
        encoded.push_back(combined);
    }
    return encoded;
}

std::string decodeSequence(const std::vector<char>& encodedSequence) {
    std::string decoded;
    for (char c : encodedSequence) {
        char first = (c >> 4) & 0x0F;
        char second = c & 0x0F;
        decoded += ('0' + first);
        if (second != 0) {
            decoded += ('0' + second);
        }
    }
    return decoded;
}

int main() {
    std::string sequence = "89623754715371538751384651465871936986";
    std::vector<char> encodedSequence = encodeSequence(sequence);

    // Display the encoded sequence
    std::cout << "Encoded sequence: ";
    for (char c : encodedSequence) {
        std::cout << std::hex << (int)c << " ";
    }
    std::cout << std::endl;

    // Decode the encoded sequence
    std::string decodedSequence = decodeSequence(encodedSequence);
    std::cout << "Decoded sequence: " << decodedSequence << std::endl;

    return 0;
}
