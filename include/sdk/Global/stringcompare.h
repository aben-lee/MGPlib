#ifndef STRINGCOMPARE_H_
#define STRINGCOMPARE_H_
#include <string>

namespace gplib
  {
    /** \addtogroup genfunc General functions from various areas */
    /* @{ */

    //!This code is taken from Effective STL, Item 35, page 153, case insensitive compare two characters and return whether c1 precedes c2,
    //! deriving from binary_function makes it adaptable, see Effective STL, Item 40, page 170
    class ciCharLess: public std::binary_function<char, char, bool>
      {
    public:
      bool inline operator()(char c1, char c2) const
        {
          return std::tolower(static_cast<unsigned char> (c1)) < std::tolower(
              static_cast<unsigned char> (c2));
        }
      };

    //! Compare s1 and s2, returns true if s1 precedes s2
    bool ciStringCompare(const std::string &s1, const std::string &s2)
      {
        return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(),
            s2.end(), ciCharLess());
      }

  /* @} */
  }
#endif /*STRINGCOMPARE_H_*/
