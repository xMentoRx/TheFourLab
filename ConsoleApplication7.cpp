#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void readFile(string* rS1)
{
    ifstream File("textfile.txt");
    if (!File.is_open())
    {
        cout << "File not open!\n";
        exit(1);
    }
    while (!File.eof())
        getline(File, *rS1);
    File.close();
}

void f_spaces(string* spS1)
{
    int countSpace = 0;
    for (int f_i = 0; (*spS1)[f_i] == ' '; f_i++)
        countSpace++;
    (*spS1).erase(0, countSpace);
    int lenSpS1 = (*spS1).length();
    for (int f_i = 0; f_i < lenSpS1; f_i++)
    {
        if ((*spS1)[f_i] == ' ')
        {
            if ((*spS1)[f_i + 1] == ' ')
            {
                countSpace = 0;
                while ((*spS1)[f_i + countSpace + 1] == ' ')
                    countSpace++;
                (*spS1).erase(f_i + 1, countSpace);
                lenSpS1 = (*spS1).length();
            }
            if (((*spS1)[f_i + 1] == '.') || ((*spS1)[f_i + 1] == ',') || ((*spS1)[f_i + 1] == ';') || ((*spS1)[f_i + 1] == ':') || ((*spS1)[f_i + 1] == '!') || ((*spS1)[f_i + 1] == '?'))
            {
                (*spS1).erase(f_i, 1);
                lenSpS1 = (*spS1).length();
            }
        }
    }
}

void f_punktMarks(string* pmS1)
{
    int countMarks = 0, countPunktMarks = 0;
    for (int i = 0; ((*pmS1)[i] == '.') || ((*pmS1)[i] == '-') || ((*pmS1)[i] == ',') || ((*pmS1)[i] == ';') || ((*pmS1)[i] == ':') || ((*pmS1)[i] == '!') || ((*pmS1)[i] == '?'); i++)
        countPunktMarks++;
    (*pmS1).erase(0, countPunktMarks);
    int lenSpS1 = (*pmS1).length();
    for (int i = 0; i < lenSpS1; i++)
    {
        if (((*pmS1)[i] == '.') || ((*pmS1)[i] == '-') || ((*pmS1)[i] == ',') || ((*pmS1)[i] == ';') || ((*pmS1)[i] == ':') || ((*pmS1)[i] == '!') || ((*pmS1)[i] == '?'))
        {
            char mark = (*pmS1)[i];
            countMarks = 0;
            while (((*pmS1)[i + countMarks + 1] == '.') || ((*pmS1)[i + countMarks + 1] == '-') || ((*pmS1)[i + countMarks + 1] == ',') || ((*pmS1)[i + countMarks + 1] == ':') || ((*pmS1)[i + countMarks + 1] == '?') || ((*pmS1)[i + countMarks + 1] == '!') || ((*pmS1)[i + countMarks + 1] == ';'))
                countMarks++;
            countPunktMarks = 0;
            while ((*pmS1)[i + countPunktMarks + 1] == mark)
                countPunktMarks++;
            if ((*pmS1)[i] == '.' && countPunktMarks + 1 >= 3)
            {
                (*pmS1).erase(i + 3, countMarks - 2);
                lenSpS1 = (*pmS1).length();
                i += 2;
                continue;
            }
            (*pmS1).erase(i + 1, countMarks);
            lenSpS1 = (*pmS1).length();
        }
    }
}

void f_letters(string* letS1)
{
    int lenSpS1 = (*letS1).length();
    if ((*letS1)[0] <= 'z' && (*letS1)[0] >= 'a')
        (*letS1)[0] -= 32;
    for (int i = 1; i < lenSpS1; i++)
    {
        if (((*letS1)[i] <= 'Z' && (*letS1)[i] >= 'A') && ((*letS1)[i - 1] != ' '))
            (*letS1)[i] += 32;
        else if ((i >= 2) && ((*letS1)[i] <= 'z' && (*letS1)[i] >= 'a') && (((*letS1)[i - 2] == '.') || ((*letS1)[i - 2] == '!') || ((*letS1)[i - 2] == '?')))
            (*letS1)[i] -= 32;
    }
}

void getstring(string* s1, int* f_exit)
{
    int getStringMenu;
    cout << "What operation you want to perform? Enter a number from 0 to 2:\n"
        << "1 - Fill string from console\n"
        << "2 - Fill string from file\n"
        << "0 - Exit\n" << endl;
    cin >> getStringMenu;
    switch (getStringMenu)
    {
    case 1:
        cin.ignore();
        getline(cin, *s1);
        break;
    case 2:
        readFile(s1);
        break;
    case 0:
        (*f_exit)++;
        return;
    default:
        cout << "Error! Repeat, please.\n\n";
        system("Pause");
        getstring(s1, f_exit);
        break;
    }
}

void check(string* s1)
{
    f_spaces(s1);
    f_punktMarks(s1);
    f_spaces(s1);
    f_letters(s1);
}

void doubleLetterWords(string dlwS1)
{
    int startWord = 0, endWord = 0, lenDLWS1 = dlwS1.length();
    for (int i = 0; i < lenDLWS1 - 1; i++)
    {
        startWord = i;
        while ((dlwS1[i] >= 'A' && dlwS1[i] <= 'Z') ||
            (dlwS1[i] >= 'a' && dlwS1[i] <= 'z') ||
            (dlwS1[i] >= '0' && dlwS1[i] <= '9'))
            i++;
        endWord = i - 1;
        for (int j = startWord; j < endWord; j++)
        {
            for (int k = j + 1; k <= endWord; k++)
            {
                if ((dlwS1[j] == dlwS1[k]) && ((dlwS1[j] >= 'A' && dlwS1[j] <= 'Z') || (dlwS1[j] >= 'a' && dlwS1[j] <= 'z')))
                {
                    cout << '{';
                    for (int m = startWord; m <= endWord; m++)
                        cout << dlwS1[m];
                    cout << "} ";
                    j = endWord;
                    break;
                }
            }
        }
        while ((i < lenDLWS1 - 1) && (dlwS1[i] != ' '))
            i++;
    }
}

void printNumLetters(string pnlS1)
{
    int lenPNLS1 = pnlS1.length();
    char letter;
    for (int i = 0; i < lenPNLS1; i++)
    {
        letter = pnlS1[i];
        if (pnlS1[i] >= '0' && pnlS1[i] <= '9')
            letter = pnlS1[i] + 48;
        cout << letter;
    }
}

void line_search(string lsS1)
{
    string sString;
    cout << "Input string\n";
    cin.ignore();
    getline(cin, sString);
    int endString = sString.length();
    int endLSS1 = lsS1.length();
    if (endString == 0 || endLSS1 < endString)
    {
        cout << "Error, repeat please!";
        system("Pause");
        sString.erase(0, endString);
        line_search(lsS1);
        return;
    }
    int j, flag_str = 0;
    for (int i = 0; i < endLSS1 - endString + 1; i++)
    {
        for (j = 0; j < endString; j++)
        {
            if (lsS1[i + j] != sString[j])
                break;
            if ((lsS1[i + j] == sString[j]) && (j == endString - 1))
            {
                cout << "String found. Position from " << i + 1 << " to " << i + endString << '\n';
                flag_str++;
                break;
            }
        }
    }
    if (!flag_str)
        cout << "String not found.\n";
}

void search_Moor(string sMS1)
{
    int lastLetter = 0, i = 0, tabl[100], flag_str = 0;
    string sString;
    cout << "Input string\n";
    cin.ignore();
    getline(cin, sString);
    int endString = sString.length();
    int endsMS1 = sMS1.length();
    if (endString == 0 || endsMS1 < endString)
    {
        cout << "Error, repeat please!";
        system("Pause");
        sString.erase(0, endString);
        search_Moor(sMS1);
        return;
    }
    if (endString == 1)
        tabl[0] = 1;
    else
        tabl[endString - 2] = 1;
    for (i = endString - 3; i >= 0; i--)
    {
        int j = i;
        while (sString[i] != sString[j + 1] && j < endString - 2)
            j++;
        if (sString[i] == sString[j + 1])
            tabl[i] = tabl[j + 1];
        else
            tabl[i] = endString - 2 - i + 1;
    }
    for (i = 0; i < endString - 1; i++)
    {
        if (sString[i] == sString[endString - 1])
        {
            tabl[endString - 1] = tabl[i];
            break;
        }
    }
    if (i == endString - 1)
        tabl[i] = endString;
    i = endString - 1;
    while (i < endsMS1)
    {
        int j = endString - 1;
        lastLetter = i;
        for (j; j >= 0; j--)
        {
            if (sString[j] != sMS1[i])
            {
                break;
            }
            i--;
        }
        i = lastLetter;
        if (j >= 0)
        {
            i = lastLetter;
            j = endString - 1;
            for (j; j >= 0; j--)
            {
                if (sString[j] == sMS1[i])
                {
                    i += tabl[j];
                    break;
                }
            }
            if (j < 0)
            {
                i += endString;
            }
        }
        else
        {
            cout << "String found. Position from " << lastLetter - endString + 2 << " to " << lastLetter + 1 << '\n';
            i++;
            flag_str++;
        }
    }
    if (!flag_str)
        cout << "String not found";
}

void search(string schS1)
{
    int getSearchMenu;
    cout << "\nLet's search for a substring in a string. Enter a number from 0 to 2:\n"
        << "1 - Linear search\n"
        << "2 - Boyer-Moore search\n"
        << "0 - Exit\n" << endl;
    cin >> getSearchMenu;
    switch (getSearchMenu)
    {
    case 1:
        cout << "\nOriginal text:\n" << schS1 << "\n\n";
        line_search(schS1);
        cout << '\n';
        search(schS1);
        break;
    case 2:
        cout << "\nOriginal text:\n" << schS1 << "\n\n";
        search_Moor(schS1);
        cout << '\n';
        search(schS1);
        break;
    case 0:
        break;
    default:
        cout << "Error! Repeat, please.\n\n";
        system("Pause");
        search(schS1);
        break;
    }
}

void menu4()
{
    int flag_exit = 0;
    string text;
    getstring(&text, &flag_exit);
    if (flag_exit)
        return;
    while (text.length() == 0)
    {
        cout << "Error! Repeat, please.\n\n";
        system("Pause");
        getstring(&text, &flag_exit);
        if (flag_exit)
            return;
    }
    cout << "Received text:\n" << text << "\n\n";
    system("Pause");
    check(&text);
    cout << "\nText after editing:\n" << text << "\n\n";
    system("Pause");
    cout << "\nWords which have the same letters:\n";
    doubleLetterWords(text);
    cout << "\n\n";
    system("Pause");
    cout << "\nText after changing numbers to letters:\n\n";
    printNumLetters(text);
    cout << "\n\n";
    system("Pause");
    search(text);
    system("Pause");
}
int main()
{
    menu4();
    return 0;

}