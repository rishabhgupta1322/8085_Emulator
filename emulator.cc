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
		    valid obj;
		    obj.checkAddress(start);
		    pc=start;
		}
		
		//Read data at running time without debugger
        void ReadingDataRuntime(){
            valid obj;
            Execution exe;
            cin.ignore();
            string line;
            cout << endl << endl << "Start typing your code from here:" << endl;
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
	        
	        //To read data at run time with debugger
        void DataInputWithoutFile(){
            valid obj;
            Execution exe;
            cout<<"\nStart typing your code from here:\n";
            while(1){
		        cout << ">>> " << pc << " ";
		        string line;
		        cin.ignore();
		        getline(cin,line);
		        if(obj.validFile(line)){
		            Memory[pc]=line;
			    pc=exe.updatedAddress(pc,Memory);
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
		
		void ProgWithInputFile(char* filename){
		    input();
		    ExecPhase obj;
            //Reading data from file
            dataInputFromFile(filename);
            //Execution of program without debugger
            obj.ExecNormal(start,Memory,sequence,flag,registers);
		}
		
		void ProgWithInputFileAndDebugger(char* filename){
		    input();
		    ExecPhase obj;
            //Reading data at running time with debugger
            dataInputFromFile(filename);
            //Execution of program with debugger
            obj.ExecDebugger(start,Memory,sequence,flag,registers);
		}
};