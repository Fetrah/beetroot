#ifndef BEETROOT_PLOT_H
#define BEETROOT_PLOT_H

// Local
#include "beetroot/Axis.h"
#include "beetroot/Histogram1D.h"
// STL
// #include <string>
#include <utility>
#include <vector>
// BOOST
#include <boost/scoped_ptr.hpp>

class mglData;
class mglGraph;

namespace beetroot {

  class Figure;

  /** @brief Plot class for containing plottable areas

    * Plot which contains plottable areas
    * @author James Robinson <james.robinson@cern.ch>
    * @date May 2013
    */
  class Plot {

  friend class Figure;  

  public:
    /** Default constructor */
    Plot( const double &xlow = 0.0, const double &xhigh = 1.0, const double &ylow = 0.0, const double &yhigh = 1.0 );

    void add_function( const std::string &function );

    void add_data( const Histogram1D &hist );

    Axis& get_axis( const Axis::Dimension &axis );

  private:
    double m_xlow, m_xhigh, m_ylow, m_yhigh;
    std::string m_function;

    Axis m_x_axis, m_y_axis;

    typedef std::pair<mglData,mglData> mgl_dataset;
    std::vector< mgl_dataset /*mglData*/ > m_datasets;

    void draw( const boost::scoped_ptr<mglGraph> &m_baseFigure ) const;
  
  };

}

#endif // BEETROOT_PLOT_H