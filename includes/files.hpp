#include <unistd.h>
#include <fcntl.h>
#include "../includes/globals.hpp"

int createSaveFile(std::vector<Block> *blockList);

void readBlocksFromFile(char *fileName, std::vector<Block> *blockList);