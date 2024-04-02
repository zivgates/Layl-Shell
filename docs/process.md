# Process Management

# Starting Process

- start [perms] [process] {parameter (optional)}
    - perms can be either user or admin
    - process is the process name
    - parameter is whats passed into the process
    - it starts the process with the specifed permissions and parameters 

(You Can Also Start a Process with ,,[process] [parameters])

# Manipulationg Processes

- process [arg] {parameters}
    - if its -k, you have to pass a PID of the process you want to kill into parameters
        - it will kill that process
    - if its -g, you have to pass the title-name of the window you want to get the pid from into the argumen
        - it will get the pid of that window
    - if its -l, no arguments are needed
        - it will list all the processes