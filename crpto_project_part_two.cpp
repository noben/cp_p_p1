#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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


// void function here for returning the result of words sets with length n
// It is actually get the Combination of all words that is in words set vector
void getStringCombinationWithLengthN(vector<string> &words, int cipher_string_len,
									 vector<vector<string> > &result,
									 vector<string> &temp_words_set,
									 int current_words_len,
									 int level)
{
	if (current_words_len>cipher_string_len)
		return;

	if (current_words_len==cipher_string_len)
	{
		result.push_back(temp_words_set);
		return;
	}

	for (int i=level; i<words.size(); i++)
	{
		temp_words_set.push_back(words[i]);
		getStringCombinationWithLengthN(words, cipher_string_len, result,
										temp_words_set, current_words_len+words[i].size(),
										i+1);
		temp_words_set.pop_back();
	}
	return;
}


// Helper function for permutate the words of length n sets
void permutateWords(vector<string> &words_sets,
					vector<string> &result, 
					vector<bool> &visited, 
					string temp_string,
					int text_length)
{
	if (temp_string.size()==text_length)
	{
		result.push_back(temp_string);
	}

	for (int i=0; i<words_sets.size(); i++)
	{
		if (!visited[i]){
			int temp_string_size = temp_string.size();
			visited[i] = true;
			temp_string += words_sets[i];
			permutateWords(words_sets, result, visited, temp_string, text_length);
			visited[i] = false;
			temp_string.resize(temp_string_size);
		}
	}
}

int main(int argc, char *argv[]) {

    ifstream ciphertext ( argv[1] );
    ifstream words ( argv[2] );
    int t = ( atoi(argv[3]) );

	string result;
    string cipher_string;
    vector<string> words_vector;

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
    if (!words.is_open())
        cout<<"Could not open file Plaintext\n";
    else
    {
        // Read input from the plaintext
        string temp_word;
        while ( words >> temp_word)
        {
        	// the below line should be used when the input file of string has '\n' at the end of each line
        	// temp_word = temp_word.substr(0, temp_word.size()-1);
            words_vector.push_back(temp_word);
            cout<< "Plaintext: "<< temp_word << endl;
        }
    }

    vector<vector<string> > words_with_length_n;
    vector<string> temp_words_set;
    getStringCombinationWithLengthN(words_vector, cipher_string.size(), words_with_length_n, temp_words_set, 0, 0);

    // Output the words set of length n for testing:
    for (int i=0; i<words_with_length_n.size(); i++)
    {
    	for (int j=0; j<words_with_length_n[i].size(); j++)
    		cout<< "words set: "<<words_with_length_n[i][j]<<endl;
    	cout<<"-------end-------"<<endl;
    }

    // Permutate each words set to get the possible plain text with the same length as cipher text
    vector<string> plaintext;
    for (int i=0; i<words_with_length_n.size(); i++)
    {
    	string temp;
    	vector<bool> visited(words_with_length_n[i].size(), false);
    	permutateWords(words_with_length_n[i], plaintext, visited, temp, cipher_string.size());
    }

    for (int i = 0; i < plaintext.size(); ++i)
    {
    	cout<<endl<<"Candidate Plaintext: "<<plaintext[i]<<endl;
    }

	// Decrypt:
	result = decrypt_1(cipher_string, plaintext, t);
	if (result == "Not Found")
    {
        // If the 1st situation cannot decrypt, then go to situation 2 as below:
        result = decrypt_2(cipher_string, plaintext, t);
    }

    cout<<endl<<"result: ";
    cout<<result<<endl;

	return 0;
}