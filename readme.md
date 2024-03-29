![alt text](resources/icon.png "Logo")



# Layl Shell
Welcome To The Layl Shell, A Shell And Script Interperter For Microsoft Windows


# How To Use

 - To enter the Shell, Just Start The Executable
 - To Use The Interperter, Either go to the commandline and start ``layl your-file-name.lys`` or enter the shell and type ``run your-file-name.lys`` (MUST BE IN SAME DIRECTORY AS THE SHELL!!!)


# Layl Shell/Script Interpreter Documentation
The Documentaion Will Be Here, As I don't think it needs a full new page (will do so though)

# MINOR COMMANDS
- echo [a]
    - prints a into the console
- wait [ms]
    - pauses the shell for the specified ms
- pause
    - pauses the shell till a key press is found


# FILE MANIPULATION COMMANDS

- fcreate [file]
    - creates a file
- fdelete [file]
    - deletes a file
- fcopy [file] [file2]
    - copys file to file2
- fread [file]
    - reads a file and prints its contents
- fwrite [file] [content]
    - writes content into file
- fprint [file] [content]
    - writes content into file without erasing the content inside


# DIRECTORY MANIUPLATION COMMANDS
- moveto [directory]
    - moves to that directory
- dcreate [directory]
    - creates that directory
- ddelete [directory]
     - deletes that directory
- pd {directory (optional)}
     - prints the content of the directory
- cd
    - prints what directory you are currently in


# START COMMAND

- start [perms] [process] {parameter (optional)}
    - perms can be either user or admin
    - process is the process name
    - parameter is whats passed into the process
    - it starts the process with the specifed permissions and parameters 

(You Can Also Start a Process with ,,[process] [parameters])

# PROCESS COMMAND
- process [arg] {parameters}
    - if its -k, you have to pass a PID of the process you want to kill into parameters
        - it will kill that process
    - if its -g, you have to pass the title-name of the window you want to get the pid from into the argumen
        - it will get the pid of that window
    - if its -l, no arguments are needed
        - it will list all the processes