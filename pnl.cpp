#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <string>
#include <queue>
//fifo logic

int fifo(){
  return 0;
}

//lifo logic
int lifo(){
  return 0;
}

std::vector<std::vector<string>> readInput(const string filePath){
  std::vector<std::vector<string>> input;

  std::ifstream file(filePath);
  std::string line;

  while (std::getline(file, line)) {
    std::vector<std::string> row;
    std::stringstream ss(line);
    std::string value;

    while (std::getline(ss, value, ',')) {
        row.push_back(value);
    }

    data.push_back(row);
  }

  file.close();
  return input;
}

int main(int argc, char* argv[]) {
  //get inputs
  std::string filePath = argv[1];
  std::string logic = argv[2];

  //process csv file
  std::vector<std::vector<string>> input = readInput(filePath);

  //different methods based on logic

  if(logic == "FIFO"){
    //fifo(filePath)
  }
  else{

  }

  //std::vector<int> a;
  printf("Hello\n");
  return 0;
}
