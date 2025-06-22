#include <iostream>
#include <ncurses.h>
#include <string>
#include <unistd.h>
using namespace std;
enum Tab { ABOUT, PROJECTS, CONTACT };
void namePrint(string& tittle , int row, int col, int delay = 100000){
	//Creates animation for webpage 
	for(size_t i =0; i < tittle.size();i++){
		mvaddch(row, col + i, tittle[i]);
		mvaddch(row +1, col + i, '-');
        refresh();
        usleep(delay);
	}

}
void create_webpage(Tab currentTab){
	clear();
    // Get terminal size
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    string title = "Valentino's Webpage";
    int title_row = rows / 2;
    int title_col = (cols - title.length()) / 2;
	//_____________________________________________________________-
    // Animate the title
    // namePrint(title, title_row, title_col);
    // Wait for key press to show next content
	//usleep(800000);
	//_____________________________________________________________-
    clear();
	//todo: Draw the webpage layout!!!!
	mvprintw((rows / 2 ) - 8, (cols - title.length()) /2 , title.c_str());	
    string tabs = "[a: About Me]  [p: Projects]  [c: Contact]";
    mvprintw((rows / 2) - 5, (cols - tabs.length()) / 2, "%s", tabs.c_str());

	//Selecting the different tabs and showing the different information 
	if (currentTab == PROJECTS) {
		string info = "MY PROJECTS!!!!!";
		mvprintw((rows / 2), (cols - tabs.length()) / 2, "%s", info.c_str());
	} else if(currentTab == CONTACT){
		string info = "CONTACT ME!!!!!";
		mvprintw((rows / 2), (cols - tabs.length()) / 2, "%s", info.c_str());
	}else {
		string info = "THIS IS INFORMATION ABOUT ME!!!!!";
		mvprintw((rows / 2), (cols - tabs.length()) / 2, "%s", info.c_str());
	}
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
	
	//TODO: get user inputs from keyboard
	Tab currentTab = ABOUT;	
    create_webpage(currentTab);
	int ch; 
	while ((ch = getch()) != 'q') {
		switch (ch) {
			case 'a':
				currentTab = ABOUT;
				break;
			case 'p':
				currentTab = PROJECTS;
				break;
			case 'c':
				currentTab = CONTACT;
				break;
		}
		create_webpage(currentTab);
	}

	// Wait for user input before exiting
	endwin();      
	return 0;
}
