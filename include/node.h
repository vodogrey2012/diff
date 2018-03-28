#ifndef NODE_H
#define NODE_H


class node
{
private:
    int is_number;
    char* data;
    node* left;
    node* right;

    void alg(bool count_func);
    node* copy_tree();
    void kill_tree();
    void add_node_graph(void* file);
    void make_brackets();
    void print_file_latex(void* file);

public:
    node(char* message);
    node();
    ~node();

    void change_data(const char* message);
    void add_node(char** ptext , const char* last);
    void print_tree();
    void alg_tree(bool count_tree);
    void kill_children();
    void diff_tree();
    int opti();
    void* create_graph();
    void* print_latex();
};

#endif // NODE_H
