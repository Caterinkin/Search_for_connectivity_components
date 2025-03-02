#include <iostream>
#include <fstream>
#include <vector>

// ������� ��� ������ ����� � ������� (DFS) � ������� ������ ���������� ���������
void DFS(int vertex, const std::vector<std::vector<int>>& adjacencyMatrix, std::vector<int>& components, int componentId)
{
    // �������� ������� ������� ��� ������������� ���������� componentId
    components[vertex] = componentId;

    // ������� ��� ������� �������
    for (int i = 0; i < adjacencyMatrix.size(); ++i)
    {
        if (adjacencyMatrix[vertex][i] == 1 && components[i] == -1)
        {
            // ���� ������� �� ��������, ���������� �������� DFS
            DFS(i, adjacencyMatrix, components, componentId);
        }
    }
}

// ������� ��� ������ ����������� ���������
int findConnectedComponents(const std::vector<std::vector<int>>& adjacencyMatrix, std::vector<int>& components)
{
    int componentId = 0; // ������������� ���������� ���������

    // �������� �� ���� �������� �����
    for (int i = 0; i < adjacencyMatrix.size(); ++i)
    {
        if (components[i] == -1)
        {
            // ���� ������� �� ����������� �� ������ ����������, ��������� DFS
            DFS(i, adjacencyMatrix, components, componentId);
            componentId++; // ����������� ������������� ��� ���������� ����������
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
        std::cerr << "������ �������� �����!" << std::endl;
        return 1; // ���������� 1 � ������ ������
    }

    // ������ ���������� ������ �����
    int N;
    inputFile >> N;

    // ������ ������� ���������
    std::vector<std::vector<int>> adjacencyMatrix(N, std::vector<int>(N));

    // ��������� ������� ��������� �� �����
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            inputFile >> adjacencyMatrix[i][j];
        }
    }

    inputFile.close();

    // ������ ������ ��� �������� ���������� � ����������� ���������
    std::vector<int> components(N, -1); // -1 ��������, ��� ������� ��� �� ��������

    // ������� ���������� ����������� ���������
    int numComponents = findConnectedComponents(adjacencyMatrix, components);

    // ������� �������������� ������ ����������� ���������
    std::cout << "�������������� ������ ����������� ���������:" << std::endl;
    for (int i = 0; i < N; ++i)
    {
        std::cout << i + 1 << " - " << components[i] + 1 << std::endl;
    }

    // ������� ���������� ����������� ���������
    std::cout << "���������� ����������� ��������� � �����: " << numComponents << std::endl;

    return EXIT_SUCCESS;
}