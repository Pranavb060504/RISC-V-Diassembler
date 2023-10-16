#include <iostream>
#include <map>
#include <vector>
#include <string>
#include<bitset>
#include<math.h>
#include<fstream>
using namespace std;




std::string hexToDecimal(const std::string& hex, map<std::string,string> hex_decimal) {
    std::string result;
    for (char c : hex) {
        std::string binary = hex_decimal[std::string(1, c)];
        result += binary;
    }
    return result;
}



int unsigned_binaryToDecimal(string &binarystring){ 
    int res=0;
    for(int i=binarystring.length()-1;i>=0;i--){
            int temp;
            if(binarystring[binarystring.length()-1-i]=='1'){
                temp=1;
            }
            else{
                temp=0;
            }
            res+= temp*pow(2,i);
    }
    return res;
}

int binaryToDecimal(string &binarystring){ 
    int res=0;
    for(int i=binarystring.length()-1;i>=0;i--){
            int temp;
            if(binarystring[binarystring.length()-1-i]=='1'){
                temp=1;
                if(i==binarystring.length()-1){
                    temp=-1;
                }
            }
            else{
                temp=0;
            }
            res+= temp*pow(2,i);
    }
    return res;
}

std::string diassembler(string &machine_code,string &type,int &line_number,int &label_number,map<string,int>&PC,map<int,string>&diassembled_code){
    string result;
    line_number+=1;

    for(auto x:PC){
            if (PC[x.first]==line_number){
                result+=x.first;
                result+=": ";
            }
        }
    if ( type == "R" ) {
            string funct7=machine_code.substr(0,7);
            // cout<<funct7<<endl;
            string rs2=machine_code.substr(7,5);
            // cout<<rs2<<endl;
            string rs1=machine_code.substr(12,5);
            // cout<<rs1<<endl;
            string funct3=machine_code.substr(17,3);
            // cout<<funct3<<endl;
            string rd=machine_code.substr(20,5);
            // cout<<rd<<endl;
            string opcode=machine_code.substr(25,7);

            if(funct3=="000" && funct7=="0000000"){
                result+="add";
            }
            if(funct3=="000" && funct7=="0100000"){
                result+="sub";
            }
            if(funct3=="100" && funct7=="0000000"){
                result+="xor";
            }
            if(funct3=="110" && funct7=="0000000"){
                result+="or";
            }
            if(funct3=="111" && funct7=="0000000"){
                result+="and";
            }
            if(funct3=="001" && funct7=="0000000"){
                result+="sll";
            }
            if(funct3=="101" && funct7=="0000000"){
                result+="srl";
            }
            if(funct3=="101" && funct7=="0100000"){
                result+="sra";
            }
            if(funct3=="010" && funct7=="0000000"){
                result+="slt";
            }
            if(funct3=="011" && funct7=="0000000"){
                result+="sltu";
            }
            
     

            result+=" x";
            result+=to_string(unsigned_binaryToDecimal(rd));
            result+=", ";
            result+="x";
            result+=to_string(unsigned_binaryToDecimal(rs1));
            result+=", ";
            result+="x";
            result+=to_string(unsigned_binaryToDecimal(rs2));
    
            return result;
    }
    if( type == "I" ){


        string imm = machine_code.substr(0,12);
        string rs1 = machine_code.substr(12,5);
        string funct3 = machine_code.substr(17,3);
        string rd = machine_code.substr(20,5);
        string opcode = machine_code.substr(25,7);
        string imm1 = machine_code.substr(0,6);
        string imm2 = machine_code.substr(6,6);
        int h=0;
        if ( funct3 == "001" && opcode=="0010011" && imm1 == "000000"){
                result+="slli";
                h=1;
        }
        else if ( funct3 == "101" && opcode=="0010011" && imm1 == "000000"){
                result+="srli";
                h=1;       
        } 
        else if ( funct3 == "101" && opcode=="0010011" && imm1 == "010000"){
                result+="srai";
                h=1;
        }
        else if ( funct3 == "000" && opcode=="0010011"){
                result+="addi";
        } 
        else if ( funct3 == "100" && opcode=="0010011"){
                result+="xori";
        } 
        else if ( funct3 == "110" && opcode=="0010011"){
                result+="ori";
        } 
        else if ( funct3 == "111" && opcode=="0010011"){
                result+="andi";
        } 
        else if ( funct3 == "010" && opcode=="0010011"){
                result+="slti";
        } 
        else if ( funct3 == "011" && opcode=="0010011"){
                result+="sltiu";
        }
        else if( funct3 == "000" && opcode=="0000011"){
                result+="lb";
        }
        else if( funct3 == "001" && opcode=="0000011"){
                result+="lh";
        }
        else if( funct3 == "010" && opcode=="0000011"){
                result+="lw";
        }
        else if( funct3 == "011" && opcode=="0000011"){
                result+="ld";
        }
        else if( funct3 == "100" && opcode=="0000011"){
                result+="lbu";
        }
        else if( funct3 == "101" && opcode=="0000011"){
                result+="lhu";
        }
        else if( funct3 == "110" && opcode=="0000011"){
                result+="lwu";
        }
        else if( funct3 == "000" && opcode=="1100111"){
                result+="jalr";
        }

            result+=" x";
            result+=to_string(unsigned_binaryToDecimal(rd));
            result+=", ";
            result+="x";
            result+=to_string(unsigned_binaryToDecimal(rs1));
            result+=", ";
            if (h==0){
                result+=to_string(binaryToDecimal(imm));
            }
            else if( h==1){
                result+=to_string(unsigned_binaryToDecimal(imm2));
            }
            return result;

    }
    if ( type == "S"){
        string imm1 = machine_code.substr(0,7);
        string rs2 = machine_code.substr(7,5);
        string rs1 = machine_code.substr(12,5);
        string funct3 = machine_code.substr(17,3);
        string imm2 = machine_code.substr(20,5);
        string opcode = machine_code.substr(25,7);

        if( funct3 == "000"){
            result+="sb";
        }
        if( funct3 == "001"){
            result+="sh";
        }
        if( funct3 == "010"){
            result+="sw";
        }
        if( funct3 == "011"){
            result+="sd";
        }
        string imm=imm1+imm2;
        result+=" x";
        result+=to_string(unsigned_binaryToDecimal(rs2));
        result+=", ";
        result+=to_string(binaryToDecimal(imm));
        result+="(x"+to_string(unsigned_binaryToDecimal(rs1))+")";
 
        return result;
    }
    
    if ( type == "J"){
        string imm1 = machine_code.substr(0,1);
        string imm2 = machine_code.substr(1,10);
        string imm3 = machine_code.substr(11,1);
        string imm4 = machine_code.substr(12,8);
        string rd = machine_code.substr(20,5);

        result+="jal";
        result+=" x";
        result+=to_string(unsigned_binaryToDecimal(rd));
        
        string imm=imm1+imm4+imm3+imm2+"0";
        result+=", ";

        int offset=binaryToDecimal(imm)/4;
        int points_to=offset+ line_number;

        for(auto x:PC){
            if(x.second==points_to){
                result+=x.first;
                return result;
            }
        }
        string temp="L"+to_string(label_number);
        result+=temp;

        PC[temp]=points_to;
        label_number+=1;
        if(offset<0){
                    int y=points_to;
                    diassembled_code[y]=temp+":"+diassembled_code[y];
                }

        return result;
    }

    if ( type == "U"){
        string imm1 = machine_code.substr(0,20);
        string rd = machine_code.substr(20,5);
        string opcode = machine_code.substr(25,7);
        if( opcode == "0110111"){
            result+="lui";
        }
        string imm=imm1+"000000000000";
        result+=" x";
        result+=to_string(unsigned_binaryToDecimal(rd));
        result+=", ";
        result+=to_string(binaryToDecimal(imm));

        return result;
    }

    if ( type == "B"){
        string imm1 =machine_code.substr(0,1);
        string imm2 =machine_code.substr(1,6);
        string rs2 =machine_code.substr(7,5);
        string rs1 =machine_code.substr(12,5);
        string funct3 =machine_code.substr(17,3);
        string imm3 =machine_code.substr(20,4);
        string imm4 = machine_code.substr(24,1);
        string opcode =machine_code.substr(25,7);

        string imm=imm1+imm4+imm2+imm3+"0";

        if ( funct3 == "000"){
                result+="beq";
        }
        if ( funct3 == "001"){
                result+="bne";
        }
        if ( funct3 == "100"){
                result+="blt";
        }
        if ( funct3 == "101"){
                result+="bge";
        }
        if ( funct3 == "110"){
                result+="bltu";
        }
        if ( funct3 == "111"){
                result+="bgeu";
        }

        result+=" x";
        result+=to_string(unsigned_binaryToDecimal(rs1));
        result+=", ";
        result+=" x";
        result+=to_string(unsigned_binaryToDecimal(rs2));
        result+=", ";
        
        int offset=binaryToDecimal(imm)/4;
        int points_to=offset + line_number;
        for(auto x:PC){
            if(x.second==points_to){
                result+=x.first;           
                return result;
            }
        }
        string temp="L"+to_string(label_number);
        result+=temp;

        PC[temp]=points_to;
        label_number+=1;
         if(offset<0){
                    int y=points_to;
                    diassembled_code[y]=temp+":"+diassembled_code[y];
                }

        return result;

    }


}

int main() {

    map< string ,string>  opcode;
    opcode["0110011"] = 'R';
    opcode["0010011"] = 'I';
    opcode["0000011"] = 'I';
    opcode["0100011"] = 'S';
    opcode["1100011"] = 'B';
    opcode["1101111"] = 'J';
    opcode["1100111"] = 'I';
    opcode["0110111"] = 'U';
    opcode["0010111"] = 'U';
    opcode["1110011"] = 'I';


    map<std::string, std::string> hex_decimal;

    hex_decimal["0"] = "0000";
    hex_decimal["1"] = "0001";
    hex_decimal["2"] = "0010";
    hex_decimal["3"] = "0011";
    hex_decimal["4"] = "0100";
    hex_decimal["5"] = "0101";
    hex_decimal["6"] = "0110";
    hex_decimal["7"] = "0111";
    hex_decimal["8"] = "1000";
    hex_decimal["9"] = "1001";
    hex_decimal["A"] = "1010"; 
    hex_decimal["B"] = "1011"; 
    hex_decimal["C"] = "1100"; 
    hex_decimal["D"] = "1101"; 
    hex_decimal["E"] = "1110"; 
    hex_decimal["F"] = "1111"; 
    hex_decimal["a"] = "1010"; 
    hex_decimal["b"] = "1011"; 
    hex_decimal["c"] = "1100"; 
    hex_decimal["d"] = "1101"; 
    hex_decimal["e"] = "1110"; 
    hex_decimal["f"] = "1111"; 

    map<string,int> PC;
    std::ifstream file("testcase4.txt"); 
    string s;
    map<int,string>diassembled_code;
    int curr_line_number=0;
    int label_number=0;

    if (file.is_open()) {
        while (std::getline(file, s)) {
                string machine_code=hexToDecimal(s,hex_decimal);
                 // cout<< machine_code<<endl;
                string extracted_opcode=machine_code.substr(machine_code.length()-7,7);
                // cout<< extracted_opcode<<endl;

                diassembled_code[curr_line_number]=diassembler(machine_code,opcode[extracted_opcode],curr_line_number,label_number,PC,diassembled_code);
                // for(auto x:PC){
                //     cout<<x.second<<endl;
                // }
        }
        file.close();
    } else {
        std::cout << "Unable to open the file." << std::endl;
    }
    for(auto x:diassembled_code){
        cout<<x.second<<endl;
    }
    // for(auto x:PC){
    //     cout<<x.first<<x.second<<endl;
    // }
}

