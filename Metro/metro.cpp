#include <iostream>
#include <vector>
#include <set>
#include <limits.h>
#include <queue>
#include <stack>
#include <cstring>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
using namespace std;

vector<int> res;

int solveIndex(string str, vector<string> &graph)
{
    for (int i = 0; i < graph.size(); i++)
    {
        if (str == graph[i])
        {
            return i;
        }
    }
    return -1;
}

int shortestPath(int n, int m, int source, int dest, vector<vector<int>> &edges, vector<string> &graph)
{
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int fir = edges[i][0];
        int sec = edges[i][1];
        int thir = edges[i][2];
        adj[fir].push_back({sec, thir});
        adj[sec].push_back({fir, thir});
    }

    vector<int> vis(n, INT_MAX), parent(n);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    parent[source] = source;
    vis[source] = 0;

    while (!pq.empty())
    {
        int weight = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        vector<pair<int, int>> res = adj[node];
        int number = res.size();
        for (int i = 0; i < number; i++)
        {
            int fir = res[i].first;
            int sec = res[i].second;
            if (sec + vis[node] < vis[fir])
            {
                vis[fir] = sec + vis[node];
                parent[fir] = node;
                pq.push({vis[fir], fir});
            }
        }
    }

    if (vis[dest] == INT_MAX)
    {
        return -1;
    }
    int i = dest;
    while (i != source)
    {
        res.push_back(i);
        i = parent[i];
    }
    res.push_back(i);

    return vis[dest];
}

int finder(vector<vector<int>> &edges, vector<string> &graph)
{
    string source;
    string dest;
    cout << "Please Enter the station's without any gaps in between -\n";
    cout << "Enter the Source station: ";
    cin >> source;
    cout << "Enter the Destination station: ";
    cin >> dest;
    transform(source.begin(), source.end(), source.begin(), ::toupper);
    transform(dest.begin(), dest.end(), dest.begin(), ::toupper);

    int sourIndex = solveIndex(source, graph);
    int destIndex = solveIndex(dest, graph);

    if (sourIndex == -1 || destIndex == -1)
    {
        return -1;
    }
    int number = shortestPath(graph.size(), edges.size(), sourIndex, destIndex, edges, graph);
    return number;
}

int main()
{
    vector<string> graph{"RAJIVCHOWK", "KASHMEREGATE", "SHAHDARA", "ANANDVIHAR", "SAKET",
                         "DWARKA", "PUNJABIBAGH", "MODELTOWN", "ROHINI", "NEHRUPLACE"};
    vector<vector<int>> edges{{1, 7, 1}, {1, 8, 1}, {1, 2, 1}, {1, 6, 1}, {1, 0, 1}, {0, 5, 1}, {0, 9, 1}, {0, 4, 1}, {0, 3, 1}};

    int num;
    int all_Helper = 0;
    bool flag = false;
    bool help = true;
    while (true)
    {
        cout << "Enter the query number: \n";
        if (help)
        {
            cout << "1. Show all the stations-\n";
            cout << "2. Time-\n";
            cout << "3. Fare-\n";
            cout << "4. Number of stations-\n";
            cout << "5. Show metro stations route-\n";
            cout << "6. Check for any other station-\n";
            cout << "7. Exit()\n";
        }
        help = true;
        cin >> num;

        if (cin.fail() || num < 1 || num > 7)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input, please enter a number between 1 and 7.\n";
            continue;
        }

        if (num == 7)
        {
            break;
        }

        switch (num)
        {
        case 1:
        {
            sort(graph.begin(), graph.end());
            cout << "\n";
            int count1 = 1;
            for (const auto &station : graph)
            {
                cout << count1 << "." << station << "  ";
                if (count1 % 6 == 0)
                {
                    cout << "\n";
                }
                count1++;
            }
            cout << "\n";
            break;
        }
        case 2:
        {

            if (flag)
            {
                cout << "\n";
                cout << "Total Time - " << all_Helper * 3 << " minutes\n";
            }
            else
            {
                int number = finder(edges, graph);
                if (number != -1)
                {
                    flag = true;
                    all_Helper = number;
                    cout << "\n";
                    cout << "Total Time - " << number * 3 << " minutes\n";
                }
                else
                {
                    cout << "\n";
                    cout << "Station name not found. Please enter a correct station name. \n";
                }
            }
            break;
        }
        case 3:
        {

            if (flag)
            {
                cout << "\n";
                cout << "Total Fare - ";
                cout << min(all_Helper * 7, 60) << " Rupees\n";
            }
            else
            {
                int number = finder(edges, graph);
                if (number != -1)
                {
                    flag = true;
                    all_Helper = number;
                    cout << "\n";
                    cout << "Total Fare - " << min(all_Helper * 7, 60) << " Rupees\n";
                }
                else
                {
                    cout << "\n";
                    cout << "Station name not found. Please enter a correct station name.\n";
                }
            }
            break;
        }
        case 4:
        {

            if (flag)
            {
                cout << "\n";
                cout << "Number of stations are - " << all_Helper << "\n";
            }
            else
            {
                int number = finder(edges, graph);
                if (number != -1)
                {
                    flag = true;
                    all_Helper = number;
                    cout << "\n";
                    cout << "Number of stations are - " << number << "\n";
                }
                else
                {
                    cout << "\n";
                    cout << "Station name not found. Please enter a correct station name.\n";
                }
            }
            break;
        }
        case 5:

            if (flag)
            {
                cout << "\n";
                cout << "Route is - ";
                for (int i = res.size() - 1; i >= 0; i--)
                {
                    cout << graph[res[i]];
                    if (i != 0)
                    {
                        cout << " -> ";
                    }
                }
                cout << "\n";
            }
            else
            {

                int number = finder(edges, graph);
                cout << "\n";
                if (number != -1)
                {
                    flag = true;
                    all_Helper = number;
                    for (int i = res.size() - 1; i >= 0; i--)
                    {
                        cout << graph[res[i]];
                        if (i != 0)
                        {
                            cout << " -> ";
                        }
                    }
                    cout << "\n";
                }
                else
                {
                    cout << "Station name not found. Please enter a correct station name.\n";
                }
            }
            break;
        case 6:
            flag = false;
            help = false;
        }
        cout << "\n";
    }
    cout << "Have a Nice day!\n";
    return 0;
}
