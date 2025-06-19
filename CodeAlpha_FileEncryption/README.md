# File Encryption and Decryption Tool

This is a professional C++ console-based application developed as part of the CodeAlpha C++ Programming Internship. The tool provides secure file encryption and decryption using a Caesar cipher algorithm with a password-based shift mechanism.

## Features

- Secure login system
- Password-derived Caesar cipher encryption
- Automatic shift key saving during encryption
- Reliable decryption using saved shift
- Console-based interface with clean prompts
- File I/O with error handling
- Activity logging with timestamps

## Technologies Used

- C++17
- File Streams (ifstream, ofstream)
- Strings, Loops, Conditionals
- Timestamps using `ctime`

## How It Works

### Encryption
1. User logs in with valid credentials
2. Provides the name of a plain-text input file
3. Enters a password to generate the encryption key (shift)
4. The Caesar shift value is calculated and saved inside the output file
5. A new file `encrypted_<timestamp>.txt` is generated

### Decryption
1. User logs in again
2. Provides the name of the previously encrypted file
3. The program automatically reads the Caesar shift from the file
4. The file is decrypted and saved as `decrypted_<timestamp>.txt`

## Folder Structure

CodeAlpha_FileEncryption/
├── main.cpp
├── input.txt
├── encrypted_.txt
├── decrypted_.txt
├── activity_log.txt
├── README.md


## How to Run

### Compile
```bash
g++ main.cpp -o main

Run
./main      # On Linux/Mac
main.exe    # On Windows (PowerShell: .\main.exe)

Default Credentials
Username: Rishi
Password: Rishiii9126
