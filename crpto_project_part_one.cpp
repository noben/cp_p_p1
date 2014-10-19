#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

string decrypt(string ctext, vector<string> &plaintext, int t)
{
    vector<int> vec_t(t, 0); // vector for storing the key
    int ctext_size = ctext.size();
    string ptext (ctext_size, 0); // initialize the ptext string
    for (int j = 1; j <= 40; ++j)
    {
        for (int i=0; i<ctext_size; i++)
        {
            ptext[i] = ctext[i] - (i/j)%t;
        }
        // compare the string ptext with input original message here? (by simply using "==" operator of string)
        // OR by using mechanisms like "string similarity" to check which plaintext to choose
        for (int i=0; i<plaintext.size(); i++)
        {
            if (plaintext[i]==ptext)
            {
                return ptext;
            }
        }
    }
	return "Not found";
}


int main(int argc, char const *argv[])
{
    ifstream ciphertext ( argv[1] );
    ifstream plaintext ( argv[2] );

    string result;
    string cipher_string;
    vector<string> plaintext_vector;

    // read ciper text from std input
    if (!ciphertext.is_open())
    	cout<<"Could not open file\n";
    else
    {
        // Read input from the ciphertext
    	while ( ciphertext >> cipher_string )
        	cout<< cipher_string<< endl;
    }

    // read plain_text from std input
    if (!plaintext.is_open())
        cout<<"Could not open file Plaintext\n";
    else
    {
        // Read input from the plaintext
        string temp_plaintext_line;
        while ( plaintext >>  temp_plaintext_line)
        {
            plaintext_vector.push_back(temp_plaintext_line);
            cout<< temp_plaintext_line << endl;
        }
    }

    // Now the variable cipher_string stores the cipher text and
    // plaintext_vector stores the original plain messages
    // result = decrypt(cipher_string, plaintext_vector, 5);

    // cout<<result<<endl;
    
	return 0;
}