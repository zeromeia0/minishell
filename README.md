# Minishell - A "simple" shell based on bash

## A fully functional shell that deals with commands, redirections, pipes and logical tokens.

This project was aimed to create a "simple" interactive command interpreter, or a shell that deals with basic command prompts, anything from a simple command execution to complex commands with multiple instructions.
Our program also supports the execution of commands while reading from files, also know shell scripts.

This project was devided into 3 crucial roles.

* Lexer
* Parser
* Executor

## Lexer

The lexer starts off by receiving the information provided to by the user as a string. First the tokenization of the information happens, meaning the string gets devided into chunks of more digestable informations. We devide everything by spaces and special tokens.

* (tokenization example 1) string to matrix
* (tokenization example 2)
* (tokenization example 3)

After the information gets tokenized we get those tokens we verify that theres no syntax erros on the part of the user such as:

* (lexer example 1) syntax the matrix

        "< in cat > out" = {"in" "cat" ">" "out"}
* (lexer example 2)
* (lexer example 3)

If there is no syntax errors, the information (now tokenized) gets to the parser.

## Parser

After the lexer has verified the syntax to be correct/parseble we parse the tokens into structures more easily interpreted but the executer.

While paying attention to the priority of execution we chose to devide the different commands in a binary tree by the logical value of tokens found like so:

* (tree parse example 1) parse the matrix into the structures
* (tree parse example 2)
* (tree parse example 3)

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
* (commands list parse example 2)
* (commands list parse example 3)

## Executor

