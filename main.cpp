#include <iostream>
#include <ncurses.h>
#include <string>
#include <unistd.h>
using namespace std;
void namePrint(string& tittle , int row, int col, int delay = 100000){
	//Creates animation for webpage 
	for(size_t i =0; i < tittle.size();i++){
		mvaddch(row, col + i, tittle[i]);
		mvaddch(row +1, col + i, '-');
        refresh();
        usleep(delay);
	}

}
void create_webpage(){
	clear();
    // Get terminal size
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    string title = "Valentino's Webpage";
    int title_row = rows / 2;
    int title_col = (cols - title.length()) / 2;
    // Animate the title
    // namePrint(title, title_row, title_col);
    // Wait for key press to show next content
	//usleep(800000);
    clear();
	//todo: Draw the webpage layout!!!!
	mvprintw((rows / 2 ) -3, (cols - title.length()) /2 , title.c_str());	
    string tabs = "Tabs: [a: About Me]  [p: Projects]  [c: Contact]";
    mvprintw(rows / 2, (cols - tabs.length()) / 2, "%s", tabs.c_str());
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
