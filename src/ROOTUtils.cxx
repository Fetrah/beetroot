// Local
#include "beetroot/ROOTUtils.h"
// ROOT
#include <TH1.h>

namespace beetroot {

  const std::vector<double> ROOTUtils::getXBins( const TH1 &hist ) {
    std::vector<double> output;
    for( int i = 1; i < hist.GetNbinsX() + 2; ++i ) {
      output.push_back( hist.GetBinLowEdge(i) );
    }
    return output;
  }

}