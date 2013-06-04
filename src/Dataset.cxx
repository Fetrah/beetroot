// Local
#include "beetroot/Dataset.h"

namespace beetroot {

  /** Default constructor */
  Dataset::Dataset( mglData x, mglData y, mglData ex, mglData ey )
    : m_x(x)
    , m_y(y)
    , m_ex(ex)
    , m_ey(ey)
  {}

  /** Get x */
  const mglData &Dataset::x() const { return m_x; }

  /** Get y */
  const mglData &Dataset::y() const { return m_y; }

  /** Get ex */
  const mglData &Dataset::ex() const { return m_ex; }

  /** Get ey */
  const mglData &Dataset::ey() const { return m_ey; }

}
