#ifndef BEETROOT_UUIDWRAPPER_H
#define BEETROOT_UUIDWRAPPER_H

// STL
#include <string>
// BOOST
#include <boost/uuid/uuid_generators.hpp>

namespace beetroot {

  /** @brief Static UUID generator.

    * UUID generation function using boost
    * @author James Robinson <james.robinson@cern.ch>
    * @date May 2013
    */
  class UUIDWrapper {

  public:
    static const std::string generate();

  private:
    static boost::uuids::random_generator m_uuidGenerator;

  };

}
#endif // BEETROOT_UUIDWRAPPER_H