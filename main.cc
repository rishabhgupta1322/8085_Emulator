#include<bits/stdc++.h>
using namespace std;

void wrongInput(){
    cout << "WRONG INPUT FORMAT" << endl;
    cout << "Input format should be in following manner" << endl;
    cout << "<Executable filename>" << endl;
    cout << "<Executable filename> -debugger" << endl;
    cout << "<Executable filename>  <input_filename>  " << endl;
    cout << "<Executable filename>  <input_filename>  -debugger"<< endl;
}

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

class valid{
    public :
        void checkAddress(string data){
            if(data.size()==4){
                for(int i=0;i<4;i++){
                    if(!((data[i]>=0 && data[i]<=9) || (data[i]>='a' && data[i]<='f') || (data[i]>='A' && data[i]<='F'))){
                        wrongData();
                    }
                }
            }else{
                wrongData();
            }
        }
        
        bool validFile(string command){
            string copy = command;
            vector <string> tokens;
            bool flag = false;
            const char *ch = command.c_str();
            char *var = (char*)ch;
            const char *delimiter = " ,";
            char *pch = strtok (var,delimiter);
            while(pch != NULL){	
	        tokens.push_back(pch);
	        pch = strtok(NULL,delimiter);
            }
            if(inRecord(tokens[0]) && argumentValidation(tokens,tokens[0]) && align(copy)){
	        flag = true;
	        if(tokens.size()>1){
	            for(int i = 1;i<tokens.size();i++){	
	                string temp = tokens[i];
	                int tempLength = tokens[i].length();
		            switch(tempLength){
		                case 1:
			            if(temp == "M")
			                flag = true;
			            else
			                flag = valregs(temp);
			            break;
		                case 2:
			            flag = valData(temp);
			            break;
		                case 4:
			            flag = valAddress(temp);
			            break;
		                default:
			            flag = false;
			            break;
		            }
		            if(!flag)
		                break;
	            }
                }
                return flag;
            }
            return flag;
        }
        
        void wrongData(){
            cout << "You have entered invalid address" << endl;
            cout << "Try Again with valid address" << endl;
            exit(0);
        }
        
        bool argumentValidation(vector<string> &memory,string str){
            string one[] = {"HLT","CMA","XCHG"};
            string two[] = {"CMP","JMP","JC","JNC","JZ","JNZ","ADD","ADI","SUB","SUI","INR","INX","DCR","DCX","DAD","LDA","STA","SHLD","LHLD","STAX"};
            string three[] = {"SET","MOV","MVI","LXI"};
            int length = sizeof(one)/sizeof(one[0]);
            for(int i=0;i<length;i++){	
	        if(str == one[i] && memory.size()==1)
          	    return true;
            }
            length = sizeof(two)/sizeof(two[0]);
            for(int i=0;i<length;i++){	
	        if(str == two[i] && memory.size()==2)
          	    return true;
            }
            length = sizeof(three)/sizeof(three[0]);
            for(int i=0;i<length;i++){	
	        if(str == three[i] && memory.size()==3)
         	    return true;
            }
            return false;
        }
        
        bool inRecord(string str){
            string repository[] = {"HLT","MOV","STAX","XCHG","ADD","SUB","INR","DCR","INX","DCX","DAD","CMA","CMP","MVI","ADI","SUI","SET","LXI","LDA","STA","SHLD","LHLD","JMP","JC","JNZ","JNC","JZ"};
            int l = sizeof(repository)/sizeof(repository[0]);
            for(int i = 0;i<l;i++){	
	        if(str == repository[i]){
	            return true;
	        }
            }
            return false;
        }
        
        bool valData(string a){
            int l=a.length();
            if(l==2){
	        if((a[0]>='0'&&a[0]<='9')||(a[0]>='A'&&a[0]<='F')){
	            if((a[1]>='0'&&a[1]<='9')||(a[1]>='A'&&a[1]<='F'))
		        return true;
	            else 
		        return false;
	        }else
	            return false;
            }else 
	        return false;
        }
};

class ExecPhase{    
    public:
        //When program is called without debugger
    	void ExecNormal(string pc,map<string,string> &Memory,vector<string> &sequence,bool flag[],string reg[]){
            int size=sequence.size();
            for(int i=0;i<size;i++)
		pc=Exec(Memory[sequence[i]],reg,flag,Memory,pc);
	}
	
	//When program is called with debugger
	void ExecDebugger(string pc,map<string,string>&Memory,vector<string>&sequence,bool flag[],string reg[]){
	    string option;
	    set<int> breakpoints;
	    set<int>::iterator it;
	    cout << "Enter Options :- " << endl;
	    while(true){
		cout << "->> ";
		//Reading option from user for debugger
		cin >> option;
		if(option == "help"){
		    char line;
		    ifstream write("help.txt");
		    //Print the content of help file
	       	    while(!write.eof()){
			write.get(line);
			cout << line;
	            }
		    write.close();
		 }else if(option == "PC"){	
		     //Print the content of program counter
		     cout<<"Program counter -->> "<<pc<<"\n";
		 }else if(option=="p" || option=="print"){
		     string valHolder;
		     cin.ignore();
		     //Read reg whose value is need to print
		     cin >> valHolder;
		     int l = valHolder.length();
		     if(l==1){
		         //print data of given reg(valHolder) if valid reg is given
		         if(valregs(valHolder))
			     cout << reg[regNumber(valHolder)] << endl;
			 else
			     cout << "Error: " << valHolder << endl;
			     cout << " You have entered invalid reg name" << endl;
			     cout << "Type 'help' for more information" << endl;
		     }else if(l==4){
		         //print data at given memory location
			 if(valAddress(valHolder))
			     cout<<Memory[valHolder]<<"\n";
			 else
			     cout << "Error: " << valHolder << endl;
			     cout << "You have entered invalid address" << endl;
			     cout << "Type 'help' for more information" << endl;
		     }else
			 cout << "Error: " << valHolder << endl;
			 cout << "Type 'help' for more information" << endl;
		 }else if(option=="q"||option=="quit"){
		     //terminate the program
		     break;
		 }else if(option=="break"||option=="b"){
		     //Add breakpoint to entered line number
		     int lineNumber;
		     cin>>lineNumber;
		     breakpoints.insert(lineNumber);
		 }else if(option=="s"||option=="step"){
		     //execute program step by step(one step at a time)
		     if(pc!="")
		         pc = Exec(Memory[pc],reg,flag,Memory,pc);
		 }else if(option=="r"||option=="run"){
		     //run the entered program
		     if(pc != ""){
		         if(breakpoints.empty()){
		             while(true){
		                 //Run program untill end of program i.e HLT
		                 if(Memory[pc] == "HLT"){
		                     pc = "";
		                     break;
		                 }
		                 else
		                     pc = Exec(Memory[pc],reg,flag,Memory,pc);
		             }
			 }else{
                             it = breakpoints.begin();
			     int var = *it;
			     while(pc!=sequence[var]){
			         pc = Exec(Memory[pc],reg,flag,Memory,pc);
			     }
		             breakpoints.erase(it);
			 }
		     }else{
			 char choice='\0';
			 cout<<"You have reached till the end of Exec. Press to continue[Y/n] ";
			 cin>>choice;
			 if(choice == 'Y' || choice == 'y'){
			     continue;
			 }else if(choice == 'N' || choice == 'n')
			     exit(0);
			 else
			     cout<<"Please input correct option\n";
			 continue;
	            }
		}else{
		    cout<<"Invalid choice has been entered. Type 'help' for more information about debugger\n";
		}
	    }
	}
};

class Emulator{
    private:
        map<string,string> Memory;
        string start,pc;
        bool flag[8];
        string registers[7];
        vector<string> sequence;
        
    public:
        Emulator(){
	    for(int i = 0;i<7;i++)
		registers[i] = "NULL";
	    for(int i=0;i<8;i++)
		flag[i] = false;
	    start = "";
	    pc = "";
	}    
	
	void input(){
	    cout << "Enter starting address in hexadecimal: ";
	    cin >> start;
	    valid obj;
	    obj.checkAddress(start);
	    pc=start;
	}
	
	//Read data at running time without debugger
        void ReadingDataRuntime(){
            valid obj;
            cin.ignore();
            string line;
            cout << endl << endl << "Start typing your code from here:" << endl;
	    while(1){
	        cout << ">> " << pc << " ";
	        getline(cin,line);
	        if(obj.validFile(line)){
	      	    Memory[pc] = line;
		    pc = updatedAddress(pc,Memory);
		    if(line == "HLT")
	                break;
		    sequence.push_back(pc);
	        }else{
                    cout << "Error: " << line << endl;
	            cout << "You have entered an incorrect statement" << endl;
	            cout << "The program will terminate" << endl;
	            exit(0);
	        }
	    }
        }
        
        //To read data at run time with debugger
        void DataInputWithoutFile(){
            valid obj;
            cout<<"\nStart typing your code from here:\n";
            while(1){
	        cout << ">> " << pc << " ";
	        string line;
	        getline(cin,line);
	        if(obj.validFile(line)){
	            Memory[pc]=line;
		    pc=updatedAddress(pc,Memory);
		    if(line == "HLT")
	                break;
		    sequence.push_back(pc);
	        }else{
		    cout << "Error: " << line << endl;
		    cout << "You have entered an incorrect statement" << endl;
		    cout << "The program will terminate" << endl;
		    exit(0);
	        }
	    }
        }
        
        //To read data from given input file
        void dataInputFromFile(char* filename){
            ifstream input;
            input.open(filename);
            if(input.fail() == true){	
	        cout << "You have entered an invalid filename." << endl;
	        cout << "The prorgam will terminate\n";
	        exit(0);
            }
            string line;
            valid obj;
            while(1){
                getline(input,line);
                if(obj.validFile(line)){
                    Memory[pc]=line;
                    pc=updatedAddress(pc,Memory);
                    if(line=="HLT")
		        break;
                    sequence.push_back(pc);
	        }else{		
                    cout << "Error: " << line << endl;
		    cout << "You have entered an incorrect statement" << endl;
		    cout << "The program will terminate" << endl;
		    exit(0);
	        }
            }
        }
	
	void noInput(){
	    input();
	    ExecPhase obj;
            //Reading data at run time
            ReadingDataRuntime();
            //Execution of program without debugger
	    obj.ExecNormal(start,Memory,sequence,flag,registers);
	}
	
	void ProgWithDebugger(){
	    input();
	    ExecPhase obj;
            //Reading data at run time
            DataInputWithoutFile();
            //Execution of program with debugger
            obj.ExecDebugger(start,Memory,sequence,flag,registers);
	}
	
	void ProgWithInputFile(){
	    input();
	    ExecPhase obj;
            //Reading data from file
            dataInputFromFile(filename);
            //Execution of program without debugger
            obj.ExecNormal(start,Memory,sequence,flag,registers);
	}
	
	void ProgWithInputFileAndDebugger(){
	    input();
	    ExecPhase obj;
            //Reading data at running time with debugger
            dataInputFromFile(filename);
            //Execution of program with debugger
            obj.ExecDebugger(start,Memory,sequence,flag,registers);
	}
        
        bool align(string str){	
            int l = str.length();
            for(int i=0;i<l;i++){	
                if(!((str[i]>='0' && str[i]<='9') || str[i] == ' ' || str[i] == ',' || (str[i]>='A' && str[i]<='Z')))
	            return false;
            }
            return true;
        }
};

int main(int argc,char* argv[]){
    Emulator EmuInst;
    if(argc==1){
        EmuInst.noInput();
    }else if(argc==2){
        if(argv[1]=="-debugger"){
            EmuInst.ProgWithDebugger();
        }else{
            EmuInst.ProgWithInputFile();
        }
    }else if(argc==3){
        if(argv[2]=="-debugger"){
            EmuInst.ProgWithInputFileAndDebugger();
        }else{
            wrongInput();
        }
    }else{
        wrongInput();
    }
    return 0;
}
