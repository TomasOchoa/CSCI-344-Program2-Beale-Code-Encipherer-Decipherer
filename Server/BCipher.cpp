// Modified Beale Cipher driver demo program
// JW Ryder - Spring 2012
#ifndef BCIPHERH
#include "BCipher.h"
#include <time.h>
#include <ctime>
#include <cstdlib>
#endif

//-----------------------------------------------
// CTOR
// PreConditions : None
// PostConditions:
// - words array will be ready to use
// - lettercount array will be ready to use
//-----------------------------------------------
BCipher::BCipher(void)
{
 ifstream in;
 ofstream out("numberedDOI.txt");
 string   aword;
 int      count = 0, linecount = 0, i;
 char     temp;

 in.open("DOI.txt");			// the DOI
 if (in.fail())
  cout << "\nProblems opening DOI file\n\n";
 else
 {
  // read in DOI. Stick in words array and
  // create a file with all words numbered
  in >> aword;
  while (!in.eof())
  {
   if (linecount == 6)
    { linecount = 0; out << endl; }
   linecount++; count++;
   out  << "(" << count << ") " << aword << " ";
   // waste words[0] - NOT USED
   words[count] = aword;	// add word to word list
   in >> aword;
  } // end while not EOF
  wordcount = count;     // save number words in DOI
 } // else file open good
 in.close();
 out.close();

 // need to make corrections to handle x's, y's,
 // and z's. Beale used the number 811 to represent y
 // and 1005 for x. I have added 1304 to represent z
 words[811]  = 'y';
 words[1005] = 'x';
 words[1304] = 'z';

 // Fill in the lettercount array with the number of
 // times a word occurs beginning with each letter
 // lettercount[0] holds number of words in DOI that
 // begin with 'a' or 'A' and so on.
 for (i = 0; i < 26; lettercount[i++] = 0);

 for (i = 1; i <= wordcount; i++)
 {
  temp = words[i][0];
  if ((temp >= ASCIIa) && (temp <= ASCIIz)) temp -= TOCAPITAL;
  lettercount[temp - ASCIIA]++;
 } // end for

 // Seed the random-number generator with current time so that
 // the numbers will be different every time we run
 srand((unsigned)time(NULL));
} // end CTOR()

//-----------------------------------------------
// DTOR
// PreConditions : None
// PostConditions: None
//-----------------------------------------------
BCipher::~BCipher(void)
{

} // end DTOR()

//-----------------------------------------------
// encode()
// PreConditions:
// - letter_to_encode is a letter of the English
//   alphabet. It can be small or capital
// PostConditions:
// - encodedvalue will be returned. It is an
//   index value in the DOI where the first letter
//   of the encodedvalue word is the letter_to_encode
//-----------------------------------------------
int BCipher::encode (char letter_to_encode)
{
 int numoccurrences, encodedvalue, randval;

 // work with caps only for internal comparisons
 if ((letter_to_encode >= ASCIIa) &&
     (letter_to_encode <= ASCIIz)) letter_to_encode -= TOCAPITAL;
 //spot = letter_to_encode - ASCIIA;
 numoccurrences = lettercount[letter_to_encode - ASCIIA];

 // Prepare to select a random word in the DOI that
 // begins with the letter_to_encode
 if (numoccurrences > 1) randval = (rand() % numoccurrences) + 1;
 else randval = 1;

 // go get the index position of the nth occurrence
 // of the letter_to_encode
 encodedvalue = get_nth(randval, letter_to_encode);

 return(encodedvalue);
} // end encode()

//-----------------------------------------------
// decode()
// PreConditions :
// - cipher is an integer value that was created
//   using the modified beale cipher algorithm
// PostConditions:
// - the first letter of the word located at the
//   cipher position of the DOI will be returned
//-----------------------------------------------
char BCipher::decode (int cipher)
{
 return (words[cipher][0]);
} // end decode()

//-----------------------------------------------
// get_nth()
// PreConditions : None
// PostConditions:
// - the nth time a word beginning with letter_to_encode
//   in the DOI is found, its index position will be
//   recorded and returned as the cipher value
//-----------------------------------------------
int BCipher::get_nth(int stopvalue, char letter_to_encode)
{
 int  count = 0, spot = 1, ans = 9999;
 char temp;

 while (count < stopvalue)
 {
  temp = words[spot][0];
  if ((temp >= ASCIIa) && (temp <= ASCIIz)) temp -= TOCAPITAL;
  if (temp == letter_to_encode)
  {
   count++;     // found one more
   if (count == stopvalue) ans = spot;
  } // then temp is letter_to_encode
  spot++;
 } // while

 return(ans);
} // end get_nth()

//-----------------------------------------------
// showbealecipher()
// PreConditions : bc2.txt exists in correct location
// PostConditions:
// - The second beale cipher will be decoded and
//   displayed on the screen
//-----------------------------------------------
void BCipher::showbealecipher()
{
 ifstream bc;
 int acode, count;

 bc.open("bc2.txt");	// open beale 2 cipher text file
 if (bc.fail())
  cout << "\nProblems opening beale 2 cipher text file\n\n";
 else
 {
  // produce the deciphered text as screen output
  bc >> acode;	count = 0;
  while (!bc.eof())
  {
   cout << words[acode][0];  // next decoded letter
   count++;
   if (count == 60){ count = 0; cout << endl; }
   bc >> acode;
  } // end while
 } // else file open good
 bc.close();
} // end showbealecipher()
