UNAME_S := $(shell uname -s)
UNAME_P := $(shell uname -p)

$(info System is $(UNAME_S) $(UNAME_P))

ifeq ($(UNAME_S),Darwin)
	CXX                = g++-13 -std=c++20
else
	CXX                = g++ -std=c++20
endif

OPTFLAGS	   = -O3
CXXFLAGS          += -Wall 
AUTOFLAGS          = -march=native -ffast-math # -mavx2
INCLUDES	   = -I. -I./include
LIBS               = -pthread -fopenmp
SOURCES            = $(wildcard *.cpp)
TARGET             = $(SOURCES:.cpp=)


ifneq ($(UNAME_P),arm)
	AUTOFLAGS += -mavx2
endif


.PHONY: all clean cleanall 

%: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(OPTFLAGS) -o $@ $< $(LIBS)

all: $(TARGET)

omp_all_pair:omp_all_pair.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(AUTOFLAGS) $(OPTFLAGS) -o $@ $< $(LIBS)

clean: 
	-rm -fr *.o *~
cleanall: clean
	-rm -fr $(TARGET)
