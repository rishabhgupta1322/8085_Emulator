#include <bits/stdc++.h>
using namespace std;

class command{
	public:

		string decimalToHex(int *decimal){
            string hex="";
            int size=sizeof(decimal)/sizeof(decimal[0]);
            for(int i=0;i<size;i++){
                if(decimal[i]>=0 && decimal[i]<=9)
                    hex = hex + char('0' + decimal[i]);
                else if(decimal[i]>=10 && decimal[i]<=15)
                    hex+=(char)('A'+(decimal[i]-10));
            }
            return hex;
        }

        void hexToDecimal(string pc,int *arr){
            int l = pc.length(), p = 0;
            for(int i =0 ;i<l;i++){
                if(pc[i]>='0' && pc[i]<='9')
                    arr[i] = pc[i] - '0';
                else 
                    arr[i] = 10 + (pc[i] - 'A'); 
            }
        }

		string hexAdd(string arg1,string arg2,bool flag[],bool carry){
		    string resultant = "";
		    int variable, value1[5] = {0,0}, value2[5] = {0,0}, tempAnswer[2];
		    hexToDecimal(arg1,value1);
		    hexToDecimal(arg2,value2);
		    tempAnswer[1] = value1[1] + value2[1];
		    if(tempAnswer[1]>=16){
				tempAnswer[1] = tempAnswer[1]%16;
				value1[0]++;
				flag[4] = true;
		    }
		    tempAnswer[0] = value1[0] + value2[0];
		    if(tempAnswer[0]>=16){
				tempAnswer[0] = tempAnswer[0]%16;
				if(carry == true)
				    flag[0] = true;
		    }
		    variable = tempAnswer[0]*16 + tempAnswer[1];
		    bitset<8> dataInBinary(variable);
		    /*Setting parity flag*/
		    int parity = dataInBinary.count();
		    if(parity%2 == 0 && parity!=0)
				flag[2] = true;
		    else
				flag[2] = false;
		    /*Setting sign flag*/
		    flag[7] = dataInBinary[7];
		    /*Setting zero flag*/
		    if(parity == 0)
				flag[6] = true;
		    /*Convert decimal data to hexadecimal and store in accumulator*/
		    for(int i = 1;i>=0;--i){
				if(tempAnswer[i]>=0 && tempAnswer[i]<=9)
				    resultant = char('0' + tempAnswer[i]) + resultant;
				else if(tempAnswer[i]>=10 && tempAnswer[i]<=15)
				    resultant = (char)('A'+(tempAnswer[i] - 10)) + resultant;
		    }
		    return resultant;
		}

		string hexAdd16bit (string arg1,string arg2,bool flag[],bool check){
		    int l1=arg1.length();
		    int l2=arg2.length();
		    string hex="";
		    if(l1==1&&l2==4){
				int value1[4]={0,0,0,0};
				for(int i=0;i<l1;i++){
				    if(arg1[i]>='0'&&arg1[i]<='9')
						value1[i]=(int)(arg1[i]-'0');
			  	    else if(arg1[i]>='A'&&arg1[i]<='Z')
						value1[i]=(int)(arg1[i]-'A');
				}
				int i=l1-1;
				value1[l1-1]++;
				while(value1[i]>=16){
				    value1[i]=value1[i]%16;
					if(i==0){
					    flag[0]=true;
					    break;
					}else
					    value1[--i]++;
				}
				int value=value1[0]*16*16*16+value1[1]*16*16+value1[2]*16+value1[3];
				bitset<16> str(value);
				flag[7]=str[15];
				int parity=str.count();
				if(parity==0)
				    flag[6]=true;
				else if(parity%2==0)
				    flag[2]=true;
				else if(parity%2==1)
				    flag[2]=false;
				for(int i=0;i<l1;i++){
				    if(value1[i]>=0&&value1[i]<=9)
					hex+=(char)value1[i];
				    else if(value1[i]>=10&&value1[i]<=15)
					hex+=(char)('A'+(value1[i]-10));
				}
		    }
		    return hex;
		}

		void ADD(string arg1,string regs[],bool flag[],map<string,string> &memory){	
		    int length=arg1.length();
		    valid val;
		    if(length == 1){
				if(val.valregs(arg1) || val.valregPair(arg1)){
				    if(arg1 != "M"){
				    	/*Fetches index of reg to access array string regs[]*/
						int regID = val.regNumber(arg1);
						/*Converting decimal value to string format and storing in accumulator*/
						regs[0] = hexAdd(regs[regID],regs[0],flag,true);
				    }else{                         
						/*Fetches data of HL pair*/
						string address = "";
						address = address + regs[5] + regs[6];
						if(address >= "0000" && address <= "FFFF"){	
						    /*Converting decimal value to string format and storing in accumulator*/
						    regs[0] = hexAdd(memory[address],regs[0],flag,true);				 
						}else{		
						    cout<<"Error: "<<arg1<<"\n";
						    cout<<"Address out of bounds\nThe program will quit\n";
						    exit(0);
					            /*error message of address out of bounds*/
						}						
			    	}
				}else{		
				    cout<<"Error: "<<arg1<<"\nInvalid reg details\nThe program will quit\n";
				    exit(0);
				    /*error of invalid reg details*/
				}
		    }else{
				cout<<"Error: "<<arg1<<"\nInvalid arguments\nThe program will quit\n";
				exit(0);
				/*Error message of invalid arguments*/
		    }
		}

		void ADI(string arg, string regs[],bool flag[]){
			valid val;
		    int length = arg.length();
		    if(length == 2){
				if(val.valData(arg)){
				    /*Performs immediate addition and stores in accumulator*/
				    regs[0] = hexAdd(arg,regs[0],flag,true);
				}else{
				    cout<<"Error: "<<arg<<"\nInvalid data content\nThe program will quit\n";
				    exit(0);
				    /*Error message of invalid data content*/
				}
		    }else{
				cout<<"Error: "<<arg<<"\nInvalid data size\nThe program will quit\n";
				exit(0);
				/*Error message of invalid data size*/
		    }
		}

		

		void SUB(string arg1,string regs[],bool flag[],map<string,string>&memory){
			valid val;
		    int length=arg1.length();
		    if(length == 1){
				if(val.valregs(arg1)){
				    if(arg1 != "M"){
						/*Fetches index of reg to access array string regs[]*/
						int regID = val.regNumber(arg1);              
						/*Converting decimal value to string format and storing in accumulator*/
						regs[0] = hexSub(regs[regID],regs[0],flag,true);
				    }else{                         
						/*Fetches data of HL pair*/
				        string address = "";
						address = address + regs[5] + regs[6];
						if(address >= "0000" && address <= "FFFF"){
						    /*Converting decimal value to string format and storing in accumulator*/
					        regs[0] = hexSub(memory[address],regs[0],flag,true);					
						}else{
						    cout<<"Error: "<<arg1<<"\nAddress out of bounds\nThe program will quit\n";
						    exit(0);
						    /*error message of address out of bounds*/
						}						
				    }
				}else{
				    cout<<"Error: "<<arg1<<"\nInvalid reg details\nThe program will quit\n";
				    exit(0);
				    /*error of invalid reg details*/
				}
		    }else{
			cout<<"Error: "<<arg1<<"\nInvalid arguments\nThe program will quit\n";
			exit(0);
			/*Error message of invalid arguments*/
		    }
		}

		void SUI(string arg, string regs[],bool flag[]){
			valid val;
		    int length = arg.length();
		    if(length == 2){
				if(val.valData(arg)){
				    /*Performs immediate subtraction and stores in accumulator*/
				    regs[0] = hexSub(arg,regs[0],flag,true);
				}else{
				    cout<<"Error: "<<arg<<"\n";
				    cout<<"This is an invalid data\n";
				    exit(0);
				    /*Error message of invalid data content*/
				}
		    }else{
				cout<<"Error: "<<arg<<"\n";
				cout<<"You have tried to enter invalid data\nThe program will quit\n";
				exit(0);
				/*Error message of invalid data size*/
		    }
		}

		string hexSub(string arg1,string arg2,bool flag[],bool carry){
		    string resultant = "";
		    int variable, parity, value1[2], value2[2], tempAnswer[2];
		    hexToDecimal(arg1,value1);
		    hexToDecimal(arg2,value2);
		    if(value1[1] < value2[1]){
				tempAnswer[1] = (16+value1[1])-value2[1];
				--value1[0];
		    }else{
				tempAnswer[1] = value1[1] - value2[1];
		    }
		    if(value1[0] < value2[0]){
				if(carry == true)
			    	flag[0] = true;
			    tempAnswer[0] = (16+value1[0]-value2[0]);
			}else
			    tempAnswer[0] = value1[0] - value2[0];
			variable = tempAnswer[0]*16 + tempAnswer[1];
	        bitset<8> dataInBinary(variable);
	        /*Setting parity flag*/
	        parity = dataInBinary.count();
	        if(parity%2 == 0 && parity!=0)
		    flag[2] = true;
	        else
		    flag[2] = false;
	        /*Setting sign flag*/
	        flag[7] = dataInBinary[7];
	        /*Setting zero flag*/
	        if(parity == 0)
	            flag[6] = true;
	        else
	            flag[6] = false;
	        /*Convert decimal data to hexadecimal and store in accumulator*/
	        for(int i = 1;i>=0;--i){
	            if(tempAnswer[i]>=0 && tempAnswer[i]<=9)
		        resultant = char('0'+tempAnswer[i]) + resultant;
	            else if(tempAnswer[i]>=10 && tempAnswer[i]<=15)
		        resultant = (char)('A'+(tempAnswer[i] - 10)) + resultant;
		    }
		    return resultant;
		}

		string hexSub16bit(string arg1,string arg2,bool flag[],bool carry){
		    string resultant = "";
		    int variable, parity, value1[4], value2[4], tempAnswer[4];
		    hexToDecimal(arg1,value1);
		    hexToDecimal(arg2,value2);
		    for(int i=3;i>=0;i--){
				if(value1[i] < value2[i]){
				    tempAnswer[i] = (16 + value1[i]) - value2[i];
					if(i!=0)
				  	    --value1[i-1];
					else{
					    if(carry)
						flag[0] = true;
					}
				}else
				    tempAnswer[i] = value1[i] - value2[i];
		    }
		    variable = tempAnswer[0]*16*16*16 + tempAnswer[1]*16*16 + tempAnswer[2]*16 + tempAnswer[3];
		    bitset<16> dataInBinary(variable);
		    /*Setting parity flag*/
		    parity = dataInBinary.count();
		    if(parity%2 == 0 && parity!=0)
				flag[2] = true;
		    else
				flag[2] = false;
		    /*Setting sign flag*/
		    flag[7] = dataInBinary[7];
		    /*Setting zero flag*/
		    if(parity == 0){
				flag[6] = true;
		    }else{
				flag[6] = false;
		    }
		    /*Convert decimal data to hexadecimal and store in accumulator*/
		    for(int i = 3;i>=0;--i){
				if(tempAnswer[i]>=0 && tempAnswer[i]<=9)
				    resultant = char('0'+tempAnswer[i]) + resultant;
				else if(tempAnswer[i]>=10 && tempAnswer[i]<=15)
				    resultant = (char)('A'+(tempAnswer[i] - 10)) + resultant;
		    }
		    return resultant;
		}

		void DAD(string arg,string regs[],bool flag[]){
			valid val;
		    int length = arg.length();
		    if(length == 1){
				if(val.valregs(arg)){
				    int regID = val.regNumber(arg);
					if(regID == 1 || regID == 3 || regID == 5){
					    string data16bit = "", data16bitHL = "", resultant = "";
						if(val.valData(regs[regID]) && val.valData(regs[regID+1]) && val.valData(regs[5]) && val.valData(regs[6])){
						    data16bit = data16bit + regs[regID] + regs[regID];
						    data16bitHL = data16bitHL + regs[5] + regs[6];
						    int value16bit[4], value16bitHL[4], carry = 0;
						    hexToDecimal(arg,value16bit);
						    hexToDecimal(arg,value16bitHL);	  
						    for(int i = 3;i>=0;i--){
								int value = value16bit[i] + value16bitHL[i] + carry;
								if(value >= 16)
								    flag[0] = true;
								else
								    flag[0] = false;
								carry = value / 16;
								value = value % 16;
								if(value>=0 && value<=9)
								    resultant = (char)('0' + value) + resultant;
								else{
								    switch(value){
										case 10:
										    resultant = "A" + resultant;
										    break;
										case 11:
										    resultant = "B" + resultant;
										    break;
										case 12:
										    resultant = "C" + resultant;
										    break;
										case 13:
										    resultant = "D" + resultant;
										    break;
										case 14:
										    resultant = "E" + resultant;
									        break;
										case 15:
										    resultant = "F" + resultant;
										    break;	
							        }
								}
					    	}
						    regs[5] = resultant[0] + resultant[1];
						    regs[6] = resultant[2] + resultant[3];	
						}else{
						    cout<<"Error: "<<arg<<"\nInvalid data content in registet\nThe program will quit\n";
						    exit(0);
						    /*Error:Invalid data content in regs*/
						}
				    }else{
						cout<<"Error: "<<arg<<"\nInvalid reg pair\nThe program will quit\n";
						exit(0);
						/*Error:Invaid reg pair*/
					}
			    }else{
					cout<<"Error: "<<arg<<"\nInvalid reg content\nThe program will quit\n";
					exit(0);
					/*Error:Invalid reg content*/ 
				}
		    }else{
				cout<<"Error: "<<arg<<"\nInvalid arguments\nThe program will quit\n";
				exit(0);
				/*Error:Invalid Input Argument*/
		    }
		}

		string JMP(string arg, string regs[],bool flag[]){
			valid val;
		    if(val.valAddress(arg))
				return arg;
		    else{
				cout<<"Error encountered in: "<<arg<<"\n";
				cout<<"The program will quit\n";
				exit(0);
		    }
		}

		string JC(string arg, string programCounter, string regs[],bool flag[]){
			valid val;
		    if(flag[0] == true)
				return arg; 
		    else{
				string resultant = "";
				int value16bit[4], returnValue[] = {0,0,0,3}, carry = 0;
				hexToDecimal(programCounter,value16bit);	  
				for(int i = 3;i>=0;i--){	
				    int value = value16bit[i] + returnValue[i] + carry;
				    carry = value / 16;
				    value = value % 16;
				    if(value>=0 && value<=9)
						resultant = (char)('0'+value) + resultant;
				    else
						resultant = (char)('A'+(value-10)) + resultant;
				}
				if(val.valAddress(resultant))
					return resultant;
				else{
				    cout<<"Error: "<<arg<<"\nAddress overflow\nThe program will quit\n";
				    exit(0);
				}
		    }
		}

		string JNC(string arg, string programCounter, string regs[],bool flag[]){
			valid val;
		    if(flag[0] == false)
				return arg;
		    else{
				string resultant = "";
				int value16bit[4], returnValue[] = {0,0,0,3}, carry = 0;
				hexToDecimal(programCounter,value16bit);	  
				for(int i = 3;i>=0;i--){
				    int value = value16bit[i] + returnValue[i] + carry;
				    carry = value / 16;
				    value = value % 16;
				    if(value>=0 && value<=9)
				        resultant = (char)('0' + value) + resultant;
				    else
					resultant = (char)('A' + (value-10)) + resultant;
				}
				if(val.valAddress(resultant))
				    return resultant;
				else{
				    cout<<"Error: "<<arg<<"\nAdress overflow\nThe program will quit\n";
				    exit(0);
				}
				/*Error - Address over-flow*/
		    }
		}

		string JZ(string arg, string programCounter, string regs[],bool flag[]){
			valid val;
		    if(flag[6] == true)
				return arg;
		    else{
				string resultant = "";
				int value16bit[4], returnValue[] = {0,0,0,3}, carry = 0;
				hexToDecimal(programCounter,value16bit);	  
				for(int i = 3;i>=0;i--){
				    int value = value16bit[i] + returnValue[i] + carry;
				    carry = value / 16;
				    value = value % 16;
				    if(value>=0 && value<=9)
						resultant = (char)('0' + value) + resultant;
				    else
						resultant = (char)('A'+(value-10)) + resultant;
				}
				if(val.valAddress(resultant))
				    return resultant;
				else{
				    cout<<"Error: "<<arg<<"\nAddress overflow\nThe program will quit\n";
				    exit(0);
				}
				/*Error - Address over-flow*/
		    }
		}

		string JNZ(string arg, string programCounter, string regs[],bool flag[]){
			valid val;
		    if(flag[6] == false){
				return arg;
		    }else{
		        string resultant = "";
		        int value16bit[4], returnValue[] = {0,0,0,3}, carry = 0;
		        hexToDecimal(programCounter,value16bit);	  
		        for(int i = 3;i>=0;i--){
				    int value = value16bit[i] + returnValue[i] + carry;
				    carry = value / 16;
				    value = value % 16;
				    if(value>=0 && value<=9)
				        resultant = (char)('0' + value) + resultant;
				    else
				        resultant = (char)('A'+(value-10)) + resultant;
		        }
		        if(val.valAddress(resultant))
			    	return resultant;
		        else{
				    cout<<"Error: "<<arg<<"\nAddress overflow\nThe program will quit\n";
				    exit(0);
		        }
		        /*Error - Address over-flow*/
		    }
		}

		void INR(string arg,string reg[],bool flag[],map<string,string>&memory){
			valid val;
		    int length = arg.length();
		    if(length == 1){
				if(val.valregs(arg)){
				    if(arg != "M"){
						/*Performs INR on a reg*/
						int regID = val.regNumber(arg);
						reg[regID] = hexAdd(reg[regID],"01",flag,false); 
				    }else{
						/*Performs DCR on HL pair*/
						string address = "";
						address = address + reg[5] + reg[6];
						if(val.valAddress(address)){
						    memory[address] = hexAdd(memory[address],"01",flag,false);
						}else{
						    cout<<"Error: "<<arg<<"\nAddress out of bounds\nThe program will quit\n";
						    exit(0);
						}
				    }
				}else{
				    cout<<"Error: "<<arg<<"\nInvalid reg details\nThe program will quit\n";
				    exit(0);
				    /*Error:Invalid reg*/
				}
		    }else{
				cout<<"Error: "<<arg<<"\nInvalid argument type\nThe program will quit\n";
				exit(0);
				/*Error: Invalid argument type*/
		    }
		}

		void INX(string arg,string reg[],bool flag[]){
			valid val;
		    int length = arg.length();
		    if(length == 1){
				if(val.valregs(arg)){
			    	int regID = val.regNumber(arg);
			    	if(regID == 1 || regID == 3 || regID == 5){
						string data16bit = "",  temporary = "", s1 = "", s2 = "";
						if(val.valData(reg[regID]) == true && val.valData(reg[regID+1]) == true){
						    data16bit = data16bit + reg[regID] + reg[regID + 1];
						    //temporary =  hexAdd16bit(data16bit,"0001",flag,false);
						    temporary = increaseAddress(data16bit);
						    s1 = s1 + temporary[0] + temporary[1];		
						    s2 = s2 + temporary[2] + temporary[3];
						    reg[regID] = s1; 
					   	    reg[regID+1] = s2;
						}else{
						    cout<<"Error: "<<arg<<"\nInvalid data content in reg\nThe program will quit\n";
						    exit(0);
						    /*Error:Invalid data content in reg*/
						}
				    }else{
						cout<<"Error: "<<arg<<"\nInvalid reg pair\nThe program will quit\n";
						exit(0);
						/*Error:Invaid reg pair*/
				    }
				}else{
				    cout<<"Error: "<<arg<<"\nInvalid reg content\nThe program will quit\n";
				    exit(0);
				    /*Error:Invalid reg content*/ 
				}
		    }else{
				cout<<"Error: "<<arg<<"\nInvalid input arguments\nThe program will quit\n";
				exit(0);
				/*Error:Invalid Input Argument*/
		    }
		}

		void DCR(string arg,string reg[],bool flag[],map<string,string>&memory){
			valid val;
		    int length = arg.length();
		    if(length == 1){
				if(val.valregs(arg)){
				    if(arg != "M"){
						/*Performs INR on a reg*/
						int regID = val.regNumber(arg);
						reg[regID] = hexSub(reg[regID],"01",flag,false);
				    }else{
						/*Performs DCR on HL pair*/
						string address = "";
						address = address + reg[5] + reg[6];
						if(val.valAddress(address)){
						    memory[address] = hexSub(memory[address],"01",flag,false);
						}else{
						    cout<<"Error: "<<arg<<"\nInvalid reg details\nThe program will quit\n";
						    exit(0);
						    /*Error:Address out of bounds*/
						}
				    }
				}else{
				    cout<<"Error: "<<arg<<"\nInvalid reg\nThe program will quit\n";
				    exit(0);
				    /*Error:Invalid reg*/
				}
		    }else{
				cout<<"Error: "<<arg<<"\nInvalid argument\nThe program will quit\n";
				exit(0);
				/*Error: Invalid argument type*/
		    }
		}

		void DCX(string arg,string reg[],bool flag[]){
			valid val;
		    int length = arg.length();
		    if(length == 1){
				if(val.valregs(arg)){
				    int regID = val.regNumber(arg);
				    if(regID == 1 || regID == 3 || regID == 5){
						string data16bit = "", temporary = "", s1 = "", s2 = "";
						if(val.valData(reg[regID]) == true && val.valData(reg[regID+1]) == true){
						    data16bit = data16bit + reg[regID] + reg[regID + 1];
						    temporary = hexSub16bit(data16bit,"0001",flag,false);
				            s1 = s1 + temporary[0] + temporary[1];		
						    s2 = s2 +temporary[2] + temporary[3];
					   	    reg[regID] = s1;
						    reg[regID+1] = s2;
						}else{
						    cout<<"Error: "<<arg<<"\nInvalid data content\nThe program will quit\n";
						    exit(0);
						    /*Error:Invalid data content in reg*/
						}
				    }else{
						cout<<"Error: "<<arg<<"\nInvalid reg pair\nThe program will quit\n";
						exit(0);
						/*Error:Invaid reg pair*/
				    }
				}else{
				    cout<<"Error: "<<arg<<"\nInvalid reg content\nThe program will quit\n";
				    exit(0);
				    /*Error:Invalid reg content*/ 
				}
		    }else{
				cout<<"Error: "<<arg<<"\nInvalid input arguments\nThe program will quit\n";
				exit(0);
				/*Error:Invalid Input Argument*/
		    }
		}

		string increaseAddress(string a){
			valid val;
			int number[5];
			string nextAddress="";
			int l=a.length();
			for(int i=l-1;i>=0;i--){
				if(a[i]>='A'&&a[i]<='F')
					number[i]=(int)(10+(a[i]-'A'));
				if(a[i]>='0'&&a[i]<='9')
					number[i]=(int)(a[i]-'0');
			}
			number[l-1]++;
			for(int i=l-1;i>=0;i--){
				if(number[i]>=0&&number[i]<=15)
					break;
				if(number[i]>=16){
					number[i]=number[i]%16;
					number[i-1]++;
				}
			}
			for(int i=0;i<l;i++){
				if(number[i]>=0&&number[i]<=9)
					nextAddress+=(char)('0'+(number[i]));
				else if(number[i]>=10 && number[i]<=15)
					nextAddress+=(char)('A'+(number[i]-10));
			}
			return nextAddress;
		}

		void SET(string arg1,string arg2,map<string,string> &memory){
			valid val;
		    int l1=arg1.length(), l2=arg2.length();
		    if(l1==4 && l2==2){	
				if(val.valAddress(arg1) && val.valData(arg2))
				    memory[arg1]=arg2;
				else{
				    cout<<"Error: "<<arg1<<" & "<<arg2<<"\nInvalid arguments\nThe program will quit\n";
				    exit(0);
				}
		    }else{
				cout<<"Error: "<<arg1<<" & "<<arg2<<"\nInvalid arguments\nThe program will quit\n";
				exit(0);
		    }
		}

		void LDA (string arg1,string reg[],bool flag[],map<string,string> &memory){
			valid val;
		    int l1=arg1.length();
		    if(l1==4){
				if(val.valAddress(arg1)){
				    reg[0] = memory[arg1];
				}else{
				    cout<<"Error: "<<arg1<<"\nInvalid address\nThe program will quit\n";
				    exit(0);
				}
		    }else{
				cout<<"Error: "<<arg1<<"\nInvalid arguments\nThe program will quit\n";
				exit(0);
		    }
		}

		void LXI (string arg1,string arg2,string reg[],bool flags[],map<string,string> &memory){
			valid val;
		    int l1=arg1.length(), l2=arg2.length();
		    if(l1==1&&l2==4){
				if(arg1=="M"){
				    if(val.valAddress(arg2)){
						string part1="",part2="";
						for(int i=0;i<2;i++){
						    part1+=arg2[i];
						    part2+=arg2[i+2];
						}
				        reg[5]=part1;
				        reg[6]=part2;
				    }else{
				        cout<<"Error: "<<arg1<<" & "<<arg2<<"\nInvalid content\nThe program will quit\n";
				        exit(0);
				    }
		        }else{
				    if(val.valregPair(arg1)&&val.valAddress(arg2)){
				        string part1="",part2="";
				        for(int i=0;i<2;i++){
						    part1+=arg2[i];
						    part2+=arg2[i+2];
				        }
				        reg[val.regNumber(arg1)]=part1;
				        reg[val.regNumber(arg1)+1]=part2;
				    }else{
				        cout<<"Error: "<<arg1<<" & "<<arg2<<"\nInvalid content\nThe program will quit\n";
				        exit(0);
				    }
	       		}
		    }else{
				cout<<"Error: "<<arg1<<" & "<<arg2<<"\nInvalid arguments\nThe program will quit\n";
				exit(0);
		    }
		}

		void LHLD (string arg1,string reg[],bool flag[],map<string,string> &memory){
			valid val;
		    int l1=arg1.length();
		    if(l1==4){
				if(val.valAddress(arg1)&&val.valAddress(increaseAddress(arg1))){
				    reg[6]=memory[arg1];
				    reg[5]=memory[increaseAddress(arg1)];
				}else{
				    cout<<"Error: "<<arg1<<"\nSome error is thrown\nThe program will quit\n";
				    exit(0);
				}
		    }else{
				cout<<"Error: "<<arg1<<"\nInvalid arguments\nThe program will quit\n";
				exit(0);
		    }
		}

		void STA (string arg1,string reg[],bool flag[],map<string,string> &memory){
			valid val;
		    int l1=arg1.length();
		    if(l1==4){
				if(val.valAddress(arg1))
				    memory[arg1]=reg[0];
				else{
				    cout<<"Error: "<<arg1<<"\nInvalid address\nThe program will quit\n";
				    exit(0);
				}
		    }else{
				cout<<"Error: "<<arg1<<"\nInvalid arguments\nThe program will quit\n";
				exit(0);
		    }
		}

		void STAX(string arg1,string reg[],bool flag[],map<string,string> &memory){
			valid val;
		    int l1=arg1.length();
		    if(l1==1){
				if(val.valregPair(arg1)){
				    string address="";
				    int index=val.regNumber(arg1);
				    address+=reg[index]+reg[index+1];
				    if(val.valAddress(address))
						memory[address]=reg[0];
				    else{
						cout<<"Error: "<<arg1<<"Invalid address\nThe program will quit\n";
						exit(0);
				    }
				}else{
				    cout<<"Error: "<<arg1<<"\nInvalid reg pair\nThe program will quit\n";
				    exit(0);
				}
		    }else{
				cout<<"Error: "<<arg1<<"\nInvalid content\nThe program will quit\n";
				exit(0);
		    }
		}

		void SHLD (string arg1, string reg[],bool flag[], map<string,string> &memory){
			valid val;
		    int l1=arg1.length();
		    if(l1==4){
				if(val.valAddress(arg1)&&val.valAddress(increaseAddress(arg1))){
				    memory[arg1]=reg[6];
				    memory[increaseAddress(arg1)]=reg[5];
				}else{
				    cout<<"Error: "<<arg1<<"\nInvalid address\nThe program will quit\n";
				    exit(0);
				}
		    }else{
				cout<<"Error: "<<arg1<<"Invalid argument\nThe program will quit\n";
				exit(0);
		    }
		}

		void XCHG (string reg[],bool flag[])
		{
		    swap(reg[3],reg[5]);
		    swap(reg[4],reg[6]);
		}

		void CMP (string arg1,string reg[],bool flag[],map<string,string> &memory){
			valid val;
		    int l1=arg1.length();
		    if(l1==1){
				if(arg1=="M"){
				    string address=reg[5]+reg[6];
					if(reg[0]<memory[address]){
					    flag[0]=true;
					}else if(reg[0]==memory[address]){
					    flag[6]=true;
					    //cout<<"zero set\n";
					}else{
					    //cout<<"both reset\n";
					    flag[0]=false;
					    flag[6]=false;
					}
				}else if(val.valregs(arg1)){
			        int index=val.regNumber(arg1);
				    if(reg[0]<reg[index]){
						//cout<<"carry set\n";
						flag[0]=true;
				    }else if(reg[0]==reg[index]){
						//cout<<"zero set\n";
						flag[6]=true;
				    }else{
						//cout<<"both reset\n";
						flag[0]=false;
						flag[6]=false;
				    }
				}else{	
				    cout<<"Error: "<<arg1<<"\nInvalid reg\nThe program will quit\n";
				    exit(0);
				}
		    }else{
				cout<<"Error: "<<arg1<<"\nInvalid argument\nThe program will quit\n";
				exit(0);
		    }
		}

		string complement(string a){
		    int l=a.length();
		    string complement="";
		    for(int i=0;i<l;i++){
				if(a[i]>='0'&&a[i]<='9'){
				    int diff=15-(a[i]-'0');
				    if(diff>=0&&diff<=9)
					complement+=('0'+diff);
				    else if(diff>=10&&diff<=15)
					complement+=('A'+(diff-10));	
				}
				if(a[i]>='A'&&a[i]<='F'){
				    int value=a[i]-'A', diff=15-value;
				    if(diff>=0&&diff<=9)
					complement+=('0'+diff);
				    else if(diff>=10&&diff<=15)
					complement+=('A'+(diff-10));
				}
		    }
		    return complement;
		}

		void MOV (string argument1,string argument2,string reg[],bool flag[],map<string,string> &memory){
			valid val;
		    int l1=argument1.length(), l2=argument2.length();
		    if(l1==1&&l2==1){
		        if(argument1=="M"&&argument2!="M"){
		            if(val.valregs(argument2)){
		                string address=reg[5]+reg[6];
		                memory[address]=reg[val.regNumber(argument2)];
		            }else{
						cout<<"Error: "<<argument1<<" & "<<argument2<<"\nInvalid reg\nThe program will quit\n";
						exit(0);
			    	}
		        }else if(argument1!="M" && argument2=="M"){
		            if(val.valregs(argument1)){
		                string address=reg[5]+reg[6];
		                reg[val.regNumber(argument1)]=memory[address];
		            }else{
						cout<<"Error: "<<argument1<<" & "<<argument2<<"\nInvalid reg\nThe program will quit\n";
						exit(0);
				    }
		        }else if(argument1!="M"&&argument2!="M"){
		            if(val.valregs(argument2)&&val.valregs(argument1)){
		                reg[val.regNumber(argument1)]=reg[val.regNumber(argument2)];
				   	}else{
						cout<<"Error: "<<"Invalid content\nThe program will quit\n";
						exit(0);
				   	}
		        }else{
				    cout<<"Error: "<<"Invalid content\nThe program will quit\n";
				    exit(0);
				}
		    }else{
				cout<<"Error: "<<"Invalid content\nThe program will quit\n";
				exit(0);
		    }
		}

		void MVI (string arg1,string arg2,string reg[],bool flags[],map<string,string> &memory){
			valid val;
		    int l1=arg1.length(), l2=arg2.length();
		    if(l1==1 && l2==2){
		        if(arg1=="M"){
		            string address=reg[5]+reg[6];
		            if(val.valData(arg2))
		                memory[address]=arg2;
		            else{
						cout<<"Error: "<<"Invalid content\nThe program will quit\n";
						exit(0);
				    }
		        }else if(val.valregs(arg1)&&val.valData(arg2)){
		            reg[val.regNumber(arg1)] = arg2;
		        }else{
				    cout<<"Error: "<<"Invalid content\nThe program will quit\n";
				    exit(0);
				}
		    }else{
				cout<<"Error: "<<"Invalid content\nThe program will quit\n";
				exit(0);
		    }
		}

		void CMA(string reg[],bool flags[]){
		    string complment = complement(reg[0]);
		    reg[0] = complment;
		    if(reg[0]=="00"){
		        flags[6] = true;
		        flags[2] = true;
		    }else{
		        string temp = reg[0];
				int array[2];
				hexToDecimal(temp,array);
				int value=array[1]*16+array[0];
				bitset<8> dataInBinary(value);
				int parity = dataInBinary.count();
				if(parity%2 == 0 && parity!=0)
				    flags[2] = true;
				else
				    flags[2] = false;
		    }
		}
};