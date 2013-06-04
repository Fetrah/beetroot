// Local
#include "beetroot/DataPoint.h"
#include <iostream>
namespace beetroot {

  /** Default constructor */
  DataPoint::DataPoint( const double &x, const double &y )
    : m_x(x)
    , m_y(y)
    , m_exlow(0)
    , m_exhigh(0)
    , m_eylow(0)
    , m_eyhigh(0)
  {}

  /** Default constructor with symmetric errors */
  DataPoint::DataPoint( const double &x, const double &ex, const double &y, const double &ey )
    : m_x(x)
    , m_y(y)
    , m_exlow(ex)
    , m_exhigh(ex)
    , m_eylow(ey)
    , m_eyhigh(ey)
  {}

  /** Default constructor with asymmetric errors */
  DataPoint::DataPoint( const double &x, const double &exlow, const double &exhigh, const double &y, const double &eylow, const double &eyhigh )
    : m_x(x)
    , m_y(y)
    , m_exlow(exlow)
    , m_exhigh(exhigh)
    , m_eylow(eylow)
    , m_eyhigh(eyhigh)
  {}

  /** Get x */
  double DataPoint::x() const { return m_x; }

  /** Get y */
  double DataPoint::y() const { return m_y; }

  /** Get ex */
  double DataPoint::ex() const { return 0.5*(m_exlow+m_exhigh); }

  /** Get ey */
  double DataPoint::ey() const { return 0.5*(m_eylow+m_eyhigh); }

  /** Get exlow */
  double DataPoint::exlow() const { return m_exlow; }

  /** Get exhigh */
  double DataPoint::exhigh() const { return m_exhigh; }

  /** Get eylow */
  double DataPoint::eylow() const { return m_eylow; }

  /** Get eyhigh */
  double DataPoint::eyhigh() const { return m_eyhigh; }

}
