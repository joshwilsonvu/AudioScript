
# Include this file in the .pro file of the any file
# linking to the Engine static library.

win32 {
    LIBS += \
        -lole32 \
        -lwinmm \
        -ldsound
} else:macx {
    LIBS += -framework CoreAudio  # link to CoreAudio framework
    LIBS += -framework CoreFoundation
} else:unix {
    LIBS +=  \ # link to appropriate libraries, at least one
        -lasound \
        -lpulse-simple \
        -lpulse
}
