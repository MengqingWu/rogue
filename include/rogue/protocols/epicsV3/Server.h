/**
 *-----------------------------------------------------------------------------
 * Title      : Rogue EPICS V3 Interface: Top Level Server
 * ----------------------------------------------------------------------------
 * File       : Server.h
 * Created    : 2018-02-12
 * ----------------------------------------------------------------------------
 * Description:
 * EPICS Server For Rogue System
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

#ifndef __ROGUE_PROTOCOLS_EPICSV3_SERVER_H__
#define __ROGUE_PROTOCOLS_EPICSV3_SERVER_H__

#include <boost/python.hpp>
#include <boost/thread.hpp>
#include <casdef.h>
#include <gdd.h>
#include <gddApps.h>
#include <gddAppFuncTable.h>
#include <map>

namespace rogue {
   namespace protocols {
      namespace epicsV3 {

         class Value;

         class Server : public caServer {

            private:

               std::map<std::string, boost::shared_ptr<rogue::protocols::epicsV3::Value>> values_;

               boost::thread * thread_;

               boost::mutex mtx_;

               void runThread();

            public:

               //! Setup class in python
               static void setup_python();

               //! Class creation
               Server ();

               ~Server();

               void start();

               void stop();

               void addValue(boost::shared_ptr<rogue::protocols::epicsV3::Value> value);

               pvExistReturn pvExistTest (const casCtx &ctx, const char *pvName);

               pvCreateReturn createPV(const casCtx &ctx, const char *pvName);

               pvAttachReturn pvAttach(const casCtx &ctx, const char *pvName);
         };

         // Convienence
         typedef boost::shared_ptr<rogue::protocols::epicsV3::Server> ServerPtr;

      }
   }
}

#endif

