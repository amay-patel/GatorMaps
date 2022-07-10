#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <iterator>
using namespace std;

class AdjacenyList
{
    private:
        map<string, vector<string>> graph;
        map<string, int> outDegs;
        map<string, double> simplifyCalc;
        map<string, double> ranks;
        int numOfNodes = 0;
    public:
        AdjacenyList();
        ~AdjacenyList();
        void insertEdge(string from, string to);
        void printEdges(map<string, vector<string>> exGraph);
        void printOutDegs(map<string, int> exGraph);
        void determinePageRank(int n);
};

AdjacenyList::AdjacenyList()
{

}

AdjacenyList::~AdjacenyList()
{

}

void AdjacenyList::insertEdge(string from, string to)
{
    graph[to].push_back(from);
    outDegs[from]++;
    if(outDegs.find(to) == outDegs.end())
    {
        outDegs[to] = 0;
        numOfNodes++;
    }
    if(graph.find(from) == graph.end())
    {
        graph[from] = {};
        numOfNodes++;
    }
}

void AdjacenyList::printEdges(map<string, vector<string>> exGraph)
{
    for(map<string, vector<string>>::iterator iter = exGraph.begin(); iter != exGraph.end(); ++iter)
    {
        cout << iter->first << " <- ";
        for(int i = 0; i < iter->second.size(); i++)
        {
            cout << iter->second[i] << " ";
        }
        cout << endl;
    }
}

void AdjacenyList::printOutDegs(map<string, int> exGraph)
{
    for(map<string, int>::iterator iter = exGraph.begin(); iter != exGraph.end(); ++iter)
    {
        cout << iter->first << " -> " << iter->second << endl;
    }
}

void AdjacenyList::determinePageRank(int n)
{
    vector<double> initialRank(numOfNodes, 1.0/numOfNodes);
    //printEdges(graph);
    //printOutDegs(outDegs);
    if(n == 1)
    {
        for(map<string, vector<string>>::iterator iter = graph.begin(); iter != graph.end(); ++iter)
        {
            cout << iter->first << " ";
            cout << fixed << showpoint;
            cout << setprecision(2);
            cout << initialRank.at(0) << endl;
        }
    }
    else if(n > 1)
    {
        for(map<string, vector<string>>::iterator iter = graph.begin(); iter != graph.end(); ++iter)
        {
            ranks[iter->first] = 1.0/numOfNodes;
        }
        for(map<string, vector<string>>::iterator iter = graph.begin(); iter != graph.end(); ++iter)
        {
            simplifyCalc[iter->first] = 1.0/outDegs[iter->first];
        }
        while(n > 1)
        {
            map<string, double> updatedPageRank;
            for(map<string, vector<string>>::iterator iter = graph.begin(); iter != graph.end(); ++iter)
            {
                double sum = 0.0;
                /*
                 * Couldn't determine what the iterator was for inner loop
                 * Used auto keyword and for each loop
                 * This will update the page rank for each page
                 */
                for(string inner : iter->second)
                {
                    double part1 = simplifyCalc[inner];
                    sum += part1 * ranks[inner];
                }
                updatedPageRank[iter->first] = sum;
            }
            ranks = updatedPageRank;
            n -= 1;
        }
        for(map<string, double>::iterator iter = ranks.begin(); iter != ranks.end(); ++iter)
        {
            cout << iter->first << " ";
            cout << fixed << showpoint;
            cout << setprecision(2);
            cout << iter->second << endl;
        }
    }
}

int main()
{
    AdjacenyList graph;
    int no_lines;
    int power_iterations;
    string from;
    string to;
    cin >> no_lines >> power_iterations;
    for(int i = 0; i < no_lines; i++)
    {
        cin >> from >> to;
        graph.insertEdge(from, to);
    }
    graph.determinePageRank(power_iterations);
    return 0;
}