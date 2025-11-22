#ifndef NQUEENS_H
#define NQUEENS_H

#ifdef __cplusplus
extern "C" {
#endif

	// Возвращает 1 — если найдено, заполняет out[i] = колонка для ряда i
	int solve_nqueens(int n, int* out);

	// С файлами
	int solve_nqueens_task(const char* input_file, const char* output_file);

#ifdef __cplusplus
}
#endif

#endif