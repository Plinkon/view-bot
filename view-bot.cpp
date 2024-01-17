#include <iostream>
#include <conio.h>
#include <string>
#include <istream>
#include <fstream>
#include <Windows.h>
#include <tlhelp32.h>

using namespace std;

char key;
int mode;
char startKey, stopKey, manualKey;
wchar_t browserProcess[100] = L"";
std::string url;
int numberOfTabs, sleepTimeInput, sleepTime, timeInput, loopAmount;

void console()
{
    cout << "\033[96m[\033[94m*\033[96m]\033[0m ";
}
void info()
{
    cout << "\033[96m[\033[91m!\033[96m]\033[0m ";
}

bool CloseBrowser(const wchar_t* processName) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return false;

    PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
    if (Process32First(snapshot, &pe32)) {
        do {
            if (wcscmp(pe32.szExeFile, processName) == 0) {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
                if (hProcess) {
                    TerminateProcess(hProcess, 0);
                    CloseHandle(hProcess);
                    CloseHandle(snapshot);
                    return true;
                }
            }
        } while (Process32Next(snapshot, &pe32));
    }

    CloseHandle(snapshot);
    return false;
}

void OpenURL(std::string url)
{
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL); // open url
}

void options()
{
    cout << "\n\n";
    cout << "                          \033[96m|-------|-------|-------|-------|-------|-------|-------|-------|" << endl;
    cout << "                          \033[96m|                            OPTIONS:                           |" << endl;
    cout << "                          |                                                               |" << endl;
    cout << "                          |               (type the number on your keyboard)              |" << endl;
    cout << "                          |                                                               |" << endl;
    cout << "                          \033[94m|   1: HOME                                            \033[94m2: RUN   |" << endl;
    cout << "                          |   --------        \033[94m3: ABOUT        4: GitHub          -------  |" << endl;
    cout << "                          |                   ---------        ----------                 |" << endl;
    cout << "                          \033[2m|                     (developed by plinkon)                    |" << endl;
    cout << "                          |-------|-------|-------|-------|-------|-------|-------|-------|\033[0m" << endl;

}

int main()
{
    console();
    cout << "\033[94mWelcome to the View Bot CLI developed by plinkon\033[0m\n\n";
    info();
    cout << "\033[1;31mIMPORTANT! IN ORDER FOR THIS TO WORK, YOU NEED TO BE LOGGED INTO A DIFFERENT\nACCOUNT THAN THE ACCOUNT WHO POSTED THE VIDEO ON YOUR DEFAULT BROWSER. ALSO MAKE SURE THAT YOUR DEFAULT BROWSER AUTO CLOSES TABS ON CLOSE OTHERWISE THIS WILL NOT WORK.\033[0m\n\n";
    cout << "\033[96m[\033[94mTIP\033[96m]\033[94m: You can navagate the program by typing the numbers 1-4 on your keyboard. Each number goes to a certian menu.\n";
    options();
    while (true)
    {
        key = _getch();

        if (key == '1') // home
        {
            system("cls");
            console();
            cout << "\033[96mHOME:\033[94m\nThis is the home menu, you can go to other menus by typing the correlated number.\nI still don't know what to do with this menu, so it's a WIP";
            options();
        }

        if (key == '2') // run
        {
            system("cls");

            while (true)
            {
                console();
                cout << "\033[96mRUN:\033[94m\nThis is the run menu where the magic happens.\n\n";
                cout << "\033[96mChoose Mode:\n[1] > Manual\n[2] > Loop\n\033[94m[3] > Advanced Loop\n[4] > Timer\n\033[2m[0] > Back\n\033[0m\033[34m";
                cout << "Type the number of the mode you choose: ";
                cin >> mode;

                if (mode == 1) // MANUAL MODE
                {
                    system("cls");
                    cout << "MODE = MANUAL\n-----\n";
                    cout << "Enter URL of video: ";
                    cin >> url;
                    cout << "Enter number of tabs: ";
                    cin >> numberOfTabs;
                    system("cls");
                    cout << "MODE = MANUAL\nPress the letter \"O\" on your keyboard to open " << numberOfTabs << " tabs with the url: " << url;
                    manualKey = _getch();
                    if (manualKey == 'O' || manualKey == 'o')
                    {
                        for (int i = 0; i < numberOfTabs; i++)
                        {
                            OpenURL(url);
                        }

                        cout << "\nProcess Complete!";
                        Sleep(2000);
                        system("cls");
                        main();
                    }
                }

                if (mode == 2) // LOOP MODE
                {
                    system("cls");
                    char startKey, stopKey;
                    wchar_t browserProcess[100] = L"";
                    std::string url;
                    int numberOfTabs, sleepTimeInput, sleepTime;

                    cout << "MODE = LOOP\n-----\n";
                    cout << "Enter URL of video: ";
                    cin >> url;
                    cout << "Enter number of tabs: ";
                    cin >> numberOfTabs;
                    cout << "Enter your default browser's process name: ";
                    wcin >> browserProcess;
                    cout << "Enter the wait time before closing the browser after each loop (seconds): ";
                    cin >> sleepTimeInput;

                    sleepTime = sleepTimeInput * 1000;
                
                    system("cls");
                    cout << "MODE = LOOP\nPress the letter \"O\" on your keyboard to start the loop with the URL: " << url << "\nPress the letter \"P\" on your keyboard to stop the loop";
                    startKey = _getch();

                    if (startKey == 'O' || startKey == 'o')
                    {
                        while (true)
                        {
                            Sleep(100); // Add a short delay to allow time for key press to register
                            if (_kbhit()) // Check if a key is pressed
                            {
                                stopKey = _getch(); // Get the pressed key
                                if (stopKey == 'P' || stopKey == 'p')
                                {
                                    break;
                                }
                            }

                            for (int i = 0; i < numberOfTabs; i++)
                            {
                                OpenURL(url);
                                Sleep(10);
                            }

                            Sleep(sleepTime);
                            CloseBrowser(browserProcess);
                        }

                        cout << "\nLoop Stopped.";
                        Sleep(2000);
                        system("cls");
                        main();
                    }


                }

                if (mode == 3) // ADVANCED LOOP
                {
                    system("cls");
                    cout << "MODE = ADV. LOOP\n-----\n";
                    cout << "Enter URL of video: ";
                    cin >> url;
                    cout << "Enter number of tabs: ";
                    cin >> numberOfTabs;
                    cout << "Enter your default browser's process name: ";
                    wcin >> browserProcess;
                    cout << "Enter the wait time before closing the browser after each loop (seconds): ";
                    cin >> sleepTimeInput;
                    cout << "Enter the amount of loops: ";
                    cin >> loopAmount;

                    sleepTime = sleepTimeInput * 1000;

                    system("cls");
                    cout << "MODE = ADV. LOOP\nPress the letter \"O\" on your keyboard to start the loop " << loopAmount << " times with the URL : " << url << "\nPress the letter \"P\" on your keyboard to stop the loop if nesecary";
                    startKey = _getch();

                    if (startKey == 'O' || startKey == 'o')
                    {
                        for (int i = 0; i < loopAmount; i++)
                        {
                            Sleep(100); // Add a short delay to allow time for key press to register
                            if (_kbhit()) // Check if a key is pressed
                            {
                                stopKey = _getch(); // Get the pressed key
                                if (stopKey == 'P' || stopKey == 'p')
                                {
                                    break;
                                }
                            }

                            for (int i = 0; i < numberOfTabs; i++)
                            {
                                OpenURL(url);
                                Sleep(10);
                            }

                            Sleep(sleepTime);
                            CloseBrowser(browserProcess);
                        }

                        cout << "\nLoop Ended.";
                        Sleep(2000);
                        system("cls");
                        main();
                    }

                }

                if (mode == 4) // TIMER
                {
                    system("cls");
                    int time;
                    // Input parameters from the user
                    std::cout << "MODE = LOOP\n-----\n";
                    std::cout << "Enter URL of video: ";
                    std::cin >> url;
                    std::cout << "Enter number of tabs: ";
                    std::cin >> numberOfTabs;
                    std::cout << "Enter your default browser's process name: ";
                    std::wcin >> browserProcess;
                    std::cout << "Enter the wait time before closing the browser after each loop (seconds): ";
                    std::cin >> sleepTimeInput;
                    std::cout << "Enter time for how long the loop will last (minutes): ";
                    std::cin >> timeInput;

                    sleepTime = sleepTimeInput * 1000;
                    time = timeInput * 60000; // total time the loop should run

                    system("cls");
                    std::cout << "MODE = TIMER\nPress the letter \"O\" on your keyboard to start the timer with the URL: " << url << "\nPress the letter \"P\" on your keyboard to stop the timer";
                    startKey = _getch();

                    if (startKey == 'O' || startKey == 'o')
                    {
                        // Get the current time to calculate the end time of the loop
                        DWORD startTime = GetTickCount64();

                        while (true)
                        {
                            Sleep(100); // Add a short delay to allow time for key press to register
                            if (_kbhit()) // Check if a key is pressed
                            {
                                stopKey = _getch(); // Get the pressed key
                                if (stopKey == 'P' || stopKey == 'p')
                                {
                                    break;
                                }
                            }

                            // Calculate elapsed time
                            DWORD currentTime = GetTickCount64();
                            DWORD elapsedTime = currentTime - startTime;

                            // Check if the total time has elapsed
                            if (elapsedTime >= time)
                            {
                                break;
                            }

                            for (int i = 0; i < numberOfTabs; i++) // this is the loop, make the loop run until the timer "time" runs out
                            {
                                OpenURL(url);
                                Sleep(10);
                            }

                            Sleep(sleepTime);
                            CloseBrowser(browserProcess);
                        }

                        std::cout << "\nLoop Stopped.";
                        Sleep(2000);
                        system("cls");
                        main();
                    }
                }

                if (mode == 0)
                {
                    system("cls");
                    main();
                }
                
                else
                {
                    cout << "Please enter a correct input!";
                    Sleep(1000);
                    system("cls");
                }
            }  
        }

        if (key == '3') // about
        {
            system("cls");
            console();
            cout << "\033[96mABOUT:\033[94m\nThis is a program made entirely by plinkon. It works as a view bot for youtube.\n";
            cout << "It opens a bunch of tabs with a youtube video in the default browser and that video will gain views.\nThe longer you run this program, the more views you get.\n";
            cout << "This program might or might not recive future updates. Who knows, we just have to wait and see.\n";
            cout << "\033[1;31mI TAKE NO RESPONSIBILITY FOR ANYTHING THAT HAPPENS TO ANYONE THAT USES THIS TOOL.\n\n";
            info();
            cout << "\033[1;31mIMPORTANT! IN ORDER FOR THIS TO WORK, YOU NEED TO BE LOGGED INTO A DIFFERENT\nACCOUNT THAN THE ACCOUNT WHO POSTED THE VIDEO ON YOUR DEFAULT BROWSER. ALSO MAKE SURE THAT YOUR DEFAULT BROWSER AUTO CLOSES TABS ON CLOSE OTHERWISE THIS WILL NOT WORK.\n";
            cout << "\n\n\033[94mversion: 1.15";
            options();
        }

        if (key == '4') // github repo
        {
            OpenURL("https://github.com/Plinkon/view-bot");
        }
    }

    return 0;
}
