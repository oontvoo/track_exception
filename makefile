LDLIBS=$(shell root-config --libs)
INCLUDE= -I/Library/Java/JavaVirtualMachines/jdk1.8.0_51.jdk/Contents/Home/include            \
	 -I/Library/Java/JavaVirtualMachines/jdk1.8.0_51.jdk/Contents/Home/include/darwin     \
	  

track_npe: lib_track_npe.o
	$(CXX) -shared -fPIC $(LDLIBS) $(INCLUDE) -o lib_track_npe.o lib_track_npe.cpp
