#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm> // std::sort

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

bool lesserThanArray(vector<int> vecA, vector<int> vecB){
    for(int i = 0; i < vecA.size(); i++)
    {
        if(vecA[i] > vecB[i])
        {
            return false;
        }
    }
    return true;
}

void safetyAlgorithm(vector<int> Available, vector<vector<int>> Max, vector<vector<int>> Allocation){
    int n = Max.size();
    int m = Available.size();
    
    string sequenciaSegura = "";

    // Inicializando a matriz Need
    vector<vector<int>> Need;
    for(int i = 0; i < Max.size(); i ++)
    {
        Need.push_back({});
        for(int j = 0; j < Max[i].size(); j ++)
        {
            Need[i].push_back(Max[i][j] - Allocation[i][j]);
        }
    }
    vector<int> Work = Available;
    vector<bool> Finish;
    for(int i = 0; i < n; i++)
    {
        Finish.push_back(false);
    }

    while(true)
    {
        bool reset = false;
        for(int i = 0; i < Finish.size(); i++)
        {
            if(!Finish[i] && lesserThanArray(Need[i], Work))
            {
                for(int k = 0; k < Work.size(); k++)
                {
                    Work[k] = Work[k] + Allocation[i][k];
                }
                sequenciaSegura = sequenciaSegura +" P"+to_string(i)+" ";
                Finish[i] = true;
                reset = true;
            }
        }
        if(reset)
        {
            continue;
        }
        bool safe = true;
        for(int j = 0; j < Finish.size(); j++)
        {
            if(Finish[j] == false)
            {
                safe = false;
            }
        }
        if(safe)
        {
            std::cout << "Estado Seguro!" << std::endl;
            std::cout << "Sequencia segura: " << sequenciaSegura << std::endl;
            return;
        }
        else
        {
            std::cout << "Estado Inseguro!";
            return;
        }
    }
    

}

int main(int argc, char *argv[])
{

    vector<vector<int>> alloc = {{0,1,0},
                                 {2,0,0},
                                 {3,0,2},
                                 {2,1,1},
                                 {0,0,2}};

    vector<vector<int>> max = {{7,5,3},
                                 {3,2,2},
                                 {9,0,2},
                                 {2,2,2},
                                 {4,3,3}};

    vector<int> avaiable = {3,3,2};

    safetyAlgorithm(avaiable, max, alloc);
    


    return 0;
}