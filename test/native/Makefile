# This makefile creates appropriate, os specific JNI headers,
# generates compiled source, and then creates a linked JNI Library.
# It should be run on the desired system before running tests.
# Currently supports OSX and Linux on x86 architectures (windows not supported, ARM not supported)
# JAVA_HOME must be set on the target machine to a Java 8 or 9 JDK for this to run successfully.

#The following represents the root project path. DO NOT EDIT
SCRIPTDIR=$(PWD)
PROJECTPATH=$(firstword $(subst /test/native/, ,$(SCRIPTDIR)))
UNAME := $(shell uname)

#USER SPECIFIED
#The following var represents the output name of the JniLib that will be created and referenced in the job map.
LIBNAME=OnyxNativeTest

#USER SPECIFIED
#The following var should contain a list of fully qualified Java classes used by the C glue functions separated by spaces
JAVAHCLASSES:= onyxplatform.test.NativeAssocFn onyxplatform.test.NativeDissocFn onyxplatform.test.NativeEmptyFn \
	onyxplatform.test.NativeGetFn onyxplatform.test.NativeMergeFn onyxplatform.test.NativePassFn

#USER SPECIFIED
#The following var should contain a list of JARS or other dirs/containers holding sources or their dependencies,
#separated by ':', used in generating java headers for native interop for classes listed in JAVACLASSES
JAVAHPATH=$(PROJECTPATH)/dependencies/clojure-1.8.0.jar:$(PROJECTPATH)/dependencies/onyx-java-0.1.6.jar:$(PROJECTPATH)/src/java/:$(PROJECTPATH)/test/java/

#USER SPECIFIED
#The following vars should contain strings representing the C, Fortran, and CPP libraries that glue the fortran code to java code.
#These strings should contain the user libraries in the order they need to be compiled (ex, "First.c Second.c Third.c")
#These vars do not need to specify libraries they depend on that are found in the common variables (those are automatically compiled first).
USERC=OnyxNativeTest.c
USERCPP=
USERFORTRAN=


ifeq ($(UNAME), Linux)
#The following represent a standard RHEL 7 system.
JNIDIR="$(JAVA_HOME)/include"
JNIMDDIR="$(JAVA_HOME)/include/linux"
JVMHEADERS="$(JAVA_HOME)/include/linux"
endif
ifeq ($(UNAME), Darwin)
#The following represent a standard OSX system.
JNIDIR="$(JAVA_HOME)/Contents/Home/include"
JNIMDDIR="$(JAVA_HOME)/Contents/Home/include/darwin"
JVMHEADERS="/System/Library/Frameworks/JavaVM.framework/Headers"
endif

#compilers
CXX=g++
CC=gcc
FF=gfortran

#The following vars contain strings representing common libraries used by all code
#at a project level. These should generally not be touched by users.
COMMONC=
COMMONCPP=OnyxNative.cpp OnyxLib.cpp
COMMONFORTRAN=


COMMONCPATH=$(PROJECTPATH)/src/native/common/
USERCPATH=$(PROJECTPATH)/test/native/
COMMONCPPPATH=$(PROJECTPATH)/src/native/
USERCPPPATH=$(PROJECTPATH)/src/native/common/
COMMONFORTRANPATH=$(PROJECTPATH)/src/native/common/
USERFORTRANPATH=$(PROJECTPATH)/src/native/common/

TARGETPATH="$(PROJECTPATH)/test/native/"
#The following is the target library for the native jni library.
ifeq ($(UNAME), Linux)
#The following represents a standard RHEL 7 system.
LNFLAGS=-dynamiclib -shared -lgfortran -I$(JVMHEADERS)
endif
ifeq ($(UNAME), Darwin)
#The following represents a standard OSX system.
LNFLAGS=-dynamiclib -shared -lgfortran -I$(JVMHEADERS) -framework JavaVM
endif

CFLAGS=-I$(JVMHEADERS) -I$(COMMONCPPPATH) -I$(COMMONCPATH) -I$(USERCPPPATH) -I$(USERCPATH) -I$(JNIDIR) -I$(JNIMDDIR) -fpic
FFLAGS=-I$(COMMONFORTRANPATH) -I$(USERFORTRANPATH) -fPIC

#The following is the target library for the native jni library.
ifeq ($(UNAME), Linux)
#The following represents a standard RHEL 7 system.
DYLIB=lib$(LIBNAME).so
endif
ifeq ($(UNAME), Darwin)
#The following represents a standard OSX system.
DYLIB=lib$(LIBNAME).jnilib
endif

COMMONFORTRAN1=$(addprefix $(COMMONFORTRANPATH), $(COMMONFORTRAN))
USERFORTRAN1=$(addprefix $(USERFORTRANPATH), $(USERFORTRAN))
COMMONC1=$(addprefix $(COMMONCPATH), $(COMMONC))
USERC1=$(addprefix $(USERCPATH), $(USERC))
COMMONCPP1=$(addprefix $(COMMONCPPPATH), $(COMMONCPP))
USERCPP1=$(addprefix $(USERCPPPATH), $(USERCPP))

all: clean gen-headers build

.PHONY : clean gen-headers build

gen-headers:
	echo
	echo "Generating headers. "
	echo ""
	$(foreach header,$(JAVAHCLASSES),javah -d $(USERCPATH) -classpath $(JAVAHPATH) -force $(header);)
	echo ""

build:
	echo "Building " $(LIBNAME) " in " $(PROJECTPATH)
	#echo "Compiling Fortran"
	#echo ""
	#cd $(TARGETPATH) && $(FF) $(FFLAGS) -c $(COMMONFORTRAN1) $(USERFORTRAN1)
	#echo ""
	echo "Compiling CPP"
	echo ""
	cd $(TARGETPATH) && $(CXX) $(CFLAGS) -c $(COMMONCPP1) $(USERCPP1)
	echo ""
	echo "Compiling C"
	echo ""
	cd $(TARGETPATH) && $(CC) $(CFLAGS) -c $(COMMONC1) $(USERC1)
	echo ""
	echo "Creating JNI Library"
	echo ""
	cd $(TARGETPATH) && $(CXX) $(LNFLAGS) *.o -o $(DYLIB)
	echo "Build success for " $(LIBNAME)

clean:
	echo "Cleaning up."
	echo ""
	-cd $(TARGETPATH) && rm *.h
	-cd $(TARGETPATH) && rm *.o
	-cd $(TARGETPATH) && rm *.mod
	-cd $(TARGETPATH) && rm *.jnilib
	-cd $(TARGETPATH) && rm *.so
	echo ""
