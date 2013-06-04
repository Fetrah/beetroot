#ifndef BEETROOT_AXIS_H
#define BEETROOT_AXIS_H

// STL
#include <string>

namespace beetroot {

  /** @brief Axis class for containing axis details

    * Class which contains axis details for a given Plot
    * @author James Robinson <james.robinson@cern.ch>
    * @date May 2013
    */
  class Axis {

  public:
    /** Enum to delineate axis types */
    enum Dimension { X, Y };

    /** Default constructor */
    Axis();

    void set_range( const double &min, const double &max );
    const double &get_min() const;
    const double &get_max() const;

    void set_label( const std::string &label );
    const std::string &get_label() const;

  private:
    double m_min, m_max;
    std::string m_label;

  };

}

#endif // BEETROOT_AXIS_H