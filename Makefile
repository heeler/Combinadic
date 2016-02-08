#Choose a compiler name Either GPP or CLANGPP
CXX_NAME=CLANGPP

#Compiler
CXX_CLANGPP=/usr/bin/clang++
CXX_GPP=/usr/bin/g++
CC=$(CXX_$(CXX_NAME))

#CFLAGS definition
#CFLAGS_CLANGPP=-std=c++11 -stdlib=libc++ -I/usr/local/include -I./UIS_Gtest -I./UIS -I./UIS_Gtest/GoogleTest/include -I./Proto

CFLAGS_CLANGPP=-std=c++11 -stdlib=libc++ -arch x86_64 -I/usr/local/include  -I./CSetUnitTests -I./CSet  
# -F/usr/local/Frameworks/gtest-framework
#######!!!!CFLAGS_GPP=-std=gnu++11 -Wall -I./UIS_Gtest -I./UIS -I./UIS_Gtest/GoogleTest
#CFLAGS_GPP=-std=gnu++11 -Wall -I./UIS_Gtest -I./UIS -I./Proto -I./UIS_Gtest/GoogleTest/include -I/usr/local/include
CFLAGS=$(CFLAGS_$(CXX_NAME)) 

#LDFLAGS= -L/usr/local/lib -lprotobuf -v
# gets -lprotocol and -L/usr/local/lib from pkg_config below


GTEST_SRC		:= $(wildcard CSetUnitTests/*.cpp) 

GTEST_OBJ 		:= $(GTEST_SRC:.cpp=.o)

CSET_SRC			:= $(wildcard CSet/*.cpp) 

CSET_OBJ			:= $(CSET_SRC:.cpp=.o)

GTEST_OBJECTS	:= $(CSET_OBJ) $(GTEST_OBJ)

GTEST_EXE		:= gtest_bin






test: $(GTEST_EXE)


$(GTEST_EXE): $(CSET_OBJ) $(GTEST_OBJ)
	$(CC) Mains/main_gtest.cpp $(CSET_OBJ) $(GTEST_OBJ) -o $@ $(CFLAGS) -F/usr/local/Frameworks -framework gtest 


$(CSET_OBJ) : $(CSET_SRC)

$(GTEST_OBJ) : $(GTEST_SRC)


%.o : %.cpp 
	$(CC) $(CFLAGS) -c $< -o $@ 

%.pb.o : %.pb.cc 
	$(CC) $(CFLAGS) -c $< -o $@

%.pb.cc : %.proto
	$(PCC) -I=Proto --cpp_out=Proto $<

clean: 
	rm $(CSET_OBJ) $(GTEST_OBJ)
