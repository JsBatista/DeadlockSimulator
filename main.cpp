#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm> // std::sort

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <typeinfo>
using namespace std;

int lesserThanArray(vector<int> vecA, vector<int> vecB){
    for(int i = 0; i < vecA.size(); i++)
    {
        if(vecA[i] > vecB[i])
        {
            return -1;
        }
    }
    return 1;
}

void safetyAlgorithm(vector<int> Available, vector<vector<int>> Max, vector<vector<int>> Allocation, bool maxIsNeed = false){
    int n = Max.size();
    int m = Available.size();
    
    string sequenciaSegura = "";

    // Inicializando a matriz Need
    vector<vector<int>> Need;

    if(maxIsNeed){
        Need = Max;
    }
    else{
        for(int i = 0; i < Max.size(); i ++)
        {
            Need.push_back({});
            for(int j = 0; j < Max[i].size(); j ++)
            {
                Need[i].push_back(Max[i][j] - Allocation[i][j]);
            }
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
            if(!Finish[i] && lesserThanArray(Need[i], Work) == 1)
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


void requestAlgorithm(vector<int> Available, vector<vector<int>> Max, vector<vector<int>> Allocation, vector<vector<int>> Request)
{
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

    for(int i = 0; i < Request.size();  i++)
    {
        bool willSkip = false;
        int returnValueNeed = lesserThanArray(Request[i], Need[i]);
        if(returnValueNeed == -1)
        {
            std::cout << "ERRO! Processo P"<<i<<" excedeu limite máximo de requisições!" << std::endl; 
            willSkip = true;
        }

        if(!willSkip)
        {
            int returnValueAvailable = lesserThanArray(Request[i], Need[i]);
            if(returnValueAvailable == 1)
            {
                for(int j = 0; j < Available.size(); j++){
                    Available[j] = Available[j] - Request[i][j];
                }
                for(int j = 0; j < Allocation[i].size(); j++){
                    Allocation[i][j] = Allocation[i][j] + Request[i][j];
                }
                for(int j = 0; j < Need[i].size(); j++){
                    Need[i][j] = Need[i][j] - Request[i][j];
                }
            }
            else{
                std::cout << "O processo P"<<i<<" vai ter que esperar por recursos!";
            }
        }
    }

    for(int i = 0; i < Allocation.size();  i++)
    {
        string toBePrinted = "";
        for(int j = 0; j < Allocation[i].size(); j++)
        {
            toBePrinted += to_string(Allocation[i][j]) + " ";
        } 
        std::cout << toBePrinted << std::endl;
    }
    std::cout << std::endl;

    for(int i = 0; i < Need.size();  i++)
    {
        string toBePrinted = "";
        for(int j = 0; j < Need[i].size(); j++)
        {
            toBePrinted += to_string(Need[i][j]) + " ";
        } 
        std::cout << toBePrinted << std::endl;
    }
    std::cout << std::endl;

    string toBePrinted = "";
    for(int i = 0; i < Available.size();  i++)
    {
        toBePrinted += to_string(Available[i]) + " ";
    }
    std::cout << toBePrinted << std::endl << std::endl;
    
    safetyAlgorithm(Available, Need, Allocation, true);
    
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

    vector<vector<int>> request = {
                            {0,0,0},
                            {1,0,2},
                            {0,0,0},
                            {0,0,0},
                            {0,0,0}
                            };

    //safetyAlgorithm(avaiable, max, alloc);
    requestAlgorithm(avaiable,max,alloc, request);


    return 0;
}