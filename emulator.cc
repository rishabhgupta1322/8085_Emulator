#include <bits/stdc++.h>
using namespace std;

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
		    cin.clear();
		    cin.ignore();
		    valid obj;
		    obj.checkAddress(start);
		    pc=start;
		}
		
		//Read data at running time without debugger
        void ReadingDataRuntime(){
        	int c=1;
            valid obj;
            Execution exe;
            string line;
            cout << "Press enter to type your program";
            cout << endl << endl << "Start typing your code from here:\n";
		    while(1){
		        cout << ">>> " << pc << " ";
		        getline(cin,line);
		        if(obj.validFile(line)){
		      	    Memory[pc] = line;
				    pc = exe.updatedAddress(pc,Memory);
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
            Execution exe;
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
                    pc=exe.updatedAddress(pc,Memory);
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

        void registerOutput(){
        	char c='A',T;
        	cout << "\nRegisters Value: \n";
        	for(int i=0;i<5;i++){
        		T=c+i;
        		cout << T << " ->> " <<registers[i] << endl;
        	}
        	cout << "H ->> " <<registers[5] << endl;
        	cout << "L ->> " <<registers[6] << endl;
        }

        void flagOutput(){
        	cout << "\nFlag Register values: \n";
        	cout << "SF ->> " << flag[7] << endl;
        	cout << "ZF ->> " << flag[6] << endl;
        	cout << "ACF ->> " << flag[4] << endl;
        	cout << "PF ->> " << flag[2] << endl;
        	cout << "CF ->> " << flag[0] << endl;
        }

        void commandOutput(){
        	cout << "Memory Address: " << endl;
        	sort(cmdaddress.begin(),cmdaddress.end());
        	for(int i=0;i<cmdaddress.size()-1;){
        		if(cmdaddress[i]==cmdaddress[i+1])
        			cmdaddress.erase(cmdaddress.begin()+i);
        		else 
        			i++;
        	}
        	for(int i=0;i<cmdaddress.size();i++){
        		cout << cmdaddress[i] << " ->> " << cmdoutput[cmdaddress[i]] << endl;
        	}
        }

        void output(){
        	registerOutput();
        	flagOutput();
        	commandOutput();
        }
		
		void noInput(){
		    input();
		    ExecPhase obj;
            //Reading data at run time
            ReadingDataRuntime();
            //Execution of program without debugger
		    obj.ExecNormal(start,Memory,sequence,flag,registers);
		    output();
		}
		
		void ProgWithDebugger(){
		    input();
		    ExecPhase obj;
            //Reading data at run time
            ReadingDataRuntime();
            //Execution of program with debugger
            obj.ExecDebugger(start,Memory,sequence,flag,registers);
            output();
		}
		
		void ProgWithInputFile(char* filename){
		    input();
		    ExecPhase obj;
            //Reading data from file
            dataInputFromFile(filename);
            //Execution of program without debugger
            obj.ExecNormal(start,Memory,sequence,flag,registers);
            output();
		}
		
		void ProgWithInputFileAndDebugger(char* filename){
		    input();
		    ExecPhase obj;
            //Reading data at running time with debugger
            dataInputFromFile(filename);
            //Execution of program with debugger
            obj.ExecDebugger(start,Memory,sequence,flag,registers);
            output();
		}
};