# DLL-Injection-Cpp
Inject a DLL into any process using this C++ program

# Installation
Go into a folder and open up Command Prompt.  
In command prompt run the following command: `git clone https://github.com/LouisTheXIV/DLL-Injection-Cpp.git`

# How to use
Note: Make sure you have Visual Studio 2019 installed with C++ development as well!

### First step:
Open the application you want to inject into. 
Go into injector/injector/ and open up Injector.cpp.  
In the main function change the const char* window_title variable to be the Window name of the program you want to inject the DLL into.

### Second step:
Build the Injector.cpp file in Debug mode, it is ok if you get an error saying DLL not found. 
Next step, drop the DLL which you want to Inject into the Injector/Injector/x64/Debug folder. 
Make sure to rename the DLL you have dropped to InjectDLL.dll.  
There is an example DLL in DLL\InjectDLL\x64\Debug\InjectDLL.dll. 
You should have an exe file in there called Injector.exe, run it.   

### Third step:
Now the DLL should have been injected successfully into the process of your choice!   
Have fun :D
