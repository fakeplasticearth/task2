#include <bits/stdc++.h>
using namespace std;
const char* path;
int n;

bool NotEmpty(const char* p)
{
    ifstream in(p);
    string s;
    if (getline(in, s))
        return 1;
    return 0;
}



int extract_year(string s)
{
    string year = "";
    int i = 0;
    while(s[i]!='(')
        i++;
    i++;
    for (int j = 0;j <= 3;j++)
    {
        year[j] = s[i];
        i++;
    }
    return atoi(year.c_str());
}

void makefiles(int k)
{
    ifstream in(path);
    ofstream out1("output1.txt");
    out1.close();
    ofstream out2("output2.txt");
    out2.close();
    int tmp = 1;
    string film;
    bool f1 = 1, f2 = 1;
    while (1)
    {
        ofstream out1("output1.txt", ios_base::app);
        for (int i = 1;i <= k;i++)
        {
            //in >> num;
            if (getline(in, film))
            {
                if (f1)
                {
                    out1 << film;
                    f1 = 0;
                }
                else
                    out1 << '\n' << film;
            }
            else
            {
                in.close();
                out1.close();
                return;
            }
        }
        out1.close();
        ofstream out2("output2.txt", ios_base::app);
        for (int i = 1;i <= k;i++)
        {
            if (getline(in, film))
            {
                if (f2)
                {
                    out2 << film;
                    f2 = 0;
                }
                else
                    out2 << '\n' << film;
            }
            else
            {
                in.close();
                out2.close();
                return;
            }
        }
        out2.close();
    }
    in.close();
    return;
}




void mergefiles(int k)
{
    int tmp = 0,x;
    ifstream in1("output1.txt");
    ifstream in2("output2.txt");
    ofstream out(path);
    bool first_not_empty = 1;
    bool f = 1;
    while (first_not_empty)
    {
        tmp = 0;
        string filma,filmb;
        int a,b;
        bool f1 = 1,f2 = 1;
        int i1 = 0, i2 = 0;
        while(first_not_empty && tmp < k)
        {
            if (f1)
            {
                f1 = 0;
                if (getline(in1, filma))
                {
                    a = extract_year(filma);
                }
                else
                {
                    first_not_empty = 0;
                    a = 100000;
                }
            }
            if (f2)
            {
                f2 = 0;
                if (getline(in2, filmb))
                {
                    b = extract_year(filmb);
                }
                else
                    b = 100000;
            }
            if (a == 100000 && b == 100000)
            {
                in1.close();
                in2.close();
                out.close();
                return;
            }
            if (a < b)
            {
                if (f)
                {
                    out << filma;
                    f = 0;
                }
                else
                    out << '\n' << filma;
                f1 = 1;
                f2 = 0;
                tmp++;
                i1++;
            }
            else
            {
                if (f)
                {
                    f = 0;
                    out << filmb;
                }
                else
                    out << '\n' << filmb;
                f1 = 0;
                f2 = 1;
                tmp++;
                i2++;
            }
            if (i1 == k / 2)
            {
                f1 = 0;
                a = 100000;
            }
            if (i2 == k / 2)
            {
                f2 = 0;
                b = 100000;
            }
        }
    }
    out.close();
    in1.close();
    in2.close();
    return;
}

int main()
{
    cout << "Enter the name of input file...\n";
    string str;
    cin >> str;
    path = str.c_str();
    ofstream out2("output2.txt");
    out2 << 1;
    out2.close();
    string s = "output2.txt";
    int st = 1;
    while (NotEmpty(s.c_str()))
    {
        makefiles(st);
        st *= 2;
        mergefiles(st);
    }
    return 0;
}
