class Execution{
    public :
        int operationSize(string str){
            string one[] = {"HLT","MOV","STAX","XCHG","ADD","SUB","INR","DCR","INX","DCX","DAD","CMA","CMP"};
            string two[] = {"MVI","ADI","SUI"};
            string three[] = {"LXI","LDA","STA","SHLD","LHLD","JMP","JC","JNZ","JNC","JZ","SET"};
            const char *ch = str.c_str();
            char *var = (char*)ch;
            const char *delimiter = " ,";
            char *pch = strtok (var,delimiter);
            string query = pch;
            int length = sizeof(one)/sizeof(one[0]);
            for(int i=0;i<length;i++){
	        if(one[i] == query)
	            return 1;
            }
            length = sizeof(two)/sizeof(two[0]);
            for(int i=0;i<length;i++){
	        if(two[i] == query)
	            return 2;
            }
            length = sizeof(three)/sizeof(three[0]);
            for(int i=0;i<length;i++){
	        if(three[i] == query)
	            return 3;
            }
            return 0;
        }

        string nextAddress(string str,int n){
            int array[4];
            string result = "";
            hexToDecimal(str,array); 
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

        string Exec(string command, string regs[], bool flag[], map<string,string>&memory,string programCounter){
            vector<string> commandPart;
            //string command = memory[programCounter];
            string inst;
            int commandSize;
            const char *partition = command.c_str(), *delimiter = " ,";
            char *temporary = (char*)partition;
            char *part = strtok(temporary,delimiter);
            while(part!=NULL){
	        inst = part;
	        commandPart.push_back(inst);
	        part = strtok(NULL,delimiter);
            }
            if(commandPart[0] == "MOV"){
	        MOV(commandPart[1],commandPart[2],regs,flag,memory);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "MVI"){
	        MVI(commandPart[1],commandPart[2],regs,flag,memory);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "LXI"){
	        LXI(commandPart[1],commandPart[2],regs,flag,memory);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "LDA"){
	        LDA(commandPart[1],regs,flag,memory);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "STA"){
	        STA(commandPart[1],regs,flag,memory);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "LHLD"){
	        LHLD(commandPart[1],regs,flag,memory);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "SHLD"){
                SHLD(commandPart[1],regs,flag,memory);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "STAX"){
	        STAX(commandPart[1],regs,flag,memory);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "XCHG"){
	        XCHG(regs,flag);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "ADD"){
	        ADD(commandPart[1],regs,flag,memory);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "ADI"){
	        ADI(commandPart[1],regs,flag);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "SUB"){
	        SUB(commandPart[1],regs,flag,memory);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "SUI"){
	        SUI(commandPart[1],regs,flag);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "INR"){
                INR(commandPart[1],regs,flag,memory);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "DCR"){
	        DCR(commandPart[1],regs,flag,memory);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "INX"){
	        INX(commandPart[1],regs,flag);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "DCX"){
         	DCX(commandPart[1],regs,flag);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "DAD"){
	        DAD(commandPart[1],regs,flag);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "CMA"){
	        CMA(regs,flag);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "CMP"){
	        CMP(commandPart[1],regs,flag,memory);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }else if(commandPart[0] == "JMP"){
         	return JMP(commandPart[1],regs,flag);
            }else if(commandPart[0] == "JC"){
	        return JC(commandPart[1],programCounter,regs,flag);
            }else if(commandPart[0] == "JNC"){
	        return JNC(commandPart[1],programCounter,regs,flag);
            }else if(commandPart[0] == "JZ"){
	        return JZ(commandPart[1],programCounter,regs,flag);
            }else if(commandPart[0] == "JNZ"){
	        return JNZ(commandPart[1],programCounter,regs,flag);
            }else if(commandPart[0] == "SET"){
	        SET(commandPart[1],commandPart[2],memory);
	        commandSize = operationSize(commandPart[0]);
	        return nextAddress(programCounter,commandSize);
            }
            return "";
        }
};
