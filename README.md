# PrettyPrinter
C/C++ Language Pretty Printer Program Source Code Indentation
                                                                                                                                
  Operations:                                                        
  - Accepts filename patterns from command line, expanding           
    wildcard characters, {*,?}, if encountered.                      
  - Accepts parameter changes from the command line, e.g.:           
      - ?    displays usage message                                   
      - i<n> sets tab width to n (default 2)                          
  - If the command line is empty, queries user for filename.         
  - Attempts to open all files, named on the command line.           
  - Reads and indents each file to stdout.                           
  
  Assumptions:                                                       
  - Each file contains correct C or C++ source code.                 
  
  Example invocation:                                                
  - pprint [-i4] pprint.cpp [>prn:] 

Reference:
- indent.c
