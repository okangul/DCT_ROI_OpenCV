LIB_PATHS=-L/usr/local/Cellar/opencv/2.4.12/lib
LIBS=-lopencv_highgui -lopencv_core
all: Assignment3

Assignment3: Assignment3.cpp
	g++ Assignment3.cpp ${LIB_PATHS} ${LIBS} -o Assignment3

.PHONY:clean

clean:
	rm Assignment3
