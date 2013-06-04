#ifndef BEETROOT_DATASET_H
#define BEETROOT_DATASET_H

// BOOST
//#include <boost/scoped_ptr.hpp>
// MathGL
#include <mgl2/data.h>

//class mglData;

namespace beetroot {

  /** @brief Dataset class for containing data

    * Dataset which contains information about a single point
    * @author James Robinson <james.robinson@cern.ch>
    * @date May 2013
    */
  class Dataset {

  public:
    /** Default constructor */
    Dataset( mglData x, mglData y, mglData ex, mglData ey );

    /** Get x */
    const mglData &x() const;

    /** Get y */
    const mglData &y() const;

    /** Get ex */
    const mglData &ex() const;

    /** Get ey */
    const mglData &ey() const;

  private:
    mglData m_x, m_y, m_ex, m_ey;
  
  };

}

#endif // BEETROOT_DATASET_H