CXX = g++

CXXFLAGS = -g -std=c++11

link_libs = -lpthread\

INCLUDES = \

SRC = .\

target = game 

files = $(foreach d, $(SRC), $(wildcard $(d)/*.cpp))
objects = $(patsubst %.cpp, %.o, $(files))

$(target) : $(objects)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(link_libs)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $^

all : $(target)

clean :
	rm -rf $(target)
	rm -rf $(objects)

