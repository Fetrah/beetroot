// Local
#include "beetroot/Named.h"

namespace beetroot {

  /** Default constructor */
  Named::Named( const std::string &name )
    : INamed()
    , m_name(name) {}

  /** Name accessor */
  const std::string &Named::name() const { return m_name; }

  /** Name setter */
  void Named::name( const std::string &name ) { m_name = name; }

}
