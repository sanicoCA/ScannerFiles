#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=================================================
// File parser.cpp written by Group Number: **
//=================================================

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)


// ** Need the updated match and next_token (with 2 global vars)
token next_token()
{  
  string lexeme;
  if (!token_available)// if there is no saved token from previous lookahead
    { 
      scanner(saved_token, lexeme);// call scanner to grab a new token
      token_available = true;      // mark that fact that you have saved it
    }
 
 return saved_token; // return the saved token
}

Boolean match(token_type expected)
{
  if (next_token() != expected)//mismatch has occurred with the next token
    { 
      // generate a syntax error message here
      // do error handling here if any
    }
  else  // match has occurred
    {   
      token_available = false;  // eat up the token
      return true;              // say there was a match
    }
}
 
// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
void s();
{

}


// The test driver to start the parser
// Done by:  **
int main()
{

  //- opens the input file
  //- calls the <story> to start parsing
  //- closes the input file 

}// end
//** should require no other input files!


