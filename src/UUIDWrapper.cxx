// Local
#include "beetroot/UUIDWrapper.h"
// BOOST
#include <boost/uuid/uuid_io.hpp>

namespace beetroot {

  boost::uuids::random_generator UUIDWrapper::m_uuidGenerator;

  const std::string UUIDWrapper::generate() {
    boost::uuids::uuid u = m_uuidGenerator();
    return boost::uuids::to_string(u);
  }

}