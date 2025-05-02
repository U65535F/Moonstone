#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Moonstone.h"

int main()
{
    setlocale(LC_ALL, "");

    wchar_t original[] = L"This is my original text that needs to be encrypted.";
    wchar_t key[] = L"MySecretKey123";

    size_t maxLength = wcslen(original) + 1;
    wchar_t* encrypted = malloc(sizeof(wchar_t) * maxLength);
    wchar_t* decrypted = malloc(sizeof(wchar_t) * maxLength);

    // Required for decryption process
    uint64_t seed = 0;
    uint64_t length = 0;

    wprintf(L"Original:  %ls\n", original);

    if (!MoonstoneCipher(original, key, &seed, &length, encrypted)) {
        wprintf(L"Encryption failed.\n");
        return 1;
    }

    // Directly printing the encrypted data sometimes can corrupt stdout buffer, which can corrupt decrypted data too. So we are using hex system.
    wprintf(L"Encrypted (hex): ");
    for (size_t i = 0; i < length; i++) {
        wprintf(L"%04x ", encrypted[i]);
    }
    wprintf(L"\n");

    if (!MoonstoneDecipher(encrypted, key, seed, length, decrypted)) {
        wprintf(L"Decryption failed.\n");
        return 1;
    }

    decrypted[length] = L'\0';
    wprintf(L"Decrypted: %ls\n", decrypted);
    wprintf(L"The decrypted data does %smatch with original data.\n", wcscmp(original, decrypted) != 0 ? L"NOT " : "");

    free(encrypted);
    free(decrypted);
    return 0;
}
