#include <bits/stdc++.h>
using namespace std;

map<string,string> cmdoutput;
vector<string> cmdaddress;

class valid{
    public :

        void wrongData(){
            cout << "You have entered invalid address" << endl;
            cout << "Try Again with valid address" << endl;
            exit(0);
        }
        
        void checkAddress(string data){
            if(data.size()==4){
                for(int i=0;i<4;i++){
                    if(!((data[i]>='0' && data[i]<='9') || (data[i]>='a' && data[i]<='f') || (data[i]>='A' && data[i]<='F'))){
                        wrongData();
                    }
                }
            }else{
                wrongData();
            }
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

        bool valAddress(string data){
            bool flag;
            int l=data.length();
            if(l==4){
            for(int i=0;i<l;i++)
                if(( data[i]>='0' && data[i]<='9')||( data[i]>='A' && data[i]<='F' )){
                    flag=true;
                }else{
                    flag=false;
                    break;
                }
            }
            return flag;
        }

        bool valregs(string reg){
            if(reg=="A"||reg=="B"||reg=="C"||reg=="D"||reg=="E"||reg=="H"||reg=="L")
                return true;
            else
                return false;
        }

        bool valregPair(string reg){
            if(reg=="B"||reg=="D"||reg=="H"||reg=="M")
                return true;
            else 
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

        bool align(string str){ 
            int l = str.length();
            for(int i=0;i<l;i++){   
                if(!((str[i]>='0' && str[i]<='9') || str[i] == ' ' || str[i] == ',' || (str[i]>='A' && str[i]<='Z')))
                    return false;
            }
            return true;
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

        int operationSize(string str){
            string one[] = {"HLT","MOV","XCHG","ADD","SUB","INR","DCR","INX","DCX","DAD","CMA","CMP"};
            string two[] = {"MVI","ADI","SUI"};
            string three[] = {"LXI","LDA","STA","SHLD","LHLD","JMP","JC","JNZ","JNC","JZ","SET","STAX"};
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

        int regNumber(string str){
            if(str=="A")
                return 0;
            else if(str=="B")
                return 1;
            else if(str=="C")
                return 2;
            else if(str=="D")
                return 3;
            else if(str=="E")
                return 4;
            else if(str=="H")
                return 5;
            else if(str=="L")
                return 6;
            return 0;
        }
};

