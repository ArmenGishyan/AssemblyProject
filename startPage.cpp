#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "LexicalAnalysis.h"
#include "SemanticAnalysis.h"
#include "CodeGeneration.h"

using namespace std;


int main()
{   
    LexicalAnalayser myFile;
    //myFile.GetFile();
    CodeGeneration obj("assemblyOutput.txt","inputFile.txt");
    obj.ReadFromFile();



    return 0;
}