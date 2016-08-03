BIN = mydraw

GLLIBS = -lGL -lGLU -lglut
LIBS = $(GLLIBS)

CPP = g++
# @TODO restructure the src and headers
COMMON_SRCS = mydraw_class.cpp
# INC =
CXXFLAGS = -std=c++11 -g

BUILD_DIR = build
SOURCE_DIR = src
TEST_DIR = $(BUILD_DIR)/test
BIN_LIST = $(addprefix $(BUILD_DIR)/, $(BIN))

HEADERS = mydraw_class

.SUFFIXES: .cpp .hpp
$(info $(BIN_LIST))

all: $(BIN_LIST)

debug: CXXFLAGS += -DDEBUG
debug: CXXFLAGS += -DANY_CASE
debug: $(BIN_LIST)

clean:
	rm -f $(BIN_LIST)
	rm -f *.o
	rm -f *~

$(BUILD_DIR)/%:  %.cpp #$(SOURCE_DIR)/%.cpp
	$(CPP) $(INC) $(COMMON_SRCS) $< $(CXXFLAGS) -o $@ $(LIBS)

#mydraw: mydraw.cpp
#	g++ mydraw_class.cpp mydraw.cpp -o $@ $(GLLIBS)


