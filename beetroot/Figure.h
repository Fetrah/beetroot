#ifndef BEETROOT_FIGURE_H
#define BEETROOT_FIGURE_H

// Local
#include "beetroot/Named.h"
#include "beetroot/Plot.h"
#include "beetroot/UUIDWrapper.h"
// STL
// #include <string>
//#include <map>
#include <vector>
// BOOST
#include <boost/scoped_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

class mglGraph;

namespace beetroot {

  /** @brief Figure class for containing plottable areas

    * Figure which contains plottable areas
    * @author James Robinson <james.robinson@cern.ch>
    * @date May 2013
    */
  class Figure : public Named {

  public:
    /** Default constructor */
    Figure( const std::string &name = "canvas", const int &width = 600, const int &height = 600 );
    /** Virtual destructor */
    virtual ~Figure();

    /** Add a subplot */
    Plot* add_subplot( const double &xlow, const double &xhigh,
                       const double &ylow, const double &yhigh );

    /** Save canvas contents to file */
    void save( const std::string &outputName = "") const;

  private:
    /** Base canvas on which subplots are drawn */
    boost::scoped_ptr<mglGraph> m_figure;
    /** Collection of subplots */
    boost::ptr_vector<Plot> m_subplots;

  };

}

#endif // BEETROOT_FIGURE_H