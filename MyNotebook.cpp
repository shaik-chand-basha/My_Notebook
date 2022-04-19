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
int getNum(int, int);
std::vector<std::string> getAllFileNames(std::string);
void showCursor(bool);
void erasePrint(int, int, int, int);
bool showMessage(std::string, std::string, bool);
void notebook();
void welcome();
void change_name();
void main_menu();
std::string searchBar(std::string);
std::string garbage;
bool cinused = false;
std::string modifyname(std::string);
std::vector<std::string> randomQuote; // threee varible for manipulating quotes globally
std::string oneQuote;
bool quoteMode;

class EncryptDecrypt
{
private:
    int secretkey[18] = {21, 13, 8, 5, 3, 2, 1, 1, 0, 2, 3, 5, 7, 11, 13, 17, 19}; // secret key to encrypt and decrypt

public:
    std::string encrypt(std::string);
    std::string decrypt(std::string);
};
class Privacy : protected EncryptDecrypt
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
class Quotes : public EncryptDecrypt
{
public:
    void quote_menu();
    void readQuotes();
    void quote_viewMenu();
    void changeQuoteMode();
};
class Notes : public EncryptDecrypt
{
private:
    std::string pageOpened;
    std::string noteOpened;
    std::string notespath = "notebook$$files/Notes/notes";

public:
    bool checkNotesExisted(std::string, std::string, bool, bool);
    void notesMenu();
    void addPage();
    void loadPage();
    void loadNotes(std::string, std::string);
    void editNote();
    bool writeNote(std::string, std::string, std::vector<std::string>);
    std::vector<std::string> readNote(std::string, std::string);
    std::vector<std::string> exchangeNote(std::string, std::string, bool, bool);
    std::vector<std::string> recent(std::string, bool, bool);
    void searchPage();
    void searchNote();
    void viewPage();
};
int main()
{
    Notes a;
    // a.searchPage();
    a.notesMenu();
    // searchBar("search results");

    /* system("title MY NOTEBOOK");
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
            showCursor(false);
            welcome();
            showCursor(true);
            std::ifstream fquotemode("notebook$$files/Quotes/quotemode.txt"); // get quote mode because in notebook
            if (fquotemode.is_open())                                         // for random quote quote mode need to be true
            {
                fquotemode >> quoteMode;
            }
            fquotemode.close();
            Quotes a;
            a.readQuotes(); // loading quotes
            main_menu();
        }
        else
        {
            exit(0);
        }
    } */
}
void gotoxy(int x, int y) // for setting cursor position on console
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void showCursor(bool visibility) // to show or hide cursor
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = visibility; // true to show | false to hide cursor
    SetConsoleCursorInfo(out, &cursorInfo);
}
void erasePrint(int x1, int x2, int y1, int y2) // erase from one cordinate to another cordinate
{
    for (int i = y1; i <= y2; i++)
    {
        for (int j = x1; j <= x2; j++)
        {
            gotoxy(j, i);
            std::cout << " ";
        }
    }
}
bool showMessage(std::string msg, std::string colorcode, bool option) // showing some message and taking yes or no
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

        std::cout << "Do you want to continue(Y/N)";
        while (true)
        {
            gotoxy(74, 12);
            returnOption = getch();
            system("color 07");
            if (returnOption == 'Y' || returnOption == 'y')
            {
                system("cls");
                return true;
                break;
            }
            else if (returnOption == 'n' || returnOption == 'N')
            {
                system("cls");
                return false;
                break;
            }
        }
    }
    else
        system("pause");
    system("cls");
    system("color 07");
    return false;
}
std::string modifyname(std::string name)
{
    name = regex_replace(name, std::regex("^ +| +$"), "$1");
    for (int i = 0; i < name.length(); i++)
    {
        if (name[i] == ' ')
        {
            name[i] = '-';
        }
    }
    return name;
}
void notebook() // display on top of page
{
    gotoxy(49, 1);
    std::cout << "MY NOTEBOOK";
    std::string displayQuote = "   ";
    int n;
    if (quoteMode) // selecting random quote
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

    i = 50 - (int)((i - 10) / 2); // based on length quote position shift
    if (i >= 100)
        i = 0;
    gotoxy(i, 3);
    std::cout << displayQuote;
    time_t now = time(0);
    gotoxy(80, 7);
    std::cout << ctime(&now);
}
void welcome() // welcome message if name entered it will show
{
    system("cls");
    system("color 07");
    std::ifstream fname("notebook$$files/Private/name.txt");
    if (!fname.is_open())
    {
        fname.close();
        std::ofstream foname("notebook$$files/Private/name.txt");
        foname.close();
        return welcome();
    }
    else
    {
        std::string name;
        std::getline(fname, name);
        if (name.empty())
        {
            showCursor(true);
            gotoxy(45, 10);
            std::cout << "Enter your name: "; // if name not entered or not set here take

            std::getline(std::cin, name);
            fname.close();
        }

        std::ofstream fname("notebook$$files/Private/name.txt", std::ios::trunc);
        system("cls");
        gotoxy(50, 12);
        std::cout << "welcome " << name;
        fname << name;
        fname.close();
        Sleep(1000);
    }
}
int getNum(int x, int y)
{
    char ch;
    int n;
    int sum = 0;
    int i = 0;
    while (true)
    {
        gotoxy(x + i, y);
        ch = getch();
        n = ch - '0';
        if (ch == 13)
            break;
        if (ch == 8)
        {
            if (i <= 0)
            {
                i = 0;
                continue;
            }
            std::cout << "\b"
                      << " ";
            sum = (sum - ((sum % 100) % 10)) / 10;
            i--;
            continue;
        }

        if (n >= 0 && n <= 9)
        {
            sum = sum * 10 + n;
            std::cout << ch;
            i++;
        }
    }
    return sum;
}
bool checkfile() // it will check file folder exist or not
{
    struct stat buffer; // if file folder not existed then it will create
    char s[] = "notebook$$files";
    if (stat(s, &buffer) == -1)
    {
        mkdir("notebook$$files");
        mkdir("notebook$$files/Notes");
        mkdir("notebook$$files/Notes/notes");
        mkdir("notebook$$files/Private");
        mkdir("notebook$$files/Quotes");
        mkdir("notebook$$files/Tasks");
        mkdir("notebook$$files/Tasks/files");
        mkdir("notebook$$files/Tasks/_$lastfile$_");

        std::ofstream ffile("notebook$$files/Private/name.txt");
        std::ofstream ffile1("notebook$$files/Private/password.txt");
        std::ofstream ffile2("notebook$$files/Quotes/onequote.txt");
        std::ofstream ffile3("notebook$$files/Quotes/quotemode.txt");
        std::ofstream ffile4("notebook$$files/Quotes/quotes.txt");
        std::ofstream ffile5("notebook$$files/Tasks/_$lastfile$_/lastopened.txt");
        std::ofstream ffile6("notebook$$files/Notes/recents.note");
        std::ofstream ffile7("notebook$$files/Close-Window-To-Continue.txt");
        std::ofstream ffile8("notebook$$files/Private/question.txt");
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
std::vector<std::string> getAllFileNames(std::string path)
{
    struct dirent *d;
    std::vector<std::string> allfilenames;
    std::string temp;
    char dir[path.length()];
    std::strcpy(dir, path.c_str());
    DIR *dr;
    dr = opendir(dir);
    if (dr != NULL)
    {
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            temp = d->d_name;
            if (temp == "." || temp == "..")
            {
                continue;
            }
            allfilenames.push_back(temp);
        }
        closedir(dr);
    }
    return allfilenames;
}
std::string EncryptDecrypt::encrypt(std::string encryptTemp) // encrypt the string and return encrypted string
{
    int i;
    int k;
    int key;
    std::string encrypted;
    char str[encryptTemp.length()];
    std::strcpy(str, encryptTemp.c_str());
    for (i = 0, k = 0; i < encryptTemp.length(); i++, k++)
    {
        key = secretkey[k];
        str[i] += key;
        if (k == 16)
            k = 0;
    }
    encrypted = str;
    return encrypted;
}
std::string EncryptDecrypt::decrypt(std::string decryptTemp) // decrypt the string and return decrypted string
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
std::string Privacy::input_password(std::string display, bool showpass) // take input password from the user
{
    system("color 07"); // and return user entered password
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
                std::cout << " " << display; // display here is placeholder sent along with function
            }

            goto here;
        }
        else
        {
            passw[i] = temp;
            if (showpass)
                std::cout << temp; // show password or not sent along with funtion when calling
            else
                std::cout << "X";
        }
        i++;
    }
    passw[i] = '\0';
    std::string s = passw;
    return s;
}
bool Privacy::login() // ask user to enter password if password matched return true else true
{
    showCursor(false);
    system("cls");
    gotoxy(45, 11);
    std::cout << " +================+";
    gotoxy(45, 12);
    std::cout << "|  ENTER PASSWORD  |";
    gotoxy(45, 13);
    std::cout << " +================+";
    std::ifstream fpass("notebook$$files/Private/password.txt");
    if (!fpass.is_open())
    {

        std::ofstream fpass1("notebook$$files/Private/password.txt", std::ios::app);
        fpass1.close();
        fpass.close();
        showMessage("System error!", "04", false);
        system("color 07");
        return false;
    }
    else
    {

        char count = '0';
        fpass >> password;
        fpass.close();
        if (password.empty())
        {
            set_password();
            system("color 07");
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
                    gotoxy(44, 12);
                    std::cout << " |  ENTER PASSWORD  | ";
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
                        std::ifstream securityQuestion("notebook$$files/Private/question.txt");
                        std::string e_securityA;
                        std::string r_securityQ, r_securityA;
                        if (securityQuestion.is_open())
                        {
                            char choice;
                            gotoxy(41, 14);
                            std::cerr << "Did you forgot password(Y/N) "; // if user forgot password then ask to answer security question
                            choice = getch();                             // set by user in main menu
                            if (choice == 'y' || choice == 'Y')
                            {
                                std::getline(securityQuestion, r_securityQ);
                                std::getline(securityQuestion, r_securityA);
                                securityQuestion.close();
                                r_securityQ = decrypt(r_securityQ);
                                r_securityA = decrypt(r_securityA);
                                system("cls");
                                system("color 07");
                                gotoxy(20, 10);
                                std::cout << r_securityQ;
                                showCursor(true);
                                std::getline(std::cin, e_securityA);
                                if (e_securityA == r_securityA)
                                {
                                    gotoxy(34, 12);
                                    std::cout << "Your Password is : \'" << password << "\'";
                                    gotoxy(45, 14);
                                    std::cout << "Please restart";
                                    getch();
                                    system("color 07");
                                    return false;
                                }
                            }
                        }
                        showMessage("For security reasons please login after sometime", "04", false); // if user entered wrong answer to security
                        system("color 07");                                                           // question it wil show and return false
                        return false;
                    }
                    gotoxy(45, 14);
                    std::cerr << "Password incorrect";
                    Sleep(300);
                    gotoxy(44, 12);
                    std::cout << " |  ENTER PASSWORD  | ";
                    gotoxy(43, 14);
                    std::cerr << "                                    ";
                    continue;
                }
            }
        }
    }
    showCursor(true);
    system("color 07");
    return true;
}
void Privacy::set_password() // set password
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
    std::ofstream fpass("notebook$$files/Private/password.txt", std::ios::trunc);
    if (fpass.is_open())
    {
        enterPassW = encrypt(enterPassW);
        fpass << enterPassW;
        fpass.close();
    }
    else
        return;
    Sleep(1000);
    return;
}
void Privacy::change_password() // change password but first ask to enter login password
{
    bool loginsuccess = login();
    if (loginsuccess)
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
        return;
    }
}
void Privacy::security_Question(bool set) // set security quetion or edit security question but when editing
{
    std::string securityQ; // user required to enter password fails to return main menu
    std::string securityA; // user required to enter password fails to return main menu
    system("cls");
    if (set)
    {
        gotoxy(20, 10);
        std::cout << "Enter your question:  ";

        std::getline(std::cin, securityQ);
        if (securityQ.length() == 0)
        {
            return security_Question(true);
        }
        else
        {
            gotoxy(20, 11);
            std::cout << "Enter your Answer:  ";

            std::getline(std::cin, securityA);

            showMessage(securityQ + "=" + securityA, "07", false);
            std::ofstream sq("notebook$$files/Private/question.txt", std::ios::trunc);
            if (sq.is_open())
            {
                securityQ = encrypt(securityQ);
                securityA = encrypt(securityA);
                sq << securityQ << std::endl
                   << securityA;
            }
            sq.close();
        }
    }
    else
    {
        bool loginsuccess = login();
        if (loginsuccess)
        {
            security_Question(true);
            return;
        }
        else
        {
            return;
        }
    }
}
void change_name() // use may change their name without entering password
{
    std::ofstream fname("notebook$$files/Private/name.txt", std::ios::trunc);
    system("cls");
    notebook();
    gotoxy(50, 6);
    std::cout << "Change Name";
    gotoxy(49, 7);
    std::cout << "+===========+";
    gotoxy(30, 10);
    std::cout << "Enter your name: ";
    showCursor(true);
    std::string name;
    std::getline(std::cin, name);
    fname << name;
    gotoxy(45, 14);
    std::cout << "Name changed successfully";
    gotoxy(45, 16);
    system("pause");
    fname.close();
}
std::string searchBar(std::string title)
{
    std::string keyword;
    erasePrint(0, 100, 8, 15);
    gotoxy(40, 10);
    std::cout << "Search ";
    gotoxy(47, 11);
    std::cout << "-----------------------------";
    gotoxy(40, 12);
    std::cout << "(Enter all to get all " << title << " | press R to return )";
    gotoxy(47, 10);
    std::getline(std::cin, keyword);
    if (keyword == "r" || keyword == "R")
    {
        return keyword; /*  */
    }
    if (keyword.length() < 3 || keyword.length() > 30)
    {
        gotoxy(35, 13);
        std::cout << "keyword should be more then 2 characters and less than 30 characters";
        gotoxy(45, 14);
        system("pause");
        return searchBar(title);
    }
    keyword = regex_replace(keyword, std::regex("^ +| +$"), "$1");
    keyword = modifyname(keyword);
    erasePrint(0, 100, 9, 15);
    return keyword;
}
bool Notes::checkNotesExisted(std::string pgname, std::string ntname, bool page, bool create)
{

    pgname = notespath + "/" + pgname;
    struct stat buffer;
    if (page)
    {

        char folder[pgname.length()];
        std::strcpy(folder, pgname.c_str());
        if (stat(folder, &buffer) == -1)
        {
            if (create)
            {
                mkdir(folder);
            }
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        ntname = pgname + "/" + ntname + ".note";
        char noteFile[ntname.length()];
        std::strcpy(noteFile, ntname.c_str());
        if (stat(noteFile, &buffer) == -1)
        {
            if (create)
            {
                std::ofstream filecreate(ntname);
                filecreate.close();
            }
            return false;
        }
        else
        {
            return true;
        }
    }
}
void Notes::notesMenu()
{
    pageOpened = "";

    char choice;
    short index;
    std::vector<std::string> recentPages;
    std::string recentfile;
    std::system("cls");
    std::system("color 07");
    notebook();
    gotoxy(50, 6);
    std::cout << "Notes Menu";
    gotoxy(49, 7);
    std::cout << "+==========+";
    gotoxy(48, 9);
    std::cout << "1.Add Page";
    gotoxy(48, 10);
    std::cout << "2.View Pages";
    gotoxy(48, 11);
    std::cout << "3.Return main menu";
    gotoxy(48, 12);
    std::cout << "4.Exit";
    gotoxy(30, 14);
    std::cout << "Select your option: ";

    recentPages = recent("-1", false, false);
    gotoxy(0, 0);
    gotoxy(40, 16);
    std::cout << "(press  a-" << (char)(recentPages.size() + 96) << " to open recent files)";
choiceselect:
    gotoxy(52, 14);
    choice = getch();
    index = (short)choice - 97;
    if (index >= 0 && index < recentPages.size())
    {
        recentfile = recentPages.at(index);
        std::string dir = notespath + "/" + recentfile;
        char folder[dir.length()];
        std::strcpy(folder, dir.c_str());
        struct stat buffer;
        if (stat(folder, &buffer) != -1)
        {

            pageOpened = recentfile;
            loadPage();
            return notesMenu();
        }
    }
    switch (choice)
    {
    case '1':
        std::cout << "add page";
        addPage();
        pageOpened = "";
        break;
    case '2':
        std::cout << "view page";
        viewPage();
        break;

    case '3':
    {
        std::cout << "Return main menu";
        return main_menu();
        break;
    }
    case '4':
    {
        std::cout << " Do you want to exit(Y/N)";
        char exitchoice;
        exitchoice = getch();
        if (exitchoice == 'n' || exitchoice == 'N')
            return notesMenu();
        else
            exit(0);
        break;
    }
    default:
        goto choiceselect;
    }

    return notesMenu();
}
bool Notes::writeNote(std::string pgname, std::string ntname, std::vector<std::string> writing)
{
    ntname = notespath + "/" + pgname + "/" + ntname + ".note";
    std::ofstream filewriting(ntname);
    std::string tempNotes;
    if (filewriting.is_open())
    {
        for (int i = 0; i < writing.size(); i++)
        {
            tempNotes = writing.at(i);
            tempNotes = encrypt(tempNotes);
            filewriting << tempNotes << std::endl;
        }
        filewriting.close();
        return true;
    }
    else
    {
        filewriting.close();
        return false;
    }
}
std::vector<std::string> Notes::readNote(std::string pgname, std::string ntname)
{
    ntname = notespath + "/" + pgname + "/" + ntname + ".note";
    std::string tempNotes;
    std::vector<std::string> reading;
    std::ifstream ffile(ntname);
    if (ffile.is_open())
    {
        while (!ffile.eof())
        {
            std::getline(ffile, tempNotes);
            tempNotes = decrypt(tempNotes);
            reading.push_back(tempNotes);
        }
    }
    ffile.close();
    return reading;
}
std::vector<std::string> Notes::exchangeNote(std::string pgname, std::string ntname, bool reading, bool edit)
{

    std::string tempNotes;
    std::vector<std::string> readnotes;
    std::string notecopy = ntname;
    ntname = notespath + "/" + pgname + "/" + ntname + ".note";
    if (reading)
    {
        std::ifstream fileread(ntname);
        if (fileread.is_open())
        {
            std::ofstream notepadfile("notebook$$files/Close-Window-To-Continue.txt");
            while (!fileread.eof())
            {
                std::getline(fileread, tempNotes);
                tempNotes = decrypt(tempNotes);
                notepadfile << tempNotes << std::endl;
            }
            fileread.close();
            notepadfile.close();
            std::system("notepad \"notebook$$files/Close-Window-To-Continue.txt\"");
            if (edit)
            {
                return exchangeNote(pgname, notecopy, false, true);
            }
        }
    }
    else
    {
        if (!edit)
            std::system("notepad \"notebook$$files/Close-Window-To-Continue.txt\"");
        std::ifstream reader("notebook$$files/Close-Window-To-Continue.txt");
        if (reader.is_open())
        {

            while (!reader.eof())
            {
                std::getline(reader, tempNotes);
                readnotes.push_back(tempNotes);
            }
        }
        reader.close();
        writeNote(pgname, notecopy, readnotes);
        // std::ofstream writing(ntname);
        // if (writing.is_open())
        //     for (int i = 0; i < readnotes.size(); i++)
        //     {
        //         tempNotes = readnotes.at(i);
        //         tempNotes = encrypt(tempNotes);
        //         writing << tempNotes << std::endl;
        //     }
        // writing.close();
    }
    std::ofstream clearfile("notebook$$files/Close-Window-To-Continue.txt", std::ios::trunc);
    clearfile.close();
    return readnotes;
}
void Notes::loadNotes(std::string pgname, std::string ntname)
{

    if (!checkNotesExisted(pgname, ntname, false, false))
    {
        showMessage("Notes either deleted or doesn't exist", "04", false);
        return;
    }
    std::system("cls");
    std::vector<std::string> fileNote;
    gotoxy(1, 4);
    std::cout << "+==================================================================================================+";
    gotoxy(1, 5);
    std::cout << "                                      " << ntname << "                                            ";
    gotoxy(1, 6);
    std::cout << "+==================================================================================================+";
    gotoxy(50, 3);
    fileNote = readNote(pgname, ntname);
    gotoxy(1, 8);
    for (int i = 0; i < fileNote.size(); i++)
    {
        std::cout << fileNote.at(i) << std::endl;
    }
    char choice;
    gotoxy(0, 0);
    getch();
    system("cls");
}
std::vector<std::string> Notes::recent(std::string filename, bool write, bool deleterecent)
{
    std::vector<std::string> readrecents;
    std::string temp;
    bool checkFile = false;
    std::ifstream ffile("notebook$$files/Notes/recents.note");
    if (ffile.is_open())
    {
        int i = 0;
        while (!ffile.eof())
        {
            std::getline(ffile, temp);
            if (temp.length() > 0)
            {
                if (filename == temp)
                {
                    checkFile = true;
                }
                else
                {
                    readrecents.push_back(temp);
                }
                i++;
                if (i == 10)
                {
                    break;
                }
            }
        }
        ffile.close();
        if (write)
        {
            std::ofstream ffile1("notebook$$files/Notes/recents.note");
            if (!deleterecent)
                ffile1 << filename << std::endl;
            for (int j = 0; j < readrecents.size() && j < 9; j++)
            {
                temp = readrecents.at(j);

                ffile1 << temp << std::endl;
            }
        }

        else
        {

            gotoxy(1, 22);
            std::cout << "+==================================================================================================+";
            gotoxy(1, 23);
            std::cout << "                                         Recent Pages                                               ";
            gotoxy(1, 24);
            std::cout << "+==================================================================================================+";

            for (int i = 0; i < readrecents.size() && i < 10; i++)
            {
                gotoxy(5, 26 + i);
                std::cout << char(i + 97) << ". " << readrecents.at(i);
            }
        }
    }
    ffile.close();
    return readrecents;
}
void Notes::loadPage()
{
    if (pageOpened.length() != 0)
    {
        if (!checkNotesExisted(pageOpened, "-1", true, false))
        {
            showMessage("Page either deleted or doesn't exist", "04", false);
            return;
        }
        char choice;
        std::vector<std::string> filesIn;
        std::vector<std::string> filesInCopy;
        std::string temp;
        std::system("cls");
        std::system("color 07");
        notebook();
        gotoxy(50, 6);
        std::cout << "Page Menu";
        gotoxy(49, 7);
        std::cout << "==========";
        gotoxy(28, 10);
        std::cout << "1.Add Note";
        gotoxy(28, 11);
        std::cout << "2.Read Note";
        gotoxy(28, 12);
        std::cout << "3.Edit Note";
        gotoxy(28, 13);
        std::cout << "4.Rename Note";
        gotoxy(28, 14);
        std::cout << "5.Delete Note";
        gotoxy(58, 10);
        std::cout << "6.Rename Page";
        gotoxy(58, 11);
        std::cout << "7.Delete Page";
        gotoxy(58, 12);
        std::cout << "8.Deep Search";
        gotoxy(58, 13);
        std::cout << "9.Return View Pages";
        gotoxy(30, 15);
        std::cout << "Select your option: ";
        gotoxy(50, 17);
        std::cout << "(press R to return)";
        filesInCopy = getAllFileNames(notespath + "/" + pageOpened);
        for (int i = 0; i < filesInCopy.size(); i++)
        {
            temp = filesInCopy.at(i);
            temp = temp.substr(0, temp.length() - 5);
            filesIn.push_back(temp);
        }
        gotoxy(1, 20);
        std::cout << "+==================================================================================================+";
        gotoxy(1, 21);
        std::cout << "                                       " << pageOpened << "                                               ";
        gotoxy(1, 22);
        std::cout << "+==================================================================================================+";
        for (int i = 0; i < filesIn.size(); i++)
        {
            gotoxy(4, 24 + i);
            std::cout << i + 1 << ".";
            gotoxy(6, 24 + i);
            std::cout << filesIn.at(i);
        }
        gotoxy(0, 0);
        gotoxy(51, 15);
        choice = getch();
        erasePrint(0, 78, 10, 15);
        if (choice == 'R' || choice == 'r')
        {
            erasePrint(0, 200, 20, 24 + filesIn.size());
            return;
        }
        switch (choice)
        {

        case '1':
        {
            addPage();
            // return loadPage();
            break;
        }
        case '2':
        {
            int n;
            gotoxy(20, 12);
            std::cout << "Enter Note number to open: ";
            std::cin >> n;
            /*  */ if (std::cin.fail())
            {
                std::cin.clear();
            }
            std::getline(std::cin, garbage);
            if (n > 0 && n <= filesIn.size())
            {

                std::string ntname = filesIn.at(n - 1);
                gotoxy(38, 13);
                std::cout << "Note name: " << ntname;
                gotoxy(20, 14);
                std::cout << "Do you want to open in notepad(Y/N)";
                char ch = getch();
                if (ch == 'Y' || ch == 'y')
                {
                    exchangeNote(pageOpened, ntname, true, false);
                }
                else
                {
                    loadNotes(pageOpened, ntname);
                }
            }
            else
            {
                showMessage("Note not found", "04", false);
            }
            break;
        }
        case '3':
        {
            gotoxy(20, 12);
            std::cout << "Enter Note number to edit: ";
            int n;
            std::cin >> n;
            if (std::cin.fail())
            {
                std::cin.clear();
            }
            std::getline(std::cin, garbage);
            if (n > 0 && n <= filesIn.size())
            {

                std::string ntname = filesIn.at(n - 1);
                gotoxy(38, 13);
                std::cout << "Note name: " << ntname;
                exchangeNote(pageOpened, ntname, true, true);
            }
            else
            {
                showMessage("Note not found", "04", false);
            }
            break;
        }
        case '4':
        {
            gotoxy(20, 12);
            std::cout << "Enter Note number to rename: ";
            int n;
            std::getline(std::cin, garbage);

            if (n > 0 && n <= filesIn.size())
            {
                std::string old_name = filesIn.at(n - 1);
                std::string new_name;
                gotoxy(38, 13);
                std::cout << "Note name: " << old_name;
                gotoxy(33, 14);
                std::cout << "Enter new Name:";

                while (true)
                {
                    gotoxy(50, 14);

                    std::getline(std::cin, new_name);
                    new_name = modifyname(new_name);
                    if (new_name.length() < 3 || new_name.length() > 30)
                    {
                        gotoxy(30, 15);
                        std::cout << "Name should be more than 2 characters and less than 30 characters";
                        Sleep(300);
                        erasePrint(47, 100, 14, 14);
                        erasePrint(27, 100, 15, 15);
                        continue;
                    }
                    if (checkNotesExisted(pageOpened, new_name, false, false))
                    {
                        gotoxy(40, 15);
                        std::cout << "note already existed try another name";
                        Sleep(300);
                        erasePrint(47, 100, 14, 14);
                        erasePrint(38, 100, 15, 15);
                        continue;
                    }
                    else
                    {
                        std::string oldname = notespath + "/" + pageOpened + "/" + old_name + ".note";
                        std::string newname = notespath + "/" + pageOpened + "/" + new_name + ".note";

                        char old[oldname.length()];
                        char renamesto[newname.length()];
                        std::strcpy(old, oldname.c_str());
                        std::strcpy(renamesto, newname.c_str());
                        if (rename(old, renamesto) == 0)
                        {

                            showMessage("renamed note successfully", "02", false);

                            break;
                        }
                        else
                        {
                            showMessage("System error", "04", false);
                            break;
                        }
                    }
                }
            }
            else
            {
                showMessage("Note not found", "04", false);
            }

            break;
        }
        case '5':
        {
            gotoxy(20, 12);
            std::cout << "Enter Note number to delete: ";
            int n;
            std::cin >> n;
            if (std::cin.fail())
            {
                std::cin.clear();
            }
            std::getline(std::cin, garbage);
            if (n > 0 && n <= filesIn.size())
            {
                std::string ntname = filesIn.at(n - 1);
                gotoxy(38, 13);
                std::cout << "Note name: " << ntname;
                gotoxy(20, 14);
                std::string pathC = notespath + "/" + pageOpened + "/" + ntname + ".note";
                char path[pathC.length()];
                std::strcpy(path, pathC.c_str());
                if (remove(path) == 0)
                {
                    std::system("cls");
                    showMessage("Note deleted successfully", "02", false);
                }
                else
                {
                    showMessage("System error", "04", false);
                }
            }
            else
            {
                showMessage("Note not found", "04", false);
            }
            break;
        }
        case '6':
        {
            std::string pg_newname;
            gotoxy(40, 12);
            std::cout << "Page name: " << pageOpened;
            gotoxy(35, 13);
            std::cout << "Enter new Name:";
            while (true)
            {

                gotoxy(50, 13);
                std::getline(std::cin, pg_newname);
                pg_newname = modifyname(pg_newname);
                if (pg_newname.length() < 3 || pg_newname.length() > 30)
                {
                    gotoxy(30, 15);
                    std::cout << "Name should be more than 2 characters and less than 30 characters";
                    Sleep(300);
                    erasePrint(47, 100, 14, 14);
                    erasePrint(27, 100, 15, 15);
                    continue;
                }

                if (checkNotesExisted(pageOpened, pg_newname, false, false))
                {
                    gotoxy(40, 15);
                    std::cout << "note already existed try another name";
                    Sleep(300);
                    erasePrint(50, 100, 13, 14);
                    erasePrint(38, 100, 15, 15);
                    continue;
                }
                else
                {
                    std::string oldname = notespath + "/" + pageOpened;
                    std::string newname = notespath + "/" + pg_newname;

                    char old[oldname.length()];
                    char renamesto[newname.length()];
                    std::strcpy(old, oldname.c_str());
                    std::strcpy(renamesto, newname.c_str());
                    if (rename(old, renamesto) == 0)
                    {
                        recent(pageOpened, true, true);
                        recent(pg_newname, true, false);
                        showMessage("renamed page successfully", "02", false);
                        pageOpened = pg_newname;
                        Sleep(300);
                        break;
                    }
                    else
                    {
                        showMessage("System error", "04", false);
                        break;
                    }
                }
            }

            break;
        }
        case '7':
        {
            if (showMessage("This will delete Page permanantly", "04", true))
            {
                if (checkNotesExisted(pageOpened, "-1", true, false))
                {
                    std::string pathC = "rmdir /s /q notebook$$files\\Notes\\notes\\" + pageOpened;
                    char path[pathC.length()];
                    std::strcpy(path, pathC.c_str());
                    std::system(path);
                    recent(pageOpened, true, true);
                    pageOpened = "";
                    return;
                }
                else
                {
                    showMessage("Page not found", "04", false);
                }
            }

            break;
        }
        case '8':
        {
            break;
        }
        case '9':
        {
            pageOpened = "";
            return notesMenu();
            break;
        }
        default:
        {
            break;
        }
        }
    }

    return loadPage();
}
void Notes::addPage()
{
    system("cls");
    notebook();
    gotoxy(50, 6);
    std::cout << "Add Page";
    gotoxy(49, 7);
    std::cout << "+=========+";
    char choice;
    std::vector<std::string> readnotes;
    std::vector<std::string> pagenames;
    std::vector<std::string> notenames;
    std::string tempNotes, pagename, notename;
    bool checkdirect = false;
    std::system("color 07");

    if (pageOpened.length() != 0)
    {
        gotoxy(2, 10);
        std::cout << "Enter Page Name: ";
        std::cout << pageOpened;
        pagename = pageOpened;
    }
    else
    {
        pagenames = getAllFileNames(notespath);
        for (int i = 0; i < pagenames.size(); i++)
        {
            gotoxy(100, 12 + i);
            std::cout << "| " << pagenames.at(i);
        }
        while (true)
        {
            gotoxy(2, 10);
            std::cout << "Enter Page Name: ";
            gotoxy(20, 10);
            std::getline(std::cin, pagename);
            if (pagename.length() < 3 || pagename.length() > 30)
            {
                gotoxy(2, 12);
                std::cout << "Name should be more than 2 characters and less than 30 characters";
                getch();
                erasePrint(0, 100, 10, 12);
                continue;
            }
            pagename = modifyname(pagename);

            std::string tempregex;

            for (int i = 0; i < pagenames.size(); i++)
            {
                tempregex = pagenames.at(i);
                if (pagename.find(tempregex) != -1)
                {
                    std::regex finder("^" + tempregex + ".$");
                    if (regex_match(pagename, finder))
                    {
                        pagename = pagename + "_";
                    }
                }
            }

            checkdirect = checkNotesExisted(pagename, "-1", true, true);

            if (checkdirect)
            {

                notenames = getAllFileNames(notespath + "/" + pagename);

                if (notenames.size() == 0)
                {

                    break;
                }
                else
                {
                    gotoxy(2, 11);
                    std::cout << "Page already exist do you want to add Note to this page(Y/N/R) ";
                    choice = getch();
                    if (choice == 'y' || choice == 'Y')
                    {
                        erasePrint(0, 100, 11, 11);
                        break;
                    }
                    else if (choice == 'R' || choice == 'r')
                    {
                        pageOpened = "";
                        return;
                        break;
                    }
                    else
                    {
                        erasePrint(0, 100, 10, 12);
                        continue;
                    }
                }
            }
            else
            {

                break;
            }
        }
    }
    erasePrint(90, 150, 12, 12 + pagenames.size());

    while (true)
    {

        notenames = getAllFileNames(notespath + "/" + pagename);

        for (int i = 0; i < notenames.size(); i++)
        {
            gotoxy(100, 12 + i);
            std::cout << "| " << notenames.at(i);
        }

        gotoxy(2, 11);
        std::cout << "Enter Note Name: ";
        {

            std::getline(std::cin, notename);
            erasePrint(90, 150, 12, 12 + notenames.size());
            notename = modifyname(notename);
            if (notename.length() < 3 || notename.length() > 30)
            {

                gotoxy(2, 12);
                std::cout << "Name should be more than 2 characters and less than 30 characters";
                getch();
                erasePrint(0, 100, 11, 12);
                continue;
            }
            if (checkNotesExisted(pagename, notename, false, true))
            {
                gotoxy(2, 12);
                std::cout << "Note already exist do you want to Edit note(Y/N) ";
                char modifychoice;
                modifychoice = getch();
                if (modifychoice == 'y' || modifychoice == 'Y')
                {
                    erasePrint(0, 100, 12, 12);
                    readnotes = exchangeNote(pagename, notename, true, true);
                    goto comehere;
                }
                else
                {
                    erasePrint(0, 100, 11, 12);
                    notename = "";
                    continue;
                }
            }
            else
            {
                break;
            }
        }
    }

    pageOpened = pagename;
    gotoxy(2, 12);
    std::cout << notename << ": ";
    gotoxy(2, 13);
    std::cout << "Note:select notepad if you want better writing experience";
    gotoxy(2, 14);
    std::cout << "Do you want to open notepad for writing (Y/N)";
    choice = getch();
    erasePrint(0, 100, 13, 14);
    gotoxy(2, 13);
    if (choice == 'y' || choice == 'Y')
    {
        readnotes = exchangeNote(pagename, notename, false, false);
        writeNote(pagename, notename, readnotes);
    comehere:
        for (int i = 0; i < readnotes.size(); i++)
        {
            gotoxy(2, 13 + i);

            std::cout << readnotes.at(i) << std::endl;
        }
    }
    else
    {
        std::string takelines, tempn;
        gotoxy(2, 13);
        std::cout << "Note:Don't use for copy paste";
        std::cout << std::endl;

        std::getline(std::cin, takelines /* ,static_cast<char>(EOF) */);

        readnotes.clear();
        std::stringstream str(takelines);
        while (std::getline(str, tempn, '\n'))
        {
            readnotes.push_back(tempn);
        }

        writeNote(pagename, notename, readnotes);
    }

    recent(pagename, true, false);
    gotoxy(25, 21 + readnotes.size());
    std::cout << "Do you want to add Another note to this page (Y/N) ";
    choice = getch();
    if (choice == 'y' || choice == 'Y')
    {

        // folderOpened = pagename;
        pageOpened = pagename;
        return addPage();
    }
    /*  */
}
void Notes::viewPage()
{
    char choice;
    bool choose;
    system("cls");
    notebook();
    gotoxy(50, 6);
    std::cout << "View Pages";
    gotoxy(49, 7);
    std::cout << "+==========+";
    gotoxy(49, 9);
    std::cout << "1.Search Pages";
    gotoxy(49, 10);
    std::cout << "2.Search Notes";
    gotoxy(49, 11);
    std::cout << "3.Deep Search";
    gotoxy(49, 12);
    std::cout << "4.Return notesmenu";
    gotoxy(40, 14);
    std::cout << "Select your choice ";
    std::vector<std::string> readRecents = recent("-1", false, false);
    gotoxy(0, 0);
    gotoxy(60, 14);
    choice = getch();
    switch (choice)
    {
    case '1':
        searchPage();
        break;
    case '2':
        searchNote();
        break;
    case '3':
        break;
    case '4':
        return notesMenu();
    }
    return viewPage();
}
void Notes::searchPage()
{
    char choice;
    system("cls");
    notebook();
    gotoxy(50, 6);
    std::cout << "Search Page";
    gotoxy(49, 7);
    std::cout << "+===========+";
    std::string keyword = searchBar("Pages");

    if (keyword == "r" || keyword == "R")
    {
        return;
    }
    std::vector<std::string> pagenames = getAllFileNames(notespath);
    std::string temp;
    std::vector<std::string> pagenamesMatched;
    if (keyword == "all")
    {
        pagenamesMatched = pagenames;
    }
    else
        for (int i = 0; i < pagenames.size(); i++)
        {
            temp = pagenames.at(i);

            if (temp.find(keyword) != -1)
            {
                pagenamesMatched.push_back(temp);
            }
        }
    while (true)
    {
        gotoxy(49, 9);
        std::cout << "1.Search again";
        gotoxy(49, 10);
        std::cout << "2.Open Page";
        gotoxy(49, 11);
        std::cout << "3.Return view pages";
        gotoxy(30, 13);
        std::cout << "Select your choice ";

        {

            gotoxy(1, 16);
            std::cout << "+==================================================================================================+";
            gotoxy(1, 17);
            std::cout << "                    Search Results For " << keyword << "   -  " << pagenamesMatched.size() << "     ";
            gotoxy(1, 18);
            std::cout << "+==================================================================================================+";

            for (int i = 0; i < pagenamesMatched.size(); i++)
            {
                gotoxy(2, 19 + i);
                std::cout << i + 1 << ". " << pagenamesMatched.at(i);
            }
            gotoxy(50, 13);
            choice = getch();
            if (choice == '3')
            {
                return;
            }
            else if (choice == '1')
            {
                return searchPage();
            }
            else
            {
                if (pagenamesMatched.size() < 1)
                {
                    break;
                }
                int n;
                while (true)
                {
                    erasePrint(0, 100, 8, 13);
                    gotoxy(40, 12);
                    std::cout << "Enter page number: ";
                    std::cin >> n;
                    if (std::cin.fail())
                    {
                        std::cin.clear();
                    }
                    std::getline(std::cin, garbage);
                    if (n > 0 && n <= pagenamesMatched.size())
                    {
                        pageOpened = pagenamesMatched.at(n - 1);
                        loadPage();
                        notebook();
                        gotoxy(50, 6);
                        std::cout << "Search Page";
                        gotoxy(49, 7);
                        std::cout << "+===========+";
                        break;
                    }
                    else
                    {
                        gotoxy(45, 13);
                        std::cout << "Page not found";
                        getch();
                        continue;
                    }
                }
            }
        }
    }
}
void Notes::searchNote()
{
    char choice;
    std::vector<std::string> pagenames;
    std::vector<std::string> pagenamesMatched;
    std::vector<std::string> notenames;
    std::vector<std::string> notenamesMatched;
    system("cls");
    notebook();
    gotoxy(50, 6);
    std::cout << "Search Note";
    gotoxy(49, 7);
    std::cout << "+===========+";
    std::string keyword = searchBar("Notes");

    if (keyword == "r" || keyword == "R")
    {
        return;
    }

    std::string pgname, ntname, temp1, temp2;
    pagenames = getAllFileNames(notespath);

    for (int i = 0; i < pagenames.size(); i++)
    {
        pgname = pagenames.at(i);
        pgname = notespath + "/" + pgname;
        notenames = getAllFileNames(pgname);
        for (int j = 0; j < notenames.size(); j++)
        {
            temp1 = notenames.at(j);
            if (keyword == "all")
            {
                notenamesMatched.push_back(temp1);
                pagenamesMatched.push_back(pagenames.at(i));
            }
            else if (temp1.find(keyword) != -1)
            {
                notenamesMatched.push_back(temp1);
                pagenamesMatched.push_back(pagenames.at(i));
            }
        }
    }

    while (true)
    {
        gotoxy(49, 9);
        std::cout << "1.Search again";
        gotoxy(49, 10);
        std::cout << "2.Open Page";
        gotoxy(49, 11);
        std::cout << "3.Open Note";
        gotoxy(49, 12);
        std::cout << "4.Return view pages";
        gotoxy(30, 14);
        std::cout << "Select your choice ";

        {

            gotoxy(1, 16);
            std::cout << "+==================================================================================================+";
            gotoxy(1, 17);
            std::cout << "                    Search Results For " << keyword << "   -  " << pagenamesMatched.size() << "             ";
            gotoxy(1, 18);
            std::cout << "+==================================================================================================+";
            for (int i = 0; i < pagenamesMatched.size(); i++)
            {
                gotoxy(2, 19 + i);
                std::cout << i + 1 << ". " << pagenamesMatched.at(i);
                gotoxy(50, 19 + i);
                std::cout << "----" << notenamesMatched.at(i);
            }
            gotoxy(0, 0);
            gotoxy(50, 14);
            choice = getch();
            switch (choice)
            {
            case '1':
            {
                return searchNote();
                break;
            }
            case '2':
            {
                if (pagenamesMatched.size() < 1)
                {
                    break;
                }
                int n;
                while (true)
                {
                    erasePrint(0, 100, 8, 13);
                    gotoxy(40, 12);
                    std::cout << "Enter page number: ";
                    std::cin >> n;
                    if (std::cin.fail())
                    {
                        std::cin.clear();
                    }
                    std::getline(std::cin, garbage);
                    if (n > 0 && n <= pagenamesMatched.size())
                    {
                        pageOpened = pagenamesMatched.at(n - 1);
                        loadPage();
                        break;
                    }
                    else
                    {
                        gotoxy(45, 13);
                        std::cout << "Page not found";
                        getch();
                        continue;
                    }
                }
                notebook();
                gotoxy(50, 6);
                std::cout << "Search Note";
                gotoxy(49, 7);
                std::cout << "+===========+";
                break;
            }
            case '3':
            {
                if (pagenamesMatched.size() < 1)
                {
                    break;
                }
                int n;
                while (true)
                {
                    erasePrint(0, 100, 8, 13);
                    gotoxy(40, 12);
                    std::cout << "Enter note number: ";
                    std::cin >> n;
                    if (std::cin.fail())
                    {
                        std::cin.clear();
                    }
                    std::getline(std::cin, garbage);
                    if (n > 0 && n <= notenamesMatched.size())
                    {
                        temp1 = pagenamesMatched.at(n - 1);
                        // temp1=temp1.substr(0,temp1.length()-5);
                        temp2 = notenamesMatched.at(n - 1);
                        temp2 = temp2.substr(0, temp2.length() - 5);
                        loadNotes(temp1, temp2);
                        break;
                    }
                    else
                    {
                        gotoxy(45, 13);
                        std::cout << "note not found";
                        getch();
                        continue;
                    }
                }
                notebook();
                gotoxy(50, 6);
                std::cout << "Search Note";
                gotoxy(49, 7);
                std::cout << "+===========+";
                break;
            }
            case '4':
            {
                return viewPage();
                break;
            }
            }
        }
    }
    return searchNote();
}
void Quotes::readQuotes() // read quotes
{
    std::ifstream fquote("notebook$$files/Quotes/quotes.txt");
    std::ifstream fquotemode("notebook$$files/Quotes/quotemode.txt");
    std::ifstream fonequote("notebook$$files/Quotes/onequote.txt");

    if (!fquote.is_open() || !fquotemode.is_open() || !fonequote.is_open())
    {
        return;
    }
    else
    {
        char mode;
        std::string tempquote;
        fquotemode >> mode; // get mode from file
        switch (mode)
        {
        case '1':
        {
            std::getline(fonequote, tempquote); // mode 1 means user selected one quote to display
            if (tempquote.length() != 0)
            {
                tempquote = decrypt(tempquote);
                oneQuote = tempquote;
            }
            else
            {
                oneQuote = " ";
            }
            break;
        }
        case '2':
        {
            randomQuote.clear();
            while (!fquote.eof())
            {

                std::getline(fquote, tempquote);
                tempquote = decrypt(tempquote);
                if (!tempquote.empty())
                    randomQuote.push_back(tempquote);
            }

            break;
        }
        }
    }

    fquote.close();
    fonequote.close();
    fquotemode.close();
}
void Quotes::changeQuoteMode()
{
    system("cls");
    notebook();
    std::string getQuote;
    bool selectchoice = true;
    gotoxy(50, 6);
    std::cout << "Quote mode";
    gotoxy(49, 7);
    std::cout << "+==========+";
    gotoxy(48, 9);
    std::cout << "1.One quote";
    gotoxy(48, 10);
    std::cout << "2.Previous One quote";
    gotoxy(48, 11);
    std::cout << "3.Random quote";
    gotoxy(48, 12);
    std::cout << "4.Return quote menu";
    gotoxy(30, 13);
    std::cout << "Select your option:";
    while (selectchoice)
    {
        gotoxy(50, 13);
        char choice = getch();
        switch (choice)
        {
        case '1':
        {

            std::ofstream fquotemode("notebook$$files/Quotes/quotemode.txt", std::ios::trunc);
            std::string templine;
            fquotemode << "1";
            fquotemode.close();
            while (true)
            {
                system("cls");
                gotoxy(15, 10);
                std::cout << "Enter Quote: ";

                std::getline(std::cin, templine);

                if (templine.length() > 150)
                {
                    gotoxy(30, 14);
                    std::cout << "Quote length over 150 characters please Enter less than 150 characters";
                    gotoxy(45, 16);
                    system("pause");
                    continue;
                }
                std::ofstream fquote("notebook$$files/Quotes/onequote.txt", std::ios::trunc);
                if (templine.length() != 0)
                {
                    oneQuote = templine;
                    templine = encrypt(templine);
                    fquote << templine;
                    quoteMode = false;
                }
                fquote.close();
                gotoxy(45, 15);
                std::cout << "Succefully changed quote mode";
                gotoxy(45, 17);
                system("pause");
                break;
            }
            readQuotes();
            selectchoice = false;
            break;
        }
        case '2':
        {
            std::ofstream fquotemode("notebook$$files/Quotes/quotemode.txt", std::ios::trunc);
            quoteMode = false;
            fquotemode << "1";
            selectchoice = false;
            fquotemode.close();
            readQuotes();
            break;
        }
        case '3':
        {
            std::ofstream fquotemode("notebook$$files/Quotes/quotemode.txt", std::ios::trunc);
            quoteMode = true;
            fquotemode << "2";
            selectchoice = false;
            fquotemode.close();
            readQuotes();
            break;
        }
        case '4':
        {
            selectchoice = false;
            break;
        }
        default:
        {
            break;
        }
        }
    }

    return;
}
void Quotes::quote_viewMenu()
{
    char choice;
    bool selectchoice = true;
    system("cls");
    notebook();
    gotoxy(50, 6);
    std::cout << "View Menu";
    gotoxy(49, 7);
    std::cout << "+===========+";
    gotoxy(48, 9);
    std::cout << "1.Add quote";
    gotoxy(48, 10);
    std::cout << "2.Delete quote";
    gotoxy(48, 11);
    std::cout << "3.Return quote menu";
    {
        gotoxy(1, 17);
        std::cout << "_____________________________________________________________________________________";
        for (int i = 0; i < randomQuote.size(); i++)
        {
            gotoxy(1, 19 + i);
            std::cout << i + 1 << "." << randomQuote.at(i);
        }
    }
    while (selectchoice)
    {
        gotoxy(30, 13);
        std::cout << "Select your option: ";
        gotoxy(50, 13);
        choice = getch();
        switch (choice)
        {
        case '1':
        {
            while (true)
            {
                system("cls");
                gotoxy(15, 13);
                std::cout << "Enter Quote: ";
                std::string line;

                std::getline(std::cin, line);
                if (line.empty())
                {
                    gotoxy(50, 15);
                    std::cout << "unable add empty quote";
                }
                else
                {
                    randomQuote.push_back(line);
                }
                gotoxy(40, 16);
                std::cout << "Do you want to add another quote(Y/N): ";
                char quotechoice = getch();
                if (quotechoice == 'n' || quotechoice == 'N')
                {
                    break;
                }
            }
            return quote_viewMenu();
            selectchoice = false;
            break;
        }
        case '2':
        {
            if (randomQuote.size() == 0)
            {
                showMessage("No quotes to delete", "04", false);
                return quote_viewMenu();
                selectchoice = false;
                break;
            }
            while (true)
            {
                erasePrint(0, 75, 9, 15);
                gotoxy(38, 12);
                std::cout << "Enter Quote number: ";
                int n;
                std::cin >> n;
                if (std::cin.fail())
                {
                    std::cin.clear();
                }

                if (n <= 0 || n > randomQuote.size())
                {
                    gotoxy(48, 14);
                    std::cout << "Quote not found";
                }
                else
                {
                    if (n == randomQuote.size() - 1)
                        randomQuote.pop_back();
                    else if (n == 1)
                        randomQuote.erase(randomQuote.begin());
                    else
                        randomQuote.erase(randomQuote.begin() + n - 1);
                    gotoxy(48, 14);
                    std::cout << "Quote deleted successfully";
                }

                break;
            }
            return quote_viewMenu();
            selectchoice = false;
            break;
        }
        case '3':
        {
            selectchoice = false;
            break;
        }
        default:
        {
            break;
        }
        }
    }
    std::string line;
    std::ofstream fquote("notebook$$files/Quotes/quotes.txt", std::ios::trunc);
    if (!randomQuote.empty())
        for (int i = 0; i < randomQuote.size(); i++)
        {
            line = randomQuote.at(i);
            line = encrypt(line);
            fquote << line << std::endl;
        }

    fquote.close();
    return;
}
void Quotes::quote_menu()
{
    {
        std::ifstream fquote("notebook$$files/Quotes/quotes.txt", std::ios::trunc);
        if (fquote.is_open())
        {
            randomQuote.clear();
            std::string tempquote;
            while (!fquote.eof())
            {
                std::getline(fquote, tempquote);
                tempquote = decrypt(tempquote);
                if (!tempquote.empty())
                    randomQuote.push_back(tempquote);
            }
            fquote.close();
        }
    }
    char choice;
    bool selectchoice = true;
    system("cls");
    notebook();
    gotoxy(50, 6);
    std::cout << "Quotes Menu";
    gotoxy(49, 7);
    std::cout << "+===========+";
    gotoxy(48, 9);
    std::cout << "1.Change quote mode";
    gotoxy(48, 10);
    std::cout << "2.View quotes";
    gotoxy(48, 11);
    std::cout << "3.Return main menu";
    gotoxy(30, 13);
    std::cout << "Select your option: ";
    while (selectchoice)
    {
        gotoxy(52, 13);
        choice = getch();
        switch (choice)
        {
        case '1':
        {
            changeQuoteMode();
            selectchoice = false;
            break;
        }
        case '2':
        {
            quote_viewMenu();
            selectchoice = false;
            break;
        }
        case '3':
        {
            return main_menu();
            selectchoice = false;
            break;
        }
        default:
            break;
        }
    }
    return quote_menu();
}
void main_menu()
{
    showCursor(true);
    Privacy p;
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
    gotoxy(30, 17);
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
        Notes notemenu;
        notemenu.notesMenu();
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
        p.change_password();
        break;
    }
    case '4':
    {
        gotoxy(49, 17);
        std::cout << "change security question";
        Sleep(100);
        p.security_Question(false);
        break;
    }

    case '5':
    {
        gotoxy(49, 17);
        std::cout << "Quote menu";
        Quotes q;
        q.quote_menu();
        break;
    }

    case '6':
    {
        gotoxy(49, 17);
        std::cout << "Change Name";
        change_name();
        break;
    }
    case '7':
        gotoxy(49, 17);
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