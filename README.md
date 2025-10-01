# Minishell - A "simple" shell based on bash

## Step by Step Explanation on How to Download, Execute and Use Our Shell:
1. step by step explanation.

## Code explenation: A Fully Functioning Shell That Deals With Commands, Redirections, Pipes And Logical Expressions

This project aims to create a "simple" interactive command interpreter, or a shell that deals with basic command prompts, anything from a simple command execution to complex commands with multiple instructions.
Our program also supports the execution of commands while reading from files, also know shell scripts.

The project completion was devided into 3 crucial roles.

* Lexer
* Parser
* Executor

## Lexer

The lexer starts off by receiving the information provided to by the user as a string. First the tokenization of the information happens, meaning the string gets devided into chunks of more digestable informations. We devide everything by spaces and special tokens basically dividing a string into a matrix.

### Tokenization
* [< in cat > out] = [<] [in] [cat] [>] [out]
* [>out1<""in cat >out2>>out3] = [>] [out1] [<] [in] [cat] [>] [out2] [>>] [out3]
* ["cat Makefile"< in>'out file'] = ["cat Makefile"] [<] [in] [>] ['out file']
* ["cat Make""file"||< in>'out file'|cat< in"_file"] = ["cat Make""file"] [||] [<] [in] [>] [out file] [|] [cat] [<] [in_"file"]


After the information gets tokenized we get those tokens and verify that theres no syntax erros on the part of the user such as:

### Syntax Verification

Inline-style: 
![alt text](https://github.com/zeromeia0/minishell/blob/main/i.png "Logo Title Text 1")



* open quotations (we chose to verify this part during the last step): a single ' or "
* open parenthesis: a single ) or (
* command ending in redirection or logical expressions: >, <, && or ||
* command starting with a logical expression: && or ||
* command with tokens followed by incompatible tokens: && &&, >> &&, > >, [not_a_token] (, ( ), ) (


If there are no syntax errors, the information (now tokenized) gets to the parser.

If there are any syntax errors we clear all allocated memory and return the prompt to the user.

## Parser

After the lexer has verified the syntax to be correct/parseble we parse the tokens into structures more easily interpreted but the executer.

While paying attention to the priority of execution we chose to devide the different commands in a binary tree by the logical value of tokens found like so:

### Structures Visualization
* (tree parse example 1) parse the matrix into the structures

Knowing that the return of each command defined how the "tree" of commands was to be executed we found that a tree type structure made the more sense for this type of information "parsing". 
            <!-- define complex command -->

After the multiple complex commands have been stored in the tree we once again devide the information in the tree nodes into even more digestable tokens on linked lists.

Here we use linked lists as the processing of the information is completely linear. We read and subsequently execute the information from left to right.
            <!-- define complex command -->

<a href="https://www.youtube.com/watch?v=E6NO0rgFub4"
target = "_blank">
LINK

Every simple command in between pipes '|' gets formatted into a single node of the linked list.
That same node has every input and output redirection accompanied by that command, meaning every input and output redirection in between the same pipes

* (commands list parse example 1) parse the information of the tree nodes into the apropriate lists;

## Executor
