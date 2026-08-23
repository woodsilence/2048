add_executable(c2048)
target_sources(c2048 PRIVATE c2048.c)
target_link_libraries(c2048 PRIVATE ncurses vendor)