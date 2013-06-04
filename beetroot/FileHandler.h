#ifndef BEETROOT_FILE_HANDLER_H
#define BEETROOT_FILE_HANDLER_H

// Local
#include "beetroot/Histogram1D.h"
#include "beetroot/ROOTFileHandler.h"

namespace beetroot {

  /** @brief File handler .

    * File handler to safely open, close, read and write ROOT files.
    * @author James Robinson <james.robinson@cern.ch>
    * @date February 2013
    */
  class FileHandler : public ROOTFileHandler {

  public:    
    /** Default constructor opens a file read-only */
    FileHandler( const std::string &name, const OpenAs &openType = READ );

    /** Virtual destructor */
    virtual ~FileHandler();
    
    Histogram1D read( const std::string &objectName ) const;
    
  private:
    /** Forbid copying */
    FileHandler( const FileHandler& );

    /** Forbid assignment */
    void operator=( const FileHandler& );

  };

}

#endif // BEETROOT_FILE_HANDLER_H
