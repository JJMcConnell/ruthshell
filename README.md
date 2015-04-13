## ruthshell
================
Shell inspired by Ruth's smooth snout. Created by Rutherford's Rascals for OS 2015

Using yacc/bison and lex/flex

How to run
----------
```
cd src
make
./shell
```

To Run A Script
---------------
`./shell < script.sh`


Not Implemented - 
    -Metacharacters:
        -Piping 
    -Wildcard Matching
    -Extra credit
        -Tilde Expansion
        -File Name Completion
    

Implemented -
    -Metacharacters:
        -Double quotes ("")
        -Backgrounding (&)
        -Escape (\)
        -I/O redirection (> and < )
    -Built-in Commands
        -setenv variable word
        -printenv
        -unsetenv variable
        -cd word_directory_name
        -alias name word
        -alias
        -unalias name
        -bye
    -External Commands (ls, pwd, echo etc.) 
    -Environment Variable Expansion ${variable}
    -Process handling (ie: CTR-C won't exit the shell)
    -Reading commands from a file
    

