ifeq ($(shell uname -s),Linux)
  CC=clang-10
  CXX=clang-10
else
  CC=clang
  CXX=clang
endif

INCLUDE_DIRS= include test/include
INC_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)

CFLAGS=-x c++ -c -Wall -Werror -std=c++11 $(INC_PARAMS) -g -D_GLIBCXX_DEBUG -O0 -fno-elide-constructors 
LDFLAGS=-lstdc++

SRC:=$(shell find src -name '*.cpp')
OBJECTS=$(SRC:.cpp=.o)

# TEST_SRC=test/tests-main.cpp
# TEST_OBJECTS=$(TEST_SRC:.cpp=.o)
# TEST_EXECUTABLE=runtests

APP_SRC=main.cpp
APP_OBJECTS=$(APP_SRC:.cpp=.o)
APP_EXECUTABLE=app

ZIP_FILE=assignment0-helloworld.zip

all: $(SRC) $(APP_SRC) $(APP_EXECUTABLE) # $(TEST_SRC) $(TEST_EXECUTABLE)

# $(TEST_EXECUTABLE): $(TEST_OBJECTS) $(OBJECTS)
# 	$(CXX) $(LDFLAGS) $(TEST_OBJECTS) $(OBJECTS) -o $@

$(APP_EXECUTABLE): $(APP_OBJECTS) $(OBJECTS)
	$(CXX) $(LDFLAGS) $(APP_OBJECTS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	-rm -f $(APP_EXECUTABLE)
	-rm -f $(TEST_EXECUTABLE)
	-rm -f $(ZIP_FILE)
	find . -name "*.gcda" -print0 | xargs -0 rm -f
	find . -name "*.gcno" -print0 | xargs -0 rm -f
	find . -name "*.o" -print0 | xargs -0 rm -f

# .PHONY: test
# test: all
# 	./$(TEST_EXECUTABLE)

.PHONY: memcheck
memcheck:
	MC_FLAGS=-fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls $(MAKE) clean all
	ASAN_OPTIONS=symbolize=1 ASAN_SYMBOLIZER_PATH=$(shell which llvm-symbolizer) ./$(TEST_EXECUTABLE)

.PHONY: static-code-analysis
static-code-analysis:
	clang-tidy --header-filter=".*" --checks="cppcoreguidelines-*, bugprone*, diagnostic-*, analyzer-*, readability-*, performance-*" ${SRC} ${APP_SRC} -- ${INC_PARAMS}

.PHONY: zip
zip:
	${MAKE} clean
	${MAKE} all
	# ${MAKE} test
	${MAKE} clean
	${MAKE} $(ZIP_FILE)

$(ZIP_FILE):
	zip -r  $(ZIP_FILE) . -x '*.git*' -x '*.vscode*'  -x '*.zip'

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m
TMP_CHECK_NOT_OK=FAIL! Replace the test file with the one from the instructions!
TMP_CHECK_OK=PASS!
.PHONY: check-tampering
check-tampering:
	@echo "Checking for tampering"
	@sha1sum 'test/tests-main.cpp' | grep -q 'b2d6c9fe21d638a37ca40994ad66b615fb9fa0a5'; \
		if [ $$? -eq 0 ]; then \
			echo "${GREEN}$(TMP_CHECK_OK)${NC}";\
			exit 0;\
		else \
			echo "${RED}$(TMP_CHECK_NOT_OK)${NC}";\
			exit 1;\
		fi