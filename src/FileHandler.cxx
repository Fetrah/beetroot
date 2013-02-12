// Local
#include "beetroot/FileHandler.h"
// STL
#include <iostream>
// BOOST
#include <boost/format.hpp>
// ROOT
#include <TFile.h>
#include <TObject.h>

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

  void FileHandler::ls() const {
    m_file->ls();
  }
 
  void FileHandler::deregisterObjects( const std::string &objectName ) const {
    m_file->GetList()->Remove( m_file->GetList()->FindObject( objectName.c_str() ) );
    gDirectory->GetList()->Remove( gDirectory->GetList()->FindObject( objectName.c_str() ) );
  }

  TObject* FileHandler::getObject( const std::string &objectName ) const {
    return m_file->Get( objectName.c_str() );
  }

  std::string FileHandler::name() const {
    return (boost::format("%s")%m_file->GetName()).str();
  }

}
