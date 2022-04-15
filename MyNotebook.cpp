#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <cctype>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <regex>
#include <sys/stat.h>
#include <cstring>
#include <cstdlib>
void gotoxy(int, int);
bool checkfile();
void ShowConsoleCursor(bool);
void notebook();
void welcome();
bool showMessage(std::string, std::string, bool);
void main_menu();
std::vector<std::string> randomQuote;
std::string oneQuote;
bool quoteMode;

class IncryptDecrypt
{
private:
    int secretkey[18] = {21, 13, 8, 5, 3, 2, 1, 1, 0, 2, 3, 5, 7, 11, 13, 17, 19};

public:
    std::string incrypt(std::string);
    std::string decrypt(std::string);
};
class Privacy : protected IncryptDecrypt
{
private:
    std::string password;
    std::string enterPassW;

public:
    bool login();
    std::string input_password(std::string, bool);
    void set_password();
    void change_password();
    void security_Question(bool);
};
int main()
{
    if (!checkfile())
    {
        showMessage("Please Restart", "07", false);
        exit(0);
    }
    else
    {
        Privacy p;
        bool loginsuccess = p.login();
        if (loginsuccess)
        {
            welcome();
            main_menu();
        }
    }
}
void gotoxy(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void ShowConsoleCursor(bool visibility)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = visibility;
    SetConsoleCursorInfo(out, &cursorInfo);
}
bool showMessage(std::string msg, std::string colorcode, bool option)
{
    system("cls");
    gotoxy(50, 10);
    char returnOption;
    std::string setc = "color " + colorcode;
    char setcolor[setc.length()];
    std::strcpy(setcolor, setc.c_str());
    system(setcolor);
    int i = msg.length();
    i = 53 - (int)((i - 10) / 2);
    if (i >= 100)
        i = 0;
    gotoxy(i, 10);
    std::cout << msg;
    gotoxy(45, 12);
    if (option)
    {

        system("Do you want to continue(Y/N)");
        while (true)
        {
            gotoxy(74, 12);
            returnOption = getch();
            if (returnOption == 'Y' || returnOption == 'y')
            {
                return true;
                break;
            }
            else if (returnOption == 'n' || returnOption == 'N')
            {
                return false;
                break;
            }
        }
    }
    else
        system("pause");
    system("color 07");
    return false;
}
void notebook()
{
    gotoxy(49, 1);
    std::cout << "MY NOTEBOOK";
    std::string displayQuote = " ";
    int n;
    if (quoteMode)
    {
        srand(time(0));
        if (randomQuote.size() > 0)
        {
            n = rand() % randomQuote.size();
            displayQuote = randomQuote.at(n);
        }
    }
    else
    {
        displayQuote = oneQuote;
    }
    int i = displayQuote.length();

    i = 50 - (int)((i - 10) / 2);
    if (i >= 100)
        i = 0;
    gotoxy(i, 3);
    std::cout << "\"" << displayQuote << "\"";
    time_t now = time(0);
    gotoxy(80, 7);
    std::cout << ctime(&now);
}
void welcome()
{
    system("cls");
    system("color 07");
    std::ifstream fname("files/Private/name.txt");
    if (!fname.is_open())
    {
        fname.close();
        std::ofstream foname("files/Private/name.txt");
        foname.close();
        return welcome();
    }
    else
    {
        std::string name;
        std::getline(fname, name);
        if (name.empty())
        {
            ShowConsoleCursor(true);
            gotoxy(45, 10);
            std::cout << "Enter your name: ";
            std::getline(std::cin, name);
            fname.close();
        }

        std::ofstream fname("files/Private/name.txt", std::ios::trunc);
        system("cls");
        gotoxy(50, 12);
        std::cout << "welcome " << name;
        fname << name;
        fname.close();
        Sleep(1000);
    }
}
bool checkfile()
{
    struct stat buffer;
    char s[] = "files";
    if (stat(s, &buffer) == -1)
    {
        mkdir("files");
        mkdir("files/Notes");
        mkdir("files/Notes/notes");
        mkdir("files/Private");
        mkdir("files/Quotes");
        mkdir("files/Tasks");
        mkdir("files/Tasks/files");
        mkdir("files/Tasks/_$lastfile$_");

        std::ofstream ffile("files/Private/name.txt");
        std::ofstream ffile1("files/Private/password.txt");
        std::ofstream ffile2("files/Quotes/onequote.txt");
        std::ofstream ffile3("files/Quotes/quotemode.txt");
        std::ofstream ffile4("files/Quotes/quotes.txt");
        std::ofstream ffile5("files/Tasks/_$lastfile$_/lastopened.txt");
        std::ofstream ffile6("files/Notes/recents.note");
        std::ofstream ffile7("files/Close-Window-To-Continue.txt");
        std::ofstream ffile8("files/security/question.txt");
        ffile.close();
        ffile1.close();
        ffile2.close();
        ffile3.close();
        ffile4.close();
        ffile5.close();
        ffile6.close();
        ffile7.close();
        SetFileAttributesA(s, FILE_ATTRIBUTE_HIDDEN);
        return false;
    }
    return true;
}
std::string IncryptDecrypt::incrypt(std::string incryptTemp)
{
    int i;
    int k;
    int key;
    std::string incrypted;
    char str[incryptTemp.length()];
    std::strcpy(str, incryptTemp.c_str());
    for (i = 0, k = 0; i < incryptTemp.length(); i++, k++)
    {
        key = secretkey[k];
        str[i] += key;
        if (k == 16)
            k = 0;
    }
    incrypted = str;
    return incrypted;
}
std::string IncryptDecrypt::decrypt(std::string decryptTemp)
{
    int i;
    int k;
    int key;
    std::string decrypted;
    char str[decryptTemp.length()];
    std::strcpy(str, decryptTemp.c_str());
    for (i = 0, k = 0; i < decryptTemp.length(); i++, k++)
    {
        key = secretkey[k];
        str[i] -= key;
        if (k == 16)
            k = 0;
    }
    decrypted = str;
    return decrypted;
}
std::string Privacy::input_password(std::string display, bool check)
{
    system("color 07");
    bool passEmpty = true;
    int i = 0;
    char passw[10];
    char temp;
    short l = 0;
    while (i < 10)
    {
    here:
        gotoxy(52 + i, 12);
        temp = getch();
        if (passEmpty)
        {
            gotoxy(44, 12);
            std::cout << "|                    |";
            passEmpty = false;
            gotoxy(52 + i, 12);
        }
        if (temp == 13)
        {

            break;
        }
        else if (temp == 8)
        {
            std::cout << "\b"
                      << " ";

            --i;
            if (i <= 0)
            {
                i = 0;
                passEmpty = true;
                gotoxy(44, 12);
                std::cout << " " << display;
            }

            goto here;
        }
        else
        {
            passw[i] = temp;
            if (check)
                std::cout << temp;
            else
                std::cout << "X";
        }
        i++;
    }
    passw[i] = '\0';
    std::string s = passw;

    return s;
}
bool Privacy::login()
{
    system("cls");
    gotoxy(50, 10);
    std::cout << "MY NOTEBOOK";
    gotoxy(45, 11);
    std::cout << " +================+";
    gotoxy(45, 12);
    std::cout << "|  ENTER PASSWORD  |";
    gotoxy(45, 13);
    std::cout << " +================+";
    std::ifstream fpass("files/Private/password.txt");
    if (!fpass.is_open())
    {

        std::ofstream fpass1("files/Private/password.txt", std::ios::app);
        fpass1.close();
        fpass.close();
        showMessage("System error!", "04", false);
        exit(0);
    }
    else
    {

        char count = '0';
        fpass >> password;
        fpass.close();
        if (password.empty())
        {
            set_password();
            return true;
        }
        else
        {
            password = decrypt(password);
            while (true)
            {
                enterPassW = input_password("|  ENTER PASSWORD  | ", false);
                if (enterPassW.length() == 0)
                {
                    continue;
                }
                if (password == enterPassW)
                {
                    system("color 02");
                    Sleep(1000);
                    break;
                }
                else
                {
                    system("color 0C");
                    ++count;
                    if (count == '3')
                    {
                        char choice;
                        gotoxy(41, 14);
                        std::cerr << "Did you forgot password(Y/N) ";
                        choice = getch();
                        if (choice == 'y' || choice == 'Y')
                        {
                            std::ifstream securityQuestion("files/security/question.txt");
                            std::string e_teachername;
                            std::string r_teachername;
                            if (securityQuestion.is_open())
                            {
                                securityQuestion >> r_teachername;
                                r_teachername = decrypt(r_teachername);
                                gotoxy(34, 15);
                                std::cout << "Enter your favourite teacher name: ";
                                std::getline(std::cin, e_teachername);
                                if (e_teachername == r_teachername)
                                {
                                    gotoxy(34, 16);
                                    std::cout << "Your Password is : \'" << password << "\'";
                                    gotoxy(45, 17);
                                    std::cout << "Please restart";
                                    getch();
                                    exit(0);
                                }
                            }
                        }
                        showMessage("For security reasons please login after sometime", "04", false);
                        exit(0);
                    }
                    gotoxy(45, 14);
                    std::cerr << "Password incorrect";
                    Sleep(1000);
                    gotoxy(44, 14);
                    std::cerr << "                       ";
                    continue;
                }
            }
        }
    }

    return true;
}
void Privacy::set_password()
{
    gotoxy(45, 11);
    std::cout << " +================+";
    gotoxy(45, 12);
    std::cout << "|   SET PASSWORD   |";
    gotoxy(45, 13);
    std::cout << " +================+";
    gotoxy(36, 14);
    std::cout << "Enter new Password Maximum 10 characters";
    enterPassW = input_password("|   SET PASSWORD   | ", true);
    gotoxy(36, 14);
    std::cout << "                                             ";
    gotoxy(45, 14);
    std::cout << "Your password is \'" << enterPassW << "\'";
    std::ofstream fpass("files/Private/password.txt", std::ios::trunc);
    if (fpass.is_open())
    {
        enterPassW = incrypt(enterPassW);
        fpass << enterPassW;
        fpass.close();
    }
    else
        return;
    Sleep(1000);
    return;
}
void Privacy::change_password()
{
    system("cls");
    notebook();
    gotoxy(46, 6);
    std::cout << "Change Password";
    gotoxy(44, 7);
    std::cout << " +================+";
    gotoxy(45, 11);
    std::cout << " +================+";
    gotoxy(45, 12);
    std::cout << "|  ENTER PASSWORD  |";
    gotoxy(45, 13);
    std::cout << " +================+";
    std::ifstream fpass("files/Private/password.txt");
    if (!fpass.is_open())
    {
        showMessage("System error!", "04", false);
        return;
    }
    else
    {

        char count = '0';
        fpass >> password;
        fpass.close();

        password = decrypt(password);
        while (true)
        {
            enterPassW = input_password("|  ENTER PASSWORD  | ", false);

            if (password == enterPassW)
            {
                system("color 02");
                Sleep(1000);
                system("cls");
                notebook();
                gotoxy(46, 6);
                std::cout << "Change Password";
                gotoxy(44, 7);
                std::cout << " +================+";
                set_password();
                return;
            }
            else
            {
                system("color 0C");
                ++count;
                if (count == '3')
                {
                    showMessage("For security reasons please try again after sometime", "04", false);
                    return;
                }
                gotoxy(45, 14);
                std::cerr << "Password incorrect";
                Sleep(1000);
                gotoxy(44, 14);
                std::cerr << "                       ";
                continue;
            }
        }
    }
}
void Privacy::security_Question(bool set)
{
    std::string securityQ;
    system("cls");
    if (set)
    {
        gotoxy(30, 10);
        std::cout << "Enter your favourite teacher name:  ";
        gotoxy(45, 11);
        std::getline(std::cin, securityQ);
        if (securityQ.length() == 0)
        {
            return security_Question(true);
        }
        else
        {
            std::ofstream sq("files/security/question.txt", std::ios::trunc);
            if (sq.is_open())
            {
                securityQ = incrypt(securityQ);
                sq << securityQ;
            }
            sq.close();
        }
    }
    else
    {
        system("cls");
        notebook();
        gotoxy(46, 6);
        std::cout << "Security Question";
        gotoxy(44, 7);
        std::cout << " +================+";
        gotoxy(45, 11);
        std::cout << " +================+";
        gotoxy(45, 12);
        std::cout << "|  ENTER PASSWORD  |";
        gotoxy(45, 13);
        std::cout << " +================+";
        std::ifstream fpass("files/Private/password.txt");
        if (!fpass.is_open())
        {

            fpass >> password;
            fpass.close();

            password = decrypt(password);

            enterPassW = input_password("|  ENTER PASSWORD  | ", false);
            if (password == enterPassW)
            {
                security_Question(true);
                return;
            }
            else
            {
                showMessage("Password incorrect Please Try again", "04", false);
                return;
            }
        }
        fpass.close();
    }
}

void main_menu()
{
    system("cls");
    system("color 07");
    notebook();
    gotoxy(50, 6);
    std::cout << "Main Menu";
    gotoxy(49, 7);
    std::cout << "+=========+";
    gotoxy(48, 9);
    std::cout << "1.Notes";
    gotoxy(48, 10);
    std::cout << "2.TaskList";
    gotoxy(48, 11);
    std::cout << "3.Change Password";
    gotoxy(48, 12);
    std::cout << "4.Change security question";
    gotoxy(48, 13);
    std::cout << "5.Quote menu";
    gotoxy(48, 14);
    std::cout << "6.Change Name";
    gotoxy(48, 15);
    std::cout << "7.Exit";
    gotoxy(30, 16);
    std::cout << "Select your option: ";
    char op;
    op = getch();
    switch (op)
    {
    case '1':
    {
        gotoxy(49, 17);
        std::cout << "Notes";
        Sleep(100);
        // Note notemenu;
        // notemenu.noteMenu();
        break;
    }

    case '2':
    {
        gotoxy(49, 17);
        std::cout << "TaskList";
        // tasksheet task;
        // task.taskmenu();
        // Sleep(100);
        break;
    }

    case '3':
    {
        gotoxy(49, 17);
        std::cout << "Change Password";
        Sleep(100);
        Privacy *obj1 = new Privacy();
        obj1->change_password();
        delete obj1;
        break;
    }
    case '4':
    {
        gotoxy(49, 17);
        std::cout << "change security question";
        Sleep(100);
        Privacy *obj1 = new Privacy();
        obj1->security_Question(false);
        delete obj1;
        break;
    }

    case '5':
    {
        gotoxy(49, 17);
        std::cout << "Quote menu";
        // quotes *a = new quotes();
        // a->quote_menu();
        // delete a;
        // Sleep(100);
        break;
    }

    case '6':
    {
        gotoxy(49, 17);
        std::cout << "Change Name";
        // change_name();
        // Sleep(100);
        // return main_menu();
        break;
    }
    case '7':
        gotoxy(49, 16);
        std::cout << "Do you want to exit?(Y/N)";
        op = getch();
        if (op == 'y' || op == 'Y')
        {
            Sleep(100);
            exit(0);
        }
        break;
    default:
        break;
    }
    return main_menu();
}