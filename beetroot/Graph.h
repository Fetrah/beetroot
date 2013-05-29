#ifndef BEETROOT_GRAPH_H
#define BEETROOT_GRAPH_H
// Local
#include "beetroot/Drawable.h"
// STL
#include <string>
#include <vector>
// ROOT
#include <TH1D.h>
#include <TAxis.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>

namespace beetroot {

  class Graph;

  //////////////////////////////////////////////////////////////////////////////////////////
  //  1D histogram
  //////////////////////////////////////////////////////////////////////////////////////////
  class Graph : public TGraphAsymmErrors, public Drawable {

    public:
      //////////////////////////////////////////////////////////////////////////////////////////
      //  Constructors & destructors
      //////////////////////////////////////////////////////////////////////////////////////////
      Graph();
      Graph( const std::string &name, const std::string &title, const std::vector<double> &xPoints, const std::vector<double> &yPoints );
      Graph( const std::string &name, const std::string &title );
      Graph( const Graph &otherGraph );
      Graph( const TGraphAsymmErrors &otherTGraphAsymmErrors );
      Graph( const TGraphErrors &otherTGraphErrors );
      Graph( const TH1 &otherTH1 );
      Graph( const std::string &name, const std::string &title, const std::vector<double> xPoints, const std::vector<double> yPoints, const std::vector<double> ex, const std::vector<double> ey );
      Graph( const std::string &name, const std::string &title, const std::vector<double> xPoints, const std::vector<double> yPoints, const std::vector<double> exLow, const std::vector<double> exHigh, const std::vector<double> eyLow, const std::vector<double> eyHigh );
      virtual ~Graph() {};

      //////////////////////////////////////////////////////////////////////////////////////////
      //  Methods
      //////////////////////////////////////////////////////////////////////////////////////////
      Graph& operator=( const Graph &otherGraph );
      Graph operator/( const Graph &otherGraph ) const;
      Graph operator/( const TH1 &otherHist ) const;
      Graph BayesDivide( const Graph &otherGraph ) const;
      //virtual void drawNew( const DrawOptions &options, bool sameAxes = false, double minY = -12345, double maxY = -12345 );
      virtual void draw( const DrawOptions &options, bool sameAxes = false );
      virtual TAxis* getAxis( const std::string &axis = "x" ) const;
      virtual double getAxisMin( const std::string &axis = "x" ) const;
      virtual double getAxisMax( const std::string &axis = "x" ) const;
      virtual double getBinContent( const int &bin ) const;
      virtual double getBinError( const int &bin ) const;
      virtual double getBinCentre( const int &bin ) const;
      virtual unsigned int getNEntries() const;
      virtual void removeUnmatchedPoints( const Drawable &model );

    private:
      virtual void removeBadPoints();
      bool AreSame(const double a, const double b) const;
  };
}
#endif // BEETROOT_GRAPH_H
