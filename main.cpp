#include <sstream>
#include <ncurses.h>
#include <string>
#include <unistd.h>
#include <vector>
using namespace std;
enum Tab { ABOUT, PROJECTS, CONTACT };
int index = std::max(0, std::min(index, 3));
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
	//prints contact informationm where users can navigate and contact me
	string title = "Contact Details:";
	string spacer = " ";
	vector<string> contact_arr(4);
	contact_arr[0] =  "  Email: valentinosorioschwarz@gmail.com";
	contact_arr[1] = "  Linkedin: https://www.linkedin.com/in/valentino-osorio-schwarz-b05842258/";
	contact_arr[2] = "  Github:  https://github.com/LiveLongFlame";
	// Centering calculation
	int start_row = (rows - 7) / 2;  // 7 lines tall
	int start_col = ((cols - title.length()) / 2) -25;

	attron(COLOR_PAIR(3));
	mvprintw(start_row + 1, start_col, "%s", title.c_str());
	attroff(COLOR_PAIR(3));
	// Print contact info with highlighting
	for (int i = 0; i < contact_arr.size(); ++i) {
		if (i == index) {
			attron(COLOR_PAIR(3) | A_REVERSE); // orange bg with reverse
			mvprintw(start_row + 3 + (i * 2), start_col, "%s", contact_arr[i].c_str());
			attroff(COLOR_PAIR(3) | A_REVERSE);
		} else {
			mvprintw(start_row + 3 + (i * 2), start_col, "%s", contact_arr[i].c_str());
		}
	}
}
void printWrappedText(const string& text, int start_row, int max_width, int term_cols) {
	istringstream iss(text);
	string word, line;
	vector<string> lines;

	// Word-wrapping logic
	while (iss >> word) {
		if ((line + word).length() + 1 > (size_t)max_width) {
			lines.push_back(line);
			line = word + " ";
		} else {
			line += word + " ";
		}
	}
	if (!line.empty()) {
		lines.push_back(line);
	}

	// Print each line centered based on max_width
	for (int i = 0; i < lines.size(); ++i) {
		int line_col = (term_cols - max_width) / 2;
		mvprintw(start_row + i, line_col, "%s", lines[i].c_str());
	}
}

void printAboutInfo(int rows, int cols) {
	string title = "About Me:";
	int max_width = 80; 
	int start_row = (rows - 7) / 2;  // 7 lines tall
	int start_col = ((cols - title.length()) / 2) -35;


	// Center the title
	attron(COLOR_PAIR(1));
	mvprintw(start_row +1, start_col, "%s", title.c_str());
	attroff(COLOR_PAIR(1));

	// Your paragraph text
	string paragraph =
		"My name is Valentino Osorio Schwarz, I'm currently a second-year Computer Science student at the Royal Melbourne Institute of Technology (RMIT) who loves to code and create new and innovative projects. "
		"I've been coding for 5 years now, and want to document all my personal projects and achievements to demonstrate my skills as a software developer.";

	// Print paragraph below title
	printWrappedText(paragraph, start_row + 2, max_width, cols);
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
			case 'a': currentTab = ABOUT; break;
			case 'p': currentTab = PROJECTS; break;
			case 'c': currentTab = CONTACT; break;
			case KEY_UP:
			case 'k':
				if (currentTab == CONTACT && index > 0 ) {
					index--;
				}
				break;
			case KEY_DOWN:
			case 'j':
				if (currentTab == CONTACT && index < 2) {
					index++;
				}
				break;
			case 10: // Enter key
				if (currentTab == CONTACT) {
					if (index == 1) {
						open_link("https://www.linkedin.com/in/valentino-osorio-schwarz-b05842258/");
					} else if (index == 2) {
						open_link("https://github.com/LiveLongFlame");
					}
				}
				break;

		}
		create_webpage(currentTab);
	}

	// Wait for user input before exiting
	endwin();      
	return 0;
}
