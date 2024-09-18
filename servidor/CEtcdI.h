// -*- C++ -*-

// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_codegen.cpp:1567

#ifndef CETCDI_F6EEJK_H_
#define CETCDI_F6EEJK_H_

#include "CEtcdS.h"
#include <iostream>
#include <map>
#include <string>

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class  CEtcd_i
  : public virtual POA_CEtcd
{
private:
  std::map<std::string, std::string> table;

public:
  // Constructor
  CEtcd_i ();

  // Destructor
  virtual ~CEtcd_i ();

  virtual std::string id ();

  virtual ::CORBA::Boolean put (const std::string key, const std::string val);

  virtual std::string get (const std::string key);

  virtual void del (const std::string key);

  // Utilizamos a classe InvalidKey do CORBA
  // depois de testar a nossa custom

  /*
  class InvalidKey : public std::exception
  {
  public:
    virtual const char* what() const noexcept override
    {
      return "invalid key";
    }
  };
  */
};

#endif /* CETCDI_H_  */