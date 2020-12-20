
#include <cstring>

#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cassert>
using namespace std;

void gotoXY(int x, int y)
{
    //Initialize the coordinates
    COORD coord = {x, y};
    //Set the position
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class LinkNode
{
private:
    char s[300];
    int slength;
    LinkNode *s_next;
    LinkNode *s_last;
public:
    LinkNode();
    LinkNode(char *name, int age);
    void SetNext(LinkNode *n);
    void SetLast(LinkNode *n);
    void Insert(int wz, char c);
    void Delete(int wz);
    void putstring(int wz, char *str, int l);
    void Setlength(int d);
    LinkNode *GetNext();
    LinkNode *GetLast();
    void Show();
    void Show(int wz);
    void change(string line);
    char *GetString();
    int GetLength();

    ~LinkNode();
};

class LinkList
{
private:
    LinkNode *s_head;

    LinkNode *point;

    LinkNode *top;
    int s_sum;

    int wz;
    int hs;
    int zs;

public:
    LinkList();

    void neww();

    void List();

    bool Insert(char c);

    void pageUp();

    void pageDown();

    void Delete();

    void Show();

    void Search();

    void Move(int n);

    int getwz();

    void enter();

    bool open();

    bool save();

    ~LinkList();
};

LinkNode::LinkNode()
{
    slength = 0;
    s_next = NULL;
    s_last = NULL;
}

LinkNode::LinkNode(char *name, int length)
{
    strcpy(s, name);
    slength = length;
    s_next = NULL;
}

void LinkNode::SetNext(LinkNode *n)
{
    s_next = n;
}

void LinkNode::Setlength(int d)
{
    slength = d;
}

void LinkNode::Insert(int wz, char c)
{
    for (int i = slength; i > wz; i--)
        s[i] = s[i - 1];
    s[wz] = c;
    slength++;
}

void LinkNode::Delete(int wz)
{
    for (int i = wz - 1; i < slength; i++)
        s[i] = s[i + 1];
    s[slength - 1] = ' ';
    slength--;
}

void LinkNode::SetLast(LinkNode *n)
{
    s_last = n;
}

LinkNode *LinkNode::GetNext()
{
    return s_next;
}

LinkNode *LinkNode::GetLast()
{
    return s_last;
}

void LinkNode::Show()
{
    for (int i = 0; i < slength; i++)
        cout << s[i];
    cout << endl;
}

void LinkNode::putstring(int wz, char *str, int l)
{
    for (int i = wz; i < l; i++)
        s[slength++] = str[i];
}

void LinkNode::change(string line)
{
    for (int i = 0; i < line.length(); i++)
        s[i] = line[i];
    slength = line.length();
}

void LinkNode::Show(int wz)
{
    for (int i = 0; i < slength; i++)
    {
        if (i == wz)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
            cout << "|";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        cout << s[i];
    }

    if (wz == slength)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        cout << "|";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    cout << endl;
}

char *LinkNode::GetString()
{
    return s;
}

int LinkNode::GetLength()
{
    return slength;
}

LinkNode::~LinkNode()
{
}

LinkList::LinkList()
{
    s_head = new LinkNode;
    s_sum = 0;
    hs = wz = 0;
    zs = 0;
    point = s_head;
    top = s_head;
}

LinkList::~LinkList()
{
}

void LinkList::neww()
{
    point = s_head;
    while (point != NULL)
    {
        LinkNode *mid = point;
        point = point->GetNext();
        delete mid;
    }

    s_head = new LinkNode;
    s_sum = 0;
    hs = wz = 0;
    zs = 0;
    point = s_head;
    top = s_head;
}

bool LinkList::Insert(char c)
{
    if ((point->GetLength()) >= 80)
        return 0;

    LinkNode *p = point;
    point->Insert(wz, c);
    wz++;
    zs++;

    return 1;
}

void LinkList::Delete()
{
    if (point == s_head && wz == 0)
        return;
    if (point != s_head && wz == 0 && point->GetLength() > 0)
    {
        if (point == s_head)
            return;
        LinkNode *mid = point;
        point = point->GetLast();
        char *str = point->GetString();
        int l = point->GetLength();
        char *t = mid->GetString();
        int l1 = mid->GetLength();
        for (int i = l, j = 0; j < l1; j++, i++)
            str[i] = t[j];
        point->Setlength(l + l1);
        wz = l;

        mid->GetNext()->SetLast(point);
        point->SetNext(mid->GetNext());
        hs--;
        delete mid;
        return;
    }

    /*
    if(point==s_head &&point->GetLength()==0)
        return;
*/

    if (point->GetLength() == 0)
    {
        LinkNode *ll = point->GetLast();
        LinkNode *nn = point->GetNext();

        if (point == s_head)
        {
            LinkNode *now = point;
            s_head = nn;
            point = nn;
            top = point;
            delete now;
            hs++;
        }
        else
        {
            ll->SetNext(nn);
            if (nn != NULL)
                nn->SetLast(ll);
            LinkNode *now = point;
            point = ll;
            wz = ll->GetLength();
            if (top == now)
                top = ll;
            delete now;
        }

        wz = point->GetLength();
        hs--;
    }
    else
    {
        point->Delete(wz);
        wz--;
        zs--;
    }
}

void LinkList::pageUp()
{
    int j = 0;
    while (j < 5 && top != s_head)
    {
        j++;
        top = top->GetLast();
        point = point->GetLast();
    }
    hs -= j;
    wz = min(wz, point->GetLength());
}

void LinkList::pageDown()
{
    int j = 0;
    while (j < 5 && point->GetNext() != NULL)
    {
        j++;
        top = top->GetNext();
        point = point->GetNext();
    }
    hs += j;
    wz = min(wz, point->GetLength());
}

void LinkList::Show()
{
    if (top->GetLast() == point)
        top = top->GetLast();
    int j = 0;
    LinkNode *wh = top;
    while (j < 18 && wh != NULL && wh != point)
        wh = wh->GetNext(), j++;
    if (j >= 18)
        top = top->GetNext();
    LinkNode *p = top;
    int i = 0;
    do
    {
        if (p != point)
            p->Show();
        else
            p->Show(wz);
        p = p->GetNext();
        i++;
    } while (p != NULL && i < 20);

    gotoXY(0, 21);

    cout << "                                                      行 " << hs + 1 << " "
         << " 列 " << wz << " 数 " << zs << endl;
}

int LinkList::getwz()
{
    return wz;
}

void LinkList::Move(int n)
{
    //cout<<n<<endl;
    switch (n)
    {
    case 0:
        if (point != s_head)
        {
            point = point->GetLast();
            if (wz > point->GetLength())
                wz = point->GetLength();
            hs--;
        }
        break;

    case 1:
        if (point->GetNext() != NULL)
        {
            point = point->GetNext();
            if (wz > point->GetLength())
                wz = point->GetLength();
            hs++;
        }
        break;

    case 2:
        if (wz > 0)
            wz--;
        else if (wz == 0 && point != s_head)
        {
            point = point->GetLast();
            wz = point->GetLength();
            hs--;
        }
        break;

    case 3:
        if (wz < point->GetLength())
            wz++;
        else if (wz == point->GetLength() && point->GetNext() != NULL)
        {
            point = point->GetNext();
            wz = 0;
            hs++;
        }

    default:
        break;
    }
}

void LinkList::enter()
{
    LinkNode *qt = new LinkNode;
    LinkNode *now = point;
    LinkNode *next = point->GetNext();

    qt->SetNext(next);
    qt->SetLast(now);
    now->SetNext(qt);

    if (next != NULL)
        next->SetLast(qt);
    char *str = point->GetString();
    int l = point->GetLength();
    qt->putstring(wz, str, l);
    for (int i = wz; i < l; i++)
        str[i] = ' ';
    point->Setlength(wz);
    point = qt;
    wz = 0;
    hs++;
}

void LinkList::Search()
{
    cout << "输入你所要查找的字符串" << endl;

    char T[100];

    cin >> T;

    int l = strlen(T);

    int next[100];

    next[0] = -1;

    int j = 0, k = -1;

    while (j < l)
        if (k == -1 || T[j] == T[k])
            next[++j] = ++k;
        else
            k = next[k];

    LinkNode *re = s_head;
    int c = 0;

    do
    {
        char *str = re->GetString();

        int len = re->GetLength();

        int i = 0, j = 0;

        while (i < len && j < l)
        {
            if (j == -1 || str[i] == T[j])
                i++, j++;
            else
                j = next[j];

            if (j == l)
            {
                hs = c;
                wz = i - l;

                point = re;

                top = point->GetLast();

                system("cls");

                Show();
                //cout<<c<<endl;

                cout << "是否往下查找(Y&N)" << endl;

                char c;

                cin >> c;

                if (c != 'Y' && c != 'y')
                    return;

                i++, j = next[j];
            }
        }

        c++;
        re = re->GetNext();

    } while (re != NULL);

    cout << "查找结束（任意键确定）" << endl;
    getchar();
    getchar();
}

bool LinkList::open()
{
    neww();
    cout << "输入所要打开文件的名称" << endl;
    string d;
    cin >> d;
    ifstream in(d.c_str());
    string line;

    if (!in)
    {
        return 0;
    }

    while (getline(in, line))
    {
        point->change(line);
        zs += point->GetLength();
        wz = point->GetLength();
        enter();
    }

    wz = point->GetLength();
    top = point;
    for (int i = 0; i < 10; i++)
        top = top->GetLast();
    in.close();
    return 1;
}

bool LinkList::save()
{
    cout << "输入所要保存的名称" << endl;
    string d;
    cin >> d;
    ofstream out(d.c_str());

    if (!out)
        return 0;

    LinkNode *qqq = s_head;

    do
    {
        for (int i = 0; i < qqq->GetLength(); i++)
            out << qqq->GetString()[i];
        out << endl;
        qqq = qqq->GetNext();
    } while (qqq != NULL);

    out.close();

    return 1;
}

LinkList linkList;
bool runing;

bool cls()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
        return false;
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten))
        return false;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
        return false;

    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten))
        return false;

    if (!SetConsoleCursorPosition(hConsole, coordScreen))
        return false;
}

void getinn()
{
    bool ok = 0, okk = 0;
    int saveok = 0;
    char ch = getch();
    if (ch == -32)
    {
        ch = getch();
        switch (ch)
        {
        case 73:
            linkList.pageUp();
            break;
        case 81:
            linkList.pageDown();
            break;
        case 72:
            linkList.Move(0);
            break;
        case 80:
            linkList.Move(1);
            break;
        case 75:
            linkList.Move(2);
            break;
        case 77:
            linkList.Move(3);
            break;
        default:
            break;
        }
    }
    else if (ch == 13)
        linkList.enter();
    else if (ch == 8)
        linkList.Delete();
    else if (ch == 6)
        linkList.Search();
    else if (ch == 15)
    {
        if (!linkList.open())
            okk = 1;
    }
    else if (ch == 27)
        runing = 0;
    else if (ch == 19)
    {
        if (!linkList.save())
            saveok = 1;
        else
            saveok = -1;
    }
    else if (!linkList.Insert(ch))
        ok = 1;
    cls();
    //system("cls");
    linkList.Show();

    if (ok)
        cout << "输入超限" << endl;

    if (okk)
        cout << "打开失败" << endl;

    if (saveok == 1)
        cout << "保存失败" << endl;

    else if (saveok == -1)
        cout << "保存成功" << endl;
}

int main()
{
    linkList.Show();
    runing = 1;

    while (runing)
    {
        getinn();
    }
    return 0;
}