#include <iostream>
#include <ncurses.h>

int main() {
    initscr(); // Initialize ncurses
    cbreak();  // Line buffering disabled, pass on everything to me
    noecho();  // Don't echo while we do getch
    keypad(stdscr, TRUE); // Allow reading of function keys like F1, F2, arrow keys etc.

    printw("Press any key to continue...\n");
    int key = getch(); // Waits for a single key press without Enter
    std::cout << key << std::endl;
    if(key == 258){
        endwin();
    }

}
