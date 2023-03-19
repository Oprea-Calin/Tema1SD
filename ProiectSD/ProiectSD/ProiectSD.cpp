#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
using namespace std;
namespace ranges
{
    template<typename Range, typename Generator>
    void generate(Range& range, Generator generator)
    {
        return std::generate(begin(range), end(range), generator);
    }
}
class RandomNumberBetween
{
public:
    RandomNumberBetween(int low, int high)
        : random_engine_{ std::random_device{}() }
        , distribution_{ low, high }
    {
    }
    int operator()()
    {
        return distribution_(random_engine_);
    }
private:
    std::mt19937 random_engine_;
    std::uniform_int_distribution<int> distribution_;
};

bool test_sort(vector <int> v, int n)
{
    int i, ok = 1;
    for (i = 1; i < n; i++)
    {
        if (v[i] > v[i + 1])
        {
            ok = 0;
        }
    }
    if (ok == 1)
        return 1;
    else
        return 0;
}
void generareExemplu(string TT, long long N, vector <int>& v, int M)
{
    if (TT == "R")
    {
        std::generate_n(std::back_inserter(v), N + 10, RandomNumberBetween(1, M));
    }
    if (TT == "C")
    {
        long long i;
        int j;
        for (i = 1; i <= N + 1; i++)
            v.push_back(j);
    }
}
void merg(vector<int>& v, int st, int m, int dr)
{
    int n1 = m - st + 1, n2 = dr - m;
    vector<int> ST;
    vector<int> DR;
    for (int i = 0; i < n1; i++)
        ST.push_back(v[st + i]);
    for (int j = 0; j < n2; j++)
        DR.push_back(v[m + 1 + j]);
    int i = 0, j = 0, k = st;
    while (i < n1 && j < n2)
    {
        if (ST[i] <= DR[j])
        {
            v[k] = ST[i];
            i++;
        }
        else
        {
            v[k] = DR[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        v[k] = ST[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        v[k] = DR[j];
        j++;
        k++;
    }
}
int Maxi(vector<int>& v, int n)
{
    int maxi = v[1];
    for (int i = 1; i < n; i++)
        if (v[i] > maxi)
            maxi = v[i];
    return maxi;
}
void RadixCountSort(vector<int>& v, int n, int exp)
{
    int i;
    vector<int> op;
    for (i = 1; i <= n; i++)
        op.push_back(0);
    int c[10] = {};
    for (i = 1; i <= n; i++)
        c[(v[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        c[i] += c[i - 1];
    for (i = n; i > 0; i--)
    {
        op[c[(v[i] / exp) % 10]] = v[i];
        c[(v[i] / exp) % 10]--;
    }
    for (i = 1; i <= n; i++)
        v[i] = op[i];
}
void RadixSort(vector<int>& v, int n)
{
    int m = Maxi(v, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        RadixCountSort(v, n, exp);
}

void radix_sort(std::vector<int>& arr)
{
    int radix = 1;
    int max = *(std::max_element(arr.begin(), arr.end()));
    while (max / radix)
    {
        std::vector<std::vector<int>> buckets(10, std::vector<int>());
        for (const auto& num : arr)
        {
            int digit = num / radix % 10;
            buckets[digit].push_back(num);
        }
        std::size_t k = 0;
        for (std::size_t i = 0; i < 10; i++)
        {
            for (std::size_t j = 0; j < buckets[i].size(); j++)
            {
                arr[k] = buckets[i][j];
                k++;
            }
        }
        radix *= 10;
    }

}

void MergeSort(vector<int>& v, int st, int dr)
{
    if (st >= dr)
    {
        return;
    }
    int m = st + (dr - st) / 2;
    MergeSort(v, st, m);
    MergeSort(v, m + 1, dr);
    merg(v, st, m, dr);
}

void QuickSort(vector<int>& v, int st, int dr)
{
    if (st < dr)
    {
        int m = (st + dr) / 2;
        int aux = v[st];
        v[st] = v[m];
        v[m] = aux;
        int i = st, j = dr, d = 0;
        while (i < j)
        {
            if (v[i] > v[j])
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
                d = 1 - d;
            }
            i += d;
            j -= 1 - d;
        }
        QuickSort(v, st, i - 1);
        QuickSort(v, i + 1, dr);
    }
}
void sortare(string tipAles, long long nrElem, vector <int>& v)
{
    if (tipAles == "Limbaj")
    {
        sort(v.begin(), v.end());
    }

    if (tipAles == "Merge")
    {
        vector<int> t;
        MergeSort(v, 1, nrElem);
    }

    if (tipAles == "Quick")
    {
        QuickSort(v, 1, nrElem);
    }

    if (tipAles == "Radix")
    {
        radix_sort(v);
    }

    if (tipAles == "Bubble")
    {
        if (nrElem < 100000)
        {
            for (int i = 1; i <= nrElem + 1; ++i)
            {
                for (int j = 1; j < nrElem + 1 - i; ++j)
                {
                    if (v[j] > v[j + 1])
                    {
                        swap(v[j], v[j + 1]);
                    }
                }
            }
        }
        else
        {
            cout << "Exemplu prea mare pentru BubbleSort." << '\n';
        }
    }
    if (tipAles == "Count")
    {
        int i, maxi = v[1];
        for (i = 1; i <= nrElem; i++)
        {
            if (v[i] > maxi)
                maxi = v[i];
        }

        vector<int> frecv;
        for (i = 0; i <= maxi; i++)
        {
            frecv.push_back(0);
        }

        for (i = 1; i <= nrElem; i++)
        {
            frecv[v[i]] += 1;
        }
        int k = 1;
        for (i = 0; i <= maxi; i++)
        {
            while (frecv[i] != 0)
            {
                v[k] = i;
                k++;
                frecv[i]--;
            }
        }
    }

}
int main()
{
    int N, i, t, T, M;
    string TT, A;
    cout << "Numar de teste: ";
    cin >> T;
    cout << endl;
    for (t = 1; t <= T; t++)
    {
       // cout << "Tip test(R,C): ";
       // cin >> TT;
        TT = "R";
        cout << endl;
        cout << "Lungime vector: ";
        cin >> N;
        vector<int> v;
        cout << endl;
        cout << "Numar maxim este  ";
        cin>>M;
        //M = 100000;
        cout << endl << endl;
        cout << "Algoritm sortare(Limbaj,Bubble,Quick,Count,Merge,Radix): ";
        cin >> A;
        generareExemplu(TT, N, v, M);
        cout << endl;
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        sortare(A, N, v);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        cout << "Durata sortare = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        cout << endl << endl;
        if (test_sort(v, N))
            cout << "Sortat corect!";
        else
            cout << "Sortat gresit!";
        cout << endl;
        cout << "-------------------------------------------------------";
        cout << endl;
    }
    return 0;
}