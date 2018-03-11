# 8085_Emulator

Getting Started :-

    In this the following commands are implemented:-
        •	Load and Store - MOV , MVI , LXI , LDA , STA , LHLD , SHLD , STAX , XCHG
        •	Arithmetic - ADD , ADI , SUB , INR , DCR , INX , DCX , DAD , SUI
        •	Logical - CMA , CMP
        •	Branching - JMP , JC , JNC , JZ , JNZ
        •	One Additional command SET should be made to set data into valid memory locations (Eg - SET 2500,0A ).

    Implementing debugger with the following commands:-
        1.	break or b `line no`:- It will set break point on given line number.
        2.	run or r :- Run the program until it ends or breakpoint is encountered.
        3.	step or s :- It will run the program one instruction at a time.
        4.	print or p:- It prints the value of register or memory location. for ex p A will print the value of
        5.	register A. p x2500 will print the value at memory location x2500 if any.
        6.	quit or q:- quits the debugger.
        7.	help:- will show all the commands of debugger.

Prerequisites :

      •	A 32-bit or 64-bit operating system(like Ubuntu, Windows or mac.......)
      •	C++ compiler like g++ and using c++11 version of g++ compiler for stoi function.

Running :

    On Ubuntu :
        •	$g++ <Program_name.cpp> -o <exe_filename>
        •	$./<exe_filename>  --debugger
        •	$./<exe_filename>   <input_filename>  
        •	$./<exe_filename>   <input_filename>  --debugger


    On IDE :
        •	Open any C++ IDE (like code-block, devc++, ...) and click on Compile and Run option.

    On Command Prompt (Windows) :
        •	First set the path of compiler.
        •	Open Command Prompt and type #$g++  <Program_name.cpp> -o <exe_filename>
        •	<exe_filename>  --debugger
        •	<exe_filename>   <input_filename>  
        •	<exe_filename>   <input_filename>  --debugger
