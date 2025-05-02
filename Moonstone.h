#ifndef MOONSTONE_H
#define MOONSTONE_H
#endif

#include <stdint.h>
#include <time.h>
#include <wchar.h>

// SplitMix64 pseudo random number generator (PRNG)
static uint64_t state = 0;
static void seed(uint64_t _seed) { state = _seed; }
static inline uint64_t sm64()
{
    uint64_t z = (state += 0x9E3779B97F4A7C15);
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EB;
    return z ^ (z >> 31);
}

int MoonstoneCipher(wchar_t* plainText, wchar_t* key, uint64_t* outSeed, uint64_t* outLength, wchar_t* cipherText)
{
    uint64_t textLength = wcslen(plainText);
    uint64_t keyLength = wcslen(key);
    if (textLength == 0 || keyLength == 0) 
        return 0;
    
    seed((uint64_t)time(0));
    uint64_t seedValue = sm64();
    uint64_t reducedSeed = seedValue % keyLength;
    if (reducedSeed == 0)
        reducedSeed++;

    uint64_t mixValue = reducedSeed;

    wchar_t* output = cipherText ? cipherText : plainText;
    for (uint64_t i = 0; i < textLength; i++) {
        mixValue &= (reducedSeed ^ i);
        mixValue |= textLength;
        output[i] = plainText[i] ^ key[((mixValue ^ i) & textLength) % reducedSeed];
    }

    *outSeed = seedValue;
    *outLength = textLength;
    return 1;
}

int MoonstoneDecipher(wchar_t* cipherText, wchar_t* key, uint64_t seedValue, uint64_t textLength, wchar_t* plainText)
{
    if (seedValue == 0 || textLength == 0) 
        return 0;
    
    uint64_t keyLength = wcslen(key);
    uint64_t reducedSeed = seedValue % keyLength;
    if (reducedSeed == 0) 
        reducedSeed++;

    uint64_t mixValue = seedValue;
    wchar_t* output = plainText ? plainText : cipherText;

    for (uint64_t i = 0; i < textLength; i++) {
        mixValue &= (reducedSeed ^ i);
        mixValue |= textLength;
        output[i] = cipherText[i] ^ key[((mixValue ^ i) & textLength) % reducedSeed];
    }

    return 1;
}
