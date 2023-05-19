find_library(COREAUDIO_LIBRARY CoreAudio)
find_library(COREAUDIO_FOUNDATION CoreFoundation)
find_library(COREAUDIO_MIDI CoreMIDI)
find_path(COREAUDIO_INCLUDE_DIRS CoreAudio/CoreAudio.h)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
        CoreAudio
        DEFAULT_MSG
        COREAUDIO_LIBRARY
        COREAUDIO_FOUNDATION
        COREAUDIO_MIDI
        COREAUDIO_INCLUDE_DIRS)

mark_as_advanced(
        COREAUDIO_LIBRARY
        COREAUDIO_FOUNDATION
        COREAUDIO_MIDI
        COREAUDIO_INCLUDE_DIRS)
