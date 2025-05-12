#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <string>
#include <queue>
#include <unordered_map>
#include <queue>
#include <cmath>

///
/// I used printf because I have some weird issue in env with ostream crashing with cout.
///

struct Trade
{
  int timestamp;
  std::string symbol;
  std::string direction;
  double price;
  int shares;
};

//calculating pnl between two orders
double calculatePnl(std::string direction, int shares1, double price1, int shares2, double price2){
  double bought, sold;
  if(direction == "B"){
    bought = (shares1 * price1);
    sold = shares2 * price2;
    return sold - bought;
  }
  else{
    bought = shares2 * price2;
    sold = shares1 * price1;
    return sold-bought;
  }
}


//fifo logic
void fifo(std::vector<Trade> & input){
  //print header first
  printf("TIMESTAMP,SYMBOL,PNL\n"); 

  // map from symbol to its queue of trades
  std::unordered_map<std::string, std::queue<Trade>> mp;
  
  //loop through all input trades
  for(auto & trade:input){
    //symbol not in map so add to map and continue
    if(mp.find(trade.symbol) == mp.end()){
      mp[trade.symbol] = std::queue<Trade>();
      mp[trade.symbol].push(trade);
      continue;
    }
    
    //trade is opposite from front of queue
    //we need to match it and calculate pnl and output it
    if(mp[trade.symbol].front().direction != trade.direction){
      //loop while queue of orders isnt empty
      std::queue<Trade> & tmp = mp[trade.symbol];
      //output for console
      std::string output = "";
      output += std::to_string(trade.timestamp);
      output += ",";
      output += trade.symbol;
      output += ",";
      double pnl = 0.0;
      
      while(!tmp.empty()){
	//done with operating on order
	if(trade.shares == 0) break;
	//order fully cancels top order
	if(tmp.front().shares <= trade.shares){
	  Trade t = tmp.front();
	  tmp.pop();
	  //reduce current trade shares
	  trade.shares -= t.shares;
	  //get pnl for transaction
	  pnl += calculatePnl(t.direction, t.shares, t.price, t.shares, trade.price);
	  continue;
	}
	//opposite order partiall cancels old order
	else{
	  //get rid of shares from queue
	  tmp.front().shares -= trade.shares;
	  //get pnl from transaction
	  pnl += calculatePnl(tmp.front().direction, trade.shares, tmp.front().price, trade.shares, trade.price);
	  trade.shares = 0;
	}
      }
      //opposite order needs to be added to queue
      if(trade.shares > 0){
	tmp.push(trade);
      }
      //output to console
      output += std::to_string(pnl);
      output += "\n";
      printf(output.c_str());
    }
    
    //trade is same as front of queue so we just add it
    else{
      mp[trade.symbol].push(trade);
    }
   
  }
  
  return;
}

//lifo logic
void lifo(){
  //if I had time I would do similar logic to above but with a stack to deal with
  //newest orders first

  return;
}

std::vector<Trade> readInput(const std::string filePath){
  std::vector<Trade> input;

  std::ifstream file(filePath);
  std::string line;
  
  //read input into vector of trades
  //skip first header line
  std::getline(file,line);
  //rest of input
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string value;
    Trade t;
    
    std::getline(ss, value, ',');
    t.timestamp = std::stoi(value);
    std::getline(ss, t.symbol, ',');
    std::getline(ss, t.direction, ',');
    std::getline(ss, value, ',');
    t.price = std::stod(value);
    std::getline(ss, value, ',');
    t.shares = std::stoi(value);
    
    input.push_back(t);
  }

  file.close();
  return input;
}

int main(int argc, char* argv[]) {
  //get inputs
  std::string filePath, logic;
  if(argc > 1){
    filePath = argv[1];
    logic = argv[2];
  }
  else{
    return 0;
  }

  //process csv file
  std::vector<Trade> input = readInput(filePath);

  //different methods based on logic

  if(logic == "fifo"){
    fifo(input);
  }
  else if(logic == "lifo"){
    //result = lifo(filePath);
  }
  else{
    return 1;
  }
  
  return 0;
}
