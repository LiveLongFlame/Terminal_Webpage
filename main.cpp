#include <cstddef>
#include <sstream>
#include <ncurses.h>
#include <string>
#include <unistd.h>
#include <vector>
#include <fstream>

using namespace std;
enum Tab { ABOUT, PROJECTS, CONTACT };

struct Project {
    string name;
    string repo_url;
    string readme_url;
};


vector<Project> projects = {
    {
        "Personal Projects",
        "https://github.com/LiveLongFlame/Personal-Projects",
        "https://raw.githubusercontent.com/LiveLongFlame/Personal-Projects/main/README.md"
    },
    {
        "CS50 Final Project",
        "https://github.com/LiveLongFlame/cs50_final_project",
        "https://raw.githubusercontent.com/LiveLongFlame/cs50_final_project/main/README.md"
    },
    {
        "Personal Website",
        "https://github.com/LiveLongFlame/Personal-Website",
        "https://raw.githubusercontent.com/LiveLongFlame/Personal-Website/main/README.md"
    },
    {
        "Budget Tracker",
        "https://github.com/LiveLongFlame/Budget-Tracker",
        "https://raw.githubusercontent.com/LiveLongFlame/Budget-Tracker/main/README.md"
    },
    {
        "Terminal Webpage",
        "https://github.com/LiveLongFlame/Terminal_Webpage",
        "https://raw.githubusercontent.com/LiveLongFlame/Terminal_Webpage/main/README.md"
    }
};
Tab currentTab = ABOUT;	
string readme_text;
bool readme = false;
bool readmore = false;
int index = 0;
int jndex = 0;
vector<vector<string>> lst = {
	{
		"  - Track & Field (High Jump, Triple Jump, sprints)",
		"  - Love Rubik's Cubes (5x5 is my favourite)",
		"  - Coding!!!!!"
	},
	{
		"  - Python, Java",
		"  - C/C++",
		"  - HTML, CSS, JavaScript, PHP, SQL"
	},
	{
		"  - Completed VCE Year 12 [2023]",
		"  - Completed Harvard's CS50 Course [2021-2023]",
		"  - Bachelor of Computer Science [2023 - present]"
	}
};

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

	attron(COLOR_PAIR(3) | A_BOLD);
	mvprintw(start_row + 1, start_col, "%s", title.c_str());
	attroff(COLOR_PAIR(3) | A_BOLD);

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
	string controls = "[q:quit] [h/j/k/l or < v ^ >  navigate]";
	mvprintw((rows / 2) + 8, (cols - controls.length()) /2, "%s" , controls.c_str()); 

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
	int start_row = (rows - 7) / 2 - 10;
	int start_col = ((cols - title.length()) / 2) - 36;

	attron(COLOR_PAIR(1) | A_BOLD);
	mvprintw(start_row + 1, start_col, "%s", title.c_str());
	attroff(COLOR_PAIR(1) | A_BOLD);

	string paragraph =
		"My name is Valentino Osorio Schwarz, I'm currently a second-year Computer Science student at the Royal Melbourne Institute of Technology (RMIT) who loves to code and create new and innovative projects. "
		"I've been coding for 5 years now, and want to document all my personal projects and achievements to demonstrate my skills as a software developer.";

	printWrappedText(paragraph, start_row + 2, max_width, cols);

	vector<string> section_titles = {
		"Hobbies:", "Programming Languages:", "Achievements:"
	};

	for (int sec = 0; sec < lst.size(); ++sec) {
		int section_title_row = (rows / 2) - 5 + (sec * 5);
		if (index == sec) {
			attron(COLOR_PAIR(1) | A_BOLD | A_UNDERLINE);
			mvprintw(section_title_row, start_col, "%s", section_titles[sec].c_str());
			attroff(COLOR_PAIR(1) | A_BOLD | A_UNDERLINE);
		} else {
			attron(COLOR_PAIR(1));
			mvprintw(section_title_row, start_col, "%s", section_titles[sec].c_str());
			attroff(COLOR_PAIR(1));
		}

		for (int i = 0; i < lst[sec].size(); ++i) {
			int item_row = (rows / 2) - 4 + (sec * 5) + i;
			if (index == sec && jndex == i) {
				attron(COLOR_PAIR(1) | A_REVERSE);
			}
			mvprintw(item_row, start_col, "%s", lst[sec][i].c_str());
			if (index == sec && jndex == i) {
				attroff(COLOR_PAIR(1) | A_REVERSE);
			}
		}
	}

	string controls = "[q:quit] [h/j/k/l or < v ^ >  navigate]";
	mvprintw((rows / 2) + 12 , (cols - controls.length()) /2, "%s" , controls.c_str());

}

string fetch_readme(const string& url) {
	const string temp_file = "/tmp/readme_tmp.md";
	string command = "curl -s \"" + url + "\" -o " + temp_file;
	system(command.c_str());

	ifstream in(temp_file);
	stringstream buffer;
	buffer << in.rdbuf();
	return buffer.str();
}
void printProjectInfo(int rows, int cols){
	//todo: Print out project information
	//users can hgihlight project and if the enter on the project 
	//then the readme file pops up to the side 
	//a little buttion saying read more.. in blue 
	//if user hits enter will ope
	
		vector<string> lst_projects(5);
		lst_projects[0] = "  -A* PathFinder";
		lst_projects[1] = "  -cs50 Project";
		lst_projects[2] = "  -Personal Website";
		lst_projects[3] = "  -Buget Tracker";
		lst_projects[4] = "  -Terminal Webpage";

	if (readme) {
		//print the project and create a title
		string tittle_projects = lst_projects[index] ;
		int start_row = (rows - 7) / 2 - 8;
		int start_col = ((cols - tittle_projects.length()) / 2) - 30;

		attron(COLOR_PAIR(2) | A_BOLD);
		mvprintw(start_row + 1, start_col, "%s", tittle_projects.c_str());
		attroff(COLOR_PAIR(2) | A_BOLD);

		readme_text = fetch_readme(projects[index].readme_url);

		int readme_start_col =  start_col + 5;
		int readme_width = 70;
		int readme_start_row = start_row +3;
		int max_lines = 15; // Limit how many lines to show

		// Wrap and print a portion of the README
		istringstream iss(readme_text);
		string line;
		int count = 0;
		while (getline(iss, line) && count < max_lines) {
			mvprintw(readme_start_row + count, readme_start_col, "%.*s", readme_width, line.c_str());
			count++;
		}

		attron(COLOR_PAIR(2) | A_REVERSE);
		mvprintw(readme_start_row + count + 1, readme_start_col, "[Enter] Read More...");
		attroff(COLOR_PAIR(2) | A_REVERSE);
	} else {
		string tittle_projects = "Projects:";
		int start_row = (rows - 7) / 2;  // 7 lines tall
		int start_col = ((cols - tittle_projects.length()) / 2) -25;

		attron(COLOR_PAIR(2) | A_BOLD);
		mvprintw(start_row + 1, start_col, "%s", tittle_projects.c_str());
		attroff(COLOR_PAIR(2) | A_BOLD);

		//prints list 
		for (size_t i = 0; i < lst_projects.size(); i++) {
			mvprintw(start_row + 3 + (int)i * 2, start_col, "%s", lst_projects[i].c_str());
		}

		// Print the selected item again with highlight
		if (index >= 0 && index < lst_projects.size()) {
			attron(COLOR_PAIR(2) | A_REVERSE);
			mvprintw(start_row + 3 + index * 2, start_col, "%s", lst_projects[index].c_str());
			attroff(COLOR_PAIR(2) | A_REVERSE);
		}

	}

	string controls = "[q:quit] [h/j/k/l or < v ^ >  navigate] [esc or b:back]";
	mvprintw((rows / 2) + 10 , (cols - controls.length()) /2, "%s" , controls.c_str());

}
void tabs_display(){

}
void create_webpage(Tab currentTab){
	clear();
    // Get terminal size
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
	
	// Tabs
	string tab_about = "[a: About Me]";
	string tab_projects = "[p: Projects]";
	string tab_contact = "[c: Contact]";
	int tabs_row = (rows / 2) - 5;
	if (currentTab == ABOUT) {
		tabs_row -= 10;
	} else if(currentTab == PROJECTS && readme){
		tabs_row -= 8;
	}

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


    refresh();
}
int main(){
	//This program uses ncurses to get user input from keyboard and navigate around CLI 
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
	//animation for name title
	namePrint();	
	usleep(800000);
	// get user inputs from keyboard
	
    create_webpage(currentTab);
	int ch; 
	while ((ch = getch()) != 'q') {
	switch (ch) {
		case 'a': currentTab = ABOUT; break;
		case 'p': currentTab = PROJECTS; break;
		case 'c': currentTab = CONTACT; break;
		
		case KEY_UP:
		case 'k':
			if (currentTab == CONTACT && index > 0) {
				index--;
			} else if (currentTab == ABOUT && index > 0) {
				index--;
				jndex = 0;
			} else if(currentTab == PROJECTS && index > 0){
				index--;
				jndex =0;
			}
			break;
		case KEY_DOWN:
		case 'j':
			if (currentTab == CONTACT && index < 2) {
				index++;
			} else if (currentTab == ABOUT && index < 2) {
				index++;
				jndex = 0;
			}else if(currentTab == PROJECTS && index < 4){
				index++;
				jndex=0;
			}
			break;
		case KEY_LEFT:
		case 'h':
			if (currentTab == ABOUT && jndex > 0) {
				jndex--;
			}
			break;
		case KEY_RIGHT:
		case 'l':
			if (currentTab == ABOUT && jndex < lst[index].size() - 1) {
				jndex++;
			}
			break;
		case 10: // Enter
			if (currentTab == CONTACT) {
				if (index == 1) open_link("https://www.linkedin.com/in/valentino-osorio-schwarz-b05842258/");
				else if (index == 2) open_link("https://github.com/LiveLongFlame");
			} else if(currentTab == PROJECTS){
				if (!readme) {
					readme = true;
					readmore = false;
				} else if (readme && !readmore) {
					readmore = true;
					open_link(projects[index].repo_url);
				} 
				
			} 
			break;
		case 27: // ESC key
		case 'b':
			if (readme) {
				readme = false;
				readmore = false;
			}
			break;
	}
	create_webpage(currentTab);
}
	// Wait for user input before exiting
	endwin();      
	return 0;
}
