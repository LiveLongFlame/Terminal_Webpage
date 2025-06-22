#include <iostream>
#include <ncurses.h>
#include <string>
using namespace std;
void namePrint(){
	//todo: Create an animation so that 'Valentino Webpage' gets printed out in the center letter by letter. Then the users presses anything on keybaord then show main webpage
}
void create_webpage(){
	//TODO: Create format and basic layout of the Webpage 
	clear();
	//Getting dimenstions of terminal 
	int y ,x;
	getmaxyx(stdscr, y, x);
	int center_y = y /2;
	int center_x = x /2;
	string tabs = "This is centered text test";
	mvprintw(center_y, center_x - tabs.length() /2, tabs.c_str());
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
