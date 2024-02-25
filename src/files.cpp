#include "../includes/files.hpp"

int createSaveFile(std::vector<Block> *blockList) {
    char fileName[] = "data/saveOne";
    int file = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file < 0) return -1;
    
    for (const auto &block : *blockList) if (write(file, &block, sizeof(Block)) < 0) return -1;

    close(file);
    return 1;
}

void readBlocksFromFile(char *fileName, std::vector<Block> *blockList) {
    int file = open("data/saveOne", O_RDONLY);
  
    Block block;
    while (read(file, &block, sizeof(Block)) > 0) {
        blockList->push_back(block);
    }

    close(file);
}