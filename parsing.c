#include <stdio.h>
#include "mpc.h"

static char input[2048];

int main(int argc, char** argv){

    /*Create some parsers*/
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Lispy = mpc_new("lispy");

    /*Define them*/
    mpca_lang(MPCA_LANG_DEFAULT,
    "                                                       \
        number   : /-?[0-9]+/ ;                             \
        operator : '+' | '-' | '*' | '/' ;                  \
        expr     : <number> | '(' <operator> <expr>+ ')' ;  \
        lispy    : /^/ <operator> <expr>+ /$/ ;             \
    ",
    Number, Operator, Expr, Lispy);
    

    puts("Lispy version 0.0.0.0.1");
    puts("Press Ctrl+C to Exit\n");

    while(1){

        fputs("lispy> ",stdout);

        fgets(input, 2048, stdin);

        //printf("No you're a %s", input);

        mpc_result_t r;
        if (mpc_parse("<stdin>",input,Lispy, &r)){
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
    }

    //Cleaning up pointers
    mpc_cleanup(4, Number, Operator, Expr, Lispy);

    return 0;
}