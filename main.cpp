
#include <iostream>
#include <conio.h>   // für getch()
#include <windows.h>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <cstdlib>
float version = 0.311;


size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}
//Initialize every int var for the programm. I know this can be done much better. Feel free to correct me by making an issue on Github :)

int news = 1;
int checkupdates = 1;
using namespace std;

/*
==============================================================================================================================
Setzt die Position des Cursers um Zeichen zu setzen.
==============================================================================================================================
*/
void SetMyCursor(short x, short y)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hStdOut,pos);
}

// Check for News
void NewsCheck()
{
    remove( "news.txt" );
    system("cls");
    SetMyCursor(0,27);
    cout<<"\nCheck for News!\n\n";
    Sleep(500);

    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url= "http://gaming-ftw.de/veloren/server-configurator/news.txt";
    char outfilename[FILENAME_MAX] = "./news.txt";
    curl = curl_easy_init();
    if (curl)
    {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);

    }
}

void UpdateCheck()
{

ofstream cfgconfig;
    cfgconfig.open ("version.cfg");
    cfgconfig << "Version = " << version;
    cfgconfig.close();







    string versionold;
    ifstream version ("version.cfg");
    if (version.is_open())
    {
        while ( getline (version,versionold) )
        {
        }
        version.close();
    }
     CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url = "http://gaming-ftw.de/veloren/server-configurator/version.cfg";
    char outfilename[FILENAME_MAX] = "version.cfg";
    curl = curl_easy_init();
    if (curl)
    {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }

    string versionneu;



    ifstream versionabfrage ("version.cfg");
    if (versionabfrage.is_open())
    {
        while ( getline (versionabfrage,versionneu) )
        {
        }
        versionabfrage.close();
    }
    if (versionold == versionneu)
    {
        cout << "You already got the newest version. :) " << versionold <<endl;
        Sleep(1000);
        checkupdates = 1;
    }
    else
    {
        char answer;
            cout << "HEY! We found an update.. Do you want to update?" << " 1 = Yes, 2 = No" << endl;
            cin >> answer;

        if (answer == '1')
        {
           ofstream cfgconfig;
        cfgconfig.open ("version.cfg");
        cfgconfig << versionold;
        cfgconfig.close();
        cout << "Current version: " << versionold << endl;
        cout << "New update!" << endl;
        cout << "New version: " << versionneu << endl;
        Sleep(2000);

        cout << "Updating!" << endl;
        Sleep(3000);
         CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url = "http://gaming-ftw.de/veloren/server-configurator/Veloren-server-configurator.exe";
    char outfilename[FILENAME_MAX] = "./Veloren-server-configuratornew.exe";
    curl = curl_easy_init();
    if (curl)
    {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
            cout << "Update complete! :)"<< endl;
            Sleep(3000);
            rename("./Veloren-server-configurator.exe","./Veloren-server-configurator_old.exe");
            rename("./Veloren-server-configuratornew.exe","./Veloren-server-configurator.exe");

             system("start Veloren-server-configurator.exe" ) ;

            exit(0);

        }
        }
        else
        {

            checkupdates = 1;

        }

    }

}


void start()
{

    if (checkupdates == 0)
    {
        if (system("ping -n 1 gaming-ftw.de"))
        {
            system("cls");
            SetMyCursor(0,26);
            cout<<"\nCan't check for updates!\n\n";
            checkupdates = 1;

        }
        else
        {
            system("cls");
            SetMyCursor(0,26);
            cout<<"\nCheck for Update!\n\n";
            UpdateCheck();
            NewsCheck();


        }
    }

    NewsCheck();
    system("cls");
    cout << " ____________________________________________________ " << endl;
    cout << "|Welcome to Veloren-Server-Configurator.             |" << endl;
    cout << "|Please select what you want to do.                  |" << endl;
    cout << "|____________________________________________________|" << endl;           //Start Menü
    cout << "|                                                    |" << endl;
    cout << "|1. Start Server                                     |" << endl;
    cout << "|2. Server Setup                                     |" << endl;
    cout << "|3. Check for updates (DEV BRANCH)                   |" << endl;
    cout << "|4. Exit                                             |" << endl;
    cout << "|____________________________________________________|" << endl;
    cout << "                                                      " << endl;
    SetMyCursor(0,26);      //Text für untere Leiste
    {
        cout << "Server-configurator: V. "<< version << endl ;
    }
    SetMyCursor(0,27);

    string newsinfo;
    ifstream news ("news.txt");
    if (news.is_open())
    {
        while ( getline (news,newsinfo) )
        {
            cout << newsinfo << '\n';
        }
        news.close();
    }
    int zahl;
    SetMyCursor(1,10);
    cin >> zahl;
    if (zahl == 1)          //Bedingung für ausführung der Schleife 1,
    {
        system("start veloren-server-cli.exe " ) ;

    }
    if (zahl == 4)          //Bedingung für ausführung der Schleife 2, beendet das Programm
    {
        exit(0);
    }

    if (zahl == 2)
    {
        string defaultconfig = "test";
        string server_name;
        string server_description;
        string max_players;
        string world_seed;
        string admins;
        string server_address;
        string map_file = "none";
        system("cls");
        cout << "=====================================================" << endl;
        cout << "Configuration:";
        cout << endl << "=====================================================";
        cout << endl << "Server name:";
        getline(cin, server_name);
        getline(cin, server_name);
        cout  << "=====================================================";
        cout << endl << "Server IP:Port:" ;
        getline(cin, server_address);
        cout  << "=====================================================";
        cout << endl << "Server description:" ;
        getline(cin, server_description);
        cout  << "=====================================================";
        cout << endl <<"Max players:";
        getline(cin, max_players);
        cout  << "=====================================================";
        cout << endl << "World Seed:";
        getline(cin, world_seed);
        cout  << "=====================================================";
        cout << endl << "Admins | Please type admins like |--> " << "\"admin1\"" << ", " << "\"admin2\"" << "<--|...  :" << endl;
        getline(cin, admins);
        cout << endl << "=====================================================";
        cout << endl << "Do you want to use own map file? 1 = Yes, 2 = No:";
        int usemap = 2;
        cin >> usemap;
        if (usemap == 1)
        {
            getline(cin, map_file);
            getline(cin, map_file);
        cout  << "=====================================================";
ofstream settings;
        settings.open("settings.ron");
        settings <<
         "(" << '\n' <<
         "gameserver_address: " << "\"" << server_address << "\"" << "," << '\n' <<

         "metrics_address: " << "\"" << "0.0.0.0:14005" << "\"" << "," << '\n' <<

         "server_name: " << "\"" << server_name << "\"" << "," << '\n' <<

         "server_description: " << "\""  << server_description << "\"" << "," << '\n' <<

         "max_players: " << max_players << "," << '\n' <<

         "world_seed: "  << world_seed << "," << '\n' <<

         "start_time: 32400," << '\n' <<

         "admins: [" << '\n' << admins << "," << '\n' << "]," << '\n' <<

         "map_file:" << map_file<< "," << '\n' <<

         ")" ;
         settings.close();
         cout << endl << "Server configuration saved! You can now start the server.";
            getch();
            system("cls");
            start();
        }
        else
        {


        ofstream settings;
        settings.open("settings.ron");
        settings <<
         "(" << '\n' <<
         "gameserver_address: " << "\"" << server_address << "\"" << "," << '\n' <<

         "metrics_address: " << "\"" << "0.0.0.0:14005" << "\"" << "," << '\n' <<

         "server_name: " << "\"" << server_name << "\"" << "," << '\n' <<

         "server_description: " << "\""  << server_description << "\"" << "," << '\n' <<

         "max_players: " << max_players << "," << '\n' <<

         "world_seed: "  << world_seed << "," << '\n' <<

         "start_time: 32400," << '\n' <<

         "admins: [" << '\n' << admins << "," << '\n' << "]," << '\n' <<

         "map_file:" << "None" << "," << '\n' <<

         ")" ;
            settings.close();
            cout << endl << "Server configuration saved! You can now start the server.";
            getch();
            system("cls");
            start();
        }
    }
    if (zahl == 3)          //Updates the program.
        checkupdates=0;
        start();

}


/*
==============================================================================================================================
Das Hauptprogramm wird inizialisiert und führt die unter Programme aus.
==============================================================================================================================
*/
int main()
{
remove( "./Veloren-server-configurator_old.exe" );

    HANDLE console;                                         //Dient zur vergrößerung des Consolen Fensters
    COORD screenBufferSize;
    SMALL_RECT windowSize;
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    screenBufferSize.X = 81;
    screenBufferSize.Y = 29;
    SetConsoleScreenBufferSize(console, screenBufferSize);
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = 80;
    windowSize.Bottom = 30;
    SetConsoleWindowInfo(console, true, &windowSize);


    start();                //Führt das unterprogramm start aus

    return 0;
}












