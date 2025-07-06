#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include<fstream>
using namespace std;

vector<string> getverse(const string& filename)
{
    vector<string> verses;
    ifstream file(filename);
    string line;
    while(getline(file, line))
    {
        if(!line.empty())
        {
            verses.push_back(line);
        }
    }
    return verses;
}
int versetime(int totalverse)
{
   time_t now = time(0);
   tm* mytime = localtime(&now);

   int sec = mytime->tm_sec;

   return sec % totalverse;
}
int userinput()
{
    int user;
    cout << "---Bible Verse Generator---\n\n";
    cout << "1-View verse randomly\n";
    cout << "2-view verse according to clock\n";
    cout << "3-Find word\n";
    cout << "4-View last verse\n";
    cout << "5-Searched words\n";
    cin >> user;
    return user;
}
string readLastLine(const string& filename)
{
    ifstream file(filename);
    string line, lastLine;

    while (getline(file, line)) {
        if (!line.empty()) {
            lastLine = line;  // overwrite until last line
        }
    }
    return lastLine;
}
int main()
{
    srand(time(0));
    time_t now = time(0);
    tm* t = localtime(&now);
    int hour = t->tm_hour;
    int min = t->tm_min;
    int sec = t->tm_sec;
    
    vector<string> verse = getverse("verses.txt");
    if (verse.empty()) {
        cout << " No verses found. Please check verses.txt\n";
        return 1;
    }

    int user = userinput();
    if(user == 1)
    {
        char user1;
        do{
            int num = rand() % verse.size();
            cout << "Verse: " << verse[num] << "\n";
            cout << "\nDo you want another verse(y/n)? ";
            cin >> user1; 
            ofstream file("lastverse.txt");
            if(file.is_open())
            {
                file << verse[num] << endl;
            }
            else{
                cout << "Error opening file(lastverse.txt)\n";
            }
        }while(user1 != 'n');
    }
    else if(user == 2)
    {
        int verseindex = versetime(verse.size());
        if(hour > 5 && hour < 12)
        {
            cout << "Good Morning:)\n";
            cout << "Today's Morning Verse: " << verse[verseindex] << "\n";
            cout << "Time: " << hour << ":" << min << ":" << sec << " AM\n"; 
        }
        else if(hour >= 12 && hour <= 16)
        {
            cout << "Good Afternoon:)\n";
            cout << "Today's Afternoon Verse: " << verse[verseindex] << "\n";
            cout << "Time: " << hour << ":" << min << ":" << sec << " PM\n"; 
        }
        else if(hour >= 17 && hour <= 20)
        {
            cout << "Good Evening:)\n";
            cout << "Today's Evening Verse: " << verse[verseindex] << "\n";
            cout << "Time: " << hour << ":" << min << ":" << sec << " PM\n"; 
        }
        else{
            cout << "Morning verse available at 5:00AM\n";
            cout << "Good Night:)\n";
            cout << "Time: " << hour << ":" << min << ":" << sec << " AM\n"; 
        }
    }
    else if(user == 3)
    {
        string word;
        cout << "Enter word: ";
        cin.ignore();
        getline(cin, word);

        ofstream file("searchedwords.txt");
        if(file.is_open())
        {
            file << word << "\n";
        }
        else{
            cerr << "opening file\n";
        }
        bool found = false;
        for(int i = 0; i < verse.size(); i++)
        {
            if(verse[i].find(word) != string::npos)
            {
                cout << verse[i] << endl;
                found = true;
            }
        }
        if(!found)
        {
            cout << "Word not found in any of the verses\n";
        }
    }
    else if(user == 4)
    {
        {
            string lastLine = readLastLine("lastverse.txt");
            cout << "Last verse: " << lastLine << endl;
        }
    }
    else if(user == 5)
    {
        ifstream file("searchedwords.txt");
        if(file.is_open())
        {
            string line;
            while(getline(file, line))
            {
                cout << line << "\n";
            }
        }
        
    }

    return 0;
}