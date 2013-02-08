#ifndef BEETROOT_FILE_HANDLER_H
#define BEETROOT_FILE_HANDLER_H
// STL
#include <string>
#include <stdexcept>
#include <typeinfo>
// ROOT
#include <TFile.h>

namespace beetroot {

  //////////////////////////////////////////////////////////////////////////////////////////
  //  ROOT File Handler
  //////////////////////////////////////////////////////////////////////////////////////////
  class FileHandler {

    public:
      //////////////////////////////////////////////////////////////////////////////////////////
      //  Typedefs and enums
      //////////////////////////////////////////////////////////////////////////////////////////
      enum OpenAs { CREATE, RECREATE, UPDATE, READ };

      //////////////////////////////////////////////////////////////////////////////////////////
      //  Constructors & destructors
      //////////////////////////////////////////////////////////////////////////////////////////
      FileHandler( const std::string &name, const OpenAs &openType = READ );
      virtual ~FileHandler();
      
      //////////////////////////////////////////////////////////////////////////////////////////
      //  Methods
      //////////////////////////////////////////////////////////////////////////////////////////
      template<typename T>
      T read( const std::string &objectName ) const {
        // Deregister any existing object with the same name (to avoid "Warning in <TFile::Append>" messages)
        m_file->GetList()->Remove( m_file->GetList()->FindObject( objectName.c_str() ) );
        gDirectory->GetList()->Remove( gDirectory->GetList()->FindObject( objectName.c_str() ) );
        // Get object from file
        T *obj;
        m_file->GetObject( objectName.c_str(), obj );
        if( !obj ) {
          throw std::runtime_error( ("No object named '"+objectName+"' of type "+typeid(obj).name()+" exists in file: "+m_file->GetName()) );
        }
        return *obj;
      }
      
      template<typename T>
      const int write( const T &object, const std::string &objectName = "", const std::string &dirName = "", const bool overwrite = true ) const {
        std::string objNameFinal( objectName=="" ? object.GetName() : objectName );
        this->cd( dirName );
        if( overwrite ) {
          m_file->Delete( objNameFinal.c_str() );
          m_file->Delete( (objNameFinal+";*").c_str() );
        }
        return object.Write( objNameFinal.c_str() );
      }
      
      virtual void mkdir( const std::string &dirName ) const ;
      virtual void cd( const std::string &path = "" ) const;
      virtual void mkcd( const std::string &dirName ) const;
      virtual void ls() const { m_file->ls(); }

    private:
      //////////////////////////////////////////////////////////////////////////////////////////
      //  Forbid copy and assignment
      //////////////////////////////////////////////////////////////////////////////////////////
      FileHandler( const FileHandler& );
      void operator=( const FileHandler& );
      
   public:
      //////////////////////////////////////////////////////////////////////////////////////////
      //  Member variables
      //////////////////////////////////////////////////////////////////////////////////////////
      TFile *m_file;
  };
}
#endif // BEETROOT_FILE_HANDLER_H
