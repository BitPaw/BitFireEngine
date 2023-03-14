# Compiler
A compiler can convert text based code into executable content. Depending on wanted output. 

## Steps overview
|Name|Input|Output|Goal|Examples|
|:-:|:-:|:-:|:-:|:-|
|Lexer<br>(Lexical-Analyser)|Text|Symbols/Tokens|Remove humaniod elements,<br>like empty spaces, new lines and comments. | Keywords (if, while, ...)<br>Symbols ( =, ; , ... )<br>Operators (+, -, ==, ...)<br>Types/Literals (number, bool, char, string)<br>Control Token (End of file) |
|Parser|Symbols/Tokens|Symbol-Tree-Structure|Structure elements in a logical tree,<br>that then can be evaluated| - |
|Evaluator|???|???|-|-|
|Typechecker|???|???|Check if types are useable in this context<br>And if they are expected.|-|

## Steps in detail
### Lexer

> Input: Raw text<br>
> Result: A large **list** of these **symbole blocks**.

Whats a block, token or symbol.. even?<br>

We could just define it as an enum or we can use inheritence, depending on preference.<br>
Also.. to not lose the context of the "real" text, we need to add this here and now.<br>
As an example, if we find an error, we want to still have the information where exactly it is, so we can give this information back to the user.

So a **symbol object** can look like the following.
|Name|Purpose|
|:-:|:-:|
|Symbol ID<br>(enum)|The deteced symbol|
|Line (X)| Line where the symbol was read|
|Column (Y)|The offset in the line|
|File| File where the symbol resides|

To convert text into blocks, read each character one by one. **ReadNextCharacter()**<br>
If you detect a known symbol, check if it needs to be scaned further. **PeekNextCharacter()**<br>
Only consume if a symbol is successfully deteced.

### Parser

> Input: The **symbole block list**<br>
> Output: The same as the input, with added tree structure.

Now we loop trough the input list. We give each block more context and merge them together.<br>
As an example, an **if** will look as the following Lexer-Output..

|if|(|NamedSymbol|And|NamedSymbol|)|{|NamedSymbol|(|)|EndOfCommand|}|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|

And after the parsing step, we now have something like..
|If||
|:-:|:-:|
|Condition|Expression ... |
|Body if true |Function Call ...|
|Body if false | Empty/Null|

Here we can now check if the syntax is correct, as we only now add the context of order.<br>
Commonly, here you can create a list of found errors. To not stop just because you found one, skip blocks to parse further.<br>
The full list can be show to the user after parsing the full file.

It will be a very complex structure. Often, at this point there is alot of performance lost if memory allocations are overused.<br>
To fight this, one should work in a preallocated buffer to avoid numberous allocations.<br>
For that, a well designed sturcture is needed.

### Evaluator
...

### Typechecker
...

