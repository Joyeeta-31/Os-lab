#include <stdio.h>
#include <stdlib.h>

int **graph;
int *visited;
int *recStack;
int vertices, edges;

// Function to detect cycle using DFS
int dfs(int node)
{
    visited[node] = 1;
    recStack[node] = 1;

    for (int i = 0; i < vertices; i++)
    {
        if (graph[node][i] == 1)
        {
            if (!visited[i])
            {
                if (dfs(i))
                    return 1;
            }
            else if (recStack[i])
            {
                return 1;
            }
        }
    }

    recStack[node] = 0;
    return 0;
}

int main()
{
    printf("Enter total number of vertices (Processes + Resources): ");
    scanf("%d", &vertices);

    // Dynamic memory allocation
    graph = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++)
        graph[i] = (int *)calloc(vertices, sizeof(int));

    visited = (int *)calloc(vertices, sizeof(int));
    recStack = (int *)calloc(vertices, sizeof(int));

    printf("Enter total number of edges: ");
    scanf("%d", &edges);

    printf("\nEnter each edge (Source Destination):\n");

    for (int i = 0; i < edges; i++)
    {
        int src, dest;

        printf("Edge %d: ", i + 1);
        scanf("%d %d", &src, &dest);

        if (src >= 0 && src < vertices && dest >= 0 && dest < vertices)
            graph[src][dest] = 1;
        else
        {
            printf("Invalid vertex! Enter again.\n");
            i--;
        }
    }

    // Display adjacency matrix
    printf("\nResource Allocation Graph (Adjacency Matrix):\n");

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }

    int deadlock = 0;

    for (int i = 0; i < vertices; i++)
    {
        if (!visited[i])
        {
            if (dfs(i))
            {
                deadlock = 1;
                break;
            }
        }
    }

    if (deadlock)
        printf("\nDeadlock Detected (Cycle Exists).\n");
    else
        printf("\nNo Deadlock (No Cycle).\n");

    // Free memory
    for (int i = 0; i < vertices; i++)
        free(graph[i]);

    free(graph);
    free(visited);
    free(recStack);

    return 0;
}
