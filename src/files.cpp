#include "../includes/files.hpp"

void createSaveFile(std::vector<Block> *blockList) {
    char fileName[] = "data/saveOne";
    int file = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    for (const auto &block : *blockList) {
        write(file, &block, sizeof(Block));
    }

    close(file);
}

void readBlocksFromFile(char *fileName, std::vector<Block> *blockList) {
    int file = open("data/saveOne", O_RDONLY);
  
    Block block;
    while (read(file, &block, sizeof(Block)) > 0) {
        blockList->push_back(block);
    }

    close(file);
}