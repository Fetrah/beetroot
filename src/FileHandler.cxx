// Local
#include "beetroot/FileHandler.h"
// STL
#include <iostream>
// ROOT
#include <TH1D.h>
#include <TH1F.h>

namespace beetroot {

  FileHandler::FileHandler( const std::string &name, const OpenAs &openType )
    : ROOTFileHandler::ROOTFileHandler( name, openType )
  {}

  FileHandler::~FileHandler() {}

  Histogram1D FileHandler::read( const std::string &objectName ) const {
    try {
      return this->ROOTFileHandler::read<TH1D>( objectName );
    } catch( const std::runtime_error &error ) {
      std::cout << "Runtime error in TH1D" << std::endl;
      try {
        return this->ROOTFileHandler::read<TH1F>( objectName );
      } catch( const std::runtime_error &error ) {
        std::cout << "Runtime error in TH1F" << std::endl;
      }
    }
    std::vector<double> v; v.push_back(0.0); v.push_back(1.0);
    Histogram1D output( "empty", v );
    return output;
  }
  
}
