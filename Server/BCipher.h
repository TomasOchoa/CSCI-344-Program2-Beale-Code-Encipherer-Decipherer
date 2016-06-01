// Modified Beale Cipher driver demo program
// JW Ryder - Spring 2012
//
// What you need to have all of this runnable
// - DOI.txt: Modified Declaration of Independence
// - bc2.txt: The Beale 2 cipher text
// Place these two files where your program will be.
// DOI will be read in when the CTOR is executed.
// bc2 will be used when the showbealecipher() runs.
// - BCipher.exe: The executable program.
// - numberedDOI.txt - This will be created when the
// program executes. It is a list of all words in the
// DOI along with each word's word number in the text.
// It is one based.

#define BCIPHERH

#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

#define TOCAPITAL 0x20
#define ASCIIA    0x41
#define ASCIIZ    0x5A
#define ASCIIa    0x61
#define ASCIIz    0x7A

class BCipher
{
 public:
  BCipher(void);
  ~BCipher(void);

  int  encode (char letter_to_encode);
  char decode (int cipher);
  int  get_nth(int stopvalue, char letter_to_encode);
  void showbealecipher();

 private:
  string words[1500];     // holds words of DOI
  int    wordcount;       // number of words in words[]
  int    lettercount[26];
};
