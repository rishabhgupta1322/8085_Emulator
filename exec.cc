#include <bits/stdc++.h>
using namespace std;

class Execution{
    public :

        string nextAddress(string str,int n){
        	command obj;
            int array[4];
            string result = "";
            obj.hexToDecimal(str,array); 
            int i = 3;
            array[i]+=n;
            while(array[i]>=16){
		        array[i] = array[i]%16;
		        array[i-1]++;
		        i--;
            }
            for(int i = 0;i<4;i++){
		        if(array[i]>=0 && array[i]<=9)
		            result = result + char('0' + array[i]);
		        else
		            result = result + char('A' + (array[i] - 10));
            }
            return result;
        }

		string updatedAddress(string PC,map<string,string>&Memory){
			command obj;
			valid val;
		    string cmd = Memory[PC];
		    string opcode;
		    if(cmd == "HLT" || cmd == "XCHG" || cmd == "CMA"){	
				opcode = cmd;
		    }else{
				const char *partition = cmd.c_str();
				char *temporary = (char*)partition;
				const char *delimiter = " ,";
				char *part = strtok(temporary,delimiter);
				opcode = part;
		    }
		    int n = val.operationSize(opcode);
		    string result;
		    for(int j=1;j<=n;j++){
				int array[4]={-1,-1,-1,-1};
				result = "";
				obj.hexToDecimal(PC,array);
				int i = 3;
				array[i]+=1;
				while(array[i]>=16){	
				    array[i] = array[i]%16;
				    array[i-1]++;
				    i--;
				}
				for(int i = 0;i<4;i++){
				    if(array[i]>=0 && array[i]<=9)
						result = result + char('0' + array[i]);
				    else
						result = result + char('A' + (array[i] - 10));
				}
				Memory[result] = Memory[PC];
				PC = result;
		    }
		    return PC;
		}

        string Exec(string cmd, string regs[], bool flag[], map<string,string>&memory,string programCounter){
            vector<string> commandPart;
            //string command = memory[programCounter];
            string inst; 
            valid val;
            int commandSize;
            const char *partition = cmd.c_str(), *delimiter = " ,";
            char *temporary = (char*)partition;
            char *part = strtok(temporary,delimiter);
            while(part!=NULL){
		        inst = *part;
		        commandPart.push_back(inst);
		        part = strtok(NULL,delimiter);
            }
            command obj;
            if(commandPart[0] == "MOV"){
	        	obj.MOV(commandPart[1],commandPart[2],regs,flag,memory);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "MVI"){
		        obj.MVI(commandPart[1],commandPart[2],regs,flag,memory);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "LXI"){
		        obj.LXI(commandPart[1],commandPart[2],regs,flag,memory);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "LDA"){
		        obj.LDA(commandPart[1],regs,flag,memory);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "STA"){
		        obj.STA(commandPart[1],regs,flag,memory);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "LHLD"){
		        obj.LHLD(commandPart[1],regs,flag,memory);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "SHLD"){
                obj.SHLD(commandPart[1],regs,flag,memory);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "STAX"){
		        obj.STAX(commandPart[1],regs,flag,memory);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "XCHG"){
	        	obj.XCHG(regs,flag);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "ADD"){
		        obj.ADD(commandPart[1],regs,flag,memory);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "ADI"){
		        obj.ADI(commandPart[1],regs,flag);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "SUB"){
		        obj.SUB(commandPart[1],regs,flag,memory);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "SUI"){
		        obj.SUI(commandPart[1],regs,flag);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "INR"){
                obj.INR(commandPart[1],regs,flag,memory);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "DCR"){
		        obj.DCR(commandPart[1],regs,flag,memory);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "INX"){
		        obj.INX(commandPart[1],regs,flag);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "DCX"){
	         	obj.DCX(commandPart[1],regs,flag);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "DAD"){
		        obj.DAD(commandPart[1],regs,flag);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "CMA"){
		        obj.CMA(regs,flag);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "CMP"){
		        obj.CMP(commandPart[1],regs,flag,memory);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "JMP"){
     			return obj.JMP(commandPart[1],regs,flag);
            }else if(commandPart[0] == "JC"){
	        	return obj.JC(commandPart[1],programCounter,regs,flag);
            }else if(commandPart[0] == "JNC"){
	       		return obj.JNC(commandPart[1],programCounter,regs,flag);
            }else if(commandPart[0] == "JZ"){
	        	return obj.JZ(commandPart[1],programCounter,regs,flag);
            }else if(commandPart[0] == "JNZ"){
	        	return obj.JNZ(commandPart[1],programCounter,regs,flag);
            }else if(commandPart[0] == "SET"){
		        obj.SET(commandPart[1],commandPart[2],memory);
		        commandSize = val.operationSize(commandPart[0]);
		        return nextAddress(programCounter,commandSize);
            }
            return "";
        }
};
