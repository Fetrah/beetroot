#ifndef BEETROOT_FILE_HANDLER_H
#define BEETROOT_FILE_HANDLER_H
// STL
#include <string>
#include <stdexcept>
#include <typeinfo>

/** Forward declaration of ROOT TFile */
class TFile;
class TObject;

namespace beetroot {

  /** @brief ROOT file handler.

    * File handler to safely open, close, read and write ROOT files.
    * @author James Robinson <james.robinson@cern.ch>
    * @date February 2013
    */
  class FileHandler {

  public:      
    /** Enum to delineate file opening options */
    enum OpenAs { CREATE, RECREATE, UPDATE, READ };
    
    /** Default constructor opens a file read-only */
    FileHandler( const std::string &name, const OpenAs &openType = READ );
    virtual ~FileHandler();
    
    template<typename T>
    /** Read an object from a ROOT file */
    T read( const std::string &objectName ) const {
      deregisterObjects(objectName);
      T *obj = dynamic_cast<T*>( getObject(objectName) );
      if( obj == NULL ) { throw std::runtime_error( (" No object named '"+objectName+"' of type "+typeid(obj).name()+" exists in file: "+this->name()) ); }
      return *obj;
    }

    template<typename T>
    /** Write an object to a ROOT file */
    const int write( const T &object, const std::string &objectName = "", const std::string &dirName = "", const bool overwrite = true ) {
      std::string objNameFinal( objectName=="" ? object.GetName() : objectName );
      this->cd( dirName );
      return object.Write( objNameFinal.c_str(), (overwrite?6:0) );
    }

    /** Make a directory inside a ROOT file */
    virtual void mkdir( const std::string &dirName ) const ;

    /** Change to another directory inside a ROOT file */
    virtual void cd( const std::string &path = "" ) const;

    /** Make a directory inside a ROOT file and change to it */
    virtual void mkcd( const std::string &dirName ) const;

    /** List the contents of a ROOT file */
    virtual void ls() const;

    /** Get the name of a ROOT file */
    virtual std::string name() const;

    
  private:
    /** Forbid copying */
    FileHandler( const FileHandler& );
    /** Forbid assignment */
    void operator=( const FileHandler& );

    /** Helper function to deregister any existing object with the same name (to avoid "Warning in <TFile::Append>" messages) */
    void deregisterObjects( const std::string &objectName ) const;

    /** Helper function to get an object from a file */
    TObject* getObject( const std::string &objectName ) const;

    /** ROOT TFile interface */
    TFile *m_file;
  };

}

#endif // BEETROOT_FILE_HANDLER_H
