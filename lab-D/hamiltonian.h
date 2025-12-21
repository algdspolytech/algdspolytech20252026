// hamiltonian.h
/**
 * @file hamiltonian.h
 * @brief Заголовочный файл
 *
 * @version 1.0
 * @date 2025.12.21
 * @author Д.Смирнов
 */

#pragma once

// Константы
#define MAX_VERTICES 100

 // Глобальные переменные для упрощения передачи между функциями
extern int adj[MAX_VERTICES + 1][MAX_VERTICES + 1];
extern int visited[MAX_VERTICES + 1];
extern int path[MAX_VERTICES];
extern int n;



void initializeData();
int readGraphFromFile(const char* filename);
int Hamiltonian(int current, int step);
int HamiltonianFromAnyVertex();
void writeResultToFile(const char* filename, int found);
void HumiltonianFinder();

void UnitTests();