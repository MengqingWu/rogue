# rogue
SLAC Python Based Hardware Abstraction &amp; Data Acquisition System

Email List For Announcements:
https://listserv.slac.stanford.edu/cgi-bin/wa?A0=AIR-ROGUE-USERS

JIRA:
https://jira.slac.stanford.edu/plugins/servlet/project-config/ESROGUE

Introduction presentation: 
https://docs.google.com/presentation/d/1m2nqGzCZXsQV8ul4d0Gk7xmwn-OLW1iucTLm7LLp9eg/edit?usp=sharing
some concepts (Blocks and Variables) are a little out of data as we have made changes.

For example scripts and sub-class source code examples see:

https://github.com/slaclab/rogue-example

## Building Rogue
Before building and using rogue you will need to either install the required support packages 
and modules or setup a conda environment. See below for instructions.

The rogue compile uses cmake. To download and build rogue:

````
$ git clone https://github.com/slaclab/rogue.git
$ cd rogue
$ git submodule init
$ git submodule update
$ mkdir build
$ cd build
$ cmake ..  (or cmake3)
$ make
````

to update from git and rebuild:
````
$ git pull
$ git submodule update
$ cd build
$ make rebuild_cache
$ make clean
$ make 
````

Two libraries are output from the compute. lib/librogue-core.so is a c++ 
core library for the various rogue classes and function. python/rogue.so
is a shared object library for importing into python.

The lib subdirecotry of rogue should be included in your LD_LIBRARY_PATH and
the python subdirectory should be include in your PYTHONPATH. A pair of setup
scripts for both bash and c-shell are include in the rogue distribution:

````
$ source setup_rogue.sh
````
or for csh:
````
$ source setup_rogue.csh
````

These scripts also set the ROGUE_DIR environment variable which is usefull when 
setting up the example projects or some SLAC projects.

You may want to create a custom setup script to combine the rogue setup with 
other environmental setups for your project.

## Installing Packages Required For Rogue

The following packages are required to build the rogue library:

- cmake   >= 3.5
- Boost   >= 1.58
- python3 >= 3.6
- bz2

To add these packages on Ubuntu 17.04 (or later):

````
$ apt-get install cmake (or cmake3)
$ apt-get install python3
$ apt-get install libboost-all-dev
$ apt-get install libbz2-dev
$ apt-get install python3-pip
$ apt-get install git
````

To add these packages on archlinux:

````
$ pacman -S cmake
$ pacman -S python3
$ pacman -S boost
$ pacman -S bzip2
$ pacman -S python-pip
$ pacman -S git
````

To use these packages on a rhel6 machine at SLAC requires some extra
steps due to the computers being out of date:

````
$ export MODULEPATH=/usr/share/Modules/modulefiles:/etc/modulefiles:/afs/slac.stanford.edu/package/spack/share/spack/modules/linux-rhel6-x86_64
$ module load cmake-3.9.4-gcc-4.9.4-ofjqova
$ source /afs/slac.stanford.edu/g/reseng/python/3.6.1/settings.sh
$ source /afs/slac.stanford.edu/g/reseng/boost/1.64.0/settings.sh
````
or for csh:
````
$ setenv MODULEPATH /usr/share/Modules/modulefiles:/etc/modulefiles:/afs/slac.stanford.edu/package/spack/share/spack/modules/linux-rhel6-x86_64
$ module load cmake-3.9.4-gcc-4.9.4-ofjqova
$ source /afs/slac.stanford.edu/g/reseng/python/3.6.1/settings.csh
$ source /afs/slac.stanford.edu/g/reseng/boost/1.64.0/settings.csh
````

The rogue distribution includes a pair of setup scripts for the SLAC environment:
````
$ source setup_slac.sh
````
or for csh:
````
$ source setup_slac.csh
````

These scripts include also include the optional zeromq and epics packages
described below.

### Optional Packages

ZeroMq is used for some of the python based messaging interface, particularly
the simulation interfaces. To use the GUI interface you will need to install
either pyqt5 or pyqt4.

On Ubuntu 17.04 (or later):

````
$ apt-get install libzmq3-dev
$ apt-get install python3-pyqt5
$ apt-get install python3-pyqt4
````

On archlinux:

````
$ pacman -S zeromq
$ pacman -S python-pyqt5
$ pacman -S python-pyqt4
````

At SLAC pyqt4 is already included with the centrally install python3, to add support
for zeromq:

````
$ source /afs/slac.stanford.edu/g/reseng/zeromq/4.2.1/settings.sh
````
or for csh:
````
$ source /afs/slac.stanford.edu/g/reseng/zeromq/4.2.1/settings.csh
````

Epics V3 support is and optional module that will be included in the rogue build
if the EPICS_BASE directory is set in the user's environment. Setup scripts
for EPICs at SLAC are included in the following directory:

````
$ source /slac/slac.stanford.edu/g/reseng/epics/base-R3-15-5-1-0/settings.sh
````
for for csh:
````
$ source /slac/slac.stanford.edu/g/reseng/epics/base-R3-15-5-1-0/settings.csh
````

### Python packages required

The following python packages are required to use rogue in the python3
environment. Currently I am using PIP to install these, but you are free 
to use your favorite python tool. These packages are already included in 
afs based SLAC python3 install mentioned above.

````
$ pip3 install PyYAML
$ pip3 install Pyro4 
$ pip3 install parse
$ pip3 install click
````

The following are optional:

````
$ pip3 install ipython
$ pip3 install pyzmq
$ pip3 install mysqlclient
````

## Using aconda environments

Activate aconda:

````
source path/to/aconda/bin/activate root
````

Create the rogue environment (required once):

````
conda env create -n rogue_env -f rogue_conda.yaml
````

Activate the rogue environement

````
conda activate rogue_env 
````

You can then build and use rogue within the conda environment. To deactive the
environment:

````
conda deactivate
source path/to/aconda/bin/deactivate root
````

## Drivers

Rogue is linked against the aes-stream-drivers package which is included 
as a submodule at the drivers sub-directory. If you need to use these
drivers please see the README.md file in that package.

## Additional Notes

The rogue package includes a readme file for compiling and installing local 
versions of python3, boost,zeromq and epics. This were created as 
notes when installing local packages at slac. These should only be neccessary
for outdated versions of Linux.

- Readme_local_packages.md

