CXX = g++
CXXFLAGS = -std=c++11 -Wall -pedantic

BUILD_DIR = build
TEMPLATE_DIR = .template
OUT_EXE = uTaste

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)

ifeq ($(OS),Windows_NT)
	LDLIBS += -l Ws2_32
endif

all: $(BUILD_DIR) $(OUT_EXE)

$(OUT_EXE): $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/strutils.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/District.o $(BUILD_DIR)/Discount.o $(BUILD_DIR)/Food.o $(BUILD_DIR)/Manual.o $(BUILD_DIR)/Reserve.o $(BUILD_DIR)/Restaurant.o $(BUILD_DIR)/Table.o $(BUILD_DIR)/Taste.o $(BUILD_DIR)/User.o
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/Manual.o: src/Manual.cpp header/Manual.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Discount.o: src/Discount.cpp header/Discount.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Food.o: src/Food.cpp header/Food.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Table.o: src/Table.cpp header/Table.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Restaurant.o: src/Restaurant.cpp header/Restaurant.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/District.o: src/District.cpp header/District.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/User.o: src/User.cpp header/User.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Reserve.o: src/Reserve.cpp header/Reserve.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Taste.o: src/Taste.cpp header/Taste.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp utils/strutils.hpp utils/strutils.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/strutils.o: utils/strutils.cpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/strutils.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/handlers.o: examples/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp src/Taste.cpp header/Taste.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: examples/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
