#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: ** 
//=====================================================

// ** MYTOKEN DFA to be replaced by the WORD DFA
// ** Done by: Efren Martinez
// ** RE: (vowel | vowel n | consonant vowel | consonant vowel n | consonant-pair vowel | consonant-pair vowel n)^+
bool wordToken(string s)
{
  string state = "q0";

  for(int pos = 0; pos < s.size(); pos++)
    {
      if(state == "q0")
	{
	  //Since 'e' and 'i' can be upper-case, tolower() is used when checking those letters 
	  if(s[pos] == 'a' || tolower(s[pos]) == 'e' || tolower(s[pos]) == 'i' || s[pos] == 'o' || s[pos] == 'u')
	    state = "q0qVn";
	  else if(s[pos] == 'b' || s[pos] == 'g' || s[pos] == 'h' || s[pos] == 'k' || s[pos] == 'm' || s[pos] == 'n' || s[pos] == 'p' || s[pos] == 'r')
	    state = "q0yqc";
	  else if(s[pos] == 'd' || s[pos] == 'j' || s[pos] == 'w' || s[pos] == 'y' || s[pos] == 'z')
	    state = "qc";
	  else if(s[pos] == 't')
	    state = "qtsqc";
	  else if(s[pos] == 's')
	    state = "qchqc";
	  else if(s[pos] == 'c')
	    state = "qch";
	  else //all letters not already checked go to state "trap", ie. it fails and returns false
	    return false;
	}

      else if(state == "q0qVn")
	{
	  if(s[pos] == 'a' || tolower(s[pos]) == 'e' || tolower(s[pos]) == 'i' || s[pos] == 'o' || s[pos] == 'u')
	    state = "q0qVn";
	  else if(s[pos] == 'b' || s[pos] == 'g' || s[pos] == 'h' || s[pos] == 'k' || s[pos] == 'm' || s[pos] == 'p' || s[pos] == 'r')
	    state = "q0yqc";
	  else if(s[pos] == 'n')
	    state = "q0q0yqc";
	  else if(s[pos] == 'd' || s[pos] == 'j' || s[pos] == 'w' || s[pos] == 'y' || s[pos] == 'z')
	    state = "qc";
	  else if(s[pos] == 't')
            state = "qtsqc";
      else if(s[pos] == 's')
            state = "qchqc";
      else if(s[pos] == 'c')
            state = "qch";
	  else 
	    return false;
	}

      else if(state == "q0yqc")
	{
          if(s[pos] == 'a' || tolower(s[pos]) == 'e' || tolower(s[pos]) == 'i' || s[pos] == 'o' || s[pos] == 'u')
            state = "q0qVn";
	  else if(s[pos] == 'y')
	    state == "qc";
	  else
	    return false;
	}

      else if(state == "qc")
	{
          if(s[pos] == 'a' || tolower(s[pos]) == 'e' || tolower(s[pos]) == 'i' || s[pos] == 'o' || s[pos] == 'u')
            state = "q0qVn";
	  else
	    return false;
	}

      else if(state == "qtsqc")
	{
          if(s[pos] == 'a' || tolower(s[pos]) == 'e' || tolower(s[pos]) == 'i' || s[pos] == 'o' || s[pos] == 'u')
            state = "q0qVn";
	  else if(s[pos] == 's')
	    state = "qc";
	  else 
	    return false;
	}

      else if(state == "qchqc")
	{
          if(s[pos] == 'a' || tolower(s[pos]) == 'e' || tolower(s[pos]) == 'i' || s[pos] == 'o' || s[pos] == 'u')
            state = "q0qVn";
          else if(s[pos] == 'h')
            state = "qc";
          else
            return false;
	}

      else if(state == "qch")
	{
	  if(s[pos] == 'h')
            state = "qc";
	  else 
	    return false;
	}

      else if(state == "q0q0yqc")
	{
          if(s[pos] == 'a' || tolower(s[pos]) == 'e' || tolower(s[pos]) == 'i' || s[pos] == 'o' || s[pos] == 'u')
            state = "q0qVn";
          else if(s[pos] == 'b' || s[pos] == 'g' || s[pos] == 'h' || s[pos] == 'k' || s[pos] == 'm' || s[pos] == 'n' || s[pos] == 'p' || s[pos] == 'r')
            state = "q0yqc";
          else if(s[pos] == 'd' || s[pos] == 'j' || s[pos] == 'w' || s[pos] == 'y' || s[pos] == 'z')
            state = "qc";
          else if(s[pos] == 't')
            state = "qtsqc";
          else if(s[pos] == 's')
            state = "qchqc";
          else if(s[pos] == 'c')
            state = "qch";
          else
            return false;
	}
    }

  //if in finals states "q0qVn" or "q0q0yqc" then return true
  if(state == "q0qVn" || state == "q0q0yqc") 
    return true;
  else 
    return false;
}

// ** Add the PERIOD DFA here
// ** Done by: Efren Martinez
bool punctuationToken(string s)
{
  if(s == ".")
    return true;
  else
    return false;
}

// ** Update the tokentype to be WORD1, WORD2, PERIOD and ERROR.
typedef enum tokentype {ERROR, };

// ** Need the lexicon to be set up here (to be used in Part C)
// ** Need the reservedwords list to be set up here
// ** Do not require any file input for these.
// ** a.out should work without any additional files.

// Scanner processes only one word each time it is called
// ** Done by: 
int scanner(tokentype& a, string& w)
{

  // ** Grab the next word from the file

  /* 
  2. Call the token functions one after another (if-then-else)
     And generate a lexical error if both DFAs failed.
     Let the token_type be ERROR in that case.
  3. Make sure WORDs are checked against the reservedwords list
     If not reserved, token_type is WORD1 or WORD2.
  4. Return the token type & string  (pass by reference)
  */

}//the end



// The test driver to call the scanner repeatedly  
// ** Done by:  **
int main()
{
  tokentype thetype;
  string theword; 

  /*
1. get the input file name from the user
2. open the input file which contains a story written in Japanese (fin.open).
3. call Scanner repeatedly until the EOF marker is read, and
     each time cout the returned results
     e.g. STRING TOKEN-TYPE
          =====  ===========
          watashi PRONOUN  (from the first call)
          wa      SUBJECT  (from the second call)
          gakkou  WORD1
          etc.
  */

  while (true)
    {
      scanner(thetype, theword);  // call the scanner

       cout << "Type is:" << thetype << endl;
       cout << "Word is:" << theword << endl;   

       // ** display the actual type instead of a number

    }

  // ** close the input file

}// end



