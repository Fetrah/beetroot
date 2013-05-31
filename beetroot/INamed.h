#ifndef BEETROOT_INAMED_H
#define BEETROOT_INAMED_H

// STL
#include <string>

namespace beetroot {

  /** @brief Interface for named objects.

    * Interface for classes which have names.
    * @author James Robinson <james.robinson@cern.ch>
    * @date May 2013
    */
  class INamed {

  public:
    /** Virtual destructor */
    virtual ~INamed() {};

    /** Name accessor */
    virtual const std::string &name() const = 0;
    /** Name setter */
    virtual void name( const std::string &name ) = 0;
  };

}

#endif // BEETROOT_INAMED_H
