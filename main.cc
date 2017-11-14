#include <bits/stdc++.h>
#include "header.cc"
using namespace std;

void wrongInput(){
    cout << "WRONG INPUT FORMAT" << endl;
    cout << "Input format should be in following manner" << endl;
    cout << "<Executable filename>" << endl;
    cout << "<Executable filename> -debugger" << endl;
    cout << "<Executable filename>  <input_filename>  " << endl;
    cout << "<Executable filename>  <input_filename>  -debugger"<< endl;
}

int main(int argc,char* argv[]){
    Emulator EmuInst;
    if(argc==1){
        EmuInst.noInput();
    }else if(argc==2){
        if(!strcmp(argv[1],"--debugger")){
            EmuInst.ProgWithDebugger();
        }else{
            EmuInst.ProgWithInputFile(argv[1]);
        }
    }else if(argc==3){
        if(!strcmp(argv[2],"--debugger")){
            EmuInst.ProgWithInputFileAndDebugger(argv[1]);
        }else{
            wrongInput();
        }
    }else{
        wrongInput();
    }
    return 0;
}
