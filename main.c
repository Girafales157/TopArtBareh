#include "structs.h"
#include "func.h"
#include <locale.h>

int main(int argc, char const *argv[]){
    setlocale(LC_ALL, "Portuguese");
    
    menu();
    
    return 0;
}
