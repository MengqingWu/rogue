/**
 *-----------------------------------------------------------------------------
 * Title      : Python Classes
 * ----------------------------------------------------------------------------
 * File       : py_rogue.cpp
 * Author     : Ryan Herbst, rherbst@slac.stanford.edu
 * Created    : 2016-08-08
 * Last update: 2016-08-08
 * ----------------------------------------------------------------------------
 * Description:
 * Python class wrapper
 * TODO:
 *    Figure out how to map rogue namespaces into python properly
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

#include <interfaces/module.h>
#include <hardware/module.h>
#include <utilities/module.h>
#include <boost/python.hpp>

BOOST_PYTHON_MODULE(rogue)
{

   PyEval_InitThreads();


};

