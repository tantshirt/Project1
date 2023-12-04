#include "rotorMachine.h"
#include <fstream>
#include <iostream>
#include <ctype.h>

// ini function 
void buildIni(const char *filename) {
    std::ifstream config(filename);
    if (!config) {
        std::cerr << "Error: Configuration file not found." << std::endl;
        exit(1);
    }

    std::ofstream ini("rotors.ini", std::ios::binary);
    int value;

    while (config >> value) {
        value ^= XOR_VALUE;
        ini.write(reinterpret_cast<char*>(&value), sizeof(value));
    }

    config.close();
    ini.close();
}

// make rotor arrays from the rotors.ini file
void buildRotors(int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE]) {
    std::ifstream ini("rotors.ini", std::ios::binary);
    if (!ini) {
        std::cerr << "Error: Rotor machine not initialized. Run with -i option and provide an appropriate configuration file." << std::endl;
        exit(1);
    }

    int value;
    //rotor1
    for (int i = 0; i < ROTOR_SIZE; ++i) {
        if (!(ini.read(reinterpret_cast<char*>(&value), sizeof(value)))) {
            std::cerr << "Error: Not enough values in rotors.ini to populate rotor1." << std::endl;
            exit(1);
        }
        rotor1[i] = value ^ XOR_VALUE;
    }

    // rotor2
    for (int i = 0; i < ROTOR_SIZE; ++i) {
        if (!(ini.read(reinterpret_cast<char*>(&value), sizeof(value)))) {
            std::cerr << "Error: Not enough values in rotors.ini to populate rotor2." << std::endl;
            exit(1);
        }
        rotor2[i] = value ^ XOR_VALUE;
    }

    ini.close();
}

// move rotor to the right
void rotateRotorRight(int rotor[ROTOR_SIZE]) {
    int last = rotor[ROTOR_SIZE - 1];
    for (int i = ROTOR_SIZE - 1; i > 0; --i) {
        rotor[i] = rotor[i - 1];
    }
    rotor[0] = last;
}

//move rotor to the left
void rotateRotorLeft(int rotor[ROTOR_SIZE]) {
    int first = rotor[0];
    for (int i = 0; i < ROTOR_SIZE - 1; ++i) {
        rotor[i] = rotor[i + 1];
    }
    rotor[ROTOR_SIZE - 1] = first;
}

// set rotor1
void setRotor1(int rotor[ROTOR_SIZE], int rotations) {
    for (int i = 0; i < rotations; ++i) {
        rotateRotorRight(rotor);
    }
}

// set rotor2
void setRotor2(int rotor[ROTOR_SIZE], int rotations) {
    for (int i = 0; i < rotations; ++i) {
        rotateRotorLeft(rotor);
    }
}

//  convert a character 
int charToIndex(char c) {
    c = toupper(c);
    if (c == ' ') return 26;
    if (c == '.') return 27;
    return c - 'A';
}

// Function to convert an index in the rotor back to a character
char indexToChar(int index) {
    if (index == 26) return ' ';
    if (index == 27) return '.';
    return index + 'A';
}

// encrypt 
void encryptFile(std::ifstream &infile, std::ofstream &outfile, int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE]) {
    char line[256];
    while (infile.getline(line, sizeof(line))) {
        for (int i = 0; line[i] != '\0'; ++i) {
            int index = charToIndex(line[i]);
            // Pass through rotor1 then rotor2
            index = rotor2[rotor1[index]];
            line[i] = indexToChar(index);
            // Rotate rotors after each character
            rotateRotorRight(rotor1);
            rotateRotorLeft(rotor2);
        }
        outfile << line << '\n';
    }
}

//  decrypt 
void decryptFile(std::ifstream &infile, std::ofstream &outfile, int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE]) {
    char line[256];
    while (infile.getline(line, sizeof(line))) {
        for (int i = 0; line[i] != '\0'; ++i) {
            int index = charToIndex(line[i]);
            for (int j = 0; j < ROTOR_SIZE; ++j) {
                if (rotor2[j] == index) {
                    index = j;
                    break;
                }
            }
            for (int j = 0; j < ROTOR_SIZE; ++j) {
                if (rotor1[j] == index) {
                    index = j;
                    break;
                }
            }
            line[i] = indexToChar(index);
            // Rotate rotors after each character
            rotateRotorRight(rotor1);
        }
        outfile << line << '\n';
    }
}
