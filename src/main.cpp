#include "CardSet.h"
#include "SFMT.h"

#include <iostream>
#include <stdint.h>

#include "immintrin.h"


namespace poker {

namespace {
Card _JC(Rank::J, Color::CLUBS);

Card _2C(Rank::_2, Color::CLUBS);
Card _2D(Rank::_2, Color::DIAMONDS);
Card _2H(Rank::_2, Color::HEARTS);
Card _2S(Rank::_2, Color::SPADES);

Card _3C(Rank::_3, Color::CLUBS);
Card _3D(Rank::_3, Color::DIAMONDS);
Card _3H(Rank::_3, Color::HEARTS);
Card _3S(Rank::_3, Color::SPADES);

Card _4C(Rank::_4, Color::CLUBS);
Card _4D(Rank::_4, Color::DIAMONDS);
Card _4H(Rank::_4, Color::HEARTS);
Card _4S(Rank::_4, Color::SPADES);

Card _5C(Rank::_5, Color::CLUBS);
Card _5D(Rank::_5, Color::DIAMONDS);
Card _5H(Rank::_5, Color::HEARTS);
Card _5S(Rank::_5, Color::SPADES);

Card _6C(Rank::_6, Color::CLUBS);
Card _6D(Rank::_6, Color::DIAMONDS);
Card _6H(Rank::_6, Color::HEARTS);
Card _6S(Rank::_6, Color::SPADES);

Card _7C(Rank::_7, Color::CLUBS);
Card _7D(Rank::_7, Color::DIAMONDS);
Card _7H(Rank::_7, Color::HEARTS);
Card _7S(Rank::_7, Color::SPADES);

Card _8C(Rank::_8, Color::CLUBS);
Card _8D(Rank::_8, Color::DIAMONDS);
Card _8H(Rank::_8, Color::HEARTS);
Card _8S(Rank::_8, Color::SPADES);

Card _9C(Rank::_9, Color::CLUBS);
Card _9D(Rank::_9, Color::DIAMONDS);
Card _9H(Rank::_9, Color::HEARTS);
Card _9S(Rank::_9, Color::SPADES);

Card _QC(Rank::Q, Color::CLUBS);
Card _QD(Rank::Q, Color::DIAMONDS);
Card _QH(Rank::Q, Color::HEARTS);
Card _QS(Rank::Q, Color::SPADES);

Card _KC(Rank::K, Color::CLUBS);
Card _KD(Rank::K, Color::DIAMONDS);
Card _KH(Rank::K, Color::HEARTS);
Card _KS(Rank::K, Color::SPADES);

Card _AC(Rank::A, Color::CLUBS);
Card _AD(Rank::A, Color::DIAMONDS);
Card _AH(Rank::A, Color::HEARTS);
Card _AS(Rank::A, Color::SPADES);

}

inline unsigned long long rdtsc(void) {
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long long) lo) | (((unsigned long long) hi) << 32);
}

uint64_t eval(CardSet cs) {
    uint64_t start = rdtsc();
    cs.rankTexasHoldem();
    return rdtsc() - start;
}

void run() {
    for(int i=0; i<10000; ++i) {
        eval(CardSet({ _6D, _6S, _8D, _9H, _9S, _AC, _2C }));
        eval(CardSet({ _6D, _6S, _8D, _9D, _4D, _AD, _QC }));
    }

    uint64_t t0 = eval(CardSet({ _6D, _6S, _8D, _9H, _9S, _AC, _2C }));
    uint64_t t1 = eval(CardSet({ _6D, _6S, _8D, _9H, _9S, _AC, _2C }));
    uint64_t t2 = eval(CardSet({ _6D, _6S, _8D, _9H, _9S, _AC, _2C }));
    uint64_t o1 = eval(CardSet({ _6D, _6S, _8D, _9H, _4S, _AC, _2C }));
    uint64_t f1 = eval(CardSet({ _6D, _6S, _8D, _9D, _4D, _AD, _QC }));
    uint64_t f2 = eval(CardSet({ _6D, _6S, _8D, _9D, _4D, _AD, _QC }));
    uint64_t d0 = eval(CardSet({ _6D, _6S, _6S, _9D, _4D, _AD, _QC }));

    std::cout << "Two Pairs: " << t0 << std::endl;
    std::cout << "Two Pairs: " << t1 << std::endl;
    std::cout << "One Pair: " << o1 << std::endl;
    std::cout << "Two Pairs: " << t2 << std::endl;
    std::cout << "Flush: " << f1 << std::endl;
    std::cout << "Flush: " << f2 << std::endl;
    std::cout << "Three: " << d0 << std::endl;
}

}

int main() {

    sfmt_t sfmt;
    sfmt_init_gen_rand(&sfmt, 12345);

    uint32_t random = sfmt_genrand_uint32(&sfmt);
    std::cout << random << std::endl;

    poker::run();

}
