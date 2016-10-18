# TODO: this ONLY work on OSX!
INCLUDE=-I/Library/Java/JavaVirtualMachines/jdk1.8.0_51.jdk/Contents/Home/include            \
	-I/Library/Java/JavaVirtualMachines/jdk1.8.0_51.jdk/Contents/Home/include/darwin     \

# compile the agent
lib_track_npe.o:
	$(CXX) -shared -fPIC $(INCLUDE) -o lib_track_npe.o lib_track_npe.cpp

# compile the driver 
compile_test_npe:
	javac test/TestNPE.java

# test npe
# This should show the stack trace with location of the NPE
test_npe: lib_track_npe.o compile_test_npe
	java -agentpath:lib_track_npe.o -cp test/:. TestNPE

clean:
	rm -rf lib_track_npe.o  *.class test/*.class
