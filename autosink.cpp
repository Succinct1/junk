#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <queue>
class node
{
public:
    node(int t)
    {
        toll = t;
        inCount = 0;
        inCountExtra = 0;
        explored = false;
        cost = INT32_MAX;
    }
    node() {
        toll = -1;
        inCount = 0;
        inCountExtra = 0;
        explored = false;
        cost = INT32_MAX;

    }
    std::unordered_map<std::string, node> dest;
    int inCount, inCountExtra, toll, cost;
    bool explored;
};
int main()
{
    int cities;
    std::cin >> cities;
    std::unordered_map<std::string, node> data;
    for (int i = 0; i < cities; i++)
    {
        std::string name;
        int toll;
        std::cin >> name >> toll;
        data[name] = node(toll);
    }

    int paths;
    std::cin >> paths;
    for (int i = 0; i < paths; i++)
    {
        std::string start, end;
        std::cin >> start >> end;
        data[start].dest[end] = data[end];
        data[end].inCount++;
    }
    for (auto &node : data)
    {
        node.second.inCountExtra = node.second.inCount;
    }

    std::vector<std::unordered_map<std::string, node>> shortestPaths;
    for (auto &n : data)
    {
        if (n.second.inCount == 0)
        {
            std::queue<std::string> q;
            std::unordered_set<std::string> distances;
            q.push(n.first);
            data[n.first].explored = true;
            distances.insert(n.first);
            while (!q.empty())
            {
                std::string current = q.front();
                q.pop();
                for (auto &node : data[current].dest)
                {
                    if (!data[node.first].explored)
                    {
                        q.push(node.first);
                        data[node.first].explored = true;
                        distances.insert(node.first);
                    }
                }
            }

            for (auto &node : data)
            {
                auto got = distances.find(node.first);
                if (got == distances.end())
                {
                    for (auto &n : data[node.first].dest)
                    {
                        data[n.first].inCount--;
                    }
                }
            }

            int i = 0;
            q.push(n.first);
            std::unordered_map<std::string, node> currentList;
            currentList[n.first] = node(0);
            currentList[n.first].cost = 0;
            data[n.first].cost = 0;
            while (!q.empty())
            {
                std::string current = q.front();
                q.pop();
                for (auto &nod : data[current].dest)
                {
                    int cost = data[current].cost + data[nod.first].toll;
                    if (cost < data[nod.first].cost)
                    {
                        data[nod.first].cost = cost;
                    }
                    data[nod.first].inCount--;
                    if (data[nod.first].inCount == 0)
                    {
                        q.push(nod.first);
                        currentList[nod.first] = node(0);
                        currentList[nod.first].cost = cost;
                    }
                }
            }
            shortestPaths.push_back(currentList);
            for (auto &node : data)
            {
                node.second.explored = false;
                node.second.inCount = node.second.inCountExtra;
                node.second.cost = INT32_MAX;
            }
        }
    }
    int travels;
    std::cin >> travels;
    std::vector<std::string> output;
    for (int i = 0; i < travels; i++)
    {
        std::string start, end;
        std::cin >> start >> end;
        bool found = false;
        for (auto& list : shortestPaths)
        {

            if (list[start].toll != -1)
            {
                if (list[end].toll != -1)
                {
                    int cost = list[end].cost - list[start].cost;
                    if (cost >= 0) {
                        output.push_back(std::to_string(cost));
                        
                        found = true;
                    }
                }
            }
        }
        if (!found)
        {
            output.push_back("NO");
        }
    }
    for (auto str : output) {
        std::cout << str << std::endl;
    }
}

