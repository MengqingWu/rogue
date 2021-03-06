/**
 *-----------------------------------------------------------------------------
 * Title         : Data file writer utility.
 * ----------------------------------------------------------------------------
 * File          : StreamWriter.h
 * Author        : Ryan Herbst <rherbst@slac.stanford.edu>
 * Created       : 09/28/2016
 * Last update   : 09/28/2016
 *-----------------------------------------------------------------------------
 * Description :
 *    Class to coordinate data file writing.
 *    This class supports multiple stream slaves, each with the ability to
 *    write to a common data file. The data file is a series of banks.
 *    Each bank has a channel and frame flags. The channel is per source and the
 *    lower 24 bits of the frame flags are used as the flags.
 *    The bank is preceeded by 2 - 32-bit headers to indicate bank information
 *    and length:
 *
 *       headerA:
 *          [31:0] = Length of data block in bytes
 *       headerB
 *          31:24  = Channel ID
 *          23:9   = Frame flags
 *
 *-----------------------------------------------------------------------------
 * This file is part of the rogue software platform. It is subject to 
 * the license terms in the LICENSE.txt file found in the top-level directory 
 * of this distribution and at: 
    * https://confluence.slac.stanford.edu/display/ppareg/LICENSE.html. 
 * No part of the rogue software platform, including this file, may be 
 * copied, modified, propagated, or distributed except according to the terms 
 * contained in the LICENSE.txt file.
 *-----------------------------------------------------------------------------
**/
#ifndef __ROGUE_UTILITIES_FILEIO_STREAM_WRITER_H__
#define __ROGUE_UTILITIES_FILEIO_STREAM_WRITER_H__
#include <boost/enable_shared_from_this.hpp>
#include <rogue/interfaces/stream/Frame.h>
#include <stdint.h>
#include <boost/thread.hpp>
#include <map>

namespace rogue {
   namespace utilities {
      namespace fileio {

         class StreamWriterChannel;

         //! Stream writer central class
         class StreamWriter : public boost::enable_shared_from_this<rogue::utilities::fileio::StreamWriter> {
            friend class StreamWriterChannel;

               //! File descriptor
               int32_t fd_;

               //! Base file name
               std::string baseName_;
               
               //! Current file index
               uint32_t fdIdx_;

               //! Size limit for auto close and re-open when limit is exceeded, zero to disable
               uint32_t sizeLimit_;

               //! Current file size in bytes
               uint32_t currSize_;

               //! Total file size in bytes
               uint32_t totSize_;

               //! Buffering size to cache file writes, zero if disabled
               uint32_t buffSize_;

               //! Write buffer
               uint8_t * buffer_;

               //! Write buffer count
               uint32_t currBuffer_;

               //! File access lock
               boost::mutex mtx_;

               //! Total number of frames in file
               uint32_t frameCount_;

               //! Internal method for file writing 
               void intWrite(void *data, uint32_t size);

               //! Check file size for next write
               void checkSize(uint32_t size);

               //! Flush file
               void flush();

               //! condition
               boost::condition_variable cond_;

               std::map<uint32_t,boost::shared_ptr<rogue::utilities::fileio::StreamWriterChannel>> channelMap_;

            protected:

               //! Write data to file. Called from StreamWriterChannel
               void writeFile ( uint8_t channel, boost::shared_ptr<rogue::interfaces::stream::Frame> frame);

            public:

               //! Class creation
               static boost::shared_ptr<rogue::utilities::fileio::StreamWriter> create ();

               //! Setup class in python
               static void setup_python();

               //! Creator
               StreamWriter();

               //! Deconstructor
               ~StreamWriter();

               //! Open a data file
               void open(std::string file);

               //! Close a data file
               void close();

               //! Set buffering size, 0 to disable
               void setBufferSize(uint32_t size);

               //! Set max file size, 0 for unlimited
               void setMaxSize(uint32_t size);

               //! Get a port
               boost::shared_ptr<rogue::utilities::fileio::StreamWriterChannel> getChannel(uint8_t channel);

               //! Get current file size
               uint32_t getSize();

               //! Get current frame count
               uint32_t getFrameCount();

               //! Block until a frame count is reached
               void waitFrameCount(uint32_t count);

         };

         // Convienence
         typedef boost::shared_ptr<rogue::utilities::fileio::StreamWriter> StreamWriterPtr;
      }
   }
}
#endif

