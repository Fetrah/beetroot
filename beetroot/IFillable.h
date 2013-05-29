#ifndef BEETROOT_IFILLABLE_H
#define BEETROOT_IFILLABLE_H

namespace beetroot {

  /** @brief Class capable of having data added to it.

    * Interface for classes which contain data.
    * @author James Robinson <james.robinson@cern.ch>
    * @date May 2013
    */
  class IFillable {

  public:
    /** Enum to delineate file opening options */
    enum OpenAs { CREATE, RECREATE, UPDATE, READ };
    
    /** Default constructor */
    IFillable();
    virtual ~IFillable();
        
  private:
    /** Forbid copying */
    IFillable( const IFillable& );
    /** Forbid assignment */
    void operator=( const IFillable& );

  };

}

#endif // BEETROOT_IFILLABLE_H
