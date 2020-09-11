g++-8 -std=c++17 -c code/main.cpp code/screens/main_menu_screen.cpp code/screens/farm_screen.cpp code/screens/market_screen.cpp
g++-8 main.o main_menu_screen.o farm_screen.o market_screen.o -lsfml-graphics -lsfml-window -lsfml-system -lstdc++fs -lX11 -o alice_game
