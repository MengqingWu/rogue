/**
 *-----------------------------------------------------------------------------
 * Title      : Rogue EPICS Interface: Stream Slave Interface
 * ----------------------------------------------------------------------------
 * File       : Slave.cpp
 * Created    : 2018-11-18
 * ----------------------------------------------------------------------------
 * Description:
 * Stream slave to epics variables
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
#include <rogue/protocols/epics/Slave.h>
#include <rogue/interfaces/stream/Frame.h>
#include <rogue/GeneralError.h>
#include <rogue/ScopedGil.h>
#include <rogue/GilRelease.h>
#include <boost/make_shared.hpp>
#include <boost/make_shared.hpp>

namespace ris = rogue::interfaces::stream;
namespace rpe = rogue::protocols::epics;
namespace bp  = boost::python;

//! Setup class in python
void rpe::Slave::setup_python() {

   bp::class_<rpe::Slave, rpe::SlavePtr, boost::noncopyable >("Slave",bp::init<std::string, uint32_t, std::string>());

   bp::implicitly_convertible<rpe::SlavePtr, ris::SlavePtr>();
   bp::implicitly_convertible<rpe::SlavePtr, rpe::ValuePtr>();
}

//! Class creation
rpe::Slave::Slave (std::string epicsName, uint32_t max, std::string type) : Value(epicsName) {

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
   else throw rogue::GeneralError("Slave::Slave","Invalid Type String: " + typeStr_);
}

rpe::Slave::~Slave() { }

void rpe::Slave::valueGet() { }

void rpe::Slave::valueSet() { }

void rpe::Slave::acceptFrame ( ris::FramePtr frame ) {
   struct timespec t;
   uint32_t tSize;
   uint32_t size_;
   uint32_t pos;
   uint32_t i;

   tSize = frame->getPayload();

   // First check to see if frame is valid
   if ( (tSize % fSize_) != 0 ) {
      rpe::Value::log_->error("Invalid frame size (%i) from epics: %s\n",tSize,epicsName_.c_str());
      return;
   }

   // Compute element count
   size_ = tSize / fSize_;

   // Limit size
   if ( size_ > max_ ) size_ = max_;

   rogue::GilRelease noGil;
   boost::lock_guard<boost::mutex> lock(rpe::Value::mtx_);

   // Release old data
   pValue_->unreference();
   pValue_ = new gddAtomic (gddAppType_value, epicsType_, 1u, size_);
   pos = 0;

   // Set timestamp
   clock_gettime(CLOCK_REALTIME,&t);
   pValue_->setTimeStamp(&t);

   // Create vector of appropriate type
   if ( epicsType_ == aitEnumUint8 ) {
      aitUint8 * pF = new aitUint8[size_];
      for ( i = 0; i < size_; i++ ) {
         pos += frame->read(&(pF[i]), pos, fSize_);
         printf("pos %i = %i\n",i,pF[i]);
      }
      pValue_->putRef(pF, new rpe::Destructor<aitUint8 *>);
   }

   else if ( epicsType_ == aitEnumUint16 ) {
      aitUint16 * pF = new aitUint16[size_];
      for ( i = 0; i < size_; i++ ) pos += frame->read(&(pF[i]), pos, fSize_);
      pValue_->putRef(pF, new rpe::Destructor<aitUint16 *>);
   }

   else if ( epicsType_ == aitEnumUint32 ) {
      aitUint32 * pF = new aitUint32[size_];
      for ( i = 0; i < size_; i++ ) pos += frame->read(&(pF[i]), pos, fSize_);
      pValue_->putRef(pF, new rpe::Destructor<aitUint32 *>);
   }

   else if ( epicsType_ == aitEnumInt8 ) {
      aitInt8 * pF = new aitInt8[size_];
      for ( i = 0; i < size_; i++ ) pos += frame->read(&(pF[i]), pos, fSize_);
      pValue_->putRef(pF, new rpe::Destructor<aitInt8 *>);
   }

   else if ( epicsType_ == aitEnumInt16 ) {
      aitInt16 * pF = new aitInt16[size_];
      for ( i = 0; i < size_; i++ ) pos += frame->read(&(pF[i]), pos, fSize_);
      pValue_->putRef(pF, new rpe::Destructor<aitInt16 *>);
   }

   else if ( epicsType_ == aitEnumInt32 ) {
      aitInt32 * pF = new aitInt32[size_];
      for ( i = 0; i < size_; i++ ) pos += frame->read(&(pF[i]), pos, fSize_);
      pValue_->putRef(pF, new rpe::Destructor<aitInt32 *>);
   }

   else if ( epicsType_ == aitEnumFloat32 ) {
      aitFloat32 * pF = new aitFloat32[size_];
      for ( i = 0; i < size_; i++ ) pos += frame->read(&(pF[i]), pos, fSize_);
      pValue_->putRef(pF, new rpe::Destructor<aitFloat32 *>);
   }

   else if ( epicsType_ == aitEnumFloat64 ) {
      aitFloat64 * pF = new aitFloat64[size_];
      for ( i = 0; i < size_; i++ ) pos += frame->read(&(pF[i]), pos, fSize_);
      pValue_->putRef(pF, new rpe::Destructor<aitFloat64 *>);
   }
   updated();
}

#endif
