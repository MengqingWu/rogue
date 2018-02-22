/**
 *-----------------------------------------------------------------------------
 * Title      : Rogue EPICS Interface: Master Stream Interface
 * ----------------------------------------------------------------------------
 * File       : Variable.cpp
 * Created    : 2018-11-18
 * ----------------------------------------------------------------------------
 * Description:
 * Rogue stream master interface for EPICs variables
 * ----------------------------------------------------------------------------
 * This file is part of the rogue software platform. It is subject to 
 * the license terms in the LICENSE.txt file found in the top-level directory 
 * of this distribution and at: 
 *    https://confluence.slac.stanford.edu/display/ppareg/LICENSE.html. 
 * No part of the rogue software platform, including this file, may be 
 * copied, modified, propagated, or distributed except according to the terms 
 * contained in the LICENSE.txt file.
 * ----------------------------------------------------------------------------
**/

#ifdef DO_EPICS

#include <boost/python.hpp>
#include <rogue/protocols/epics/Master.h>
#include <rogue/GeneralError.h>
#include <rogue/ScopedGil.h>
#include <rogue/GilRelease.h>
#include <boost/make_shared.hpp>
#include <boost/make_shared.hpp>

namespace ris = rogue::interfaces::stream;
namespace rpe = rogue::protocols::epics;
namespace bp  = boost::python;

//! Setup class in python
void rpe::Master::setup_python() {

   bp::class_<rpe::Master, rpe::MasterPtr, boost::noncopyable >("Master",bp::init<std::string, uint32_t, std::string>());

   bp::implicitly_convertible<rpe::MasterPtr, ris::MasterPtr>();
   bp::implicitly_convertible<rpe::MasterPtr, rpe::ValuePtr>();
}

//! Class creation
rpe::Master::Master (std::string epicsName, uint32_t max, std::string type) : Value(epicsName) {

   // Init gdd record
   this->initGdd(type, false, 1);
   max_ = max;

   // Determine size in bytes & init data
   if ( epicsType_ == aitEnumUint8 ) {
      aitUint8 * pF = new aitUint8[1];
      pF[0] = 0;
      pValue_->putRef(pF, new rpe::Destructor<aitUint8 *>);
   }

   else if ( epicsType_ == aitEnumUint16 ) {
      aitUint16 * pF = new aitUint16[1];
      pF[0] = 0;
      pValue_->putRef(pF, new rpe::Destructor<aitUint16 *>);
   }

   else if ( epicsType_ == aitEnumUint32 ) {
      aitUint32 * pF = new aitUint32[1];
      pF[0] = 0;
      pValue_->putRef(pF, new rpe::Destructor<aitUint32 *>);
   }

   else if ( epicsType_ == aitEnumInt8 ) {
      aitInt8 * pF = new aitInt8[1];
      pF[0] = 0;
      pValue_->putRef(pF, new rpe::Destructor<aitInt8 *>);
   }

   else if ( epicsType_ == aitEnumInt16 ) {
      aitInt16 * pF = new aitInt16[1];
      pF[0] = 0;
      pValue_->putRef(pF, new rpe::Destructor<aitInt16 *>);
   }

   else if ( epicsType_ == aitEnumInt32 ) {
      aitInt32 * pF = new aitInt32[1];
      pF[0] = 0;
      pValue_->putRef(pF, new rpe::Destructor<aitInt32 *>);
   }

   else if ( epicsType_ == aitEnumFloat32 ) {
      aitFloat32 * pF = new aitFloat32[1];
      pF[0] = 0.0;
      pValue_->putRef(pF, new rpe::Destructor<aitFloat32 *>);
   }

   else if ( epicsType_ == aitEnumFloat64 ) {
      aitFloat64 * pF = new aitFloat64[1];
      pF[0] = 0.0;
      pValue_->putRef(pF, new rpe::Destructor<aitFloat64 *>);
   }
   else throw rogue::GeneralError("Master::Master","Invalid Type String: " + typeStr_);
}

rpe::Master::~Master() { }

void rpe::Master::valueGet() { }

void rpe::Master::valueSet() {

   // Not yet supported
   printf("Set called\n");

}

#endif
