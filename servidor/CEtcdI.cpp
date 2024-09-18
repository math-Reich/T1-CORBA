// -*- C++ -*-

// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_codegen.cpp:1621

#include "CEtcdI.h"
#include <iostream>
#include <map>
#include <string>

using namespace std;

// Implementation skeleton constructor
CEtcd_i::CEtcd_i ()
{
}

// Implementation skeleton destructor
CEtcd_i::~CEtcd_i ()
{
}

std::string CEtcd_i::id ()
{
  return string("CEtcd_Server");
}

::CORBA::Boolean CEtcd_i::put (
  const std::string key,
  const std::string val)
{
  bool tableKeyExists = table.find(key) != table.end();
	table[key] = val;

	return !tableKeyExists;
}

std::string CEtcd_i::get (
  const std::string key)
{
  	string getValue;
	if (table.find(key) != table.end())
	{
		getValue = table[key];
		return getValue;
	}

	throw InvalidKey();
}

void CEtcd_i::del (const std::string key)
{
  auto iterator = table.find(key);
  if (iterator  == table.end())
	{
		throw InvalidKey();
	}

	table.erase(iterator);
}