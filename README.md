# RISC-V-Diassembler
<div align="center">
  <h1>Running the Disassembler Program</h1>
</div>

This repository contains a C++ program for disassembling test cases provided in `testcase1.txt` to `testcase5.txt`. Follow the steps below to run the disassembler.

### Step 1: Clone the Repository

```sh
  git clone https://github.com/Pranavb060504/RISC-V-Disassembler.git
  cd RISC-V-Disassembler

### Step 2: Update File Path


In the Disassembler.cpp file, locate the main function at line 391. Update the file path in the following line:
std::ifstream file("{FilePath}");
Replace {FilePath} with the path of testcase files.

### Step 3: Compile the Code


  Compile the code by typing the following command on your terminal:
    <center><b> g++ Disassembler.cpp -o "Filename" </b></center>

### Step 4: Run the Program

  Run the code by typing the following command on the terminal:
    <center><b> ./Filename.exe </b></center>
  Make sure to replace "Filename.exe" with the actual name of the compiled executable file if it's different.

  



