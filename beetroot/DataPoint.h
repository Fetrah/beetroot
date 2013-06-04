#ifndef BEETROOT_DATA_POINT_H
#define BEETROOT_DATA_POINT_H

// Local
#include "beetroot/DataPoint.h"

namespace beetroot {

  /** @brief DataPoint class for containing data

    * DataPoint which contains information about a single point
    * @author James Robinson <james.robinson@cern.ch>
    * @date May 2013
    */
  class DataPoint {

  public:
    /** Default constructor */
    DataPoint( const double &x, const double &y );

    /** Default constructor with symmetric errors */
    DataPoint( const double &x, const double &ex, const double &y, const double &ey );

    /** Default constructor with asymmetric errors */
    DataPoint( const double &x, const double &exlow, const double &exhigh, const double &y, const double &eylow, const double &eyhigh );

    /** Get x */
    const double &x() const;

    /** Get y */
    const double &y() const;

    /** Get ex */
    const double &ex() const;

    /** Get ey */
    const double &ey() const;

    /** Get exlow */
    const double &exlow() const;

    /** Get exhigh */
    const double &exhigh() const;

    /** Get eylow */
    const double &eylow() const;

    /** Get eyhigh */
    const double &eyhigh() const;

  private:
    double m_x, m_y, m_exlow, m_exhigh, m_eylow, m_eyhigh;
  
  };

}

#endif // BEETROOT_DATA_POINT_H