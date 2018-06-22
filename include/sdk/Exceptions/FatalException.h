#ifndef CFATALEXCEPTION_H_
#define CFATALEXCEPTION_H_
#include <stdexcept>
#include <string>
namespace gplib
  {
    //! The basic exception class for all errors that arise in gplib
    /*! The FatalException class is thrown when there is a problem that cannot be fixed within the program
     * It is derived from runtime_error to make error message handling easier.
     */
    class FatalException: public std::runtime_error
      {
    public:
      //! The constructor takes the error description as an argument, just like std::runtime_error
      FatalException(const std::string whatString) :
        std::runtime_error(whatString)
        {
        }
      ;
      virtual ~FatalException() throw ()
        {
        }
      ;
      };
  }
#endif /*CFATALEXCEPTION_H_*/
