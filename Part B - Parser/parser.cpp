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

/*
  These will be used to easily print the actual token type name.
  
  If tokentype expected is WORD1, or it's actual value 0, 
  then    
  cout << token_type[expected];     
  will output the string:  WORD1
*/
string token_type[] = {"WORD1", "WORD2", "PERIOD", "ERROR", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"}; 

void noun();
void verb();
void be();
void tense();
void s3();
void s2();
void s1();

string saved_lexeme; //save the latest read string from file
tokentype saved_token; //save the latest read token type

string thefile; //name of file being read

bool token_available = false; //start token_available as false
bool traceON; //checks whether trace should be on or off

ofstream fout; //so we can write to file from error functions

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
void syntax_error1(tokentype expected, string lexeme)
{
  cout << "SYNTAX ERROR: Expected " << token_type[expected] << " but found " << lexeme << "\n\n\n";

  fout << "In file " << thefile << ":" << endl; //write the name of the file opened to the error file

  fout << "SYNTAX ERROR: Expected " << token_type[expected] << " but found " << lexeme << "\n\n"; //write to error file

  exit(1);
}

void syntax_error2(string lexeme, string parser_function)
{
  cout << "SYNTAX ERROR: Unexpected " << lexeme << " found in " << parser_function << "\n\n\n";

  fout << "In file " << thefile << ":" << endl; //write the name of the file opened to the error file

  fout << "SYNTAX ERROR: Unexpected " << lexeme << " found in " << parser_function << "\n\n"; //write to error file

  exit(1);
}

// ** Need the updated match and next_token (with 2 global vars)
tokentype next_token()
{  
  string lexeme;

  if(!token_available)// if there is no saved token from previous lookahead
    {       
      scanner(saved_token, lexeme);// call scanner to grab a new token
      token_available = true;      // mark that fact that you have saved it
      
      saved_lexeme = lexeme; //update saved_lexeme with latest string from file
      
      if(traceON)
	cout << "Scanner was called..." << endl; 
    }

  return saved_token; // return the saved token
}

bool match(tokentype expected)
{
  if(next_token() != expected)//mismatch has occurred with the next token
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
//<story>::= <s1>{<s1>}
void story()
{
  while(true)
    {
      switch(next_token())
	{
	case EOFM:
	  return;
	default:
	  cout << endl;
          if(traceON) //if trace is off, skip these cout's
            cout << "========== Processing <story> ==========" << endl;
          s1();
          break;
	}
    }
}

//<s1>::= [CONNECTOR]<noun>SUBJECT<s2>
void s1()
{
  if(traceON)
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

//<s2>::= <verb><tense>PERIOD | <noun><s3>
void s2()
{
  if(traceON)
    cout << "Processing <s2>" << endl;
  
  switch(next_token())
    {
    case WORD2:
      verb();
      tense();
      if(next_token() == PERIOD)
        match(PERIOD);
      else
        syntax_error1(PERIOD, saved_lexeme);
      break;

    case WORD1:
    case PRONOUN:
      noun();
      s3();
      break;

    default:
      syntax_error2(saved_lexeme, "s2");
    }
}

//<s3>::= <be>PERIOD | DESTINATION<verb><tense>PERIOD | OBJECT[<noun>DESTINATION]<verb><tense>PERIOD
void s3()
{
  if(traceON)
    cout << "Processing <s3>" << endl;

  switch(next_token())
    {
    case IS:
    case WAS:
      be();      
      if(next_token() == PERIOD)
        match(PERIOD);
      else
        syntax_error1(PERIOD, saved_lexeme);
      break;

    case DESTINATION:
      match(DESTINATION);
      verb();
      tense();
      if(next_token() == PERIOD)
        match(PERIOD);
      else
        syntax_error1(PERIOD, saved_lexeme);
      break;


    case OBJECT:
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
      break;

    default:
      syntax_error2(saved_lexeme, "s3");
    }     
}

//<noun>::= WORD1 | PRONOUN
void noun()
{
  if(traceON)
    cout << "Processing <noun>" << endl;

  switch(next_token())
    {
    case WORD1:
      match(WORD1);
      break;
    case PRONOUN:
      match(PRONOUN);
      break;
    default:
      syntax_error2(saved_lexeme, "noun");
    }
}

//<verb>::= WORD2
void verb()
{
  if(traceON)
    cout << "Processing <verb>" << endl;

  switch(next_token())
    {
    case WORD2:
      match(WORD2);
      break;
    default:
      syntax_error2(saved_lexeme, "verb");
    }
}

//<be>::= IS | WAS
void be()
{
  if(traceON)
    cout << "Processing <be>" << endl;

  switch(next_token())
    {
    case IS:
      match(IS);
      break;
    case WAS:
      match(WAS);      
      break;
    default:
      syntax_error2(saved_lexeme, "be");
    }
}

//<tense>::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
void tense()
{
  if(traceON)
    cout << "Processing <tense>" << endl;

  switch(next_token())
    {
    case VERBPAST:
      match(VERBPAST);
      break;
    case VERBPASTNEG: 
      match(VERBPASTNEG);
      break;
    case VERB:
      match(VERB);
      break;
    case VERBNEG:
      match(VERBNEG);
      break;
    default:
      syntax_error2(saved_lexeme, "tense");
    }
}

// The test driver to start the parser
// Done by:  **
int main()
{
  //- opens the input file
  //- calls the <story> to start parsing
  //- closes the input file  

  //  string thefile;
  char traceDecision;

  cout << "Please enter the name of the file: " << endl;
  cin >> thefile;

  //loop until a proper answer is given
  while(traceDecision != 'y' && traceDecision != 'n')
    {
      cout << "Do you want trace on? (y or n): ";
      cin >> traceDecision;
     
      if(traceDecision == 'y')
	traceON = true;
      else if(traceDecision == 'n')
	traceON = false;
    }

  fin.open(thefile.c_str());
  /*
    Open file to write errors.

    New errors will be added to the end of the file
    instead of overwriting what was previously written.
  */
  fout.open("errors.txt", ios::out | ios::app); 

  story(); //call story() to start parsing

  fin.close();
  fout.close();

  return 0;
}// end
//** should require no other input files!


