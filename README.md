##  Table of Contents
- [Project Overview](#project-overview)
- [Key Features](#key-features)
- [Installation & Usage](#installation--usage)


##  Project Overview
Secure-Notes is a multi-user system designed to store sensitive text data or just personal notes. Unlike standard text files, data stored by this application is fully encrypted on the disk.
* **Authentication:** Passwords are **hashed** (one-way) before storage, so they cannot be reverse-engineered even if the data file is stolen.
* **Privacy:** Notes are encrypted using a **Session Key** derived from the user's login. This key exists *only in RAM* and is never written to the hard drive.
  
Password hashing is done using DJB2 algorithm and Notes are encrypted using Vigenere cipher.
##  Key Features
* **User System:** Secure Registration and Login with credential validation.
* **Dynamic Storage:** Notes use dynamic memory allocation (`malloc`), allowing efficient storage of messages of varying lengths.
* **CRUD Operations:** Create, Read, Update, and Delete notes.
* **Search:** Full-text search capability that decrypts notes on-the-fly to find keywords.
* **Secure Persistence:** Custom binary file format (`data.dat`) handles storage of dynamic data structures.
* **Memory Hygiene:** Sensitive data is scrubbed (`memset`) from memory immediately after use to prevent RAM scraping.
* **Robust Error Catching:** Every function has error catching statements so that the user knows why the program failed to do something.

##  Installation & Usage

### Prerequisites
* GCC Compiler
* Make Tool

### Compilation and Running
To build the project using the Makefile: 

```bash
make
```
To run the application:
```bash
make run
```
Alternatively, directly run the executable:
```bash
./notes       #on linux
notes.exe     #on windows
```
Make sure you are in the same directory as the project folder.




