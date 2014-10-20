// We consider solving the problem from 3 situations:
// 1st situation:
//      
// 2nd situation:
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// 1st situation: 
string decrypt_1(string ctext, vector<string> &plaintext, int t)
{
    int ctext_size = ctext.size();
    
    for (int k=0; k<plaintext.size(); k++)
    {
        string temp_plain_string = plaintext[k];

        int i=0;
        for (; i<ctext_size-t; i++)
        {
            cout<<"t: "<<t<<endl;
            cout<<"ctext i: "<<ctext[i]<<endl;
            cout<<"ctext i+t: "<<ctext[i+t]<<endl;
            cout<<"plain_text i: "<<temp_plain_string[i]<<endl;
            cout<<"plain_text i+t: "<<temp_plain_string[i+t]<<endl;
            if ((ctext[i]-temp_plain_string[i]) != (ctext[i+t]-temp_plain_string[i+t]))
            {
                break;
            }
        }
        if (i==(ctext_size-t)) return temp_plain_string;
    }
    // Assuming the input and out put text will always be lower case string
	return "Not Found";
}

// 2nd situation:
string decrypt_2(string ctext, vector<string> &plaintext, int t)
{
    int L = ctext.size();
    for (int l=0; l<plaintext.size(); l++)
    {
        int y = 0;
        string temp_plain_string = plaintext[l];
        while ( (y<L) && !(ctext[y] - temp_plain_string[y]) )
        {
            y++;
        }
        y++;
        
        if (y == 1)
        {
            continue;
        }
        else
        {
            int i=0;
            for (; i<t; i++)
            {
                bool flag = 1;
                for (int j=0; j<y-1; j++)
                {
                    if ( (ctext[i*y+j] - temp_plain_string[i*y+j]) != (ctext[i*y+j-1] - temp_plain_string[i*y+j-1]) )
                    {
                        flag = 0;
                        break;
                    }
                }
                if (!flag)
                {
                    break;
                }
            }
            
            if (i == t)
            {
                int k = 0;
                for (; k<L-t*y; k++)
                {
                    if ( (ctext[k] - temp_plain_string[k]) != (ctext[k+t*y] - temp_plain_string[k+t*y]) )
                    {
                        break;
                    }
                }
                if (k == L-t*y)
                {
                    return temp_plain_string;
                }
            }
        }
    }
    return "Not Found";
}


int main(int argc, char *argv[])
{
    ifstream ciphertext ( argv[1] );
    ifstream plaintext ( argv[2] );
    int t = ( atoi(argv[3]) );

    cout<<"Input t: "<<t<<endl;

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
        	cout<< "Ciphertext: "<< cipher_string<< endl;
    }

    // read plain_text from std input
    if (!plaintext.is_open())
        cout<<"Could not open file Plaintext\n";
    else
    {
        // Read input from the plaintext
        string temp_plaintext_line;
        while ( plaintext >> temp_plaintext_line)
        {
            plaintext_vector.push_back(temp_plaintext_line);
            cout<< "Plaintext: "<< temp_plaintext_line << endl;
        }
    }

    // Now the variable cipher_string stores the cipher text and
    // plaintext_vector stores the original plain messages, t stores the input t
    result = decrypt_1(cipher_string, plaintext_vector, t);
    if (result == "Not Found")
    {
        // If the 1st situation cannot decrypt, then go to situation 2 as below:
        result = decrypt_2(cipher_string, plaintext_vector, t);
    }

    cout<<"result: ";
    cout<<result<<endl;
    
	return 0;
}