
#ifndef UTIL_H_
#define UTIL_H_
#include <string>
#include <fstream>
#include "FatalException.h"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#ifdef HAVEREADLINE
#include <readline/readline.h>
#endif

namespace gplib
  {
    /** \addtogroup genfunc General functions from various areas */
    /* @{ */

    //! Generate a sequence of integers, for use with generate and generate_n algorithms, taken from Josuttis, p. 296
    /*! The constructor takes the starting value and each call to operator() returns the current value and increases
     * it by 1.
     */
    class IntSequence
      {
    private:
      int value;
    public:
      IntSequence(int start) :
        value(start)
        {
        }
      int operator()()
        {
          return value++;
        }
      };

    //! Given a filename, return the file extension including the dot, i.e. for test.t it will return .t
    inline std::string GetFileExtension(const std::string &filename)
      {
        std::string ending;
        size_t dotpos = filename.find_last_of('.');
        if (dotpos != std::string::npos)
          ending = filename.substr(dotpos);
        return ending;
      }

    //! Display the prompt and return a filename read in from the command line with either readline or cin
    /*! The functions will display the string prompt thour cout and read in a filename. If
     * HAVEREADLINE is defined it will use the readline library for automatic completion. Otherwise
     * it will simply use cin. The read filename is trimmed of whitespace and returned.
     */
    std::string AskFilename(const std::string prompt)
    {
      std::string result;
#ifdef HAVEREADLINE
      char *inputline = readline(prompt.c_str());
      result = inputline;
      free(inputline);
#endif
#ifndef HAVEREADLINE
      std::cout << prompt;
      std::cin >> result;
#endif
      boost::trim(result);
      return result;
    }

    //! Given an open input filestream search for the string token in the file and return the line containing that token, throws if fails
    /*! This function performs a case-sensitive search for the content of the string token. If a line in the file contains
     * this string the function returns this line. If the token cannot be found it throws a FatalException.
     * @param filestream An open infile stream, will be pointing to the next line after finding the token
     * @param token The token to search for
     * @return The line in the file that contains the token
     */
    std::string FindToken(std::ifstream &filestream, const std::string &token)
    {
      //first we didn't find anything and we are not at the end of the file
      bool found = false;
      bool end = false;
      //holds the current line in the file
      std::string line;
      //while we didn't find the token and are not at the end of the file
      while (!found && !end)
        {
          //we read in the current line
          //if successful try to find the token, otherwise assume we reached
          //the end of the file (at least of what we can read)
          if (std::getline(filestream, line))
            {
              found = boost::algorithm::contains(line, token);
            }
          else
            {
              end = true;
            }
        }
      //if we found it we return the line, otherwise we throw an exception
      if (found)
        {
          return line;
        }
      else
        {
          throw FatalException("Token " + token + " not found !");
        }
    }

    //! Remove all file starting with Root from current directory
    void CleanFiles(const std::string &Root)
    {
      boost::filesystem::directory_iterator end_itr; // default construction yields past-the-end
      //go through all files in the current directory
      for (boost::filesystem::directory_iterator itr(
          boost::filesystem::current_path()); itr != end_itr; ++itr)
        {
          //get the name of the current file and see whether it starts
          //with the root given as a parameter
          const std::string currfile = itr->path().filename().string();
          if (boost::algorithm::starts_with(currfile, Root))
            {
              boost::filesystem::remove_all(currfile);
            }
        }
    }
/* @} */
}
#endif /*UTIL_H_*/
