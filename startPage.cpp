#include <iostream>
#include "LexicalAnalysis.h"
#include "CodeGeneration.h"

int main()
{  
    LexicalAnalayser myFile;
   
    myFile.GetFile();
    myFile.MakeExpressioncMatrix();
    
    CodeGeneration Codeobj(myFile.PassMatrixToCodeGen());
    Codeobj.DataSegment();
    Codeobj.CodeSegment();
    
    return 0;
}