// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <iostream>
#include <vector>

std::vector<char> get_message(int number_hash) {

    std::string input;

    std::cout << "\nEnter the " << number_hash<< "st string to hash: ";
    std::getline(std::cin, input);

    std::vector<char> message(input.begin(), input.end());

    return message;
}

std::vector<int> convert_ascii(const std::vector<char> &original_message) {
    std::vector<int> ascii_message;
    ascii_message.reserve(original_message.size());

    for (char c: original_message) {
        ascii_message.push_back(static_cast<int>(c));
    }

    return ascii_message;
}

std::vector<int> hash_func(int number_hash){
    std::vector<char> original_message = get_message(number_hash);
    std::vector<int> ascii_message = convert_ascii(original_message);
    std::vector<int> hash_message;


    int adder = 10;

    int first_size = ascii_message.size() % 16;

    if (first_size != 16 or ascii_message.empty()) {
        for (int i = 0; i != 16 - first_size; i++) {
            ascii_message.push_back(adder + ascii_message[i]);
            adder++;
        }
    }

    for (int i = 0; i < 16; i++) {
        hash_message.push_back(ascii_message[i]);
    }

    int offset = 15;
    if (ascii_message.size() / 16 > 1) {
        for (int i = 0; i < ascii_message.size() / 16; i++) {

            for (int j = 0; j < 16; j++) {
                hash_message[j] += ascii_message[j + offset] xor
                                   (j != 15 ? ascii_message[j + offset + 1] : ascii_message[j + offset - 2]) + adder;
                adder++;
            }
            offset += 16;
        }
    }

    for (int i = 0; i < 16; i++) {
        hash_message[i] += ascii_message[15 - i];

        if (hash_message[i] < 0) {
            hash_message[i] = -hash_message[i];
        }

        while (hash_message[i] >= 10) {
            hash_message[i] = hash_message[i] % 10;
        }
    }

    std::cout << "Hash: ";
    for (int i = 0; i < 16; i++) {
        std::cout << hash_message[i];
    }

    return hash_message;
}



int main() {
    std::vector<int> hash_message1 = hash_func(1);
    std::vector<int> hash_message2 = hash_func(2);

    if (hash_message1 == hash_message2){
        printf("\nIncoming messages one and two are the same");
    } else {
        printf("\nIncoming messages are different");
    }
    return 0;
}
