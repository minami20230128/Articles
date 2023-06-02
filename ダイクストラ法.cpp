//・ダイクストラ法とは
//主に、ある地点を始点として枝分かれした道の中から最短距離を求める問題などに使われるアルゴリズム
//1. 頂点集合全体をVとし、始点からの最短経路(最短距離)が既に確定した頂点集合をSとする。
//2. 現時点で経路が判明している頂点のうち、始点からの距離が最小となる頂点vを新たにSに追加する。
//3. まだSに含まれていない頂点集合(V - S)のうちvと接する各頂点について、既に求めた最短距離をもとに始点からの最短距離を更新する。
//4. 全ての頂点が確定するまで(V - Sが空になるまで)2と3を繰り返す。

//┌─────7─────B─────2─────┐
//│           │           │
//│           1           │
//│           │           │
//A-────4─────C─────6────-E
//│                       │
//│                       │
//│                       │
//└─────3─────D─────5─────┘

//例えば、上図の道においてAからEの最短経路を求める際は以下のように計算する

//始点Aから隣接した地点B、C、Dまでの最短距離を求める(A-B=7、A-C=4、A-D=3)
//AからC・Dまでの最短距離も確定したので、Sに入れる
//まだ確定していないBまでの最短距離を確定する(A-B=7、A-C-B=5)
//Bまでの最短距離を7->5に更新し、Sに入れる
//最後に、Eまでの最短距離を求める(B-E=5+2=7、C-E=4+6=10、D-E=3+5=8)

//よって、A-B-Eの経路が最短である

//実装
#include <vector>
#include <map>
#include <string>

struct Node
{
    std::string name;
    std::map<Node, int> nextnodes;
    int minimumdist = INT_MAX;

    public:
    Node(std::string name)
    {
        this->name = name;
    }

    int GetDistance(const Node dst)
    {
        auto itr = this->nextnodes.begin();
        while (itr != this->nextnodes.end())
        {
            if (itr->first.name == dst.name)
            {
                return itr->second;
            }

            itr++;
        }
    }
};

int main()
{
    Node nodeA = Node("A");
    Node nodeB = Node("B");
    Node nodeC = Node("C");
    Node nodeD = Node("D");
    Node nodeE = Node("E");

    nodeA.nextnodes = {{nodeB, 7}, {nodeC, 4}, {nodeD, 3}};
    nodeB.nextnodes = {{nodeA, 4}, {nodeC, 1}, {nodeE, 2}};
    nodeC.nextnodes = {{nodeA, 4}, {nodeE, 6}};
    nodeD.nextnodes = {{nodeA, 3}, {nodeE, 5}};
    nodeE.nextnodes = {{nodeB, 2}, {nodeC, 6}, {nodeD, 5}};
    
    std::vector<Node> V = {nodeA, nodeB, nodeC, nodeD, nodeE};
    std::vector<Node> S = {};

    int nodenumber = V.size();

    auto itr = V.begin();
    while(itr != V.end())
    {
        Node processnode = *itr;
        V.erase(itr);
        S.push_back(processnode);

        for(auto&& node : V)
        {
            if(processnode.GetDistance(node) < node.minimumdist)
            {
                node.minimumdist = processnode.GetDistance(node) + node.minimumdist;
            }
        }
    }
    return 0;
}
