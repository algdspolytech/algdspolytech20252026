#include "CppUnitTest.h"
#include "graph.h"  // graph.h должен иметь extern "C" объявления

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphTests
{
    TEST_CLASS(GraphCreationTests)
    {
    public:

        //1Тест на создание графа с нормальным количеством вершин
        TEST_METHOD(create_graph_NormalCount_returnValidVal)
        {
            Graph* graph = create_graph(4);
            Assert::IsNotNull(graph);
            Assert::AreEqual(4, graph->vertices_count);
            for (int i = 0; i < 4; ++i) {
                Assert::AreEqual(0, graph->sizes[i]);
            }
            free_graph(graph);
        }

        //Тест на создание графа с отрицательным количеством вершин
        TEST_METHOD(create_graph_NegativeCount_returnNull)
        {
            Graph* graph = create_graph(-1);
            Assert::IsNull(graph);
        }

        //Тест на создание графа с нулевым количеством вершин
        TEST_METHOD(create_graph_ZeroCount_returnValidVal)
        {
            Graph* graph = create_graph(0);
            Assert::IsNotNull(graph);
            Assert::AreEqual(0, graph->vertices_count);
            free_graph(graph);
        }
    };

    TEST_CLASS(AddEdgeTests)
    {
    public:

        //Тест на добавление корректного ребра
        TEST_METHOD(add_edge_ValidVertices_EdgeAdded)
        {
            Graph* graph = create_graph(3);
            add_edge(graph, 0, 1);

            Assert::AreEqual(1, graph->sizes[0]);
            Assert::AreEqual(1, graph->adjacency_list[0][0]);

            free_graph(graph);
        }

        //Тест на добавление ребра с неверной исходной вершиной
        TEST_METHOD(add_edge_InvalidFromVertex_NoChange)
        {
            Graph* graph = create_graph(2);
            int initial_size = graph->sizes[0];

            add_edge(graph, 5, 1); //Неверная исходная вершина

            Assert::AreEqual(initial_size, graph->sizes[0]);
            free_graph(graph);
        }

        //Тест на добавление ребра с неверной целевой вершиной
        TEST_METHOD(add_edge_InvalidToVertex_NoChange)
        {
            Graph* graph = create_graph(2);
            int initial_size = graph->sizes[0];

            add_edge(graph, 0, 5); //Неверная целевая вершина

            Assert::AreEqual(initial_size, graph->sizes[0]);
            free_graph(graph);
        }

        //Тест на добавление нескольких ребер из одной вершины
        TEST_METHOD(add_edge_MultipleEdges_AllAdded)
        {
            Graph* graph = create_graph(4);

            add_edge(graph, 0, 1);
            add_edge(graph, 0, 2);
            add_edge(graph, 0, 3);

            Assert::AreEqual(3, graph->sizes[0]);
            Assert::AreEqual(1, graph->adjacency_list[0][0]);
            Assert::AreEqual(2, graph->adjacency_list[0][1]);
            Assert::AreEqual(3, graph->adjacency_list[0][2]);

            free_graph(graph);
        }
    };

    TEST_CLASS(MatrixConversionTests)
    {
    public:

        //Тест на несуществующий файл
        TEST_METHOD(adjacency_matrix_to_adjacency_list_FileNotExist_returnNull)
        {
            Graph* graph = adjacency_matrix_to_adjacency_list("nonexistent_file.txt");
            Assert::IsNull(graph);
        }

        //Тест на пустой файл
        TEST_METHOD(adjacency_matrix_to_adjacency_list_EmptyFile_returnNull)
        {
            //Создаем пустой файл
            FILE* file = fopen("empty_file.txt", "w");
            fclose(file);

            Graph* graph = adjacency_matrix_to_adjacency_list("empty_file.txt");
            Assert::IsNull(graph);

            remove("empty_file.txt");
        }

        //Тест на файл с одной вершиной без ребер
        TEST_METHOD(adjacency_matrix_to_adjacency_list_SingleVertexNoEdges_returnValidGraph)
        {
            //Создаем тестовый файл
            FILE* file = fopen("single_vertex.txt", "w");
            fprintf(file, "1\n");
            fprintf(file, "0\n");
            fclose(file);

            Graph* graph = adjacency_matrix_to_adjacency_list("single_vertex.txt");

            Assert::IsNotNull(graph);
            Assert::AreEqual(1, graph->vertices_count);
            Assert::AreEqual(0, graph->sizes[0]);

            free_graph(graph);
            remove("single_vertex.txt");
        }

        //Тест на корректное преобразование матрицы смежности
        TEST_METHOD(adjacency_matrix_to_adjacency_list_ValidMatrix_returnCorrectList)
        {
            //Создаем тестовый файл
            FILE* file = fopen("test_matrix.txt", "w");
            fprintf(file, "3\n");
            fprintf(file, "0 1 1\n");
            fprintf(file, "1 0 0\n");
            fprintf(file, "1 0 0\n");
            fclose(file);

            Graph* graph = adjacency_matrix_to_adjacency_list("test_matrix.txt");

            Assert::IsNotNull(graph);
            Assert::AreEqual(3, graph->vertices_count);

            //Проверяем вершину 0
            Assert::AreEqual(2, graph->sizes[0]);
            Assert::AreEqual(1, graph->adjacency_list[0][0]);
            Assert::AreEqual(2, graph->adjacency_list[0][1]);

            //Проверяем вершину 1
            Assert::AreEqual(1, graph->sizes[1]);
            Assert::AreEqual(0, graph->adjacency_list[1][0]);

            //Проверяем вершину 2
            Assert::AreEqual(1, graph->sizes[2]);
            Assert::AreEqual(0, graph->adjacency_list[2][0]);

            free_graph(graph);
            remove("test_matrix.txt");
        }

        //Тест на сложный граф
        TEST_METHOD(adjacency_matrix_to_adjacency_list_ComplexGraph_returnValidList)
        {
            //Создаем тестовый файл
            FILE* file = fopen("complex_matrix.txt", "w");
            fprintf(file, "4\n");
            fprintf(file, "0 1 0 1\n");
            fprintf(file, "1 0 1 1\n");
            fprintf(file, "0 1 0 0\n");
            fprintf(file, "1 1 0 0\n");
            fclose(file);

            Graph* graph = adjacency_matrix_to_adjacency_list("complex_matrix.txt");

            Assert::IsNotNull(graph);
            Assert::AreEqual(4, graph->vertices_count);

            //Проверяем степени вершин
            Assert::AreEqual(2, graph->sizes[0]);
            Assert::AreEqual(3, graph->sizes[1]);
            Assert::AreEqual(1, graph->sizes[2]);
            Assert::AreEqual(2, graph->sizes[3]);

            //Проверяем соседей вершины 1
            Assert::AreEqual(0, graph->adjacency_list[1][0]);
            Assert::AreEqual(2, graph->adjacency_list[1][1]);
            Assert::AreEqual(3, graph->adjacency_list[1][2]);

            free_graph(graph);
            remove("complex_matrix.txt");
        }
    };

    TEST_CLASS(MemoryTests)
    {
    public:

        //Тест на освобождение нулевого указателя
        TEST_METHOD(free_graph_NullPointer_NoCrash)
        {
            free_graph(nullptr);
        }

        //Тест на освобождение валидного графа
        TEST_METHOD(free_graph_ValidGraph_MemoryFreed)
        {
            Graph* graph = create_graph(3);
            add_edge(graph, 0, 1);
            add_edge(graph, 0, 2);
            free_graph(graph);
            
        }

        //Тест на освобождение графа с ребрами
        TEST_METHOD(free_graph_GraphWithEdges_MemoryFreed)
        {
            Graph* graph = create_graph(4);
            add_edge(graph, 0, 1);
            add_edge(graph, 0, 2);
            add_edge(graph, 1, 3);
            free_graph(graph);

        }
    };
}