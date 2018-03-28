#include <iostream>
#include <stdio.h>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <node.h>

#define DOALGEBRA false


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
    char* text;
    scanf("%m[^\n]" , &text);
    node* base = new node();
    (*base).add_node(&text , text + strlen(text));
    return base;

}

