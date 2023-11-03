#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <ctime>
using namespace std;

#define ull unsigned long long
#define ll long long

const int maxn = 1000;

// 高精度
struct bign
{
    int d[maxn], len;

    void clean()
    {
        while (len > 1 && !d[len - 1])
            len--;
    }

    bign()
    {
        memset(d, 0, sizeof(d));
        len = 1;
    }
    bign(int num) { *this = num; }
    bign(char *num) { *this = num; }
    bign operator=(const char *num)
    {
        memset(d, 0, sizeof(d));
        len = strlen(num);
        for (int i = 0; i < len; i++)
            d[i] = num[len - 1 - i] - '0';
        clean();
        return *this;
    }
    bign operator=(int num)
    {
        char s[20];
        sprintf(s, "%d", num);
        *this = s;
        return *this;
    }
    // 加法
    bign operator+(const bign &b)
    {
        bign c = *this;
        int i;
        for (i = 0; i < b.len; i++)
        {
            c.d[i] += b.d[i];
            if (c.d[i] > 9)
                c.d[i] %= 10, c.d[i + 1]++;
        }
        while (c.d[i] > 9)
            c.d[i++] %= 10, c.d[i]++;
        c.len = max(len, b.len);
        if (c.d[i] && c.len <= i)
            c.len = i + 1;
        return c;
    }
    // 减法
    bign operator-(const bign &b)
    {
        bign c = *this;
        int i;
        for (i = 0; i < b.len; i++)
        {
            c.d[i] -= b.d[i];
            if (c.d[i] < 0)
                c.d[i] += 10, c.d[i + 1]--;
        }
        while (c.d[i] < 0)
            c.d[i++] += 10, c.d[i]--;
        c.clean();
        return c;
    }
    // 乘法
    bign operator*(const bign &b) const
    {
        int i, j;
        bign c;
        c.len = len + b.len;
        for (j = 0; j < b.len; j++)
            for (i = 0; i < len; i++)
                c.d[i + j] += d[i] * b.d[j];
        for (i = 0; i < c.len - 1; i++)
            c.d[i + 1] += c.d[i] / 10, c.d[i] %= 10;
        c.clean();
        return c;
    }
    // 除法
    bign operator/(const bign &b)
    {
        int i, j;
        bign c = *this, a = 0;
        for (i = len - 1; i >= 0; i--)
        {
            a = a * 10 + d[i];
            for (j = 0; j < 10; j++)
                if (a < b * (j + 1))
                    break;
            c.d[i] = j;
            a = a - b * j;
        }
        c.clean();
        return c;
    }
    // 模除
    bign operator%(const bign &b)
    {
        int i, j;
        bign a = 0;
        for (i = len - 1; i >= 0; i--)
        {
            a = a * 10 + d[i];
            for (j = 0; j < 10; j++)
                if (a < b * (j + 1))
                    break;
            a = a - b * j;
        }
        return a;
    }
    // 加等于
    bign operator+=(const bign &b)
    {
        *this = *this + b;
        return *this;
    }
    // 小于
    bool operator<(const bign &b) const
    {
        if (len != b.len)
            return len < b.len;
        for (int i = len - 1; i >= 0; i--)
            if (d[i] != b.d[i])
                return d[i] < b.d[i];
        return false;
    }
    // 大于
    bool operator>(const bign &b) const { return b < *this; }
    // 小于等于
    bool operator<=(const bign &b) const { return !(b < *this); }
    // 大于等于
    bool operator>=(const bign &b) const { return !(*this < b); }
    // 不等于
    bool operator!=(const bign &b) const { return b < *this || *this < b; }
    // 等于
    bool operator==(const bign &b) const { return !(b < *this) && !(b > *this); }

    // 转字符串
    string str() const
    {
        char s[maxn] = {};
        for (int i = 0; i < len; i++)
            s[len - 1 - i] = d[i] + '0';
        return s;
    }
};

// 输入
istream &operator>>(istream &in, bign &x)
{
    string s;
    in >> s;
    x = s.c_str();
    return in;
}
// 输出
ostream &operator<<(ostream &out, const bign &x)
{
    out << x.str();
    return out;
}

// 欧几里得算法
bign gcd(bign a, bign b);
// 扩展欧几里得
ll exGcd(ll a, ll b, ll &x, ll &y);
// bign转ll
ll bign2ll(bign a);
// 求解ax = 1(mod n)
bign mod_reverse(bign a, bign n);
// 中国剩余定理
bign ChineseRemainder(bign a[], bign mod[]);
// 牛顿法开三次方
bign sqrt3(bign x);

int main()
{
    bign e, m;
    cout << "===========小指数加密攻击===========" << endl;
    e = 3;
    bign ni[3];
    bign ci[3];

    cout << "e = 3" << endl;
    // 读入n1, n2, n3并检查是否互素
    while (true)
    {
        cout << "n1 = ";
        cin >> ni[0];
        cout << "n2 = ";
        cin >> ni[1];
        cout << "n3 = ";
        cin >> ni[2];
        if (gcd(ni[0], ni[1]) == 1 && gcd(ni[1], ni[2]) == 1 && gcd(ni[0], ni[2]) == 1)
        {
            break;
        }
        else
        {
            cout << "n1, n2, n3不互素, 请重新输入!" << endl;
        }
    }
    // 读入c1, c2, c3
    cout << "c1 = ";
    cin >> ci[0];
    cout << "c2 = ";
    cin >> ci[1];
    cout << "c3 = ";
    cin >> ci[2];
    cout << endl;
    // 通过中国剩余定理求解明文的三次方
    m = ChineseRemainder(ci, ni);

    // cout << m << endl;

    // 通过牛顿法开三次方求出明文
    cout << "明文m = " << sqrt3(m) << endl;
    cout << endl;
    system("pause");
    return 0;
}

// 欧几里得算法
bign gcd(bign a, bign b)
{
    bign temp;
    while (b > 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// 扩展欧几里得
ll exGcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll r = exGcd(b, a % b, x, y);
    ll temp = x;
    x = y;
    y = temp - a / b * y;
    return r;
}

// bign转ll
ll bign2ll(bign a)
{
    ll res = 0;
    for (int i = a.len - 1; i >= 0; i--)
    {
        res = res * 10 + a.d[i];
    }
    return res;
}
// 求解ax = 1(mod n)
bign mod_reverse(bign a, bign n)
{
    ll d, x, y;
    d = exGcd(bign2ll(a), bign2ll(n), x, y);
    ll lln = bign2ll(n);
    bign res;
    res = (x % lln + lln) % lln;
    if (d = 1)
    {
        return res;
    }
    else
        return -1;
}

// 中国剩余定理
bign ChineseRemainder(bign a[], bign mod[])
{
    bign k = mod[0];
    bign b = 0;
    bign z = 0;
    for (int i = 1; i < 3; i++)
    {
        k = k * mod[i];
    }
    for (int i = 0; i < 3; i++)
    {
        z = mod_reverse((k / mod[i]), mod[i]);
        b = b + (a[i] * (k / mod[i]) * z);
    }
    return b % k;
}

// 牛顿法开三次方
bign sqrt3(bign x)
{
    bign x1 = x;
    bign x2 = x / 2;
    while (x1 - x2 > 0)
    {
        x1 = x2;
        x2 = (x1 * 2 + x / (x1 * x1)) / 3;
    }
    return x2;
}