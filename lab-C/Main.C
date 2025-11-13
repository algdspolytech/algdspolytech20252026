#include <stdio.h>
#include <stdlib.h>
#include "Graph.H"
#include "Tests.H"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

void UnitTests(void)
{
	FileParsing__NonExistFile();
	FileParsing__EmptyFile();
	FileParsing__NotEmptyFile();
	ListParsing__IncorrectSymbol();
	ListParsing__ManySpaces();
	ListParsing__EmptyLines();
	ListParsing__EmptyString();
	ListParsing__ZeroEdges();
	MatrixCreate__NonExistingNodes();
	MatrixCreate__EmptyMatrix();
}

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	UnitTests();

	return 0;
}
