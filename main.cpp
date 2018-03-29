#include <iostream>
#include <stdio.h>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <node.h>

#define DOALGEBRA false

///+(ctg(3))(/(^(x)(+(sin(x))(ln(-(^(x)(2))(4))))(cos(+(^(sin(1))(2))(*(x)(4))))))

///+(ctg(3))(/(^(x)(+(sin(x))(ln(-(^(x)(2))(4)))))(cos(+(^(sin(1))(2))(*(x)(4)))))


using namespace std;

struct func
{
    char* name = NULL;
    int n_opend = 0;
    int n_closed = 0;
};

node* scan_message();


int main()
{
    node* a = scan_message();



    do
    {
        (*a).alg_tree(DOALGEBRA);
    }
    while((*a).opti());



    (*a).diff_tree();


    do
    {
        (*a).alg_tree(DOALGEBRA);
    }
    while((*a).opti());

    (*a).create_graph();
    (*a).print_latex();



    return 0;
}


node* scan_message()
{
    char* text = (char*)calloc(100 , sizeof(char));
    sprintf(text , "+(ctg(3))(/(^(x)(+(sin(x))(ln(-(^(x)(2))(4)))))(cos(+(^(sin(1))(2))(*(x)(4)))))");
    //scanf("%m[^\n]" , &text);
    node* base = new node();
    (*base).add_node(&text , text + strlen(text));
    return base;

}

