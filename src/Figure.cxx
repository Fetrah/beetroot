// Local
#include "beetroot/Figure.h"
// STL
#include <stdexcept>
// BOOST
#include <boost/foreach.hpp>
#include <boost/format.hpp>
// MathGL
#include <mgl2/mgl.h>

#include <iostream>
namespace beetroot {

  //////////////////////////////////////////////////////////////////////////////////////////
  //  Histogram 1D
  //////////////////////////////////////////////////////////////////////////////////////////
  Figure::Figure( const std::string &name, const int &width, const int &height )
    : Named( name )
    , m_figure( new mglGraph( 0, width, height ) )
    , m_subplots()
        //, m_subplots_ptrVec()
  {
    /** Set figure to use full plot size by default */
    m_figure->SetPlotFactor(1.0);
    /** Reserve space for 100 subplots */
    //m_subplots_ptrVec.reserve(100);
  }

  Figure::~Figure() {}

  Plot* Figure::add_subplot( const double &xlow, const double &xhigh,
                             const double &ylow, const double &yhigh )
  {
    m_subplots.push_back( new Plot(xlow, xhigh, ylow, yhigh) );
    std::cout << "There are now " << m_subplots.size() << " subplots. This one is at " << &m_subplots.back() << std::endl; //<< " : "  << &m_subplots_ptrVec[m_subplots_ptrVec.size()-1] << std::endl;
    return &m_subplots.back();
  }

  // void Figure::switch_to_subplot( int i ) {
  //   m_figure->ShowFrame(i);
  // }


  // void Figure::draw( const std::string &function ) {
  //   m_figure->FPlot( function.c_str() );
  //   return;
  // }


  void Figure::save( const std::string &outputName ) const {
    
    BOOST_FOREACH( const Plot &subplot, m_subplots ) {
      subplot.draw( m_figure );
    }

    const std::string savePath( outputName == "" ? name() : outputName );
    if( savePath == "" ) { throw std::runtime_error( "No output path specified! Refusing to save!" ); }

    //m_figure->FPlot("sin(pi*x)");
    //m_figure->Box();
    //m_figure->WriteFrame( (boost::format("%s.pdf") % savePath).str().c_str() );
    m_figure->WriteEPS( (boost::format("%s.eps") % savePath).str().c_str() );
    m_figure->WritePNG( (boost::format("%s.png") % savePath).str().c_str() );
    return;
  }

}
