#include <iostream>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <unordered_map>
#include <string>
#include <sstream>
class clock
{
private:
    std::time_t start; //  the start time of the object creation
public:
    std::unordered_map<std::string, int> mp; // alarm where key is the time stored as string and value if the number of times it is snoozed;
    clock()                                  // constructor which stores the time when object was declared
    {
        auto st = std::chrono::system_clock::now();
        start = std::chrono::system_clock::to_time_t(st);
    }
    std::string get_curr_time();        // to get current time
    std::string set_alarm(std::string); // to set the alarm
    std::string del_alarm(std::string); // to delete the alarm
};
std::string clock::get_curr_time()
{
    // this line of code separates time and print only current time

    auto curr_time = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(curr_time);
    std::string ans = std::ctime(&end_time);
    std::stringstream iss(ans);
    std::string word;
    int ct = 0;

    while (iss >> word)
    {
        ct++;
        if (ct == 4)
        {
            ans = word;
        }
    }
    // ans containing only the current time
    return ans;
}
std::string clock::set_alarm(std::string s)
{
    std::stringstream iss(s);
    std::string word;
    std::string ans;
    int ct = 0;

    while (iss >> word)
    {
        ct++;
        if (ct == 4)
        {
            ans = word;
        }
    }
    // searched if the alarm is already present in the map
    if (mp.find(ans) != mp.end())
    {
        return "The alarm is already set for " + s;
    }
    // adds the alarm to the map and set the snooze counter of the alarm as zero
    else
    {
        mp[ans] = 0;
    }

    return "The alarm has been set for " + s;
}
std::string clock::del_alarm(std::string s)
{
    std::stringstream iss(s);
    std::string word;
    std::string ans;
    int ct = 0;

    while (iss >> word)
    {
        ct++;
        if (ct == 4)
        {
            ans = word;
        }
    }

    // searches for the alarm in the map , if found then delete it
    if (mp.find(ans) != mp.end())
    {
        mp.erase(ans);
        return "Alarm for " + s + " has been deleted\n";
    }
    else
    {
        return "Alarm not found\n";
    }
}
void check(std::unordered_map<std::string, int> mp, class clock c1)
{
    // this runs until the map is empty
    while (mp.size() != 0)
    {
        std::string s = c1.get_curr_time();
        char choice;
        // if the alarm is found them ask for snooze or to stop the alarm
        if (mp.find(s) != mp.end())
        {
            for (auto &it : mp)
            {
                std::cout << it.first << std::endl;
            }
            std::cout << "****Ringing **** alarm for " << s << std::endl;
            std::cout << "Press S to Snooze the alarm or Press X to Stop the alarm\n";
            std::cin >> choice;
            if (choice == 'S')
            {
                mp[s]++;
                if (mp[s] >= 3)
                {
                    std::cout << "Cannot Snooze the Alarm " << s << " as maximum snooze limit is reached\n";
                    mp.erase(s);
                }
                else
                {
                    std::string new_s = s;
                    int temp = (s[3] - '0') * 10 + (s[4] - '0') + 5;
                    int carry = temp / 60;
                    carry = carry + (s[0] - '0') * 10 + (s[1] - '0');
                    temp = temp % 60;
                    std::string min = std::to_string(temp);
                    std::string hr = std::to_string(carry);
                    std::cout << min << ' ' << hr << std::endl;
                    if (min.size() > 1)
                    {
                        new_s[3] = min[0];
                        new_s[4] = min[1];
                    }
                    else
                    {
                        new_s[4] = min[0];
                    }
                    if (hr.size() > 1)
                    {
                        new_s[0] = hr[0];
                        new_s[1] = hr[1];
                    }
                    else
                    {
                        new_s[1] = hr[0];
                    }
                    std::cout << new_s << std::endl;
                    mp[new_s] = mp[s];
                    mp.erase(s);
                }
            }
            else if (choice == 'X')
            {
                mp.erase(s);
            }
        }
    }
    return;
}
int main()
{
    // instance of clock class
    class clock c1;
    // current time
    std::cout << "The current time : " << c1.get_curr_time() << std::endl;

    // set alarm
    std::string s;
    std::cout << "Enter the time to set alarm ( For ex-> \"Sun Nov 13 03:17:54 2022\" )";
    std::getline(std::cin, s);
    std::cout << c1.set_alarm(s) << std::endl;

    // deleting an alarm
    std::cout << c1.set_alarm("Sun Nov 13 02:38:48 2022") << std::endl;
    std::cout << c1.del_alarm("Sun Nov 13 02:38:48 2022") << std::endl;

    // this checks for alarms to ring
    check(c1.mp, c1);
    return 0;
}