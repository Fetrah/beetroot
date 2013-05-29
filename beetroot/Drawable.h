#ifndef BEETROOT_DRAWABLE_H
#define BEETROOT_DRAWABLE_H

// STL
#include <string>

class TAxis;

namespace beetroot {

  //const std::vector<double> toVector( const unsigned int nBins, const double xLow, const double xHigh );
  //const std::vector<double> getXBins( const TH1 &hist );
  //const std::vector<double> getXBins( const TGraph &graph );
  

  /** @brief Super-class from which drawable classes inherit.

    * Super-class to define all drawing methods centrally.
    * @author James Robinson <james.robinson@cern.ch>
    * @date February 2013
    */
  class Drawable {
  
  public:
    /** Enum to delineate file opening options */
    enum DrawOptions { AXIS_ONLY, HISTOGRAM, FULL_HISTOGRAM, FULL_BAND, POINTS, POINTS_NOXERRORS };

    /** Default constructor opens a file read-only */
    Drawable() {}

    /** Default destructor */
    virtual ~Drawable() {};

    /** Get the name of the object */
    virtual std::string name() const;

    /** Scale by adding a constant factor to each point */
    virtual void addConstantFactor( const double &factor );

    /** Scale by multiplying each point by a constant factor */
    virtual void multConstantFactor( const double &factor );

    virtual void copyMarkerStyling( const Drawable &copyFrom );
    virtual void draw( const DrawOptions &options, bool sameAxes = false ) = 0;
    virtual TAxis* getAxis( const std::string &axis = "x" ) const = 0;
    virtual double getBinError( const int &bin ) const = 0;
    virtual double getBinContent( const int &bin ) const = 0;
    virtual double getBinCentre( const int &bin ) const = 0;
    virtual unsigned int getNEntries() const = 0;
    virtual double getAxisMin( const std::string &axis = "x" ) const = 0;
    virtual double getAxisMax( const std::string &axis = "x" ) const = 0;
    virtual bool pointIsBad( const unsigned int &point ) const;
    virtual void removeUnmatchedPoints( const Drawable &model ) = 0;
    virtual void setColour( const int colour = 0 );
    virtual void setRange( const double low, const double high, const std::string axis = "x" ) const;
    virtual void setTitle( const std::string title, const std::string axis = "x" ) const;

  // private:
  //   virtual void removeBadPoints() = 0;
  };
}
#endif // BEETROOT_DRAWABLE_H
