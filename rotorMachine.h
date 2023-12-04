#ifndef ROTORMACHINE_H
#define ROTORMACHINE_H

#include <fstream>

const int ROTOR_SIZE = 28;
const int XOR_VALUE = 42;

void buildIni(const char *filename);
void buildRotors(int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE]);
void rotateRotorRight(int rotor[ROTOR_SIZE]);
void rotateRotorLeft(int rotor[ROTOR_SIZE]);
void setRotor1(int rotor[ROTOR_SIZE], int rotations);
void setRotor2(int rotor[ROTOR_SIZE], int rotations);
int charToIndex(char c);
char indexToChar(int index);

void encryptFile(std::ifstream &infile, std::ofstream &outfile, int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE]);
void decryptFile(std::ifstream &infile, std::ofstream &outfile, int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE]);

#endif // ROTORMACHINE_H
