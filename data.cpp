#include <bits/stdc++.h>
using namespace std;
map<string, set<string>> pre, cur;
#define old_file "old.md"
#define new_file "new.md"
#define result_file "result.html"
string getname(string str)
{
    stringstream ss;
    string title, name;
    ss << str;
    ss >> title >> name;
    return name;
}
void parser(char *path, map<string, set<string>> &cur)
{
    ifstream in(path);
    string str, name;
    while (getline(in, str))
    {
        //cout << str << endl;
        if (!str.length())
            continue;
        else if (str[0] == '#')
            name = getname(str);
        else
            cur[name].insert(str);
    };
    in.close();
}
struct html
{
    string head, tail;
    vector<pair<string, string>> data1, data2, data3;
    void setcols(string s1, string s2)
    {
        head = "<html><body><table border=\"1\" align=\"center\"><tr><th>" + s1 + "</th><th>" + s2 + "</th></tr>";
        tail = "</table></body></html>";
    }
    void print(char *path)
    {
        ofstream out(path);
        setcols("大学", "新增信息");
        out << head << endl;
        for (auto item : data1)
            out << "<tr><th>" << item.first << "</th><th>" << item.second << "</th></tr>" << endl;
        out << tail << endl;
        setcols("大学", "移去信息");
        out << head << endl;
        for (auto item : data2)
            out << "<tr><th>" << item.first << "</th><th>" << item.second << "</th></tr>" << endl;
        out << tail << endl;
        setcols("大学", "目前信息");
        out << head << endl;
        for (auto item : data3)
            out << "<tr><th>" << item.first << "</th><th>" << item.second << "</th></tr>" << endl;
        out << tail << endl;
    }
};
void diff_result(char *path)
{
    html result;
    for (auto item : pre)
    {
        if (cur.count(item.first))
        {
            for (auto info : item.second)
            {
                if (cur[item.first].find(info) == cur[item.first].end())
                    result.data2.push_back({item.first, info});
            }
        }
        else
        {
            for (auto info : item.second)
                result.data2.push_back({item.first, info});
        }
    }
    for (auto item : cur)
    {
        if (pre.count(item.first))
        {
            for (auto info : item.second)
            {
                if (pre[item.first].find(info) == pre[item.first].end())
                    result.data1.push_back({item.first, info});
            }
        }
        else
        {
            for (auto info : item.second)
                result.data1.push_back({item.first, info});
        }
        for (auto info : item.second)
            result.data3.push_back({item.first, info});
    }
    result.print(path);
}
int main()
{
    parser(new_file, cur);
    parser(old_file, pre);
    diff_result(result_file);
    return 0;
}