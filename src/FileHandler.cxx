// Local
#include "beetroot/FileHandler.h"
// STL
#include <iostream>

namespace beetroot {

  FileHandler::FileHandler( const std::string &name, const OpenAs &openType )
    : m_file( TFile::Open( name.c_str(), (openType == UPDATE ? "UPDATE" :
                                          openType == RECREATE ? "RECREATE" :
                                          openType == CREATE ? "CREATE" : "READ") ) ) {
    if ( !m_file || !m_file->IsOpen() ) {
      throw std::runtime_error(("Could not open file: "+name));
    }
  }

  FileHandler::~FileHandler() {
    m_file->Close();
    if( m_file->IsOpen() ) {
      throw std::runtime_error( ("Could not close file: "+std::string(m_file->GetName())) );
    }
  }
  
  void FileHandler::mkdir( const std::string &dirName ) const {
    m_file->mkdir( dirName.c_str() );
  }
  
  void FileHandler::cd( const std::string &path ) const {
    m_file->cd( path.c_str() );
  }

  void FileHandler::mkcd( const std::string &dirName ) const {
    this->mkdir( dirName );
    this->cd( dirName );
  }

}
