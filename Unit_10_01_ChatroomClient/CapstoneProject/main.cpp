#include <ncurses.h>
#include <string>
#include <vector>
#include <algorithm>

// ---------------------- Base Window Class ----------------------

class WindowBase {
protected:
    WINDOW* win;
    int height;
    int width;
    int starty;
    int startx;

public:
    WindowBase(int h, int w, int y, int x)
        : win(nullptr), height(h), width(w), starty(y), startx(x) {
        win = newwin(height, width, starty, startx);
    }

    virtual ~WindowBase() {
        if (win) {
            delwin(win);
            win = nullptr;
        }
    }

    virtual void render() = 0;

    WINDOW* getWindow() const { return win; }

    int getHeight() const { return height; }
    int getWidth() const { return width; }

    void drawBorder() {
        box(win, 0, 0);
    }
};

// ---------------------- Header Window ----------------------

class HeaderWindow : public WindowBase {
    std::string title;
public:
    HeaderWindow(int h, int w, int y, int x, const std::string& t)
        : WindowBase(h, w, y, x), title(t) {}

    void render() override {
        werase(win);
        drawBorder();

        // Color pair 2 for header
        wattron(win, COLOR_PAIR(2) | A_BOLD);

        int midY = 1;
        int startX = (width - static_cast<int>(title.size())) / 2;
        if (startX < 1) startX = 1;

        mvwprintw(win, midY, startX, "%s", title.c_str());

        wattroff(win, COLOR_PAIR(2) | A_BOLD);
        wrefresh(win);
    }
};

// ---------------------- Message Area Window ----------------------

class MessageArea : public WindowBase {
    const std::vector<std::string>& messages;
    int& scrollOffset; // 0 = bottom, positive = scroll up

public:
    MessageArea(int h, int w, int y, int x,
                const std::vector<std::string>& msgs,
                int& offset)
        : WindowBase(h, w, y, x),
          messages(msgs),
          scrollOffset(offset) {}

    void render() override {
        werase(win);
        drawBorder();

        int innerHeight = height - 2; // leave room for border
        if (innerHeight <= 0) {
            wrefresh(win);
            return;
        }

        int total = static_cast<int>(messages.size());
        int maxVisible = innerHeight;
        int maxScroll = std::max(0, total - maxVisible);
        if (scrollOffset > maxScroll) scrollOffset = maxScroll;
        if (scrollOffset < 0) scrollOffset = 0;

        int startIndex = std::max(0, total - maxVisible - scrollOffset);
        int endIndex   = total;

        int line = 1; // inside border
        wattron(win, COLOR_PAIR(3));

        for (int i = startIndex; i < endIndex && line <= innerHeight; ++i) {
            std::string msg = messages[i];
            if ((int)msg.size() > width - 2) {
                msg = msg.substr(0, width - 3);
                msg.push_back('.');
            }
            mvwprintw(win, line, 1, "%s", msg.c_str());
            ++line;
        }

        wattroff(win, COLOR_PAIR(3));
        wrefresh(win);
    }
};

// ---------------------- Room List Window ----------------------

class RoomListWindow : public WindowBase {
    const std::vector<std::string>& rooms;
    int& selectedIndex;

public:
    RoomListWindow(int h, int w, int y, int x,
                   const std::vector<std::string>& r,
                   int& selected)
        : WindowBase(h, w, y, x), rooms(r), selectedIndex(selected) {}

    void render() override {
        werase(win);
        drawBorder();

        int innerHeight = height - 2;
        wattron(win, COLOR_PAIR(4));

        int line = 1;
        for (int i = 0; i < (int)rooms.size() && line <= innerHeight; ++i) {
            if (i == selectedIndex) {
                wattron(win, A_REVERSE | A_BOLD); // highlight selected room
            }
            std::string roomName = rooms[i];
            if ((int)roomName.size() > width - 2) {
                roomName = roomName.substr(0, width - 3);
                roomName.push_back('.');
            }

            mvwprintw(win, line, 1, "%s", roomName.c_str());

            if (i == selectedIndex) {
                wattroff(win, A_REVERSE | A_BOLD);
            }
            ++line;
        }

        wattroff(win, COLOR_PAIR(4));
        wrefresh(win);
    }
};

// ---------------------- Input Window ----------------------

class InputWindow : public WindowBase {
    std::string& inputBuffer;

public:
    InputWindow(int h, int w, int y, int x, std::string& buffer)
        : WindowBase(h, w, y, x), inputBuffer(buffer) {}

    void render() override {
        werase(win);
        drawBorder();

        wattron(win, COLOR_PAIR(5));

        std::string prompt = " > ";
        mvwprintw(win, 1, 1, "%s", prompt.c_str());

        int maxInputWidth = width - 2 - (int)prompt.size();
        std::string visibleInput = inputBuffer;
        if ((int)visibleInput.size() > maxInputWidth) {
            visibleInput = visibleInput.substr(visibleInput.size() - maxInputWidth);
        }

        mvwprintw(win, 1, 1 + (int)prompt.size(), "%s", visibleInput.c_str());

        wattroff(win, COLOR_PAIR(5));
        wmove(win, 1, 1 + (int)prompt.size() + (int)visibleInput.size());
        wrefresh(win);
    }
};

// ---------------------- Main UI Controller ----------------------

class ChatClientUI {
    HeaderWindow*     header;
    MessageArea*      messageArea;
    RoomListWindow*   roomList;
    InputWindow*      inputArea;

    std::vector<std::string> messages;
    std::vector<std::string> rooms;

    int scrollOffset;
    int selectedRoom;
    std::string inputBuffer;

    int maxY;
    int maxX;

public:
    ChatClientUI()
        : header(nullptr), messageArea(nullptr),
          roomList(nullptr), inputArea(nullptr),
          scrollOffset(0), selectedRoom(0),
          maxY(0), maxX(0) {

        getmaxyx(stdscr, maxY, maxX);

        rooms = {"General", "Sports", "Programming", "Random"};
        messages = {
            "Welcome to the chat!",
            "System: Use Up/Down arrows to change rooms.",
            "System: PageUp/PageDown to scroll messages.",
            "System: Type a message and press Enter to add it.",
            "System: Press 'q' to quit."
        };

        layoutWindows();
    }

    ~ChatClientUI() {
        delete header;
        delete messageArea;
        delete roomList;
        delete inputArea;
    }

    void layoutWindows() {
        int headerHeight = 3;
        int inputHeight  = 3;
        int roomWidth    = std::max(20, maxX / 4);

        int messageHeight = maxY - headerHeight - inputHeight;
        if (messageHeight < 5) messageHeight = 5;

        int messageWidth = maxX - roomWidth;

        delete header;
        delete messageArea;
        delete roomList;
        delete inputArea;

        header = new HeaderWindow(headerHeight, maxX, 0, 0,
                                  "Advanced C++ Chat Client - Demo UI");

        messageArea = new MessageArea(
            messageHeight,
            messageWidth,
            headerHeight,
            0,
            messages,
            scrollOffset
        );

        roomList = new RoomListWindow(
            maxY - headerHeight - inputHeight,
            roomWidth,
            headerHeight,
            messageWidth,
            rooms,
            selectedRoom
        );

        inputArea = new InputWindow(
            inputHeight,
            maxX,
            maxY - inputHeight,
            0,
            inputBuffer
        );
    }

    void render() {
        header->render();
        messageArea->render();
        roomList->render();
        inputArea->render();
    }

    void handleKey(int ch, bool& running) {
        switch (ch) {
            case 'q':
            case 'Q':
                running = false;
                break;

            case KEY_UP:
                if (selectedRoom > 0) {
                    selectedRoom--;
                }
                break;

            case KEY_DOWN:
                if (selectedRoom < (int)rooms.size() - 1) {
                    selectedRoom++;
                }
                break;

            case KEY_PPAGE: // Page Up - scroll messages up
                scrollOffset += 1;
                break;

            case KEY_NPAGE: // Page Down - scroll messages down
                scrollOffset -= 1;
                if (scrollOffset < 0) scrollOffset = 0;
                break;

            case KEY_BACKSPACE:
            case 127:
            case 8:
                if (!inputBuffer.empty()) {
                    inputBuffer.pop_back();
                }
                break;

            case '\n':
            case KEY_ENTER:
                if (!inputBuffer.empty()) {
                    std::string msg = "[" + rooms[selectedRoom] + "] You: " + inputBuffer;
                    messages.push_back(msg);
                    inputBuffer.clear();
                    scrollOffset = 0; // jump back to bottom
                }
                break;

            default:
                if (ch >= 32 && ch <= 126) { // printable ASCII
                    inputBuffer.push_back(static_cast<char>(ch));
                }
                break;
        }
    }
};

// ---------------------- Curses Setup Helpers ----------------------

void initColors() {
    if (!has_colors()) return;

    start_color();
#ifdef NCURSES_VERSION
    use_default_colors();
#endif

    init_pair(1, COLOR_WHITE,   COLOR_BLACK);
    init_pair(2, COLOR_YELLOW,  COLOR_BLUE);   // header
    init_pair(3, COLOR_WHITE,   COLOR_BLACK);  // messages
    init_pair(4, COLOR_CYAN,    COLOR_BLACK);  // rooms
    init_pair(5, COLOR_GREEN,   COLOR_BLACK);  // input
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(1); // show cursor in input area

    initColors();

    ChatClientUI ui;
    ui.render();

    bool running = true;
    while (running) {
        int ch = getch();
        ui.handleKey(ch, running);
        ui.render();
    }

    endwin();
    return 0;
}
