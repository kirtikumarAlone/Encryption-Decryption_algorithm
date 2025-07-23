#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <algorithm>

class RSACrypto {
private:
    long long n, e, d; // n = modulus, e = public exponent, d = private exponent
    
    // Check if number is prime
    bool isPrime(long long num) {
        if (num < 2) return false;
        if (num == 2) return true;
        if (num % 2 == 0) return false;
        
        for (long long i = 3; i * i <= num; i += 2) {
            if (num % i == 0) return false;
        }
        return true;
    }
    
    // Generate random prime number in range
    long long generatePrime(long long min, long long max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<long long> dis(min, max);
        
        long long candidate;
        do {
            candidate = dis(gen);
            if (candidate % 2 == 0) candidate++; // Make odd
        } while (!isPrime(candidate));
        
        return candidate;
    }
    
    // Calculate Greatest Common Divisor
    long long gcd(long long a, long long b) {
        while (b != 0) {
            long long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
    // Extended Euclidean Algorithm to find modular inverse
    long long extendedGCD(long long a, long long b, long long &x, long long &y) {
        if (a == 0) {
            x = 0;
            y = 1;
            return b;
        }
        
        long long x1, y1;
        long long gcd = extendedGCD(b % a, a, x1, y1);
        
        x = y1 - (b / a) * x1;
        y = x1;
        
        return gcd;
    }
    
    // Calculate modular inverse
    long long modInverse(long long a, long long m) {
        long long x, y;
        long long g = extendedGCD(a, m, x, y);
        
        if (g != 1) return -1; // Modular inverse doesn't exist
        
        return (x % m + m) % m;
    }
    
    // Fast modular exponentiation
    long long modPow(long long base, long long exp, long long mod) {
        long long result = 1;
        base = base % mod;
        
        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base) % mod;
            }
            exp = exp >> 1;
            base = (base * base) % mod;
        }
        
        return result;
    }

public:
    // Generate key pair
    void generateKeys() {
        // Step 1: Generate two distinct prime numbers
        long long p = generatePrime(100, 500);
        long long q = generatePrime(100, 500);
        
        // Ensure p and q are different
        while (p == q) {
            q = generatePrime(100, 500);
        }
        
        // Step 2: Calculate n = p * q
        n = p * q;
        
        // Step 3: Calculate Euler's totient function φ(n) = (p-1)(q-1)
        long long phi = (p - 1) * (q - 1);
        
        // Step 4: Choose e such that 1 < e < φ(n) and gcd(e, φ(n)) = 1
        e = 65537; // Common choice for e
        while (gcd(e, phi) != 1) {
            e += 2;
        }
        
        // Step 5: Calculate d, the modular inverse of e
        d = modInverse(e, phi);
        
        std::cout << "Keys generated successfully!\n";
        std::cout << "Prime p: " << p << ", Prime q: " << q << "\n";
        std::cout << "Public Key (n, e): (" << n << ", " << e << ")\n";
        std::cout << "Private Key (n, d): (" << n << ", " << d << ")\n\n";
    }
    
    // Encrypt a single character
    long long encryptChar(char c) {
        long long m = static_cast<long long>(c);
        return modPow(m, e, n);
    }
    
    // Decrypt a single number back to character
    char decryptChar(long long c) {
        long long m = modPow(c, d, n);
        return static_cast<char>(m);
    }
    
    // Encrypt a string
    std::vector<long long> encrypt(const std::string& message) {
        std::vector<long long> encrypted;
        
        for (char c : message) {
            encrypted.push_back(encryptChar(c));
        }
        
        return encrypted;
    }
    
    // Decrypt a vector of numbers back to string
    std::string decrypt(const std::vector<long long>& encrypted) {
        std::string decrypted;
        
        for (long long c : encrypted) {
            decrypted += decryptChar(c);
        }
        
        return decrypted;
    }
    
    // Get public key components
    std::pair<long long, long long> getPublicKey() {
        return {n, e};
    }
    
    // Get private key components
    std::pair<long long, long long> getPrivateKey() {
        return {n, d};
    }
    
    // Set keys manually (for demonstration)
    void setKeys(long long n_val, long long e_val, long long d_val) {
        n = n_val;
        e = e_val;
        d = d_val;
    }
};

// Demonstration function
void demonstrateRSA() {
    RSACrypto rsa;
    
    std::cout << "=== RSA Encryption/Decryption Demo ===\n\n";
    
    // Generate keys
    rsa.generateKeys();
    
    // Message to encrypt
    std::string message = "Hello RSA!";
    std::cout << "Original message: \"" << message << "\"\n\n";
    
    // Encrypt the message
    std::cout << "Encrypting message...\n";
    std::vector<long long> encrypted = rsa.encrypt(message);
    
    std::cout << "Encrypted values: ";
    for (size_t i = 0; i < encrypted.size(); ++i) {
        std::cout << encrypted[i];
        if (i < encrypted.size() - 1) std::cout << " ";
    }
    std::cout << "\n\n";
    
    // Decrypt the message
    std::cout << "Decrypting message...\n";
    std::string decrypted = rsa.decrypt(encrypted);
    std::cout << "Decrypted message: \"" << decrypted << "\"\n\n";
    
    // Verify
    if (message == decrypted) {
        std::cout << "✓ Encryption/Decryption successful!\n";
    } else {
        std::cout << "✗ Encryption/Decryption failed!\n";
    }
}

// Interactive mode function
void interactiveMode() {
    RSACrypto rsa;
    rsa.generateKeys();
    
    std::cout << "\n=== Interactive RSA Mode ===\n";
    std::cout << "Enter messages to encrypt/decrypt (type 'quit' to exit)\n\n";
    
    std::string input;
    while (true) {
        std::cout << "Enter message: ";
        std::getline(std::cin, input);
        
        if (input == "quit") break;
        
        if (!input.empty()) {
            // Encrypt
            std::vector<long long> encrypted = rsa.encrypt(input);
            std::cout << "Encrypted: ";
            for (size_t i = 0; i < encrypted.size(); ++i) {
                std::cout << encrypted[i];
                if (i < encrypted.size() - 1) std::cout << " ";
            }
            std::cout << "\n";
            
            // Decrypt
            std::string decrypted = rsa.decrypt(encrypted);
            std::cout << "Decrypted: \"" << decrypted << "\"\n\n";
        }
    }
}

int main() {
    int choice;
    
    std::cout << "RSA Encryption/Decryption Program\n";
    std::cout << "1. Run demonstration\n";
    std::cout << "2. Interactive mode\n";
    std::cout << "Choose option (1 or 2): ";
    std::cin >> choice;
    std::cin.ignore(); // Clear input buffer
    
    switch (choice) {
        case 1:
            demonstrateRSA();
            break;
        case 2:
            interactiveMode();
            break;
        default:
            std::cout << "Invalid choice. Running demonstration...\n";
            demonstrateRSA();
            break;
    }
    
    return 0;
}