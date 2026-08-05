cmake_minimum_required(VERSION 3.20)
project(Seminar7_1012)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Seminar7_1012
        main.cpp
        AppCore/Action.cpp 
        AppCore/RepositoryFactory.cpp 
        AppCore/Repository.cpp 
        AppCore/RepositoryFile.cpp 
        AppCore/Service.cpp 
        AppCore/Transmission.cpp 
        AppCore/UI.cpp 
        AppCore/TransmissionsGUI.cpp
        AudioEngine/AcousticWave.cpp
        AudioEngine/DynamicArray.cpp
        AudioEngine/MorseEncoder.cpp
        AudioEngine/SignalProcessor.cpp
        AudioEngine/WaveOutput.cpp
)

target_include_directories(Seminar7_1012 PRIVATE AppCore AudioEngine)

target_link_libraries(Seminar7_1012 PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)