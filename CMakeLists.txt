cmake_minimum_required(VERSION 3.16)
project(Machine0)

set(CMAKE_CXX_STANDARD 20)
set(MACHZ_VERSION "0.1.0")
set(MACHZ_COMPANY_NAME "wolfink")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_compile_definitions(PLUGIN_VERSION="${MACHZ_VERSION}")

# include submodule libraries
add_subdirectory(JUCE)

file(GLOB MachZSources 
    ${SRC_DIR}/*.cpp
    ${SRC_DIR}/standalone/*.cpp
    ${SRC_DIR}/synth/*.cpp
    ${SRC_DIR}/debug/*.cpp
    ${SRC_DIR}/gui/*.cpp
)

include_directories(BEFORE include)

juce_add_plugin(MachZSynth
    PRODUCT_NAME           "Machine0"
    VERSION                ${MACHZ_VERSION}
    PLUGIN_DESCRIPTION     "A synthesizer focused on producing warm/natural sounds" 
    IS_SYNTH                TRUE
    NEEDS_MIDI_INPUT        TRUE
    NEEDS_MIDI_OUTPUT       FALSE
    IS_MIDI_EFFECT          FALSE
    FORMATS                 VST3
    VST3_CATEGORIES         Instrument
    VST3_COPY_DIR           "${CMAKE_SOURCE_DIR}/bin/VST3"
    COPY_PLUGIN_AFTER_BUILD TRUE)

# juce_add_gui_app(MachZSynth_standalone
#     PRODUCT_NAME       "Machine0"
#     VERSION            ${MACHZ_VERSION}
# )

set_target_properties(MachZSynth PROPERTIES CXX_STANDARD 20)
target_sources(MachZSynth PRIVATE ${MachZSources})

# set_target_properties(MachZSynth_standalone PROPERTIES CXX_STANDARD 20)
# target_sources(MachZSynth_standalone PRIVATE ${MachZSources})

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} PREFIX "Source Files" FILES ${MachZSources})

set(libs
    juce::juce_audio_utils
    juce::juce_audio_plugin_client
    juce::juce_dsp)

set(SHARED_COMPILE_DEFINITIONS
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0)
set(STANDALONE_COMPILE_DEFINITIONS
    JUCE_JACK=1
    JUCE_JACK_CLIENT_NAME="Machine0"
    ${SHARED_COMPILE_DEFINITIONS})
set(PLUGIN_COMPILE_DEFINITIONS
    JUCE_VST3_CAN_REPLACE_VST2=0
    ${SHARED_COMPILE_DEFINITIONS}
    )

list(APPEND libs)

target_compile_definitions(MachZSynth PUBLIC ${PLUGIN_COMPILE_DEFINITIONS})
# target_compile_definitions(MachZSynth_standalone PUBLIC ${STANDALONE_COMPILE_DEFINITIONS})

target_link_libraries(MachZSynth PRIVATE ${libs} juce::juce_recommended_config_flags)
# target_link_libraries(MachZSynth_standalone PRIVATE ${libs} juce::juce_recommended_config_flags)

execute_process(
  COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
)
