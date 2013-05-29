// Local
#include "beetroot/Drawable.h"
// STL
#include <cmath>
// ROOT
#include <TAxis.h>
#include <TAttLine.h>
#include <TAttMarker.h>
#include <TAttFill.h>
#include <TH1.h>
#include <TGraphAsymmErrors.h>

namespace beetroot {

  //////////////////////////////////////////////////////////////////////////////////////////
  //  AzimuthalDecorrelation helper functions
  //////////////////////////////////////////////////////////////////////////////////////////
  // const std::vector<double> toVector( const unsigned int nBins, const double xLow, const double xHigh ) {
  //   std::vector<double> output;
  //   double dX( (xHigh-xLow) / nBins );
  //   for( unsigned int i = 0; i < nBins + 1; ++i ) {
  //     output.push_back( xLow +i*dX );
  //   }
  //   return output;
  // }
  
  // const std::vector<double> getXBins( const TH1 &hist ) {
  //   std::vector<double> output;
  //   for( int i = 1; i < hist.GetNbinsX() + 2; ++i ) {
  //     output.push_back( hist.GetBinLowEdge(i) );
  //   }
  //   return output;
  // }

  // const std::vector<double> getXBins( const TGraph &graph ) {
  //   std::vector<double> output;
  //   for( int i = 0; i < graph.GetN(); ++i ) {
  //     double x(0), y(0);
  //     graph.GetPoint( i, x, y );
  //     output.push_back( x - graph.GetErrorXlow(i) );
  //   }
  //   return output;
  // }

  std::string Drawable::name() const {
    const TNamed* pTNamed = dynamic_cast<const TNamed*>( this );
    if( pTNamed ) {
      return std::string( pTNamed->GetName() );
    }
    return "";
  }

  void Drawable::setColour( const int colour ) {
    TAttLine* pTAttLine = dynamic_cast<TAttLine*>( this );
    if( pTAttLine ) {
      pTAttLine->SetLineColor(colour);
    }
    TAttFill* pTAttFill = dynamic_cast<TAttFill*>( this );
    if( pTAttFill ) {
      pTAttFill->SetFillColor(colour);
    }
    TAttMarker* pTAttMarker = dynamic_cast<TAttMarker*>( this );
    if( pTAttMarker ) {
      pTAttMarker->SetMarkerColor(colour);
    }
  }

  void Drawable::copyMarkerStyling( const Drawable &copyFrom ) {
    const TAttMarker* pTAttMarker = dynamic_cast<const TAttMarker*>( &copyFrom );
    TAttMarker* pThisTAttMarker = dynamic_cast<TAttMarker*>( this );
    if( pTAttMarker && pThisTAttMarker ) {
      pThisTAttMarker->SetMarkerSize( pTAttMarker->GetMarkerSize() );
      pThisTAttMarker->SetMarkerStyle( pTAttMarker->GetMarkerStyle() );
      pThisTAttMarker->SetMarkerColor( pTAttMarker->GetMarkerColor() );
    }
    const TAttLine* pTAttLine = dynamic_cast<const TAttLine*>( &copyFrom );
    TAttLine* pThisTAttLine = dynamic_cast<TAttLine*>( this );
    if( pTAttLine && pThisTAttLine ) {
      pThisTAttLine->SetLineColor( pTAttLine->GetLineColor() );
    }
  }
  
  void Drawable::addConstantFactor( const double &factor ) {
    TH1* pTH1 = dynamic_cast<TH1*>( this );
    if( pTH1 ) {
      for( int iBin = 1; iBin < pTH1->GetNbinsX() + 1; ++iBin ) {
        const double y( pTH1->GetBinContent(iBin) );
        pTH1->SetBinContent( iBin, y+factor );
      }
    }
    
    TGraph* pTGraph = dynamic_cast<TGraph*>( this );
    if( pTGraph ) {
      for( int iBin = 0; iBin < pTGraph->GetN(); ++iBin ) {
        double x(0.), y(0.);
        pTGraph->GetPoint( iBin, x, y );
        pTGraph->SetPoint( iBin, x, y+factor );
      }
    }
  }

  void Drawable::multConstantFactor( const double &factor ) {
    TH1* pTH1 = dynamic_cast<TH1*>( this );
    if( pTH1 ) {
      for( int iBin = 1; iBin < pTH1->GetNbinsX() + 1; ++iBin ) {
        const double y( pTH1->GetBinContent(iBin) );
        const double yerr( pTH1->GetBinError(iBin) );
        pTH1->SetBinContent( iBin, y*factor );
        pTH1->SetBinError( iBin, yerr*factor );
      }
    }
    
    TGraphAsymmErrors* pTGraph = dynamic_cast<TGraphAsymmErrors*>( this );
    if( pTGraph ) {
      for( int iBin = 0; iBin < pTGraph->GetN(); ++iBin ) {
        double x(0.), y(0.), eylow(pTGraph->GetErrorYlow(iBin)), eyhigh(pTGraph->GetErrorYhigh(iBin));
        pTGraph->GetPoint( iBin, x, y );
        pTGraph->SetPoint( iBin, x, y*factor );
        pTGraph->SetPointError( iBin, pTGraph->GetErrorXlow(iBin), pTGraph->GetErrorXhigh(iBin), eylow*factor, eyhigh*factor );
      }
    }
  }
 
  bool Drawable::pointIsBad( const unsigned int &point ) const {
    if( fabs(this->getBinError(point)) >= fabs(this->getBinContent(point)) ) { return true; }
    if( this->getBinError(point) == 0 ) { return true; }
    return false;
  }
 
  void Drawable::setRange(const double low, const double high, const std::string axis) const {
    if( axis == "x" ) {
      TH1* pTH1 = dynamic_cast<TH1*>( const_cast<Drawable*>(this) );
      if( pTH1 ) {
        this->getAxis("x")->SetRangeUser( low, high );
      }

      TGraph* pTGraph = dynamic_cast<TGraph*>( const_cast<Drawable*>(this) );
      if( pTGraph ) {
        this->getAxis("x")->SetLimits( low, high );
      }
    } else if( axis == "y" ) {
      this->getAxis("y")->SetRangeUser( low, high );
    }
  }
  
  void Drawable::setTitle( const std::string title, const std::string axis ) const {
    if( axis == "x" ) {
      TH1* pTH1 = dynamic_cast<TH1*>( const_cast<Drawable*>(this) );
      if( pTH1 ) {
        pTH1->SetXTitle( title.c_str() );
      }
      TGraph* pTGraph = dynamic_cast<TGraph*>( const_cast<Drawable*>(this) );
      if( pTGraph ) {
        pTGraph->GetHistogram()->SetXTitle( title.c_str() );
      }
    } else if ( axis == "y" ) {
      TH1* pTH1 = dynamic_cast<TH1*>( const_cast<Drawable*>(this) );
      if( pTH1 ) {
        pTH1->SetYTitle( title.c_str() );
      }
      TGraph* pTGraph = dynamic_cast<TGraph*>( const_cast<Drawable*>(this) );
      if( pTGraph ) {
        pTGraph->GetHistogram()->SetYTitle( title.c_str() );
      }
    }
  }
}
