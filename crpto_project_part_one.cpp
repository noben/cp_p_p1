#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream cyphertext ( argv[1] );

    if (!cyphertext.is_open())
    	cout<<"Could not open file\n";
    else
    {
    	string cypher_string;
    	while ( cyphertext >> cypher_string )
        	cout<< cypher_string<< endl;
    }

	
	return 0;
}