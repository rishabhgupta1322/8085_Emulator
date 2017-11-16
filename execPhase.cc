#include <bits/stdc++.h>
using namespace std;

class ExecPhase{    
    public:
		
        //When program is called without debugger
    	void ExecNormal(string pc,map<string,string> &Memory,vector<string> &sequence,bool flag[],string reg[]){
    		Execution exe;
            int size=sequence.size();
            for(int i=0;i<size;i++){
				pc=exe.Exec(Memory[sequence[i]],reg,flag,Memory,pc);
            }
		}
	

	//When program is called with debugger
	void ExecDebugger(string pc,map<string,string>&Memory,vector<string>&sequence,bool flag[],string reg[]){
		valid val;
		Execution exe;
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
			        if(val.valregs(valHolder))
				    cout << reg[val.regNumber(valHolder)] << endl;
				else
				    cout << "Error: " << valHolder << endl;
				    cout << " You have entered invalid reg name" << endl;
				    cout << "Type 'help' for more information" << endl;
			    }else if(l==4){
			        //print data at given memory location
					if(val.valAddress(valHolder))
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
			       pc = exe.Exec(Memory[pc],reg,flag,Memory,pc);
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
							    pc = exe.Exec(Memory[pc],reg,flag,Memory,pc);
						}
					}else{
					    it = breakpoints.begin();
						int var = *it;
						while(pc!=sequence[var]){
					    	pc = exe.Exec(Memory[pc],reg,flag,Memory,pc);
						}
					    breakpoints.erase(it);
					}
			    }else{
					char choice='\0';
					cout<<"You have reached till the end of Exec. Press to continue[Y/n] ";
					cin>>choice;
					if(choice == 'Y' || choice == 'y'){
					    continue;
					}else if(choice == 'N' || choice == 'n'){
					    exit(0);
					}
					else{
					    cout<<"Please input correct option\n";
					}
					continue;
		        }
			}else{
			    cout<<"Invalid choice has been entered. Type 'help' for more information about debugger\n";
			}
	    }
	}
};
