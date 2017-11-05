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
  
  saved_lexeme = saved_token; //update saved_lexeme

  return saved_token; // return the saved token
}

Boolean match(token_type expected)
{
  if (next_token() != expected)//mismatch has occurred with the next token
    { 
      // generate a syntax error message here
      // do error handling here if any
      syntax_error1();
    }
  else  // match has occurred
    {   
      token_available = false;  // eat up the token
      
      cout << "Matched " << expected << endl; //cout matched token
      
      return true;              // say there was a match
    }
} 

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Done by: Efren Martinez
void story()
{

}

void s1()
{
  cout << "Processing <s1>" << endl;
  
  if(next_token() == CONNECTOR)
    match(CONNECTOR);

  noun();

  if(next_token() == SUBJECT)
    match(SUBJECT);

  s2();
}

void s2()
{
  cout << "Processing <s2>" << endl;
  
  if(next_token() == WORD2)// <verb>
    {    
      verb();

      tense();

      if(next_token() == PERIOD)
	match(PERIOD);
    }

  else
    {
      noun();

      s3();
    }
}

void s3()
{
  if(next_token() == IS || next_token() == WAS)
    {
      be();

      if(next_token() == PERIOD)
        match(PERIOD);
    }

  else if(next_token() == DESTINATION)
    {
      match(DESTINATION);

      verb();

      tense();

      if(next_token() == PERIOD)
        match(PERIOD);
    }

  else if(next_token() == OBJECT)
    {
      match(OBJECT);

      if(next_token() == WORD1 || next_token() == PRONOUN)
	{
	  noun();

	  if(next_token() == DESTINATION)
	    match(DESTINATION);
	}

      verb();

      tense();

      if(next_token() == PERIOD)
        match(PERIOD);
    }
}

void noun()
{
  if(next_token() == WORD1)
    match(WORD1);
  else if(next_token() == PRONOUN)
    match(PRONOUN);
  else
    syntax_error2(next_token(), string);
}

void verb()
{
  if(next_token() == WORD2)
    match(WORD2);
}

void be()
{
  if(next_token() == IS)
    match(IS);
  else if(next_token() == WAS)
    match(WAS);
}

void tense()
{
  if(next_token() == VERBPAST)
    match(VERBPAST);
  else if(next_token() == VERBPASTNEG)
    match(VERBPASTNEG);
  else if(next_token() == VERB)
    match(VERB);
  else if(next_token() == VERBNEG)
    match(VERBNEG);
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


