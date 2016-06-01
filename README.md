# CSCI 344: Intro To Computer Communications
## Program 2: Slightly Modified Beale Code Encipherer/Decipherer (MBC)
### Goal:
- Write two programs. 
    - Client Program - Acts as the user interface 
    - Server Program - Takes commands, does requested work and returns results to a client program. 
- All communications between the client and server must be done using UNIX C++ Sockets. 
- Use loopback for server host

### Client Program:
 - Commands:
    - 'e' or 'E'
        - Encipher command
        - Sends the data to server to be enciphered using the MBC encryption alg. 
        - Server will encipher data and return the cipher code
        - Client then displays the original string followed by the cipher code on the line below 
        - Should be neat and labeled.
        - Take input from command line
    - 'd' or 'D'
        - Oppose of encipher command
        - Take cipher code as input and send to server to decipher
        - When done, print both cipher code and deciphered code to screen neatly in client program
        - String on command line should be integers seperated by at least one blank
    - 'q' or 'Q'
        - Quit
        - Get out of loop and say bye to user
    
### Server Program:
- Take a command from client until the command 'q' is read
- Encipher or Decipher based upon the command recieved ('e' or 'd')
- Data packet will never be longer than 80bytes
- Should have no screen output from server code with the exception of error messages (All I/O happens from within the client)

### Notes:
- Must read command line all at once (Dont break up the command with another prompt)
- Clear the screen often 
- Five files located on the CSCI 344 home page will help
    - BCipher.h - MBC class definition file 
    - BCipher.cpp - MBC class implementation file
    - bcdriver.cpp - Example driver program to show how to call BCipher methods
    - bc2.txt - Cipher text for Beale Cipher 2, the solved one
    - DOI.txt - Modified version of US Declartion of Independence to work with program. 
- Refer to http://en.wikipedia.org/wiki/Beale_ciphers  
 


