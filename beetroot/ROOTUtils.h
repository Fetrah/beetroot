#ifndef BEETROOT_ROOTUTILS_H
#define BEETROOT_ROOTUTILS_H

// STL
#include <vector>

class TH1;

namespace beetroot {

  /** @brief ROOT utility provider.

    * Provide missing ROOT utilities
    * @author James Robinson <james.robinson@cern.ch>
    * @date May 2013
    */
  class ROOTUtils {

  public:
    static const std::vector<double> getXBins( const TH1 &hist );
            
  };

}
#endif // BEETROOT_ROOTUTILS_H