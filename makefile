# TODO: this ONLY work on OSX!
INCLUDE=-I/Library/Java/JavaVirtualMachines/jdk1.8.0_51.jdk/Contents/Home/include            \
	-I/Library/Java/JavaVirtualMachines/jdk1.8.0_51.jdk/Contents/Home/include/darwin     \

lib_track_npe.o:
	$(CXX) -shared -fPIC $(INCLUDE) -o lib_track_npe.o lib_track_npe.cpp

clean:
	rm lib_track_npe.o 
