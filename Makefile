EXECUTABLE=bogey

SOURCES=main.cpp\
	object/ShadedSquare.cpp\
	lib/BaseDrawableGeode.cpp\
	lib/KeyboardEventHandler.cpp\
	lib/UpdateTimerCallback.cpp\

CXX=g++
CXXFLAGS=-Wall\
	 -Werror\
	 -Wmissing-include-dirs\
	 -Wextra\
	 -Wcast-qual\
	 -Wwrite-strings\
	 -Wconversion\
	 -pedantic\
	 -Winit-self\
	 -Wunused\
	 -Wfloat-equal\
	 -Wcast-align
CXXFLAGS_R=-O2 -s
CXXFLAGS_D=-O0 -g
LIBS=osg osgDB osgViewer osgGA OpenThreads
DEFINE_D=DEBUG
INCPATH=.

#######################
# AUTOMATIC VARIABLES #
#######################

# Ensures mode is release or debug
ifndef mode
    mode=debug
endif 
ifneq ($(mode), release)
ifneq ($(mode), debug)
    $(error mode must be release or debug)
endif
endif

BUILD_DIR:=build/$(mode)/
OBJECTS_DIR:=$(BUILD_DIR)objects/
OBJECTS:=$(addprefix $(OBJECTS_DIR),$(SOURCES:.cpp=.o))

# Ensures directory tree is created
has_build_dir=$(wildcard $(BUILD_DIR))
ifeq ($(has_build_dir),)
    $(shell for d in $(sort $(dir $(OBJECTS))); do \
         [ -d $$d ] || mkdir -p $$d; \
    done)
endif

LDFLAGS:=$(addprefix -l,$(LIBS)) $(addprefix -framework ,$(FRAMEWORKS))
INCPATH:=$(addprefix -I,$(INCPATH))
DEFINE:=$(addprefix -D,$(DEFINE))

ifeq ($(mode), debug)
    m=D
endif
ifeq ($(mode), release)
    m=R
endif

ifdef CXXFLAGS_$m
CXXFLAGS:=$(CXXFLAGS_$m) $(CXXFLAGS)
endif
ifdef LIBS_$m
LDFLAGS:=$(LDFLAGS) $(addprefix -l,$(LIBS_$m))
endif
ifdef FRAMEWORKS_$m
LDFLAGS:=$(LDFLAGS) $(addprefix -framework ,$(FRAMEWORKS_$m))
endif
ifdef INCPATH_$m
INCPATH:=$(INCPATH) $(addprefix -I,$(INCPATH_$m))
endif
ifdef DEFINE_$m
DEFINE:=$(DEFINE) $(addprefix -D,$(DEFINE_$m))
endif

#####################
# COMPILATION RULES #
#####################

.PHONY: release debug clean

# COMPILATION RULES
compile: $(OBJECTS)
	$(CXX) -o $(BUILD_DIR)$(EXECUTABLE) $(LDFLAGS) $(OBJECTS)

$(OBJECTS_DIR)%.o: %.cpp
	$(CXX) -c $< -o $@ $(INCPATH) $(DEFINE) $(CXXFLAGS)

# DEPENDECIES CHECK
ifneq ($(has_build_dir),)
    include $(BUILD_DIR)make.depend
endif

$(BUILD_DIR)make.depend: $(SOURCES)
	for d in $(SOURCES); do \
	    $(CXX) -MM $$d -MT $(OBJECTS_DIR)$${d/.cpp/.o} $(INCPATH) >> $@; \
	done

clean:
	rm -rf $(BUILD_DIR)
