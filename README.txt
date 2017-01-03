——————————
README 
——————————
Compiling the code for the assignment follows 2 simple steps 
1.) make -f makeAsgnServer2
2.) make -f makeAsgnClient

In order to run the program simply run for the server:
./Server2 52040 <Maximum Number of Clients> <Maximum Time before timeout (s)>

and for each client : 
./client <IP address of Server> 52040

To my knowledge the program works as intended. 

Tests done which will are found in the report are

Initial setup
Testing if the Server can be initialised with values
	1< and > 10 for maximum number of clients 
and 
	1< and > 120 for maximum idle time

Testing if the Server can have more clients than initialised with
Testing if a client stays connected after it has exceeded its maximum allocated idle time
Testing what happens to clients if the server closes prematurely

JOIN 
Testing if JOIN is called with invalid syntax
Testing if a client can JOIN to the server multiple times 
Testing if a client can JOIN with invalid inputs (character length for nickname,hostname,realname exceeds limit)
Testing if the client can JOIN with a nickname already used
Testing if the client can JOIN with a realname already used
Testing if the client can JOIN with a nickname/realname previously used and reconnected
Tesitng if the client can JOIN with a new nickname and realname

WHOIS
Testing if WHOIS is called with invalid syntax
Testing if the client will output an error if the WHOIS <nickname> is not found
Testing if the client will output the correct input if WHOIS <nickname> exists

ALIVE
Testing what happens when user enters ALIVE in client
Testing if time to timeout after typing ALIVE and leaving client idle matches specified server timeout time

MSG 
Testing what happens when <string> in  MSG <string> message does not exist in list of connections
Testing what happens when <string> after MSG <string> message does exist in list of connections

QUIT
Testing QUIT with quit message
Testing QUIT without quit message


Disclaimer
The code for this assignment was based off my tutorials and uses the wrapper functions from my Advanced Computer Communications textbook. This code was designed to be run on the redhat linux computers used at Curtin University.

Assumptions
I made the assumption that <hostname> does not need to be validated for the machine other than its character length.
I also made the assumption that server_machine_name means the IP address for the Server machine host
 
