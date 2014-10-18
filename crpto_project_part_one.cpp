#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

string decrypt(stirng ctext, int t)
{
	// 1. x>y
	// 2. x<y
	// 3. x==y

    vector<int> vec_t(t, 0); // vector for storing the key
    int ctext_size = ctext.size();
    string ptext (ctext_size, 0); // initialize the ptext string
    for (int j = 1; j <= 40; ++j)
    {
        for (int i=0; i<ctext_size; i++)
        {
            ptext[i] = ciphertext[i] - (i/j)%t;
        }
        // compare the string ptext with input original message here? (by simply using "==" operator of string)
    }
	
}


int main(int argc, char const *argv[])
{
    ifstream ciphertext ( argv[1] );
    ifstream t ( argv[2] );

    string result;

    if (!ciphertext.is_open())
    	cout<<"Could not open file\n";
    else
    {
        // Read input from the phertext
    	string cipher_string;
    	while ( ciphertext >> cipher_string )
        	cout<< cipher_string<< endl;
        result = decrypt( cipher_string, 5 );
    }

     
	
	return 0;
}