# Moonstone
A cipher based on XOR cipher. <br>
It uses key, seed and length of data to decrypt the data. <br>
Try to avoid this cipher in applications where security is crucial, It's recommended to use other strong cipher like AES, ChaCha, RSA, etc. <br>
Use this cipher for educational purposes and in small non-commericial applications.

# How to use?
**Cipher** <br>
```cpp
int MoonstoneCipher(wchar_t* plainText, wchar_t* key, uint64_t* outSeed, uint64_t* outLength, wchar_t* cipherText)
```
Parameters: <br>
`plainText` = Unicode array which needs to be encrypted. <br>
`key` = Unicode array which contains the key. <br>
`outSeed` = Pointer to `uint64_t` variable that will receive the seed. <br>
`outLength` = Pointer to `uint64_t` variable that will receive length of data. <br>
`cipherText` = Pointer to the unicode array which will receive the encrypted data. If this is 0 then the encrypted data will be written to the `plainText` buffer from parameter. 

Return: <br>
`0` = failure <br>
`1` = success

**Decipher** <br>
```cpp
int MoonstoneDecipher(wchar_t* cipherText, wchar_t* key, uint64_t seedValue, uint64_t textLength, wchar_t* plainText)
```
Parameters: <br>
`cipherText` = Unicode array which needs to be decrypted. <br>
`key` = Unicode array which contains the key. <br>
`seedValue` = Seed received by the `MoonstoneCipher` for decryption. <br>
`textLength` = `outLength` received by the `MoonstoneCipher` for decryption. <br>
`plainText` = Pointer to the unicode array which will receive the decrypted data. If this is 0 then the decrypted data will be written to the `cipherText` buffer from parameter. 

Return: <br>
`0` = failure <br>
`1` = success

# Result
The result of ciphered text are different each sequence. <br>
Sequence 1:
```
Original:  This is my original text that needs to be encrypted.
Encrypted (hex): 002d 0011 0010 000a 006d 0024 003e 006d 0014 0000 0059 0016 003f 0024 002a 0024 0023 002c 0021 006d 0027 0036 002b 0027 006d 0039 0025 002c 0027 0073 003d 0036 0036 0037 0020 0073 000d 0016 0059 001b 0036 0073 0036 003d 001a 000b 0000 0009 000d 001c 001d 0057
Decrypted: This is my original text that needs to be encrypted.
The decrypted data does match with original data.
```
Sequence 2:
```
Original:  This is my original text that needs to be encrypted.
Encrypted (hex): 0019 0025 0024 003e 006d 0024 003e 006d 0020 0034 006d 0022 003f 0024 002a 0024 0023 002c 0021 006d 0039 0028 0035 0039 006d 0039 0025 002c 0039 006d 0023 0028 0028 0029 003e 006d 0039 0022 006d 002f 0028 006d 0028 0023 002e 003f 0034 003d 0039 0028 0029 0063
Decrypted: This is my original text that needs to be encrypted.
The decrypted data does match with original data.
```

# Credits
Special thanks to Nathan ([@snowballlearth](https://github.com/snowballearth), 🇮🇩) for writing base of Moonstone. This is the improved version of it. The original code is preserved at `original` branch of this repository.
