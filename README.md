# Minishell - A "simple" shell based on bash

## A fully functional shell that deals with commands, redirections, pipes and logical tokens.

This project was aimed to create a "simple" interactive command interpreter, or a shell that deals with basic command prompts, anything from a simple command execution to complex commands with multiple instructions.

Our program also supports the execution of commands while reading from files, also know shell scripts.
This project was devided into 2 crucial roles.

* Parser
* Executor

## Parser

The parser starts off by receiving the information provided to by the user as a string. First the tokenization of the information happens, meaning the string gets devided into chunks of more digestable informations. We devide everything by spaces and special tokens.

* (example 1)
* (example 2)
* (example 3)

After the information gets tokenized we get those tokens we verify that theres no syntax erros on the part of the user such as:

* (parse example 1)
* (parse example 2)
* (parse example 3)

If there is no syntax errors the information (now tokenized) gets put into structures for easier execution in the later steps