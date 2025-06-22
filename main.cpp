#include <iostream>
#include <ncurses.h>
using namespace std;
void create_webpage(){
	//TODO: Create format and basic layout of the Webpage 
	clear();
	refresh();
}
int main(){
	//This program uses ncurses to get user input from keyboard and navigate around CLI 
	//TODO: Add keyboard movements and layouts
	/* initialize curses */
	initscr();     
	noecho();          
	cbreak();      
	//hide cursor
	curs_set(0);   

    create_webpage();
	// Wait for user input before exiting
    getch();
	endwin();      
	return 0;
}
