CXX      = g++

.DEFAULT_GOAL := all

SOURCES =
SOURCES += scoredword.cpp
SOURCES += state.cpp
SOURCES += position.cpp
SOURCES += letter.cpp
SOURCES += letterBag.cpp
SOURCES += playerletters.cpp
SOURCES += gaddagnode.cpp
SOURCES += gaddag.cpp
SOURCES += bonus.cpp
SOURCES += spot.cpp
SOURCES += board.cpp

OBJECTS = $(SOURCES:.cpp=.o)

CXXFLAGS  += -g -Wall -std=c++11 -pedantic -O3
LDFLAGS +=

$(OBJECTS) : %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

CLEAN_OBJECTS = $(OBJECTS)
TARGETS = 

########## test_board ##########

BOARD_SOURCES = test_board.cpp
BOARD_OBJECTS = $(BOARD_SOURCES:.cpp=.o)

test_board : $(BOARD_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(BOARD_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(BOARD_OBJECTS): %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

all : test_board
TARGETS += test_board
CLEAN_OBJECTS += $(BOARD_OBJECTS)

########## cleanup ##########
DEPS = $(CLEAN_OBJECTS:.o=.d)

clean:
	@rm -f $(DEPS) $(TARGETS) $(CLEAN_OBJECTS)

-include $(DEPS)
