#include <ncurses.h>
#include <string>
#include <unistd.h>
using namespace std;
enum Tab { ABOUT, PROJECTS, CONTACT };
void namePrint() {
    clear();
    int row, col;
    getmaxyx(stdscr, row, col);

    std::string tittle = "Valentino's Webpage";
    int title_row = row / 2;
    int title_col = (col - tittle.length()) / 2;
    int delay = 100000; // 100ms

    // Animate the title
    for (size_t i = 0; i < tittle.size(); i++) {
        mvaddch(title_row, title_col + i, tittle[i]);
        mvaddch(title_row + 1, title_col + i, '-');
        refresh();
        usleep(delay);
    }
}
void open_link(const string& url) {
    if (!url.empty()) {
        string command = "xdg-open '" + url + "' >/dev/null 2>&1 &";
        system(command.c_str());
    }
}
void printContactInfo(int rows, int cols){
	//todo: Print out contact information 
	//if user hits j/k they can move up or down 
	//what gets highelights background turns to orange
	//tittl is orange
	// https://linkedin.com/in/valentinoosorio
	// https://github.com/LiveLongFlame
	string title = "Contact Details:";
	string email = "  Email: valentinoosorioschwarz@gmail.com";
	string spacer = " ";
	string phone = "  Phone Number: 0490854889";
	string linkedin = "  Linkedin: https://www.linkedin.com/in/valentino-osorio-schwarz-b05842258/";
	string github = "  Github:  https://github.com/LiveLongFlame";

	// Centering calculation
	int start_row = (rows - 7) / 2;  // 7 lines tall
	int start_col = ((cols - title.length()) / 2) -25;

	// Draw box
	attron(COLOR_PAIR(3));
	mvprintw(start_row + 1, start_col, "%s", title.c_str());
	attroff(COLOR_PAIR(3));
	mvprintw(start_row + 3, start_col, "%s", email.c_str());
	mvprintw(start_row + 4, start_col, "%s", spacer.c_str());
	mvprintw(start_row + 5, start_col, "%s", phone.c_str());
	mvprintw(start_row + 6, start_col, "%s", spacer.c_str());
	mvprintw(start_row + 7, start_col, "%s", linkedin.c_str());
	mvprintw(start_row + 8, start_col, "%s", spacer.c_str());
	mvprintw(start_row + 9, start_col, "%s", github.c_str());
}
void printAboutInfo(int rows, int cols){
	//todo: Print out about ifnormatin structure like website 
	// for 
		string info = "THIS IS INFORMATION ABOUT ME!!!!!";
		mvprintw((rows / 2), (cols - info.length()) / 2, "%s", info.c_str());
}
void printProjectInfo(int rows, int cols){
	//todo: Print out project information
	//users can hgihlight project and if the enter on the project 
	//then the readme file pops up to the side 
	//a little buttion saying read more.. in blue 
	//if user hits enter will ope
		string info = "MY PROJECTS!!!!!";
		mvprintw((rows / 2), (cols - info.length()) / 2, "%s", info.c_str());
}
void create_webpage(Tab currentTab){
	clear();
    // Get terminal size
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
	//todo: Draw the webpage layout!!!!
	
	// Tabs
	string tab_about = "[a: About Me]";
	string tab_projects = "[p: Projects]";
	string tab_contact = "[c: Contact]";
	int tabs_row = (rows / 2) - 5;

	int col_start = (cols - (tab_about.length() + tab_projects.length() + tab_contact.length() + 4)) / 2;

	// About Tab
	if (currentTab == ABOUT) attron(COLOR_PAIR(1));
	mvprintw(tabs_row, col_start, tab_about.c_str());
	if (currentTab == ABOUT) attroff(COLOR_PAIR(1));

	// Projects Tab
	if (currentTab == PROJECTS) attron(COLOR_PAIR(2));
	mvprintw(tabs_row, col_start + tab_about.length() + 2, tab_projects.c_str());
	if (currentTab == PROJECTS) attroff(COLOR_PAIR(2));

	// Contact Tab
	if (currentTab == CONTACT) attron(COLOR_PAIR(3));
	mvprintw(tabs_row, col_start + tab_about.length() + tab_projects.length() + 4, tab_contact.c_str());
	if (currentTab == CONTACT) attroff(COLOR_PAIR(3));
	//Selecting the different tabs and showing the different information 
	if (currentTab == PROJECTS) {
		printProjectInfo(rows, cols);
	} else if(currentTab == CONTACT){
		printContactInfo(rows , cols);
	}else {
		printAboutInfo(rows , cols);
	}


	//Telling users controls and inputs
	//q:quit , h/j/k/l or ← ↓ ↑ → Navigation
	string controls = "[q:quit] [h/j/k/l or < v ^ >  navigate]";
	mvprintw((rows / 2) + 8, (cols - controls.length()) /2, "%s" , controls.c_str()); 
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
	//allows for keypad interaction 
	keypad(stdscr, TRUE);
	// Adding colours to different tabs
	start_color();
	use_default_colors();
	init_pair(1, COLOR_MAGENTA, -1); // About = Purple
	init_pair(2, COLOR_CYAN, -1);    // Projects = Light Blue
	init_pair(3, COLOR_YELLOW, -1);  // Contact = Orange-ish
	//namePrint();	
	//usleep(800000);
	// get user inputs from keyboard
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
