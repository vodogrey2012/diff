#include "node.h"
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <assert.h>
#include <cstdio>
#include <cmath>
#include <unistd.h>

#define SHOWSTEP 0

/**
realeased:
alg : +, -, *, /, ^     , sin, cos , tg , ctg , sh , ch , th , cth , arcsin , arccos , arctg , arcctg , exp , ln , log , sqrt , abs;
diff: +, -, *, /, x^, ^x, sin, cos,  tg , ctg   sh , ch , th , cth , arcsin , arccos , arctg , arcctg , exp , ln , log , sqrt , abs , x, c,
**/

node :: node(char* message)
{
    sscanf(message , "%ms" , &data);
    //printf("%s" , data);
    left = NULL;
    right = NULL;
    is_number = true;
    return;
}

node :: node()
{
    data = NULL;
    left = NULL;
    right = NULL;
    is_number = true;
    return;
}

node :: ~node()
{
    if(data)
        free(data);
    if(left)
        free(left);
    if(right)
        free(right);
    return;
}

void node :: change_data(const char* message)
{
    sscanf(message , "%ms" , &data);
    return;
}

void node :: add_node(char** ptext , const char* last)
{
    char c;
    char* word;
    while (*ptext < last)
    {
        sscanf(*ptext , "%c" , &c);
        if(c == '(')
        {
            //printf("open-");
            (*ptext)++;
            if(left == NULL)
            {
                left = new node();
                (*left).add_node(ptext , last);
            }
            else
            {
                right = new node();
                (*right).add_node(ptext , last);
            }
        }
        else if(c == ')')
        {
            //printf("close-");
            (*ptext)++;
            return;
        }

        else if((*ptext) < last)
        {
            //printf("word-");
            sscanf(*ptext, "%m[^()]" , &word);
            (*ptext) += strlen(word);
            data = word;
        }

    }
    //printf("end-");
    return;

}

void node :: print_tree()
{
    printf("(%s" , data);
    if(left)
        (*left).print_tree();
    if(right)
        (*right).print_tree();
    printf(")");
    return;
}

void node :: alg_tree(bool count_func)
{
    if(left)
        (*left).alg_tree(count_func);
    if(right)
        (*right).alg_tree(count_func);
    if(left || right)
        alg(count_func);
    if(SHOWSTEP)
    {
        (*this).print_tree();
        printf("\n");
    }

    return;


}

void node :: alg(bool count_func)
{
    if((left && (*(left->data) == 'x')) || (right && (*(right->data) == 'x')))
    {
        is_number = false;
        return;
    }

    if((left && ((left -> is_number) == false)) || (right && ((right -> is_number) == false)))
    {
        is_number = false;
        return;
    }

    double a = 0;
    double b = 0;
    if(left)
        a = atof(left->data);
    if(right)
        b = atof(right->data);

    if(!strcmp(data , "+"))
    {
        sprintf(data , "%g" , (a + b));
    }

    else if(!strcmp(data , "-"))
    {
        sprintf(data , "%g" , (a - b));
    }

    else if(!strcmp(data , "*"))
    {
        sprintf(data , "%g" , (a * b));
    }

    else if(!strcmp(data , "/"))
    {
        if(b == 0)
        {
            printf("Invalid input: div 0\n");
            exit(0);
        }
        sprintf(data , "%g" , (a / b));
    }

    else if(!strcmp(data , "sin"))
    {
        if (count_func)
        {
            sprintf(data , "%g" , sin(a + b));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "cos"))
    {
        if (count_func)
        {
            sprintf(data , "%g" , cos(a + b));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "tg"))
    {
        if (count_func)
        {
            sprintf(data , "%g" , tan(a + b));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "ctg"))
    {
        if (count_func)
        {
            sprintf(data , "%g" , (1/tan(a + b)));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "sh"))
    {
        if (count_func)
        {
            sprintf(data , "%g" , sinh(a + b));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "ch"))
    {
        if (count_func)
        {
            sprintf(data , "%g" , cosh(a + b));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "th"))
    {
        if (count_func)
        {
            sprintf(data , "%g" , tanh(a + b));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "cth"))
    {
        if (count_func)
        {
            sprintf(data , "%g" , (1/tanh(a + b)));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "exp"))
    {
        if (count_func)
        {
            sprintf(data , "%g" , (exp(a + b)));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "arcsin"))
    {
        if(((a + b) > 1) && ((a + b) < -1) )
        {
            printf("Invalid data: arcsin arg\n");
            exit(0);
        }
        if (count_func)
        {
            sprintf(data , "%g" , (asin(a + b)));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "arccos"))
    {
        if(((a + b) > 1) && ((a + b) < -1) )
        {
            printf("Invalid data: arccos arg\n");
            exit(0);
        }
        if (count_func)
        {
            sprintf(data , "%g" , (acos(a + b)));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "arctg"))
    {
        if (count_func)
        {
            sprintf(data , "%g" , (atan(a + b)));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "arcctg"))
    {
        if (count_func)
        {
            sprintf(data , "%g" , (atan(1/(a + b))));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "ln"))
    {
        if((a + b) < 0)
        {
            printf("Invalid data: ln arg\n");
            exit(0);
        }
        if (count_func)
        {
            sprintf(data , "%g" , (log(a + b)));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "log"))
    {
        if((a + b) < 0)
        {
            printf("Invalid data: log arg\n");
            exit(0);
        }
        if (count_func)
        {
            sprintf(data , "%g" , (log10(a + b)));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "sqrt"))
    {
        if((a + b) < 0)
        {
            printf("Invalid data: sqrt arg\n");
            exit(0);
        }
        if (count_func)
        {
            sprintf(data , "%g" , (sqrt(a + b)));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "abs"))
    {
        if (count_func)
        {
            sprintf(data , "%g" , (fabs(a + b)));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else if(!strcmp(data , "^"))
    {

        if((a == 0) && (b == 0))
        {
            printf("Invalid data: 0^0\n");
            exit(0);
        }
        if (count_func)
        {
            sprintf(data , "%g" , (pow(a , b)));
        }
        else
        {
            is_number = false;
            return;
        }
    }

    else
    {
        printf("Unknown function: %s" , data);
        exit(0);
    }


    kill_children();
    left = NULL;
    right = NULL;
    return;
}

void node :: kill_children()
{
    delete(left);
    delete(right);
    left = NULL;
    right = NULL;
}

void node :: diff_tree()
{
    if(!strcmp(data , "+"))
    {
        (*left).diff_tree();
        (*right).diff_tree();
    }

    else if(!strcmp(data , "-"))
    {
        (*left).diff_tree();
        (*right).diff_tree();
    }

    else if(!strcmp(data , "*"))
    {
        node* n_left = (*this).copy_tree();
        node* n_right = (*this).copy_tree();
        (*left).kill_tree();
        (*right).kill_tree();
        left = n_left;
        right = n_right;
        change_data("+");
        (*(left->left)).diff_tree();
        (*(right->right)).diff_tree();
    }

    else if(!strcmp(data , "^"))
    {
        if(strstr(right->data , "x") && !strstr(left->data , "x"))
        {
            node* save_diff = (*right).copy_tree();
            node* save_step = (*right).copy_tree();
            node* save_base1 = (*left).copy_tree();
            node* save_base2 = (*left).copy_tree();
            (*left).kill_tree();
            (*right).kill_tree();
            change_data("*");
            left = new node("ln");
            left->left = save_base1;
            right = new node("*");
            right->left = new node("^");
            (right->left)->left = save_base2;
            (right->left)->right = save_step;
            right->right = save_diff;
            (*(right->right)).diff_tree();
        }
        else if(!strstr(right->data , "x") && strstr(left->data , "x"))
        {
            node* save_const = (*left).copy_tree();
            node* save_diff = (*left).copy_tree();
            node* step = (*right).copy_tree();
            (*left).kill_tree();
            (*right).kill_tree();
            left = new node("^");
            left->left = save_const;
            left->right = new node("-");
            left->right->left = right;
            left->right->right = new node("1");
            right = new node("*");
            right->left = step;
            right->right = save_diff;
            change_data("*");
            (*(right->right)).diff_tree();
        }
        else
        {
            printf("Invalid differentiation: f(x)^f(x)");
            exit(0);
        }
    }

    else if(!strcmp(data , "exp"))
    {
        node* save_exp = copy_tree();
        node* save_func = (*left).copy_tree();
        (*left).kill_tree();
        change_data("*");
        left = save_exp;
        right = save_func;
        (*right).diff_tree();
    }

    else if(!strcmp(data , "/"))
    {
        node* diff_chisl = (*left).copy_tree();
        node* na_znam = (*right).copy_tree();
        node* diff_znam = (*right).copy_tree();
        node* na_chisl = (*left).copy_tree();
        node* znam = (*right).copy_tree();
        (*left).kill_tree();
        (*right).kill_tree();
        left = new node("-");
        left->left = new node("*");
        left->left->left = diff_chisl;
        left->left->right = na_znam;
        left->right = new node("*");
        left->right->left = diff_znam;
        left->right->right = na_chisl;
        right = new node("^");
        right->left = znam;
        right ->right = new node("2");
        (*(left->left->left)).diff_tree();
        (*(left->right->left)).diff_tree();
    }

    else if(!strcmp(data , "arcsin"))
    {
        node* save = (*left).copy_tree();
        node* diff = (*left).copy_tree();
        (*left).kill_tree();
        change_data("/");
        left = diff;
        right = new node("sqrt");
        right->left = new node("-");
        right->left->left = new node("1");
        right->left->right = new node("^");
        right->left->right->left = save;
        right->left->right->right = new node("2");
        (*left).diff_tree();
    }

    else if(!strcmp(data , "arccos"))
    {
        node* save = (*left).copy_tree();
        node* diff = (*left).copy_tree();
        (*left).kill_tree();
        change_data("/");
        left = new node("*");
        left->left = new node("-1");
        left->right = diff;
        right = new node("sqrt");
        right->left = new node("-");
        right->left->left = new node("1");
        right->left->right = new node("^");
        right->left->right->left = save;
        right->left->right->right = new node("2");
        (*(left->right)).diff_tree();
    }

    else if(!strcmp(data , "arcctg"))
    {
        node* save = (*left).copy_tree();
        node* diff = (*left).copy_tree();
        (*left).kill_tree();
        change_data("/");
        left = new node("*");
        left->left = new node("-1");
        left->right = diff;
        right = new node("+");
        right->left = new node("1");
        right->right = new node("^");
        right->right->left = save;
        right->right->right = new node("2");
        (*(left->right)).diff_tree();
    }

    else if(!strcmp(data , "arctg"))
    {
        node* save = (*left).copy_tree();
        node* diff = (*left).copy_tree();
        //(*left).kill_tree();
        change_data("/");
        left = diff;
        right = new node("+");
        right->left = new node("1");
        right->right = new node("^");
        right->right->left = save;
        right->right->right = new node("2");
        (*left).diff_tree();
    }

    else if(!strcmp(data , "sin"))
    {
        node* all = copy_tree();
        node* diff_arg = (*left).copy_tree();
        (*left).kill_tree();
        change_data("*");
        left = all;
        (*left).change_data("cos");
        right = diff_arg;
        (*right).diff_tree();

    }

    else if(!strcmp(data , "cos"))
    {
        node* all = copy_tree();
        node* diff_arg = (*left).copy_tree();
        (*left).kill_tree();
        change_data("*");
        left = new node("*");
        left->left = new node("-1");
        left->right = all;
        (*(left->right)).change_data("sin");
        right = diff_arg;
        (*right).diff_tree();
    }

    else if(!strcmp(data , "sh"))
    {
        node* all = copy_tree();
        node* diff_arg = (*left).copy_tree();
        (*left).kill_tree();
        change_data("*");
        left = all;
        (*left).change_data("ch");
        right = diff_arg;
        (*right).diff_tree();
    }

    else if(!strcmp(data , "ch"))
    {
        node* all = copy_tree();
        node* diff_arg = (*left).copy_tree();
        (*left).kill_tree();
        change_data("*");
        left = all;
        (*left).change_data("sh");
        right = diff_arg;
        (*right).diff_tree();
    }

    else if(!strcmp(data , "ln"))
    {
        right = (*left).copy_tree();
        change_data("/");
        (*left).diff_tree();

    }

    else if(!strcmp(data , "log"))
    {
        node* save = (*left).copy_tree();
        node* diff = (*left).copy_tree();
        (*left).kill_tree();
        change_data("/");
        left = diff;
        right = new node("*");
        right->left = save;
        right->right = new node("ln");
        right->right->left = new node("10");
        (*left).diff_tree();
    }

    else if(!strcmp(data , "ctg"))
    {
        node* arg = (*left).copy_tree();
        node* diff = (*left).copy_tree();
        (*left).kill_tree();
        change_data("/");
        left = new node("*");
        left->left = new node("-1");
        left->right = diff;
        right = new node("^");
        right->left = new node("sin");
        right->left->left = arg;
        right->right = new node("2");
        (*(left->right)).diff_tree();
    }

    else if(!strcmp(data , "cth"))
    {
        node* arg = (*left).copy_tree();
        node* diff = (*left).copy_tree();
        (*left).kill_tree();
        change_data("/");
        left = new node("*");
        left->left = new node("-1");
        left->right = diff;
        right = new node("^");
        right->left = new node("sh");
        right->left->left = arg;
        right->right = new node("2");
        (*(left->right)).diff_tree();
    }

    else if(!strcmp(data , "tg"))
    {
        node* arg = (*left).copy_tree();
        node* diff = (*left).copy_tree();
        (*left).kill_tree();
        change_data("/");
        left = diff;
        right = new node("^");
        right->left = new node("cos");
        right->left->left = arg;
        right->right = new node("2");
        (*left).diff_tree();
    }

    else if(!strcmp(data , "th"))
    {
        node* arg = (*left).copy_tree();
        node* diff = (*left).copy_tree();
        (*left).kill_tree();
        change_data("/");
        left = diff;
        right = new node("^");
        right->left = new node("ch");
        right->left->left = arg;
        right->right = new node("2");
        (*left).diff_tree();
    }

    else if(!strcmp(data , "sqrt"))
    {
        node* save = copy_tree();
        node* diff = (*left).copy_tree();
        (*left).kill_tree();
        change_data("/");
        left = new node("*");
        left->left = new node("0.5");
        left->right = diff;
        right = save;
        (*(left->right)).diff_tree();
    }

    else if(!strcmp(data , "x"))
    {
        change_data("1");
        assert(!left);
        assert(!right);
    }

    else if(!strcmp(data , "abs"))
    {
        if(!strcmp(left->data , "0"))
        {
            printf("Invalid differentiation: abs(0)");
            exit(0);
        }
        node* arg = (*left).copy_tree();
        change_data("*");
        right = new node("sign");
        right->left = arg;
        (*left).diff_tree();
    }

    else
    {
        change_data("0");
        assert(!left);
        assert(!right);
    }

}

void node :: kill_tree()
{
    /*
    if(left)
        (*left).kill_tree();
    if(right)
        (*right).kill_tree();
    if(left)
        delete left;
    if(right)
        delete right;
    return;*/
}

node* node :: copy_tree()
{
    if(!this)
        return NULL;

    node* ans = new node(data);
    ans->left = (*left).copy_tree();
    ans->right = (*right).copy_tree();

    return ans;
}

int node :: opti()
{
    int ret = 0;
    is_number = true;
    if(left)
        ret = (*left).opti();
    if(right)
        ret = (*right).opti();
    if(left && right)
    {
        if(!strcmp(data , "+")  || !strcmp(data , "-"))
        {
            if(!strcmp(left->data , "0"))
            {
                (*left).kill_tree();
                data = right->data;
                left = right->left;
                right = right->right;
                return 1;
            }
            else if(!strcmp(right->data , "0"))
            {
                (*right).kill_tree();
                data = left->data;
                right = left->right;
                left = left->left;
                return 1;
            }
        }
        if(!strcmp(data , "^"))
        {
            if(!strcmp(left->data , "1"))
            {
                left = NULL;
                right = NULL;
                change_data("1");
                return 1;
            }
            else if(!strcmp(right->data , "1"))
            {
                (*right).kill_tree();
                data = left->data;
                right = left->right;
                left = left->left;
                return 1;
            }
            else if(!strcmp(right->data , "0"))
            {
                (*right).kill_tree();
                change_data("1");
                right = NULL;
                left = NULL;
                return 1;
            }
        }
        else if(!strcmp(data , "*"))
        {
            if(!strcmp(left->data , "0") || !strcmp(right->data , "0"))
            {
                (*left).kill_tree();
                (*right).kill_tree();
                left = NULL;
                right = NULL;
                change_data("0");
                return 1;
            }
            else if(!strcmp(left->data , "1"))
            {
                //(*left).kill_tree();
                data = right->data;
                left = right->left;
                right = right->right;
                return 1;
            }
            else if(!strcmp(right->data , "1"))
            {
                (*right).kill_tree();
                data = left->data;
                right = left->right;
                left = left->left;
                return 1;

            }
        }
    }
    return ret;
}

void node :: add_node_graph(void* file)
{
    fprintf((FILE*)file , "node%p [shape = \"record\" , label = \"{pointer = %p |is_number = %d | data = %s | left = %p | right = %p}\"];\n" , this , this , is_number , data , left , right);
    if(left && left->data)
        (*left).add_node_graph(file);
    if(right && right->data)
        (*right).add_node_graph(file);
    if(left && left->data)
        fprintf((FILE*)file , "node%p -> node%p;\n", this , left);
    if(right && right->data)
        fprintf((FILE*)file , "node%p -> node%p;\n", this , right);
    return;
}

void* node :: create_graph()
{
    FILE* file = fopen("first.dot" , "w");
    fprintf(file , "digraph mi{\n");
    add_node_graph(file);
    fprintf(file , "}\n");
    fclose(file);
    system("dot -Tpng -O first.dot");
    system("xdg-open first.dot.png");
    return 0;
}

const char* output_latex = "out.tex";
const char* compile_latex = "pdflatex out.tex";
const char* output_pdftex = "evince out.pdf";

void* node :: print_latex()
{
    FILE* file = fopen(output_latex , "w");
    //interpret is_number as a bracket condition

    is_number = 0;
    make_brackets();
    fprintf(file ,  "\\documentclass[12pt]{article}\n"
                    "\\usepackage[english]{babel}\n"
                    "\\begin {document}\n"
                    "$$ f'(x) = ");
    print_file_latex(file);
    fprintf(file ,  " $$\n"
                    "\\end{document}\n");
    fclose(file);
    system(compile_latex);
    system(output_pdftex);
    return file;
}

void node :: make_brackets()
{
    // 0 - func
    // 1 - (func)
    // 2 - {func}
    // 3 - func()
    // 4 - frac{}{}
    // 5 - (frac{}{})
    // 6 - {func()}
    // 7 - sqrt{}
    // 8 - (sqrt{})
    // 9 - abs()

    if(!strcmp(data , "sqrt"))
    {
        is_number = 7;
        left->is_number = 0;
    }
    else if(!strcmp(data , "abs"))
    {
        is_number = 9;
        left->is_number = 0;
    }
    else if(!strcmp(data , "*"))
    {
        if(strstr("+-" , left->data))
            left->is_number = 1;
        else
            left->is_number = 0;
        if(strstr("+-" , right->data))
            right->is_number = 1;
        else
            right->is_number = 0;
    }
    else if(!strcmp(data , "^"))
    {
        if((left->left) || (left->right))
            left->is_number = 1;
        else
            left->is_number = 0;
        right->is_number = 2;
    }
    else if(!strcmp(data , "/"))
    {
        is_number = 4;
        left->is_number = 0;
        right->is_number = 0;
    }
    else if(!strcmp(data , "-"))
    {
        if(!strcmp(right->data , "+") || !strcmp(right->data , "-"))
            right->is_number = 1;
        else
            right->is_number = 0;
        left->is_number = 0;
    }
    else if(!strcmp(data , "x"))
    {
        if(is_number != 2)
                is_number = 0;
    }
    else if((strcmp(data , "+")) && (!right) && (left))
    {
        if(is_number == 2)
            is_number = 6;
        else
            is_number = 3;
        left->is_number = 0;
    }
    else
    {
        if(left)
            left->is_number = 0;
        if(right)
            right->is_number = 0;
    }

    if(left)
        (*left).make_brackets();
    if(right)
        (*right).make_brackets();

    return;
}

void node :: print_file_latex(void* file)
{
    // 0 - func
    // 1 - (func)
    // 2 - {func}
    // 3 - func()
    // 4 - frac{}{}
    // 5 - (frac{}{})
    // 6 - {func()}
    // 7 - sqrt{}
    // 8 - (sqrt{})
    // 9 - abs()

    switch(is_number)
    {
    case 0:
        {
            //assert((left && right) || (!left && !right));
            //printf("is_number = %d" , is_number);
            if(left && right)
            {
                (*left).print_file_latex(file);
                fprintf((FILE*)file , "%s" , data);
                (*right).print_file_latex(file);
            }
            else if(!left && !right)
            {
                fprintf((FILE*)file , "%s" , data);
            }
            break;
        }
    case 1:
        {
            assert((left && right) || (!left && !right));
            fprintf((FILE*)file , "(");
            if(left && right)
            {
                (*left).print_file_latex(file);
                fprintf((FILE*)file , "%s" , data);
                (*right).print_file_latex(file);
            }
            else if(!left && !right)
            {
                fprintf((FILE*)file , "%s" , data);
            }
            fprintf((FILE*)file , ")");
            break;
        }
    case 2:
        {
            assert((left && right) || (!left && !right));
            fprintf((FILE*)file , "{");
            if(left && right)
            {
                (*left).print_file_latex(file);
                fprintf((FILE*)file , "%s" , data);
                (*right).print_file_latex(file);
            }
            else if(!left && !right)
            {
                fprintf((FILE*)file , "%s" , data);
            }
            fprintf((FILE*)file , "}");
            break;
        }
    case 4:
        {
            fprintf((FILE*)file , "\\frac{");
            (*left).print_file_latex(file);
            fprintf((FILE*)file , "}{");
            (*right).print_file_latex(file);
            fprintf((FILE*)file , "}");
            break;
        }
    case 5:
        {
            fprintf((FILE*)file , "(\\frac{");
            (*left).print_file_latex(file);
            fprintf((FILE*)file , "}{");
            (*right).print_file_latex(file);
            fprintf((FILE*)file , "})");
            break;
        }
    case 3:
        {
            fprintf((FILE*)file , "%s(" , data);
            (*left).print_file_latex(file);
            fprintf((FILE*)file , ")");
            break;
        }
    case 6:
        {
            fprintf((FILE*)file , "{%s(" , data);
            (*left).print_file_latex(file);
            fprintf((FILE*)file , ")}");
            break;
        }
    case 7:
        {
            fprintf((FILE*)file , "\\sqrt{" , data);
            (*left).print_file_latex(file);
            fprintf((FILE*)file , "}");
            break;
        }
    case 8:
        {
            fprintf((FILE*)file , "\\(sqrt{" , data);
            (*left).print_file_latex(file);
            fprintf((FILE*)file , "})");
            break;
        }
    case 9:
        {
            fprintf((FILE*)file , "|" , data);
            (*left).print_file_latex(file);
            fprintf((FILE*)file , "|");
            break;
        }

    default:
        {
            exit(2);
        }

    }
    return;


}




