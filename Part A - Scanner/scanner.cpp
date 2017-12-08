#include<iostream>
#include<fstream>
#include<string>
#include<vector>
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
	    state = "qc";
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
typedef enum tokentype {WORD1, WORD2, PERIOD, ERROR,
                VERB,VERBNEG,VERBPAST,VERBPASTNEG,
                IS,WAS,OBJECT,SUBJECT,DESTINATION, 
                PRONOUN, CONNECTOR, EOFM };

// ** Need the lexicon to be set up here (to be used in Part C)
// ** Need the reservedwords list to be set up here
// ** Done by: Jason and Chris
bool isReserved(string s, tokentype& t)
{
  for(int i = 0; i < s.size(); i++)
  {
   s[i] = tolower(s[i]);
  }
  if(s == "masu")
  {
    t = VERB;
    return true;
  }
  else if(s == "masen")
  {
    t = VERBNEG;
    return true;
  }
  else if(s == "mashita")
  {
    t = VERBPAST;
    return true;
  }

  else if(s == "masendeshita")
  {
    t = VERBPASTNEG;
    return true;
  }
  else if(s == "desu")
  {
    t = IS;
    return true;
  }
  else if(s == "deshita")
  { 
    t = WAS;
    return true;
  }
  else if(s == "o")
  {
    t = OBJECT;
    return true;
  }
  else if(s == "wa")
  {
    t = SUBJECT;
    return true;
  }
  else if(s == "ni")
  {
    t = DESTINATION;
    return true;
  }
  else if(s == "watashi")
  {
    t = PRONOUN;
    return true;
  }
  else if(s == "anata")
  {
    t = PRONOUN;
    return true;
  }
  else if(s == "kare")
  {
    t = PRONOUN;
    return true;
  }
  else if(s == "kanojo")
  {
    t = PRONOUN;
    return true;
  }
  else if(s == "sore")
  {
    t = PRONOUN;
    return true;
  }
  else if(s == "mata")
  {
    t = CONNECTOR;
    return true;
  }
  else if(s == "soshite")
  {
    t = CONNECTOR;
    return true;
  }
  else if(s == "shikashi")
  {
    t = CONNECTOR;
    return true;
  }
  else if(s == "dakara")
  {
    t = CONNECTOR;
    return true;
  }
  else if(s == "eofm")
  {
    
    t = EOFM;
    return true;
  }
  else
  {
    return false;
  }


  
}
// ** Do not require any file input for these.
// ** a.out should work without any additional files.

// Scanner processes only one word each time it is called
// ** Done by: Jason
int scanner(tokentype& a, string& w)
{

  // ** Grab the next word from the file

  if(punctuationToken(w))
  a = PERIOD;
  else if(wordToken(w))
  {
    if(isReserved(w,a))
    {
      return 1;
    }
    else
    {
      if(w[w.size()-1] == 'I' | w[w.size()-1] == 'E')
      {
        a = WORD2;
      }
      else
      {
        a = WORD1;
      }
    }

  }
  else
  {
    a = ERROR;
  }

  /* 
  2. Call the token functions one after another (if-then-else)
     And generate a lexical error if both DFAs failed.
     Let the token_type be ERROR in that case.
  3. Make sure WORDs are checked against the reservedwords list
     If not reserved, token_type is WORD1 or WORD2.
  4. Return the token type & string  (pass by reference)
  */
return 1;
}//the end



// The test driver to call the scanner repeatedly  
// ** Done by:  Chris
int main()
{
  tokentype thetype;
  string theword; 
  string thefile;
  fstream fin;

  cout << "Please Enter the name of the file" << endl;
  cin >> thefile;
  fin.open(thefile.c_str());
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
  while ( theword != "eofm")
    {
      fin >> theword; 
      scanner(thetype, theword);  // call the scanner

       cout << "Word is:" << theword << endl;   
       switch (thetype)
       {
         case WORD1:
         cout << "Type is: WORD1" << endl;
         break;
         case WORD2:
         cout << "Type is: WORD2" << endl;
         break;
         case PERIOD:
         cout << "Type is: PERIOD" << endl;
         break;
         case ERROR:
         cout << "Lexical error: " << theword <<" is not a valid token" << endl;
         break;
         case VERB:
         cout << "Type is: VERB" << endl;
         break;
         case VERBNEG:
         cout << "Type is: VERBNEG" << endl;
         break;
         case VERBPAST:
         cout << "Type is: VERBPAST" << endl;
         break; 
         case VERBPASTNEG:
         cout << "Type is: VERBPASTNEG" << endl;
         break;
         case IS:
         cout << "Type is: IS" << endl;
         break; 
         case WAS:
         cout << "Type is: WAS" << endl;
         break;
         case OBJECT:
         cout << "Type is: OBJECT" << endl;
         break; 
         case SUBJECT:
         cout << "Type is: SUBJECT" << endl;
         break;
         case DESTINATION:
         cout << "Type is: DESTINATION" << endl;
         break;
         case PRONOUN:
         cout << "Type is: PRONOUN" << endl;
         break;
         case CONNECTOR:
         cout << "Type is: CONNECTOR" << endl;
         break;
         case EOFM:
         break;

       };

       // ** display the actual type instead of a number

    }

  // ** close the input file

}// end



