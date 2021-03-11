#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

int n;
int months[13] = {
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

struct Timer
{
    int year, month, day, hour, minute, week;
    Timer(string str)
    {
        sscanf(str.c_str(), "%04d%02d%02d%02d%02d", &year, &month, &day, &hour, &minute);
    }
    bool operator< (const Timer& t) const
    {
        if (year != t.year) return year < t.year;
        if (month != t.month) return month < t.month;
        if (day != t.day) return day < t.day;
        if (hour != t.hour) return hour < t.hour;
        return minute < t.minute;
    }
    int is_leap()
    {
        if (year % 4 == 0 && year % 100 || year % 400 == 0)
            return 1;
        return 0;
    }
    int get_days()
    {
        if (month == 2) return months[2] + is_leap();
        return months[month];
    }
    void next()
    {
        if ( ++ minute == 60)
        {
            minute = 0;
            if ( ++ hour == 24)
            {
                hour = 0;
                week = (week + 1) % 7;
                if ( ++ day > get_days())
                {
                    day = 1;
                    if ( ++ month > 12)
                    {
                        month = 1;
                        year ++ ;
                    }
                }
            }
        }
    }
    string to_string()
    {
        char str[20];
        sprintf(str, "%04d%02d%02d%02d%02d", year, month, day, hour, minute);
        return str;
    }
};

struct Task
{
    bool minutes[60], hours[24], day_of_month[32], month[13], day_of_week[7];
    string name;
    bool check(Timer& t)
    {
        return minutes[t.minute] && hours[t.hour] && day_of_month[t.day] &&
            month[t.month] && day_of_week[t.week];
    }
}task[20];
unordered_map<string, int> nums;

void init()
{
    string keys[] = {
        "jan", "feb", "mar", "apr", "may", "jun",
        "jul", "aug", "sep", "oct", "nov", "dec",
        "sun", "mon", "tue", "wed", "thu", "fri",
        "sat"
    };
    int values[] = {
        1, 2, 3, 4, 5, 6,
        7, 8, 9, 10, 11, 12,
        0, 1, 2, 3, 4, 5,
        6
    };
    for (int i = 0; i < 19; i ++ )
        nums[keys[i]] = values[i];
}

int get(string str)
{
    if (str[0] >= '0' && str[0] <= '9') return stoi(str);
    string s;
    for (auto c: str) s += tolower(c);
    return nums[s];
}

void work(string str, bool st[], int len)
{
    if (str == "*")
    {
        for (int i = 0; i < len; i ++ ) st[i] = true;
    }
    else
    {
        for (int i = 0; i < str.size(); i ++ )
        {
            int j = i + 1;
            while (j < str.size() && str[j] != ',') j ++ ;
            string s = str.substr(i, j - i);
            i = j;
            int k = s.find('-');
            if (k != -1)
            {
                int l = get(s.substr(0, k)), r = get(s.substr(k + 1));
                for (int u = l; u <= r; u ++ ) st[u] = true;
            }
            else st[get(s)] = true;
        }
    }
}

int main()
{
    init();
    string start, end;
    cin >> n >> start >> end;
    for (int i = 0; i < n; i ++ )
    {
        string minutes, hours, day_of_month, month, day_of_week, name;
        cin >> minutes >> hours >> day_of_month >> month >> day_of_week >> name;
        work(minutes, task[i].minutes, 60);
        work(hours, task[i].hours, 24);
        work(day_of_month, task[i].day_of_month, 32);
        work(month, task[i].month, 13);
        work(day_of_week, task[i].day_of_week, 7);
        task[i].name = name;
    }

    Timer t("197001010000"), S(start), E(end);
    t.week = 4;

    int cnt = 0;
    while (t < E)
    {
        if (!(t < S))
        {
            for (int i = 0; i < n; i ++ )
                if (task[i].check(t))
                    cout << t.to_string() << ' ' << task[i].name << endl;
        }
        t.next();
    }

    return 0;
}