// replace my comments with your own
// except: you can use my comment about one-word lookahead

// you may modify the code that I have supplied if you wish

#include "ReadTweets.h"
#include <cctype>
#include <cstdlib>
#include <iostream>

string removePunct(string word)
{ // should return a copy of the word with all leading and trailing punctuation      
  // removed
  // punctuation elsewhere in the word should not be removed
  // note that a word could havce more than one leading/trailing punctuation symbols
  // you need to write this

    /*
    int lhs = 0, rhs = word.size() - 1;
    while (lhs <= rhs && !isalnum(word[lhs])) lhs++;
    while (lhs <= rhs && !isalnum(word[rhs])) rhs--;
    if (lhs > rhs) return "";
    else return word.substr(lhs, rhs - lhs + 1);
    */

    
    std::remove_copy_if(word.begin(), word.end(),
        std::back_inserter(word), //Store output  
        [](int c) { &std::ispunct; } //lambda is equivelant to std::ptr_fun<int, int>(&std::ispunct) but as it is depreciated, a lambda is necessary
    );

  return word;
}

ReadTweets::ReadTweets(const char *fname)
{   wordfile.open(fname);//open file
    if (!wordfile)
    {   cout << "Failed to open " << fname << endl;
        exit(1);
    }
    wordfile >> nextword;
    eoffound = false;
}

string ReadTweets::getNextWord()
{ // should return next word in file, converted to lower case
  // empty string should be returned if next word contains no letters
  
  // uses a one-word lookahead to avoid any problems relating to when if end-of-file
  // is detected due to absence/presence of newline at end of file

  // incomplete

  string word = nextword;
  wordfile >> nextword;

  if (wordfile.eof())
      eoffound = true;

  word = removePunct(word);

  // need to check that word contains a letter, and if not return an empty string;
  // also need to convert to lower case before returning

  if (nextword.empty())
      return "";

  for (auto i : word)
      tolower(word[i]);

  return word;
}

bool ReadTweets::isNextWord()
{ return !eoffound;
}

bool ReadTweets::getTweets()
{ // you must write this
    return 0;
}

bool ReadTweets::getTweetsToShow()
{ // you must write this
    return 0;
}

void ReadTweets::close()
{ // you must write this
}
