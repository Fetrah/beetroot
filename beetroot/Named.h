#ifndef BEETROOT_NAMED_H
#define BEETROOT_NAMED_H

// Local
#include "INamed.h"

namespace beetroot {

  /** @brief Implementation of named objects.

    * Interface for classes which have names.
    * @author James Robinson <james.robinson@cern.ch>
    * @date May 2013
    */
  class Named : public INamed {

  public:
    /** Default constructor */
    Named( const std::string &name );

    /** Name accessor */
    virtual const std::string &name() const;
    /** Name setter */
    virtual void name( const std::string &name );
        
  private:
    /** Object name */
    std::string m_name;
  };

}

#endif // BEETROOT_NAMED_H
