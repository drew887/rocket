CC:= g++
CXXFLAGS:= -Wall -g --std=c++11 -lGL -lGLEW -fPIC
.PHONY: clean
src:= $(foreach dir,$(CURDIR),$(notdir $(wildcard $(CURDIR)/*.cpp)))
heads:= $(foreach dir,$(CURDIR),$(notdir $(wildcard $(CURDIR)/*.h)))
Target:= $(notdir $(CURDIR))

all: $(Target)
$(Target): $(src:.cpp=.o)
	$(CC) -shared $**.o -o $(Target).so $(CXXFLAGS) -lc -Wl,-soname,$(Target).so

%.o: %.cpp $(heads)
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f *.o $(Target).so
