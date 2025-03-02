#include <iostream>
#include <fstream>
#include <vector>

// Функция для обхода графа в глубину (DFS) и пометки вершин компонента связности
void DFS(int vertex, const std::vector<std::vector<int>>& adjacencyMatrix, std::vector<int>& components, int componentId)
{
    // Помечаем текущую вершину как принадлежащую компоненту componentId
    components[vertex] = componentId;

    // Обходим все смежные вершины
    for (int i = 0; i < adjacencyMatrix.size(); ++i)
    {
        if (adjacencyMatrix[vertex][i] == 1 && components[i] == -1)
        {
            // Если вершина не посещена, рекурсивно вызываем DFS
            DFS(i, adjacencyMatrix, components, componentId);
        }
    }
}

// Функция для поиска компонентов связности
int findConnectedComponents(const std::vector<std::vector<int>>& adjacencyMatrix, std::vector<int>& components)
{
    int componentId = 0; // Идентификатор компонента связности

    // Проходим по всем вершинам графа
    for (int i = 0; i < adjacencyMatrix.size(); ++i)
    {
        if (components[i] == -1)
        {
            // Если вершина не принадлежит ни одному компоненту, запускаем DFS
            DFS(i, adjacencyMatrix, components, componentId);
            componentId++; // Увеличиваем идентификатор для следующего компонента
        }
    }

    return componentId; 
}

int main()
{
    setlocale(LC_ALL, "rus");

    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1; // Возвращаем 1 в случае ошибки
    }

    // Читаем количество вершин графа
    int N;
    inputFile >> N;

    // Создаём матрицу смежности
    std::vector<std::vector<int>> adjacencyMatrix(N, std::vector<int>(N));

    // Заполняем матрицу смежности из файла
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            inputFile >> adjacencyMatrix[i][j];
        }
    }

    inputFile.close();

    // Создаём массив для хранения информации о компонентах связности
    std::vector<int> components(N, -1); // -1 означает, что вершина ещё не посещена

    // Находим количество компонентов связности
    int numComponents = findConnectedComponents(adjacencyMatrix, components);

    // Выводим принадлежность вершин компонентам связности
    std::cout << "Принадлежность вершин компонентам связности:" << std::endl;
    for (int i = 0; i < N; ++i)
    {
        std::cout << i + 1 << " - " << components[i] + 1 << std::endl;
    }

    // Выводим количество компонентов связности
    std::cout << "Количество компонентов связности в графе: " << numComponents << std::endl;

    return EXIT_SUCCESS;
}