#ifndef BEETROOT_HISTOGRAM1D_H
#define BEETROOT_HISTOGRAM1D_H

// Local
#include "beetroot/Named.h"
// STL
#include <string>
#include <vector>
// BOOST
#include <boost/scoped_ptr.hpp>

namespace YODA { class Histo1D; }
class TH1D;

namespace beetroot {

  /** @brief Histogram class with separation between data and presentation

    * Histogram class with separation between data and presentation
    * YODA is used to store the data and ROOT for the presentation
    * @author James Robinson <james.robinson@cern.ch>
    * @date May 2013
    */
  class Histogram1D : public Named {
    
  public:
    /** Default constructor */
    Histogram1D( const std::string &name, const std::vector<double> &xBins );
    //Histogram1D( const std::string &name, const int nBins, const double xLow, const double xHigh );
    /** Default copy constructor */
    Histogram1D( const Histogram1D &otherHistogram1D );
    /** Construct from a ROOT TH1D */
    Histogram1D( const TH1D &otherTH1D );
    /** Virtual destructor */
    virtual ~Histogram1D();

    //////////////////////////////////////////////////////////////////////////////////////////
    //  Methods
    //////////////////////////////////////////////////////////////////////////////////////////
    Histogram1D& operator=( const Histogram1D &otherHistogram1D );
    void printAll();

  private:
    //////////////////////////////////////////////////////////////////////////////////////////
    //  Member variables
    //////////////////////////////////////////////////////////////////////////////////////////
    boost::scoped_ptr<YODA::Histo1D> m_data;
    boost::scoped_ptr<TH1D> m_style;

  };

}

  /*class Histogram1D : public TH1D, public Drawable {

    public:
      //////////////////////////////////////////////////////////////////////////////////////////
      //  Constructors & destructors
      //////////////////////////////////////////////////////////////////////////////////////////
      Histogram1D( const std::string &name, const std::string &title, const std::vector<double> &xBins );
      Histogram1D( const std::string &name, const std::string &title, const int nBins, const double xLow, const double xHigh );
      Histogram1D( const Histogram1D &otherHistogram1D );
      Histogram1D( const TH1D &otherTH1D );
      //Histogram1D( const TH1F &otherTH1F );
      Histogram1D( const TProfile &otherTProfile );
      //Histogram1D( const Graph &otherGraph );
      virtual ~Histogram1D() {};

      //////////////////////////////////////////////////////////////////////////////////////////
      //  Methods
      //////////////////////////////////////////////////////////////////////////////////////////
      Histogram1D& operator=( const Histogram1D &otherHistogram1D );
      Histogram1D operator/( const Histogram1D &otherHistogram1D ) const;
      void normalize( double normfact);
      Histogram1D BinomialDivide( const Histogram1D &otherHistogram1D ) const;
      Graph BayesDivide( const Histogram1D &otherHistogram1D ) const;
      virtual double getBinContent( const int &bin ) const;
      virtual double getBinError( const int &bin ) const;
      virtual double getBinCentre( const int &bin ) const;
      virtual unsigned int getNEntries() const;
      virtual void draw( const DrawOptions &options, bool sameAxes = false );
      //virtual void drawNew( const DrawOptions &options, bool sameAxes = false, double minY = -12345, double maxY = -12345 );
      virtual TAxis* getAxis( const std::string &axis = "x" ) const;
      virtual double getAxisMin( const std::string &axis = "x" ) const;
      virtual double getAxisMax( const std::string &axis = "x" ) const;
      virtual void removeUnmatchedPoints( const Drawable &model );

    private:
      virtual void removeBadPoints();
  };*/

#endif // BEETROOT_HISTOGRAM1D_H
