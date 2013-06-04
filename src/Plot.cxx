// Local
#include "beetroot/Figure.h"
#include "beetroot/Plot.h"
// STL
#include <stdexcept>
// BOOST
#include <boost/foreach.hpp>
#include <boost/format.hpp>
// MathGL
#include <mgl2/data.h>
#include <mgl2/mgl.h>

#include <iostream>
namespace beetroot {

  //////////////////////////////////////////////////////////////////////////////////////////
  //  Histogram 1D
  //////////////////////////////////////////////////////////////////////////////////////////
  Plot::Plot( const double &xlow, const double &xhigh, const double &ylow, const double &yhigh )
    : m_xlow(xlow)
    , m_xhigh(xhigh)
    , m_ylow(ylow)
    , m_yhigh(yhigh)
    , m_function("")
    , m_x_axis()
    , m_y_axis()
    , m_datasets()
  {}

  void Plot::add_function( const std::string &function ) {
    //m_parentFigure->FPlot( function.c_str() );
    //m_parentFigure->Axis();
    //m_parentFigure->Label('y',"axis 1",0); 
    //m_parentFigure->Box();
    m_function = function;
    std::cout << "Setting function to " << m_function << " for " << this << std::endl;
    return;
  }

  void Plot::add_data( const Histogram1D &hist ) {
    mglData x( hist.bins().size() ), y( hist.bins().size() );
    unsigned int index(0);
    BOOST_FOREACH( const DataPoint &data_point, hist.data() ) {
      x.a[index] = data_point.x();
      y.a[index] = data_point.y();
      std::cout << "x,y :: " << x.a[index] << ", " << y.a[index] << std::endl;
      ++index;
    }
    m_datasets.push_back( std::make_pair(x,y) /*y*/ );
  }

  // void Plot::print() {
  //   std::cout << this << " properties: ( "<<m_xlow<<", "<<m_xhigh<<", "<<m_ylow<<", "<<m_yhigh<<", false )" << std::endl;
  // }

  //   m_figure->Axis();
  //   m_figure->Label('y',"axis 1",0); 
  //   m_figure->Box();

  Axis& Plot::get_axis( const Axis::Dimension &axis ) {
    if( axis == Axis::X ) { return m_x_axis; }
    return m_y_axis;
  }


  void Plot::draw( const boost::scoped_ptr<mglGraph> &m_baseFigure ) const {
    //std::cout << this << " InPlot( "<<m_xlow<<", "<<m_xhigh<<", "<<m_ylow<<", "<<m_yhigh<<", false )" << std::endl;
    m_baseFigure->InPlot( m_xlow, m_xhigh, m_ylow, m_yhigh, false );
    //std::cout << this << " FPlot( " << m_function.c_str() << ")" << std::endl;
    /** Plot axis labels */
    if( m_x_axis.get_label() != "" ) { m_baseFigure->Label('x', m_x_axis.get_label().c_str(), 0); }
    if( m_y_axis.get_label() != "" ) { m_baseFigure->Label('y', m_y_axis.get_label().c_str(), 0); }
    /** Set axis ranges */
    if( m_x_axis.get_min() != m_x_axis.get_max() ) { m_baseFigure->SetRange('x', m_x_axis.get_min(), m_x_axis.get_max()); }
    if( m_y_axis.get_min() != m_y_axis.get_max() ) { m_baseFigure->SetRange('y', m_y_axis.get_min(), m_y_axis.get_max()); }

    /** Plot a function if there is one */
    if( m_function != "" ) {
      m_baseFigure->FPlot( m_function.c_str() );
    }
    /** Plot datasets if there are any */
    BOOST_FOREACH( const mgl_dataset &dataset, m_datasets ) {
      m_baseFigure->Plot( dataset.first, dataset.second /*, "o"*/ );
    }
    m_baseFigure->Axis();
    m_baseFigure->Box();
    //std::cout << this << " There are " << m_baseFigure->GetNumFrame() << " frames" << std::endl;
    return;
  }

}
