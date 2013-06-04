// Local
#include "beetroot/Axis.h"

namespace beetroot {

  Axis::Axis()
    : m_min(0.0)
    , m_max(0.0)
    , m_label("")
  {}


  void Axis::set_range( const double &min, const double &max ) {
    m_min = min;
    m_max = max;
  }

  const double &Axis::get_min() const {
    return m_min;
  }

  const double &Axis::get_max() const{
    return m_max;
  }

  void Axis::set_label( const std::string &label ) {
    m_label = label;
  }

  const std::string &Axis::get_label() const {
    return m_label;
  }

}
