CC = mingw32-g++

QT_INC_PATH = /c/QtSDK/Desktop/Qt/4.8.1/mingw/include
QT_LIB_PATH = /c/QtSDK/Desktop/Qt/4.8.1/mingw/lib

LIBNAME = build/libqt4json
ALL=$(LIBNAME).dll
CFLAGS = -Wall -I. -I.. -I../.. -I/include -DQT_SHARED -I$(QT_INC_PATH) -I$(QT_INC_PATH)/QtCore
LDFLAGS = -Wl -Wl,-enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc -enable-stdcall-fixup -Wl,-s -shared -Wl,--out-implib,$(LIBNAME).a -mwindows
LIBS =  -L$(QT_LIB_PATH) -lQtCore4 -lpthread -lws2_32 -ljson-c
BUILD_DIR = build

SRC = 	libqt4json.cpp \
		CCommon.cpp
	

OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC)) 

all: $(BUILD_DIR) $(ALL)

.PHONY: $(BUILD_DIR)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(ALL): $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)
	
$(BUILD_DIR)/%.o: ../%.cpp
	$(CC) -o $@ $(CFLAGS) -c $<
	
clean:
	rm -rf $(BUILD_DIR)
