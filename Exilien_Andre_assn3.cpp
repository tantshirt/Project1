#include "rotorMachine.h"
#include <iostream>
#include <fstream>
#include <cstring>

void printUsage() {
    std::cerr << "Usage:\n"
              << "./Exilien_Andre_assn3 -i <file>\n"
              << "./Exilien_Andre_assn3 -e <file1> <file2> -r <r1> <r2>\n"
              << "./Exilien_Andre_assn3 -d <file1> <file2> -r <r1> <r2>\n"
              << "./Exilien_Andre_assn3 -e <file1> <file2> -r <r1> <r2> -i <file>\n"
              << "./Exilien_Andre_assn3 -d <file1> <file2> -r <r1> <r2> -i <file>\n";
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printUsage();
    }

    int rotor1[ROTOR_SIZE], rotor2[ROTOR_SIZE];
    bool initialize = false, encrypt = false, decrypt = false;
    char *inputFile = nullptr, *outputFile = nullptr, *configFile = nullptr;
    int rotations1 = 0, rotations2 = 0;

    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc) {
                configFile = argv[++i];
                initialize = true;
            } else {
                printUsage();
            }
        } else if (strcmp(argv[i], "-e") == 0) {
            if (i + 2 < argc) {
                inputFile = argv[++i];
                outputFile = argv[++i];
                encrypt = true;
            } else {
                printUsage();
            }
        } else if (strcmp(argv[i], "-d") == 0) {
            if (i + 2 < argc) {
                inputFile = argv[++i];
                outputFile = argv[++i];
                decrypt = true;
            } else {
                printUsage();
            }
        } else if (strcmp(argv[i], "-r") == 0) {
            if (i + 2 < argc) {
                rotations1 = atoi(argv[++i]);
                rotations2 = atoi(argv[++i]);
            } else {
                printUsage();
            }
        }
    }

    if (initialize) {
        buildIni(configFile);
    }

    if ((encrypt || decrypt) && !inputFile) {
        std::cerr << "Error: No input file specified." << std::endl;
        printUsage();
    }

    if ((encrypt || decrypt) && !outputFile) {
        std::cerr << "Error: No output file specified." << std::endl;
        printUsage();
    }

    buildRotors(rotor1, rotor2);
    setRotor1(rotor1, rotations1);
    setRotor2(rotor2, rotations2);

    std::ifstream infile(inputFile);
    std::ofstream outfile(outputFile);

    if (!infile) {
        std::cerr << "Error: Input file not found." << std::endl;
        exit(1);
    }

    if (encrypt) {
        encryptFile(infile, outfile, rotor1, rotor2);
    } else if (decrypt) {
        decryptFile(infile, outfile, rotor1, rotor2);
    }

    infile.close();
    outfile.close();

    return 0;
}
