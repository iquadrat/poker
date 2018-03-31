#include "CardSet.h"

#include <iostream>

namespace poker {

void run() {
    CardSet cs;
    HandRanking ranking = cs.rankTexasHoldem();
    if (ranking.getRanking() == HandRanking::FOUR_OF_A_KIND) {
        std::cout << "Poker!" << std::endl;
    }

}


}

int main() {


    poker::run();


}
