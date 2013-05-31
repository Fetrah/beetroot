// Local
#include "beetroot/Histogram1D.h"
#include "beetroot/ROOTUtils.h"
#include "beetroot/UUIDWrapper.h"
// STL
#include <cmath>
#include <iostream>
// #include <stdexcept>
// BOOST
#include <boost/foreach.hpp>
// YODA
#include <YODA/Histo1D.h>
// ROOT
//#include <TAxis.h>
#include <TH1D.h>
//#include <TH1F.h>
//#include <TProfile.h>

namespace beetroot {

  //////////////////////////////////////////////////////////////////////////////////////////
  //  ROOT Helpers
  //////////////////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////////////////////////////////////////////
  //  Histogram 1D
  //////////////////////////////////////////////////////////////////////////////////////////
  Histogram1D::Histogram1D( const std::string &name, const std::vector<double> &xBins )
    : Named( name )
    , m_data( new YODA::Histo1D(xBins) )
    , m_style( new TH1D(UUIDWrapper::generate().c_str(), UUIDWrapper::generate().c_str(), (xBins.size()>0?xBins.size()-1:0), &xBins[0]) )
  {
    /** Make the style histogram memory-resident */
    m_style->SetDirectory(0);
  }

  /** @brief Construct a Histogram1D from a TH1D including underflow and overflow bins
    *
    * This can't be done correctly as YODA::Histo1D stores full fill information
    * Here we approximate by filling each bin n times with weight w
    * such that content = n * w and error = sqrt( n * w^2 )
    */
  Histogram1D::Histogram1D( const TH1D &otherTH1D )
    : Named( otherTH1D.GetName() )
    , m_data( new YODA::Histo1D( ROOTUtils::getXBins(otherTH1D) ) )
    , m_style( new TH1D(otherTH1D) )
  {
    /** Make the style histogram memory-resident */
    m_style->SetDirectory(0);

    /** Loop over the input histogram bins and extract fill parameters 
      * taking n = c^2 / e^2 and w = e^2 / c
      * Since we can't guarantee that n is integral, we take floor(n)
      * then add one more event with weight: w_final = ( c - floor(n)*w ) 
      * NB. negative bin content => negative weight
      */
    for( int iBin = 0; iBin <= otherTH1D.GetNbinsX()+1; ++iBin ) {
      const double x = otherTH1D.GetBinCenter(iBin);
      const double c = otherTH1D.GetBinContent(iBin);
      const double e = otherTH1D.GetBinError(iBin);
      unsigned int n = floor( (c*c) / (e*e) );
      double w = e*e / c;
      /** Catch cases where c or w are inf or nan */
      if( !std::isnormal(n) ) { n = 0; }
      if( !std::isnormal(w) ) { w = 0; }
      std::cout << "c = " << c << " +/- " << e << " => " << n << " lots of " << w << std::endl;
      for( unsigned int iFill = 0; iFill < n; ++iFill ) {
        m_data->fill( x, w );
      }
      if( c > (n * w) ) {
        m_data->fill( x, (c - n*w) );
      }
    }
  }

  Histogram1D::Histogram1D( const Histogram1D &otherHistogram1D )
    : Named( otherHistogram1D.name() )
    , m_data( otherHistogram1D.m_data.get() )
    , m_style( otherHistogram1D.m_style.get() )
  {}

  Histogram1D& Histogram1D::operator=( const Histogram1D &otherHistogram1D ) {
    m_data.reset( otherHistogram1D.m_data.get() );
    m_style.reset( otherHistogram1D.m_style.get() );
    return *this;
  }

  Histogram1D::~Histogram1D() {}


  void Histogram1D::printAll() {
    std::cout << "***** Style *****" << std::endl;
    m_style->Print("all");
    std::cout << "***** Data *****" << std::endl;
    if( m_data->underflow().numEntries() ) { std::cout << "Underflow:: x: " << m_data->underflow().mean() << ", y: " << m_data->underflow().sumW() << " +/- " << sqrt(m_data->underflow().sumW2()) << std::endl; }
    BOOST_FOREACH( const YODA::HistoBin1D &bin, m_data->bins() ) {
      std::cout << "x: " << bin.midpoint() << ", y: " << bin.area() << " +/- " << bin.areaErr() << std::endl;
    }
    if( m_data->overflow().numEntries() ) { std::cout << "Overflow:: x: " << m_data->overflow().mean() << ", y: " << m_data->overflow().sumW() << " +/- " << sqrt(m_data->overflow().sumW2()) << std::endl; }
    std::cout << "***** End *****" << std::endl;
  }




  // //////////////////////////////////////////////////////////////////////////////////////////
  // //  Histogram 1D
  // //////////////////////////////////////////////////////////////////////////////////////////
  // Histogram1D::Histogram1D( const std::string &name, const std::string &title, const std::vector<double> &xBins )
  //   : TH1D( name.c_str(), title.c_str(), (xBins.size()>0?xBins.size()-1:0), &xBins[0] ) { this->Sumw2(); }

  // Histogram1D::Histogram1D( const std::string &name, const std::string &title, const int nBins, const double xLow, const double xHigh )
  //   : TH1D( name.c_str(), title.c_str(), nBins, xLow, xHigh ) { this->Sumw2(); }

  // Histogram1D::Histogram1D( const Histogram1D &otherHistogram1D ) : TH1D( (TH1D&)otherHistogram1D ) { this->Sumw2(); } 

  // Histogram1D::Histogram1D( const TH1D &otherTH1D ) : TH1D( otherTH1D ) { this->Sumw2(); }

  // // Histogram1D::Histogram1D( const TH1F &otherTH1F ) :
  // //   TH1D( (std::string("TH1D_")+std::string(otherTH1F.GetName())).c_str(),
  // //         otherTH1F.GetTitle(),
  // //         otherTH1F.GetNbinsX(),
  // //         &getXBins( otherTH1F )[0] )
  // // {
  // //   for( int i = 0; i < fNcells; ++i ) {
  // //     this->SetBinContent(i, otherTH1F.GetBinContent(i) );
  // //     this->SetBinError(i, otherTH1F.GetBinError(i) );
  // //   }
  // //   this->Sumw2();
  // // }

  // /** Construct from a TProfile */
  // Histogram1D::Histogram1D( const TProfile &otherTProfile ) : TH1D( otherTProfile ) { this->Sumw2(); }

  // // Histogram1D::Histogram1D( const Graph &otherGraph ) : 
  // //   TH1D( (std::string("TH1D_")+std::string(otherGraph.GetName())).c_str(),
  // //         otherGraph.GetTitle(),
  // //         otherGraph.GetN(),
  // //         &getXBins( otherGraph )[0] )
  // // {
  // //   for( int i = 0; i < fNcells; ++i ) {
  // //     double x(0), y(0); otherGraph.GetPoint( i, x, y );
  // //     this->SetBinContent( i, y );
  // //     this->SetBinError( i, otherGraph.GetErrorY(i) );
  // //   }
  // //   this->Sumw2();
  // // }

  // Histogram1D& Histogram1D::operator=( const Histogram1D &otherHistogram1D ) {
  //   TH1D::operator= ( otherHistogram1D );
  //   this->Sumw2();
  //   return *this;
  // }

  // Histogram1D Histogram1D::operator/( const Histogram1D &otherHistogram1D ) const {
  //   Histogram1D output( *this );
  //   output.SetName( std::string( std::string(this->GetName())+"_"+std::string(otherHistogram1D.GetName()) ).c_str() );
  //   if( output.GetNbinsX() != otherHistogram1D.GetNbinsX() ) {
  //     std::cerr << this->name() << " has " << this->GetNbinsX() << " bins while "
  //               << otherHistogram1D.name() << " has " << otherHistogram1D.GetNbinsX()
  //               << " bins!. Attempting to divide histograms with non-equal bins! Check this!" << std::endl;
  //   }
  //   // The most common division we want to do ignores the errors from the denominator
  //   for( int i = 0; i < output.GetNbinsX()+1; ++i ) {
  //     int otherBin(i);
  //     if( output.GetNbinsX() != otherHistogram1D.GetNbinsX() ) {
  //       // Get appropriate other bin number if using non-equal bins
  //       otherBin = -1;
  //       for( unsigned int iOther = 0; iOther < otherHistogram1D.getNEntries() + 1; ++iOther ) {
  //         if( fabs( otherHistogram1D.getBinCentre(iOther) - this->getBinCentre(i) ) < 1e-10 ) { otherBin = iOther; }
  //       }
  //     }
  //     double otherValue( otherBin == -1 ? 0.0 : otherHistogram1D.GetBinContent(otherBin) );
  //     output.SetBinContent( i, (otherValue == 0.0 ? 0.0 : this->GetBinContent(i) / otherValue) );
  //     output.SetBinError( i, (otherValue == 0.0 ? 0.0 : this->GetBinError(i) / otherValue) );
  //   }
  //   return output;
  // }

  // Histogram1D Histogram1D::BinomialDivide( const Histogram1D &otherHistogram1D ) const {
  //   Histogram1D output( *this );
  //   Histogram1D otherHist( otherHistogram1D );
  //   output.Divide( this, &otherHist, 1, 1, "B" );
  //   return output;
  // }

  // Graph Histogram1D::BayesDivide( const Histogram1D &otherHistogram1D ) const {
  //   Graph output;
  //   output.Divide( this, &otherHistogram1D, "cl=0.683 b(1,1) mode" );
  //   return output;
  // }

  // double Histogram1D::getBinContent( const int &bin ) const {
  //   return this->GetBinContent(bin);
  // }

  // double Histogram1D::getBinError( const int &bin ) const {
  //   return this->GetBinError(bin);
  // }

  // double Histogram1D::getBinCentre( const int &bin ) const {
  //   return this->GetBinCenter(bin);
  // }

  // unsigned int Histogram1D::getNEntries() const {
  //   return this->GetNbinsX();
  // }

  // void Histogram1D::draw( const DrawOptions &option, bool sameAxes ) {
  //   this->removeBadPoints();
  //   std::string optionString;
  //   switch(option) {
  //   case FULL_BAND:
  //     optionString = "E2";
  //     break;
  //   case AXIS_ONLY:
  //     optionString = "axis";
  //     break;
  //   case HISTOGRAM:
  //     this->SetFillColor(kWhite);
  //     optionString = "hist";
  //     break;
  //   case FULL_HISTOGRAM:
  //     optionString = "ehist";
  //     break;
  //   case POINTS:
  //     optionString = "ep";
  //     break;
  //   case POINTS_NOXERRORS:
  //     optionString = "epX0";
  //     break;
  //   default:
  //     ;
  //   }
  //   if( sameAxes ) { optionString += "same"; }
  //   this->Draw(optionString.c_str());
  // }

  // TAxis* Histogram1D::getAxis( const std::string &axis ) const {
  //   if ( axis == "x" ) { return this->GetXaxis(); }
  //   else if ( axis == "y" ) { return this->GetYaxis(); }
  //   throw std::runtime_error("Plottable::getAxis: Axis " + axis + " is not available!");
  // }


  // double Histogram1D::getAxisMin( const std::string &axis ) const {
  //   // Check for bins
  //   if( this->GetNbinsX() < 1 ) {
  //     throw std::runtime_error("Plottable::getAxisMin: there are no entries!");
  //   }
  //   // Find minimum
  //   if( axis == "x" ) {
  //     double min(this->GetBinLowEdge(1));
  //     for( int i = 1; i < this->GetNbinsX(); ++i ) {
  //       double xLow( this->GetBinLowEdge(i) );
  //       if( xLow < min ) { min = xLow; }
  //     }
  //     return min;
  //   } else if ( axis == "y" ) {
  //     double min(this->getBinContent(1));
  //     for( int i = 1; i < this->GetNbinsX(); ++i ) {
  //       double yLow( this->getBinContent(i) - this->getBinError(i) );
  //       if( yLow < min ) { min = yLow; }
  //     }
  //     return min;
  //   }
  //   throw std::runtime_error("Plottable::getAxisMin: Axis " + axis + " is not available!");
  // }

  // double Histogram1D::getAxisMax( const std::string &axis ) const {
  //   // Check for bins
  //   if( this->GetNbinsX() < 1 ) {
  //     throw std::runtime_error("Plottable::getAxisMax: there are no entries!");
  //   }
  //   // Find maximum
  //   if( axis == "x" ) {
  //     double max(this->GetBinLowEdge(1));
  //     for( int i = 1; i < this->GetNbinsX(); ++i ) {
  //       double xHigh( this->GetBinLowEdge(i+1) );
  //       if( xHigh > max ) { max = xHigh; }
  //     }
  //     return max;
  //   } else if ( axis == "y" ) {
  //     double max(this->getBinContent(1));
  //     for( int i = 1; i < this->GetNbinsX(); ++i ) {
  //       double yHigh( this->getBinContent(i) + this->getBinError(i) );
  //       if( yHigh > max ) { max = yHigh; }
  //     }
  //     return max;
  //   }
  //   throw std::runtime_error("Plottable::getAxisMax: Axis " + axis + " is not available!");
  // }
  
  // void Histogram1D::normalize(double normfact) {
  //   this->Scale(normfact);
  // }

  // void Histogram1D::removeBadPoints() {
  //   // For some reason this resets the text size - bypass by storing here
  //   const double xLabelSize(this->getAxis("x")->GetLabelSize()), yLabelSize(this->getAxis("y")->GetLabelSize());
  //   const double xTitleSize(this->getAxis("x")->GetTitleSize()), yTitleSize(this->getAxis("y")->GetTitleSize());
  //   for( int iX = 0; iX < this->GetNbinsX() + 1; ++iX ) {
  //     if( this->pointIsBad(iX) ) {
  //       this->SetBinContent(iX, 0, 0);
  //     }
  //   }
  //   // Restore text size
  //   this->getAxis("x")->SetLabelSize(xLabelSize); this->getAxis("y")->SetLabelSize(yLabelSize);
  //   this->getAxis("x")->SetTitleSize(xTitleSize); this->getAxis("y")->SetTitleSize(yTitleSize);
  // }

  // void Histogram1D::removeUnmatchedPoints( const Drawable &model ) {
  //   for( unsigned int iX = 0; iX < this->getNEntries(); ++iX ) {
  //     int modelBin(-1);
  //     for( unsigned int iOther = 0; iOther < model.getNEntries() + 1; ++iOther ) {
  //       if( fabs( model.getBinCentre(iOther) - this->getBinCentre(iX) ) < 1e-10 ) { modelBin = iOther; }
  //     }
  //     if( modelBin == -1 || model.pointIsBad(modelBin) ) { this->SetBinContent(iX, 0, 0 ); this->SetBinError(iX, 0, 0); }
  //   }
  // }

}
