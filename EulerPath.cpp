
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

int eulerPath(vector<vector<int>> &graph) {

    int size = graph.size();
    int i, j, countNeighbours, countOdd = 0;

    for(i = 0; i < size; i++) {

        countNeighbours = 0;
        for(j = 0; j < size; j++)
            if(graph[i][j] == 1)
                countNeighbours++;
           

        if(countNeighbours % 2 == 1)
            countOdd++;
    }

    if(countOdd > 2) 
        return 0;

    return 1;
} 

void printPath (vector<vector<int>> &graph) {

    int size = graph.size();
    int start = 0;
    int countNeighbours, i, j;

    for(i = 0; i < size; i++) {

        countNeighbours = 0;
        for(j = 0; j < size; j++) 
            if(graph[i][j] == 1) 
                countNeighbours++;
        
        // Ако е намерен връх с нечетна степен, той става стартов
        if(countNeighbours % 2 == 1) {

            start = i;
            // Това води до излизане от цикъла
            i = size + 1;
        }
    }

    stack<int> st;
    vector<int> path;

    int current = start;
    int neighbor = 0;
    
    for(i = 0; i < size; i++)
        if(graph[current][i] == 1)
            neighbor++;
       
    while (!st.empty() || neighbor) {

        // Ако текущият връх няма съсед, добави го в пътеката
        if (neighbor == 0) {

            path.push_back(current);
            current = st.top();
            st.pop();
        }

        else  {

            for (i = 0; i < size; i++) {

                if (graph[current][i] == 1) {

                    st.push(current);
                    graph[current][i] = 0;
                    graph[i][current] = 0;
                    current = i;
                    // Това води до излизане от цикъла
                    i = size + 1;
                }
            }

        }

        // Намира броя на съседите на текущия връх
        neighbor = 0;
        for(int i = 0; i<size; i++)
            if(graph[current][i] == 1) 
                neighbor++;      
    }

    // Принтира пътеката
    for (const auto& ele : path) cout << ele + 1 << " ";
    cout << current + 1;
}



int main() {

    vector<vector<int>> graph = {
        {0, 1, 0, 0, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {0, 1, 0, 1, 0}
    };

    if(eulerPath(graph)) {
        cout<<"Yes"<<endl;
        printPath(graph);
    }
    else
        cout<<"No"<<endl;
    
    return 0;
}
