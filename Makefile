LDFLAGS = `pkg-config --libs opencv` `pkg-config --libs x11`
CXXFLAGS += -std=c++11 -g


all: imwrite imcapture imread matchTemplate

clean :
	$(RM) imwrite imcapture imread matchTemplate
