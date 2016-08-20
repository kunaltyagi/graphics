BIN = mydraw

GLLIBS = -lGL -lGLU -lglut
XLIBS = -lX11 -lpthread -lXrandr -lXi
LIBS = $(GLLIBS) #$(XLIBS)

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
# $(info $(BIN_LIST))

all: CXXFLAGS += -O2
all: $(BIN_LIST)

debug_basic: CXXFLAGS += -DDEBUG_BASIC
debug_basic: CXXFLAGS += -DANY_CASE
debug_basic: debug

debug: CXXFLAGS += -DDEBUG
debug: $(BIN_LIST)

clean:
	rm -f $(BIN_LIST)
	rm -f *.o
	rm -f *~

$(BUILD_DIR)/%:  %.cpp $(COMMON_SRCS) #$(SOURCE_DIR)/%.cpp
	$(CPP) $(CXXFLAGS) $(INC) $(COMMON_SRCS) $< -o $@ $(LIBS)

#mydraw: mydraw.cpp
#	g++ mydraw_class.cpp mydraw.cpp -o $@ $(GLLIBS)


