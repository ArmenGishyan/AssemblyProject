#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "LexicalAnalysis.h"
#include "SemanticAnalysis.h"
#include "CodeGeneration.h"
#include "varRegWrap.h"

using namespace std;


int main()
{   int a=0;
    LexicalAnalayser myFile;
   
    myFile.GetFile();
    myFile.MakeExpressioncMatrix();
    myFile.print();
    CodeGeneration Codeobj(myFile.PassMatrixToCodeGen());
    Codeobj.DataSegment();
    Codeobj.CodeSegment();
    
   // CodeGeneration obj("assemblyOutput.txt","inputFile.txt");
  //  obj.ReadFromFile();



    return 0;
}