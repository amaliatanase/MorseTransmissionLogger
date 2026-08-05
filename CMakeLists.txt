cmake_minimum_required(VERSION 3.20)
project(Seminar7_1012)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Căutăm pachetul Qt6
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# Am scos main.cpp-ul duplicat (dacă fișierul tău se numește main_2.cpp, schimbă aici)
add_executable(Seminar7_1012
        main.cpp
        Action.cpp
        RepositoryFactory.cpp
        Repository.cpp
        RepositoryFile.cpp
        Service.cpp
        Transmission.cpp
        UI.cpp
        TransmissionsGUI.cpp
)

# Am adăugat prefixul Qt6:: pentru a le recunoaște corect
target_link_libraries(Seminar7_1012 PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)