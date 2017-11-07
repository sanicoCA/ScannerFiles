#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<vector>
#include "scanner.cpp"
using namespace std;

//=================================================
// File parser.cpp written by Group Number: **
//=================================================

//These will be used to easily cout the actual token type.

//If tokentype expected is WORD1 or 0, 
//then    cout << token_type[expected];     
//will output:  WORD1
string token_type[] = {"WORD1", "WORD2", "PERIOD", "ERROR","VERB","VERBNEG","VERBPAST","VERBPASTNEG","IS","WAS","OBJECT","SUBJECT","DESTINATION", "PRONOUN", "CONNECTOR", "EOFM" }; 

void noun();
void verb();
void be();
void tense();
void s3();
void s2();
void s1();

string saved_lexeme; //save the latest read string from file
tokentype saved_token; //save the latest read token type
bool token_available = false; //start token_available as false

fstream fin; //so we can read from file in any function

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
void syntax_error1(tokentype expected, string lexeme)
{
  cout << "SYNTAX ERROR: Expected " << token_type[expected] << " but found " << lexeme << "\n\n\n";

  exit(1);
}

void syntax_error2(string lexeme, string parser_function)
{
  cout << "SYNTAX ERROR: Unexpected " << lexeme << " found in " << parser_function << "\n\n\n";

  exit(1);
}

// ** Need the updated match and next_token (with 2 global vars)
tokentype next_token()
{  
  string lexeme;

  if (!token_available)// if there is no saved token from previous lookahead
    { 
      fin >> lexeme; //read next string from file
      
      scanner(saved_token, lexeme);// call scanner to grab a new token
      token_available = true;      // mark that fact that you have saved it
      
      saved_lexeme = lexeme; //update saved_lexeme
      
      cout << "Scanner was called..." << endl; 
    }

  return saved_token; // return the saved token
}

bool match(tokentype expected)
{
  if (next_token() != expected)//mismatch has occurred with the next token
    { 
      // generate a syntax error message here
      // do error handling here if any
      syntax_error1(expected, saved_lexeme); 
    }
  else  // match has occurred
    {   
      token_available = false;  // eat up the token
      
      cout << "Matched " << token_type[expected] << endl; //cout matched token
      
      return true;              // say there was a match
    }
} 

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Done by: 
void story()
{
  do
    {
      cout << "\n========== Processing <story> ==========" << endl;
      s1();

    }while(next_token() != EOFM);  
}

void s1()
{
  cout << "Processing <s1>" << endl;

  if(next_token() == CONNECTOR)
    match(CONNECTOR);

  noun();

  if(next_token() == SUBJECT)
    match(SUBJECT);
  else 
    syntax_error1(SUBJECT, saved_lexeme);

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
      else
	syntax_error1(PERIOD, saved_lexeme);
    }

  else
    {
      noun();

      s3();
    }
}

void s3()
{
  cout << "Processing <s3>" << endl;

  if(next_token() == IS || next_token() == WAS)
    {
      be();

      if(next_token() == PERIOD)
        match(PERIOD);
      else
        syntax_error1(PERIOD, saved_lexeme);
    }

  else if(next_token() == DESTINATION)
    {
      match(DESTINATION);

      verb();

      tense();

      if(next_token() == PERIOD)
        match(PERIOD);
      else
        syntax_error1(PERIOD, saved_lexeme);
    }

  else if(next_token() == OBJECT)
    {
      match(OBJECT);

      if(next_token() == WORD1 || next_token() == PRONOUN)
	{
	  noun();

	  if(next_token() == DESTINATION)
	    match(DESTINATION);
	  else
	    syntax_error1(DESTINATION, saved_lexeme);
	}

      verb();

      tense();

      if(next_token() == PERIOD)
        match(PERIOD);
      else
        syntax_error1(PERIOD, saved_lexeme);
    }
  else
    {
      syntax_error2(saved_lexeme, "s3");
    }
}

void noun()
{
  cout << "Processing <noun>" << endl;

  if(next_token() == WORD1)
    match(WORD1);
  else if(next_token() == PRONOUN)
    match(PRONOUN);
  else
    syntax_error2(saved_lexeme, "noun");
}

void verb()
{
  cout << "Processing <verb>" << endl;

  if(next_token() == WORD2)
    match(WORD2);
  else
    syntax_error2(saved_lexeme, "verb");
}

void be()
{
  cout << "Processing <be>" << endl;

  if(next_token() == IS)
    match(IS);
  else if(next_token() == WAS)
    match(WAS);
  else
    syntax_error2(saved_lexeme, "be");
}

void tense()
{
  cout << "Processing <tense>" << endl;

  if(next_token() == VERBPAST)
    match(VERBPAST);
  else if(next_token() == VERBPASTNEG)
    match(VERBPASTNEG);
  else if(next_token() == VERB)
    match(VERB);
  else if(next_token() == VERBNEG)
    match(VERBNEG);
  else
    syntax_error2(saved_lexeme, "tense");
}

// The test driver to start the parser
// Done by:  **
int main()
{
  //- opens the input file
  //- calls the <story> to start parsing
  //- closes the input file  
  string thefile;

  cout << "Please enter the name of the file: " << endl;
  cin >> thefile;

  fin.open(thefile.c_str());

  story();

  fin.close();

  return 0;
}// end
//** should require no other input files!


