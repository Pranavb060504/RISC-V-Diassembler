# RISC-V-Diassembler
clone the repository:
  git clone https://github.com/Pranavb060504/RISC-V-Disassembler.git
  cd RISC-V-Disassembler

1.  testcase.txt contains all testcases with actual code from which they were generated, 
    Use the testcase1.txt,...testcase5.txt files for running the code

2. Provide path of the file in main function -Line 391 
    std::ifstream file("{FilePath}");- Replace {Filepath} by the path

3. Run the below commands on your terminal:
    -> g++ Disassembler.cpp -o "Filename"
    -> ./Filename.exe
