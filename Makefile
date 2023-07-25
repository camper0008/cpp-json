
PROGRAM = program
CPP_FLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -Wconversion
CXX = clang++

SOURCE_FOLDER = .
BUILD_FOLDER = build
CPP_FILES = $(shell find $(SOURCE_FOLDER) -name "*.cpp")
HPP_FILES = $(shell find $(SOURCE_FOLDER) -name "*.hpp")

OBJECT_FILES = $(patsubst $(SOURCE_FOLDER)/%.cpp, $(BUILD_FOLDER)/%.o, $(CPP_FILES))

all: $(PROGRAM) compile_flags.txt

$(PROGRAM): $(OBJECT_FILES)
	$(CXX) $^ -o $(BUILD_FOLDER)/$@

$(BUILD_FOLDER)/%.o: $(SOURCE_FOLDER)/%.cpp $(HPP_FILES) build_folder
	$(CXX) $< -c -o $@ $(CPP_FLAGS)

build_folder:
	mkdir $(BUILD_FOLDER) -p

compile_flags.txt:
	echo -xc++ $(CPP_FLAGS) | sed 's/\s\+/\n/g' > compile_flags.txt

clean:
	rm -rf $(BUILD_FOLDER)

