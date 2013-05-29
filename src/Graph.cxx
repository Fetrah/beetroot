// Local
#include "beetroot/Graph.h"
#include "beetroot/Histogram1D.h"
// STL
#include <iostream>
#include <cmath>
#include <stdexcept>

namespace beetroot {

   //////////////////////////////////////////////////////////////////////////////////////////
  //  Graph
  //////////////////////////////////////////////////////////////////////////////////////////
  Graph::Graph() : TGraphAsymmErrors() {}

  Graph::Graph( const std::string &name, const std::string &title, const std::vector<double> &xPoints, const std::vector<double> &yPoints )
    : TGraphAsymmErrors( (xPoints.size() == yPoints.size() ? xPoints.size() : 0), &xPoints[0], &yPoints[0] ) {
    this->SetName( name.c_str() );
    this->SetTitle( title.c_str() );
  }

  Graph::Graph( const std::string &name, const std::string &title ) : TGraphAsymmErrors() {
    this->SetName( name.c_str() );
    this->SetTitle( title.c_str() );
  }

  Graph::Graph( const Graph &otherGraph ) : TGraphAsymmErrors( otherGraph ) {
    this->SetName( otherGraph.GetName() );
    this->SetTitle( otherGraph.GetTitle() );
  }

  Graph::Graph( const TGraphAsymmErrors &otherTGraphAsymmErrors ) : TGraphAsymmErrors( otherTGraphAsymmErrors ) {
    this->SetName( otherTGraphAsymmErrors.GetName() );
    this->SetTitle( otherTGraphAsymmErrors.GetTitle() );
  }

  Graph::Graph( const TGraphErrors &otherTGraphErrors ) :
    TGraphAsymmErrors( otherTGraphErrors.GetN(), otherTGraphErrors.GetX(), otherTGraphErrors.GetY(),
                       otherTGraphErrors.GetEXlow(), otherTGraphErrors.GetEXhigh(),
                       otherTGraphErrors.GetEYlow(), otherTGraphErrors.GetEYhigh() )
  {
    this->SetName( otherTGraphErrors.GetName() );
    this->SetTitle( otherTGraphErrors.GetTitle() );
  }

  Graph::Graph( const TH1 &otherTH1 ) : TGraphAsymmErrors( &otherTH1 ) {}

  Graph::Graph( const std::string &name, const std::string &title, const std::vector<double> xPoints, const std::vector<double> yPoints, const std::vector<double> ex, const std::vector<double> ey )
  :  TGraphAsymmErrors( (xPoints.size() == yPoints.size() ? xPoints.size() : 0), &xPoints[0], &yPoints[0], &ex[0], &ex[0], &ey[0], &ey[0] ) {
    this->SetName( name.c_str() );
    this->SetTitle( title.c_str() );
  }

  Graph::Graph( const std::string &name, const std::string &title, const std::vector<double> xPoints, const std::vector<double> yPoints, const std::vector<double> exLow, const std::vector<double> exHigh, const std::vector<double> eyLow, const std::vector<double> eyHigh )
  :  TGraphAsymmErrors( (xPoints.size() == yPoints.size() ? xPoints.size() : 0), &xPoints[0], &yPoints[0], &exLow[0], &exHigh[0], &eyLow[0], &eyHigh[0] ) {
    this->SetName( name.c_str() );
    this->SetTitle( title.c_str() );
  }

  Graph& Graph::operator=( const Graph &otherGraph ) {
    TGraphAsymmErrors::operator= ( otherGraph );
    return *this;
  }

  void Graph::draw( const DrawOptions &option, bool sameAxes ) {
    const double xTitleOffset( this->getAxis("x")->GetTitleOffset() );
    const double xTitleSize( this->getAxis("x")->GetTitleSize() );
    const double yTitleOffset( this->getAxis("y")->GetTitleOffset() );
    const double yTitleSize( this->getAxis("y")->GetTitleSize() );
    this->removeBadPoints();
    std::string optionString("");
    // Draw axes unless they exist
    if( !sameAxes ) { optionString = "a"; }
    if( option == FULL_BAND ) {
      // Full band requires "2"
      optionString += "2";
    } else if ( option != AXIS_ONLY ) {
      // Draw points unless FULL_BAND or AXIS_ONLY
      optionString += "p";
    }
    // Draw unless no options provided
    if( optionString != "" ) { this->Draw(optionString.c_str()); }
    // Reset sizes - no idea why these change
    this->getAxis("x")->SetTitleOffset(xTitleOffset);
    this->getAxis("x")->SetTitleSize(xTitleSize);
    this->getAxis("y")->SetTitleOffset(yTitleOffset);
    this->getAxis("y")->SetTitleSize(yTitleSize);
  }
  
  TAxis* Graph::getAxis( const std::string &axis ) const {
    if ( axis == "x" ) { return this->GetXaxis(); }
    else if ( axis == "y" ) { return this->GetYaxis(); }
    throw std::runtime_error("Plottable::getAxis: Axis " + axis + " is not available!");
  }

  double Graph::getAxisMin( const std::string &axis ) const {
    // Check for bins
    if( this->GetN() < 1 ) {
      throw std::runtime_error("Plottable::getAxisMin: there are no entries!");
    }
    // Find minimum
    if( axis == "x" ) {
      double min(this->getBinCentre(1));
      for( int i = 0; i <= this->GetN(); ++i ) {
        double xLow( this->getBinCentre(i) - this->GetErrorXlow(i) );
        if( xLow < min ) { min = xLow; }
      }
      return min;
    } else if ( axis == "y" ) {
      double min(this->getBinContent(1));
      for( int i = 0; i <= this->GetN(); ++i ) {
        double yLow( this->getBinContent(i) - this->getBinError(i) );
        if( yLow < min ) { min = yLow; }
      }
      return min;
    }
    throw std::runtime_error("Plottable::getAxisMin: Axis " + axis + " is not available!");
  }

  double Graph::getAxisMax( const std::string &axis ) const {
    // Check for bins
    if( this->GetN() < 1 ) {
      throw std::runtime_error("Plottable::getAxisMax: there are no entries!");
    }
    // Find maximum
    if( axis == "x" ) {
      double max(this->getBinCentre(1));
      for( int i = 0; i <= this->GetN(); ++i ) {
        double xHigh( this->getBinCentre(i) + this->GetErrorXhigh(i) );
        if( xHigh > max ) { max = xHigh; }
      }
      return max;
    } else if ( axis == "y" ) {
      double max(this->getBinContent(1));
      for( int i = 0; i <= this->GetN(); ++i ) {
        double yHigh( this->getBinContent(i) + this->getBinError(i) );
        if( yHigh > max ) { max = yHigh; }
      }
      return max;
    }
    throw std::runtime_error("Plottable::getAxisMax: Axis " + axis + " is not available!");
  }

  Graph Graph::operator/( const Graph &otherGraph ) const {
    std::vector<double> xPoints, yPoints, exLow, exHigh, eyLow, eyHigh;
    double *x_otherGraph = otherGraph.GetX(); double *exlow_otherGraph = otherGraph.GetEXlow(); double *exhigh_otherGraph = otherGraph.GetEXhigh(); double *y_otherGraph = otherGraph.GetY();
    double *x_this = this->GetX(); double *exlow_this = this->GetEXlow(); double *exhigh_this = this->GetEXhigh(); double *y_this = this->GetY(); double *eylow_this = this->GetEYlow(); double *eyhigh_this = this->GetEYhigh();

    // Iterate over all points in this graph
    for( int iThis = 0; iThis < this->GetN(); ++iThis ) {
      double xlow_this(x_this[iThis] - exlow_this[iThis]), xhigh_this(x_this[iThis] + exhigh_this[iThis]);
      // Look through all points in the other graph for a match
      for( int iOther = 0; iOther < otherGraph.GetN(); ++iOther ) {
        double xlow_otherGraph(x_otherGraph[iOther] - exlow_otherGraph[iOther]), xhigh_otherGraph(x_otherGraph[iOther] + exhigh_otherGraph[iOther]);
        // Found match
        if( AreSame(xlow_otherGraph, xlow_this) && AreSame(xhigh_otherGraph, xhigh_this) ) {
          double x( 0.5*(xlow_this + xhigh_this) );
          double scaledErrLow( eylow_this[iThis]/y_otherGraph[iOther] );
          double scaledErrHigh( eyhigh_this[iThis]/y_otherGraph[iOther] );
          xPoints.push_back( x );
          yPoints.push_back( y_this[iThis]/y_otherGraph[iOther] );
          exLow.push_back( x - xlow_this );
          exHigh.push_back( xhigh_this - x );
          eyLow.push_back( scaledErrLow );
          eyHigh.push_back( scaledErrHigh );
          break;
        }

      }
    }

    Graph ratioGraph( std::string(this->GetName()+std::string("_")+otherGraph.GetName()), "Ratio", xPoints, yPoints, exLow, exHigh, eyLow, eyHigh );
    return ratioGraph;
  }
  
  Graph Graph::BayesDivide( const Graph &otherGraph ) const {
    std::vector<double> xPoints, yPoints, exLow, exHigh, ey;
    double *x_otherGraph = otherGraph.GetX(); double *exlow_otherGraph = otherGraph.GetEXlow(); double *exhigh_otherGraph = otherGraph.GetEXhigh(); double *y_otherGraph = otherGraph.GetY(); double *ey_otherGraph = otherGraph.GetEYlow();
    double *x_this = this->GetX(); double *exlow_this = this->GetEXlow(); double *exhigh_this = this->GetEXhigh(); double *y_this = this->GetY(); double *ey_this = this->GetEYlow();

    // Iterate over all points in this graph
    for( int iThis = 0; iThis < this->GetN(); ++iThis ) {
      double xlow_this(x_this[iThis] - exlow_this[iThis]), xhigh_this(x_this[iThis] + exhigh_this[iThis]);
      // Look through all points in the other graph for a match
      for( int iOther = 0; iOther < otherGraph.GetN(); ++iOther ) {
        double xlow_otherGraph(x_otherGraph[iOther] - exlow_otherGraph[iOther]), xhigh_otherGraph(x_otherGraph[iOther] + exhigh_otherGraph[iOther]);
        // Found match
        if( AreSame(xlow_otherGraph, xlow_this) && AreSame(xhigh_otherGraph, xhigh_this) ) {
          double x( 0.5*(xlow_this + xhigh_this) );
          double err1( ey_this[iThis]/y_otherGraph[iOther] );
          double err2( ey_otherGraph[iOther]*y_this[iThis]/y_otherGraph[iOther]/y_otherGraph[iOther] );
          xPoints.push_back( x );
          yPoints.push_back( y_this[iThis]/y_otherGraph[iOther] );
          exLow.push_back( x - xlow_this );
          exHigh.push_back( xhigh_this - x );
          ey.push_back( sqrt(err1*err1+err2*err2) );
          break;
        }

      }
    }

    Graph ratioGraph( std::string(this->GetName()+std::string("_")+otherGraph.GetName()), "Ratio", xPoints, yPoints, exLow, exHigh, ey, ey );
    return ratioGraph;
  }

  Graph Graph::operator/( const TH1 &otherHist ) const {
    Graph otherGraph( otherHist );
    return ( *this / otherGraph );
  }
  
  double Graph::getBinContent( const int &bin ) const {
    double x(0), y(0);
    if( this->GetPoint(bin, x, y) == -1 ) { return 0; }
    return y;
  }

  double Graph::getBinError( const int &bin ) const {
    return std::max( this->GetErrorYhigh(bin), this->GetErrorYlow(bin) );
  }

  double Graph::getBinCentre( const int &bin ) const {
    double x(0), y(0);
    if( this->GetPoint(bin, x, y) == -1 ) { return 0; }
    return x;
  }

  unsigned int Graph::getNEntries() const {
    return this->GetN();
  }
  
  void Graph::removeBadPoints() {
    // For some reason this resets the text size - bypass by storing here
    const double xLabelSize(this->getAxis("x")->GetLabelSize()), yLabelSize(this->getAxis("y")->GetLabelSize());
    const double xTitleSize(this->getAxis("x")->GetTitleSize()), yTitleSize(this->getAxis("y")->GetTitleSize());
    for( unsigned int iX = 0; iX < this->getNEntries(); ++iX ) {
      if( this->pointIsBad(iX) ) { this->SetPoint(iX, 0, 0 ); }
    }
    // Restore text size
    this->getAxis("x")->SetLabelSize(xLabelSize); this->getAxis("y")->SetLabelSize(yLabelSize);
    this->getAxis("x")->SetTitleSize(xTitleSize); this->getAxis("y")->SetTitleSize(yTitleSize);
  }

  void Graph::removeUnmatchedPoints( const Drawable &model ) {  
    for( unsigned int iX = 0; iX < this->getNEntries(); ++iX ) {
      int modelBin(-1);
      for( unsigned int iOther = 0; iOther < model.getNEntries(); ++iOther ) {
        if( fabs( model.getBinCentre(iOther) - this->getBinCentre(iX) ) < 1e-10 ) { modelBin = iOther; }
      }
      if( modelBin == -1 || model.pointIsBad(modelBin) ) { this->SetPoint(iX, 0, 0 ); this->SetPointError(iX, 0, 0, 0, 0); }
    }
  }

  bool Graph::AreSame(const double a, const double b) const {
    return fabs(a - b) < 1e-10;
  }
}
