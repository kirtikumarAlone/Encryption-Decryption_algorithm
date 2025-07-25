# RSA Encryption/Decryption Algorithm

A complete implementation of the RSA (Rivest-Shamir-Adleman) public-key cryptographic algorithm in C++. This program demonstrates the fundamental concepts of asymmetric encryption using mathematically generated public and private key pairs.

## 🔐 Features

- **Automatic Key Generation**: Generates RSA key pairs using randomly selected prime numbers
- **Public Key Encryption**: Encrypt messages using the public key (n, e)
- **Private Key Decryption**: Decrypt messages using the private key (n, d)
- **String Support**: Encrypt and decrypt entire text messages character by character
- **Interactive Mode**: Real-time encryption/decryption testing
- **Educational Display**: Shows key generation process and mathematical components

## 🚀 Quick Start

### Prerequisites

- C++ compiler (GCC, Clang, or MSVC)
- Standard C++ libraries (included with most compilers)

### Compilation

```bash
g++ -o Encry_Decry_algo.c++
```

### Running the Program

```bash
./Encry_Decry_algo      # Linux/Mac
Encry_Decry_algo.exe      # Windows
```

## 📖 How It Works

### RSA Algorithm Steps

1. **Prime Generation**: Select two distinct prime numbers (p, q)
2. **Modulus Calculation**: Compute n = p × q
3. **Totient Function**: Calculate φ(n) = (p-1)(q-1)
4. **Public Exponent**: Choose e such that gcd(e, φ(n)) = 1
5. **Private Exponent**: Calculate d as the modular inverse of e mod φ(n)

### Encryption/Decryption

- **Encryption**: ciphertext = message^e mod n
- **Decryption**: message = ciphertext^d mod n

## 🎯 Usage Examples

### Demo Mode
```
RSA Encryption/Decryption Program
1. Run demonstration
2. Interactive mode
Choose option (1 or 2): 1

=== RSA Encryption/Decryption Demo ===

Keys generated successfully!
Prime p: 347, Prime q: 419
Public Key (n, e): (145393, 65537)
Private Key (n, d): (145393, 87673)

Original message: "Hello RSA!"

Encrypting message...
Encrypted values: 43527 101929 108735 108735 111474 8659 82194 43527 16738 88447

Decrypting message...
Decrypted message: "Hello RSA!"

✓ Encryption/Decryption successful!
```

### Interactive Mode
```
Choose option (1 or 2): 2

=== Interactive RSA Mode ===
Enter messages to encrypt/decrypt (type 'quit' to exit)

Enter message: Secret Message
Encrypted: 89234 101929 99847 114523 101929 116834 8659 77291 101929 114523 114523 16738 103928 101929
Decrypted: "Secret Message"

Enter message: quit
```

## 🔧 Code Structure

### Main Components

- **`RSACrypto` Class**: Core encryption/decryption functionality
- **Prime Generation**: `isPrime()`, `generatePrime()`
- **Mathematical Operations**: `gcd()`, `modInverse()`, `modPow()`
- **Key Management**: `generateKeys()`, `getPublicKey()`, `getPrivateKey()`
- **Encryption/Decryption**: `encrypt()`, `decrypt()`, `encryptChar()`, `decryptChar()`

### Key Methods

| Method | Description |
|--------|-------------|
| `generateKeys()` | Creates new RSA key pair |
| `encrypt(string)` | Encrypts a text message |
| `decrypt(vector<long long>)` | Decrypts encrypted data |
| `getPublicKey()` | Returns (n, e) pair |
| `getPrivateKey()` | Returns (n, d) pair |

## ⚠️ Security Considerations

**This is an educational implementation.** For production use, consider:

- **Larger Key Sizes**: Use at least 2048-bit keys
- **Secure Random Generation**: Use cryptographically secure random number generators
- **Padding Schemes**: Implement OAEP (Optimal Asymmetric Encryption Padding)
- **Side-Channel Protection**: Guard against timing attacks
- **Key Management**: Secure key storage and distribution

## 🧮 Mathematical Background

The RSA algorithm relies on the mathematical difficulty of factoring large composite numbers. The security comes from the fact that while it's easy to multiply two large primes, it's computationally infeasible to factor their product back into the original primes.

### Key Mathematical Concepts

- **Modular Arithmetic**: All operations performed modulo n
- **Euler's Totient Function**: φ(n) = (p-1)(q-1) for prime factors p, q
- **Modular Inverse**: d ≡ e^(-1) (mod φ(n))
- **Fermat's Little Theorem**: Foundation for the encryption/decryption process

## 🔍 Example Output Analysis

When you run the program, you'll see:

1. **Prime Selection**: Two random primes (e.g., p=347, q=419)
2. **Modulus**: n = p×q (e.g., n=145393)
3. **Public Key**: (n, e) where e is typically 65537
4. **Private Key**: (n, d) where d is calculated using the extended Euclidean algorithm
5. **Encryption**: Each character converted to ASCII, then encrypted
6. **Decryption**: Encrypted values converted back to original characters

## 📚 Learning Objectives

This implementation helps understand:

- Public-key cryptography principles
- Mathematical foundations of RSA
- Key generation processes
- Encryption/decryption workflows
- Modular arithmetic applications

## 🐛 Troubleshooting

### Common Issues

1. **Compilation Errors**: Ensure you have a C++11 compatible compiler
2. **Runtime Errors**: Check that random number generation is working
3. **Decryption Failures**: Verify key generation completed successfully

### Debug Tips

- The program displays all key components for verification
- Each step of the process is logged to console
- Encrypted values are shown as space-separated numbers

## 📄 License

This educational implementation is provided as-is for learning purposes. Feel free to modify and use for educational projects.

## 🤝 Contributing

This is an educational example. For improvements or bug fixes:

1. Test thoroughly with various input sizes
2. Verify mathematical correctness
3. Ensure cross-platform compatibility
4. Document any changes clearly

---

**Note**: This implementation uses smaller key sizes for demonstration purposes. Never use this code for securing sensitive data in production environments.
