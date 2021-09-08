# Leopard Compiler

> There may be some display mistakes due to GitHub Markdown interpreter, so you can download and read this tutorial.

**The full text has a total of `19927` characters, and the recommended reading time is `3~5` hours.**

This is a compiler of `C0` language.

* This project is constructed with `CMake`, which means the execution requires a `Cmake` suite on your platform.

* `submit.ps1` will generate a `.zip` file containing `./include` and `./src`.

* `test.ps1` will compile `./bin/testfile.txt` and run in `Mars` simulator whose output is saved in `./bin/output.txt`.

# 0 Overview

This project is called `Leopard`, which is a high-level language compiler for `C0` language grammar. It supports the conversion of `C0` language into target code executable on the processor of `MIPS` architecture. At the same time, the code optimization module introduced in `Leopard` can effectively improve the execution efficiency of the target code. Therefore, `Leopard` is a `C0` language compiler with practical significance and practical value.

The design document will give a detailed introduction to the implementation process of the project from five aspects: lexical analysis, syntax analysis, error handling, code generation, and code optimization. Each part will have corresponding realization logic and theoretical explanation for readers' reference.

If readers encounter any problems during the reading process, please contact silencejiang12138@gmail.com, and the author will try to reply as soon as possible.

# 1 Grammar Interpretation

## 1.1 Rules

**1. \<Addition operator\> ::= +｜-**

**2. \<Multiplication Operator\> ::= \*｜/**

**3. \<Relational Operator\> ::= \<｜\<=｜\>｜\>=｜!=｜==**

**4. \<Letter\> ::= ＿｜a｜. . . ｜z｜A｜. . . ｜Z**

**5. \<Number\> ::= 0｜1｜. . . ｜9**

**6. \<Character\> ::='\<Addition operator\>'｜'\<Multiplication operator\>'｜'\<Letter\>'｜'\<Number\>'**

* `'` is **terminator**

**7. \<String\> ::= "{ASCII characters with decimal code 32,33,35-126}"**

* At least one character is required in the string
* 32: Space
* 33: Exclamation mark
* 34: double quotes
* 39: single quotation mark

**8. \<Program\> ::= [\<Constant description\>] [\<Variable description\>] {\<Function definition with return value\>|\<Function definition without return value\>}\<Main function\>**

**9. ＜Constant description＞ ::= const＜constant definition＞;{ const＜constant definition＞;}**

**10. \<Constant Definition\> ::= int\<Identifier\>=\<Integer\>{,\<Identifier\>=\<Integer\>} | char\<Identifier\>=\<Character\>{,\<Identifier\>=\<Character ＞}**

**11. ＜Unsigned integer＞ ::= ＜Number＞{＜Number＞}**

**12. \<Integer\> ::= [＋｜－] \<Unsigned integer\>**

**13. \<Identifier\> ::= \<Letter\> {\<Letter\>｜\<Number\>}**

* Identifiers and reserved words are not case sensitive. For example, if and IF are reserved words, the same identifiers as reserved words are not allowed.

**14. \<Declaration header\> ::= int\<identifier\> |char\<identifier\>**

**15. ＜Constant＞ ::= ＜Integer＞|＜Character＞**

**16. ＜Variable description＞ ::= ＜Variable definition＞;{＜Variable definition＞;}**

**17. ＜Variable definition＞ ::= ＜Variable definition without initialization＞|＜Variable definition and initialization＞**

**18. \<Variable definition without initialization\> ::= \<Type identifier\>(\<Identifier\>|\<Identifier\>'['\<Unsigned integer\>']'|\<Identifier\>'['＜Unsigned Integer\>']''['\<Unsigned Integer\>']'){,(\<Identifier\>|\<Identifier\>'['\<Unsigned Integer\>']'|\<Identifier\>'['\<None Signed integer\>']''['\<unsigned integer\>']' )}**

* Variables include simple variables, one-dimensional and two-dimensional arrays. \<Unsigned integer\> represents the number of elements in each dimension of the array, and its value must be greater than 0. The array elements are stored in row priority.

* When the variable is not initialized **no initial value**

* Extract the common factor:

  ＜Variable definition without initialization＞ ::=

  \<Type identifier\> \<Identifier\>

  ('['\<unsigned integer\>']'|'['\<unsigned integer\>']''['\<unsigned integer\>']'|\<empty\>)

  {,(\<Identifier\>|\<Identifier\>'['\<Unsigned integer\>']'|\<Identifier\>'['\<Unsigned integer\>']''['\<Unsigned integer\>']' )}

**19. \<Variable definition and initialization\> ::= \<Type identifier\>\<Identifier\>=\<Constant\>|\<Type identifier\>\<Identifier\>'['\<Unsigned integer\>']'='{ '\<constant\>{,\<constant\>}'}'|\<type identifier\>\<identifier\>'['\<unsigned integer\>']''['\<unsigned integer\>']'='{'' {'\<Constant\>{,\<Constant\>}'}'{,'{'\<Constant\>{,\<Constant\>}'}'}'}'**

* Simple variables, one-dimensional and two-dimensional arrays can be assigned initial values ​​when they are declared. \<Unsigned integer\> represents the number of elements in each dimension of the array, and its value must be greater than 0. The array elements are stored in line first, \<constant\> The type of should be exactly the same as the \<type identifier\>, otherwise an error will be reported; the number of initial values ​​of each dimension is consistent with the number of elements of the dimension, otherwise an error will be reported, and there will be no default value.

* Extract the common factor:

  \<Variable definition and initialization\> ::=

  \<Type identifier\> \<Identifier\>

  (=\<constant\>|'['\<unsigned integer\>']'='{'\<constant\>{,\<constant\>}'}'|'['\<unsigned integer\>']''['＜none Signed integer\>']'='{''{'\<constant\>{,\<constant\>}'}'{,'{'\<constant\>{,\<constant\>}'}'}'}')

**20. \<Type identifier\> ::= int | char**

**21. ＜Function definition with return value＞ ::= ＜Declaration head＞'('＜Parameter table＞')''{'＜Compound statement＞'}'**

**22. ＜No return value function definition＞ ::= void＜identifier＞'('＜Parameter table＞')''{'＜Compound statement＞'}'**

**23. \<Compound sentence\> ::= [\<Constant description\>] [\<Variable description\>] \<Sentence list\>**

**24. ＜Parameter table＞ ::= ＜type identifier＞＜identifier＞{,＜type identifier＞＜identifier＞}| ＜empty＞**

**25. ＜Main function＞ ::= void main'('')''{'＜Compound statement＞'}'**

**26. \<Expression\> ::= [＋｜－] \<term\> {\<addition operator\> \<term\>}**

* [+|-] only works on the **first**\<item\>

**27. ＜term＞ ::= ＜factor＞ {＜multiplication operator＞＜factor＞}**

**28. \<factor\> ::= \<identifier\>｜\<identifier\>'['\<expression\>']'|\<identifier\>'['\<expression\>']''['\<expression ＞']'|'('\<Expression\>')'｜\<Integer\>|\<Character\>|\<Function call statement with return value\>**

* For variables or constants of char type, use the integer corresponding to the character's ASCII code to participate in the operation.
* The \<expression\> in \<identifier\>'['\<expression\>']' and \<identifier\>'['\<expression\>']''['\<expression\>']' can only be integers Type, the subscript starts from 0.
* A single \<identifier\> does not include the array name, that is, the array cannot participate in the operation as a whole, and the array elements can participate in the operation.

**29. \<Sentence\> ::= \<Loop statement\>｜\<Conditional statement\>| \<Function call statement with return value\>; |\<Function call statement without return value\>;｜\<Assignment statement\>;｜\<Read statement\> ;｜\<write sentence\>;｜\<case sentence\>｜\<empty\>;|\<return sentence\>; |'{'\<sentence list\>'}'**

**30. \<Assignment Statement\> ::= \<Identifier\>=\<Expression\>|\<Identifier\>'['\<Expression\>']'=\<Expression\>|\<Identifier\>'['\<Expression Formula\>']''['\<Expression\>']' =\<Expression\>**

* \<Identifier\>=\<Identifier\> in \<Expression\> cannot be a constant name or an array name

**31. \<conditional statement\> ::= if'('\<condition\>')'\<sentence\> [else\<sentence\>]**

**32. \<condition\> ::= \<expression\> \<relational operator\> \<expression\>**

* Expressions must be of integer type in order to be compared

**33. \<Loop statement\> ::= while'('\<condition\>')'\<sentence\>| for'('\<Identifier\>=\<Expression\>;\<Condition\>;\<Identifier\>=\<Identification Symbol\>(+|-)\<step\>')'\<sentence\>**

* for statement **Condition judgment first**, then enter the loop body if the conditions are met

**34. ＜Step length＞::= ＜Unsigned integer＞**

**35. \<Case statement\> ::= switch'('\<Expression\>')''{'\<Case table\>\<default\>'}'**

**36. \<Situation table\> ::= ＜Case sub-sentence\> {\<Case sub-sentence\>}**

**37. \<Case sub-statement\> ::= case\<constant\>: \<statement\>**

**38. \<default\> ::= default: \<sentence\>**

* In the case statement, only int and char types are allowed in the expression after switch and the constant after case; after each case statement is executed, the subsequent case statement is not executed.

**39. \<Function call statement with return value\> ::= \<Identifier\>'('\<Value parameter list\>')'**

**40. ＜No return value function call statement＞ ::= ＜identifier＞'('＜Value parameter table＞')'**

* When calling a function, only functions that have been defined before can be called. This is true for functions that return a value or not.

**41. ＜Value parameter table＞ ::= ＜Expression＞{,＜Expression＞}｜＜Empty＞**

* The expression of the actual parameter cannot be an array name, but an array element.
* The calculation sequence of the actual parameters requires that the generated object code run result is consistent with the run result of the Clang8.0.1 compiler.

**42. \<Sentence list\> ::= ｛\<Sentence\>}**

**43. \<Reading sentence\> ::= scanf'('\<Identifier\>')'**

* Obtain the value of \<identifier\> from standard input. The identifier cannot be a constant name or an array name.
* When the generated PCODE or MIPS assembly is running, for each scanf statement, no matter the type of the identifier is char or int, a carriage return is required at the end; the input data in the testin.txt file is also on one line for each item
* Follow the usage of syscall instruction when generating MIPS assembly

**44. ＜Write sentence＞ ::= printf'(' ＜String＞,＜Expression＞')'| printf'('＜String＞')'| printf'('＜Express＞') '**

* When printf'(' ＜string＞,＜expression＞')' is output, first output the content of the string, and then output the value of the expression, there is no space between the two.
* When the expression is a character type, output characters; when it is an integer type, output an integer.
* \<string\> output as is** (no escape)**
* The content of each printf statement is output to one line and processed as a newline character at the end \n.

**45. \<Return Statement\> ::= return['('\<Expression\>')']**

* There can be no return statement in a function with no return value, or a statement like `return;`
* A function with a return value only needs to appear ** a ** return statement with a return value (expression with parentheses), and there is no need to check whether each branch has a return statement with a return value.

## 1.2 Convention

* The expression type is char type, there are the following three situations

  * The expression is composed of \<identifier\>, \<identifier\>'['\<expression\>'] and \<identifier\>'['\<expression\>']''['\<expression\>']', and The type of \<identifier\> is char, that is, constants and variables of the char type, and one-dimensional and two-dimensional array elements of the char type.

  * The expression consists of only one \<character\>, which is a character literal.

  * The expression consists only of a function call with a return value, and the return value of the called function is char type.

  > In all other cases, the type of \<expression\> is `int`.

* **Type conversion only occurs in **expression calculation. Once the character type participates in the operation, it is converted into an integer type, including the character type enclosed in parentheses**, which is also considered to participate in the operation, such as ('c' ) The result is an integer.

* In other cases, such as assignment, function parameter passing, and relationship comparison in if/while conditional statements require **type exact match**, and the relationship comparison in \<condition\> can only be a comparison between integer types, not a character type.

## 1.3 Q&A

* Does the program specified in the grammar need a header file?

  unnecessary

* No need to consider the meaning of permutation and combination

  With a/without a, with b without b, all situations can be covered by only having both and neither.

* Are multiple `const` in the same line in the `const` rule

  There are no whitespace characters from the perspective of the compiler, so just pay attention to the semicolon between the two `const`.

* Is there no format string for `scanf`

  It is not needed in the custom grammar, just put the identifier in parentheses.

* How to deal with sentences that have newlines in the output of `printf`

  The `printf` function will add a newline by default after the compiler processes it. If the string itself has `n` newline characters, it will output `(n+1)` newline characters.

* Need to add `;` after `\<empty\>` statement

  It depends on the rules, which is required in Rule 29. However, there is no need to add any content between the curly braces if there is no sentence corresponding to Rule 42.

* It is not written in the grammar, but you need to add `;` after the return statement.

  Yes, and note that when there is a return value, you need to add `()` on both sides.

* `a = (a==b);` is illegal

  There is no boolean type in the grammar

* `int b = 10, c = 10;` is it legal

  In the custom grammar, the constant definition will only appear in the constant description, so you need to add `const` in front. For **variable definition with initialization**, it is **cannot** initialize multiple variables at the same time .

* `int a[10] = {1};` can not automatically initialize the unassigned memory space

  When initializing the array, the amount of data passed in `{}` needs to match the size of the array.

* Does printf need to format and replace strings?

  No, just concatenate the string and the value of the identifier directly.

* In the **compound statement**, the constant description and the variable description must be placed in front of the statement list in order.

* How to read in data

  ```c
  scanf(a);
  ```

  **No need** format string

* `char s[10] = "Hello";` Is it illegal?

  * ** Arrays can only be variables, and constants can only be single variables. **

  * String initialization

    ```c
    char s[4] = {'1', '2', '3', '4'};
    ```


# 2 Lexical analysis

## 2.1 Design Ideas

Through the theoretical basis of lexical analysis, we have learned: the role of the lexical analysis program in the compiler, or its function-is to filter the source code in text format and convert it into symbols (`Token`), Let the next part be able to know what the content of the source code is, like an "intermediary." Therefore, before the lexical analysis program is coded, it should be analyzed and designed closely following such a thinking path.

Design ideas can be roughly divided into two categories: process-oriented and object-oriented. The difference between the two is not the focus of discussion here. However, it is not difficult to know through previous learning that if the development of the compiler is incremental, then the object-oriented approach usually has higher scalability and flexibility.

Therefore, I adopted the object-oriented idea to design the lexical analysis program: treat the lexical analysis as a class, and the specific lexical analysis operations are encapsulated by the abstractness of the class. In this way, not only can the calling logic of the main function (compiled main function) be simplified, but also the interactivity between the lexical analysis module and the other parts of the compiler can be improved to a certain extent.

At the same time, we noticed that, unlike grammatical analysis, the recursive operation of lexical analysis is not obvious, most of which are just a single character or rely on loops to complete the analysis. Therefore, it is not necessary to use the recursive descent analysis method in this part, just use the simple conditional branch structure directly.

```mermaid
graph TD

other_parts --\> Lexical_analysis
Lexical_analysis--\>other_parts
Lexical_analysis--\>source_code_documentation
```



## 2.2 Implementation

For further analysis of lexical analysis requirements, we can summarize the following attributes and methods as the basis for implementation.

* `currentToken`: The symbol obtained by the current lexical analysis program from the source code and used to provide `Token` to other parts.
* `finish`: Indicates whether the lexical analysis program is executed to the end of the file, if not, it means that the lexical analysis program was abnormally terminated.
* `getNextToken()`: Get the next `Token`

The highlight of lexical analysis is undoubtedly in the processing logic of the **"read-analyze-return" symbol, which is `getNextToken()`. Therefore, the design and realization of this method are particularly important.

In the symbol table provided to us by the course group, a classification method is actually implied, such as `+`, `-`, `*`, `/` operators in one group. This classification method is logically friendly to coders, but it is not so perfect in the conditional branch structure-for example, the two symbols of `int` and "identifier", if you follow the distance on the table, They are not put together for analysis. However, in fact, the intersection of the two $FIRST$ sets is not empty, so it is necessary for us to analyze them in a unified manner and then distinguish them.

In summary, the last method I took was to find the `FIRST` array of all symbols, and then group the symbols, put together the intersections of $FIRST$ that are not empty, and then sort them by the `ASCII` code. Finally, set the order of related macros and conditional branches according to this order.

### 2.2.1 Documentation

> As a supplement to the implementation, attach the adjusted lexical analysis document below.

#### 2.2.1.1 Category code

| Number | Word Name | Category Code |
| ---- | -------- | --------- |
| 1 | != | NEQ |
| 2 | (| LPARENT |
| 3 |) | RPARENT |
| 4 | * | MULT |
| 5 | + | PLUS |
| 6 |, | COMMA |
| 7 |-| MINU |
| 8 | / | DIV |
| 9 |: | COLON |
| 10 |; | SEMICN |
| 11 | \< | LSS |
| 12 | \<= | LEQ |
| 13 | = | ASSIGN |
| 14 | == | EQL |
| 15 |\> | GRE |
| 16 | \>= | GEQ |
| 17 | [| LBRACK |
| 18 |] | RBRACK |
| 19 | case | CASETK |
| 20 | char | CHARTK |
| 21 | const | CONSTTK |
| 22 | default | DEFAULTTK |
| 23 | else | ELSETK |
| 24 | for | FORTK |
| 25 | if | IFTK |
| 26 | int | INTTK |
| 27 | main | MAINTK |
| 28 | printf | PRINTFTK |
| 29 | return | RETURNTK |
| 30 | scanf | SCANFTK |
| 31 | switch | SWITCHTK |
| 32 | void | VOIDTK |
| 33 | while | WHILETK |
| 34 | {| LBRACE |
| 35 |} | RBRACE |
| 36 | Identifier | IDENFR |
| 37 | Integer Constant | INTCON |
| 38 | Character Constants | CHARCON |
| 39 | String | STRCON |

* $FIRST(identifier)=\{\_,a,...z,A,...,Z\}$

  > There is a conflict with a reserved word, only **all field matching** can be used to determine whether it is a reserved word.

* $FIRST (integer constant)=\{0,1,...9\}$

  > Constants include signs, but **integer constants** only have numbers, that is, `-9` is parsed as `-` and `9`.

* $FIRST(character constant)=\{'\}$

  > Do not consider `'` when outputting

* $FIRST(string)=\{"\}$

  > Do not consider `"` when outputting

## 2.3 Summary

Through the design and implementation of the lexical analysis program, a few thoughts can be summarized:

* The understanding of C++ basic operations is not proficient, such as the use of `stringstream`. Need to follow up this knowledge supplement in the future study, let more energy be placed on the design of the compiler.
* The engineering practice of lexical analysis not only allows me to truly use the theoretical knowledge I learned in class, but more importantly, it in turn promotes my thinking about the theoretical basis of compiler principles and deepens my understanding of what I have learned in class. For example, the difference between lexical analysis and grammatical analysis. It is really abstract to me to distinguish it from theory. However, when lexical analysis is realized, because it is necessary to understand the function of lexical analysis, it is necessary to clarify the relationship between it and grammatical analysis at the same time. This teaching method has benefited me a lot!

# 3 grammatical analysis

## 3.1 Design Ideas

When designing the architecture, there is no doubt that we should always keep in mind the requirements of the subject and the function of grammatical analysis. Therefore, in this part I plan to use a problem-oriented approach to narrate: the problems and thinking paths faced in the design process are displayed through Q&A, so as to not only directly explain the realization method of the grammatical analysis function, but also to integrate the grammatical analysis in the whole The role of the compiler and its role are explained more clearly.

**Q: What does the compiler need to get after parsing?**

A:

Through the study of the theory class and the practice of the lexical analysis stage, we already know: after passing the lexical analysis, it is equivalent to "filtering" the source text of the program, that is, discarding some irrelevant blank characters, and discarding Significant symbols in the source text are recognized. And these meaningful symbols are the words with category codes that we get in the lexical analysis stage. The grammatical analysis, on this basis, further identifies each Token and its combination as the corresponding grammatical component, that is, the **non-terminal symbol** in the grammar.

From the above analysis, it can be known that ** grammatical analysis is based on lexical analysis, considering various tokens and their combinations, and parses out various grammatical components of the source text for subsequent semantic analysis and intermediate code generation. **



**Q: The difference between Token and Symbol**

A: Token is the result of lexical analysis, and Symbol is the general term for identifiers in the symbol table.

* For Token, each Token is obtained through the most basic lexical analysis and is classified according to "look".
* For Symbol, it is another name for the identifier in the symbol table, including the names of constants, variables, and functions, which are based on grammatical analysis. Because they are all `IDENFR` in the Token before the grammatical analysis, they cannot be distinguished. But after grammatical analysis, they can be distinguished.

> Token/grammatical component/Symbol is a gradual relationship: first you need to get all the tokens of the program, and then determine its grammatical components, for different identifiers, they are classified into different Symbols.



**Q: How to deal with the semicolon encountered in the syntax analysis**

A: The purpose of grammatical analysis is to combine and filter Tokens. The parts of Token that cannot be used as grammatical components, such as semicolons, play an auxiliary role in grammatical analysis: it is used to determine whether a certain grammatical component is over.



**Q: What kind of update is legal when reading to the end of the file**

A: When you read the end of the file, you need to pay attention to whether the syntax analysis is over. If the recursive subroutine is still not analyzed at the end of the file, it means that there is a problem with the analysis.



**Q: When will the syntax analysis update the characters?**

A:

To answer this question, we first need to clarify several consensuses:

* Before entering the subroutine, you need to pre-read a Token.
* Before exiting the subroutine, a Token needs to be pre-read.

The first pre-reading is for the subroutine to directly start the analysis according to the grammar, and the second pre-reading is for the subsequent analysis process to be carried out directly after the subroutine exits.

However, there is another situation in grammatical analysis: the judgment of a character that is not a grammatical component. This type of judgment does not need to call a subroutine, so the character update needs to be done manually. Although the subroutine is not called, we can regard the judgment logic of these characters as a subroutine**, so we can update it after judging the character.

It should be noted that not all non-grammatical component characters need to be updated after judgment. Because there is a type of judgment for matching the `FIRST` array, such as the matching of `+/-` before entering the integer subroutine, they may still be used in the subroutine and therefore cannot be updated; but in another In this case, for example, before calling \<constant definition\> by \<constant description\>, it is necessary to judge whether it is `const`. After the judgment is finished, because `const` is no longer used in the subroutine, the characters need to be updated. **To sum up, whether the non-grammatical component is updated after judgment depends on whether it will be used in the next analysis, if it is, then it will not be updated, otherwise it will be updated. **



**Q: The influence of the difference between character constants and letters on grammatical analysis**

A: A character constant is a combination of several grammatical components **including single quotation marks**, but these grammatical components do not have single quotation marks themselves. From the perspective of Token, it is the difference between `CHARCON` and non-`CHARCON`. For letters, this subtle difference does not have a particularly big impact, but for addition operators, if you directly judge whether the text is `+`, there may be a combination of `PLUS` type Token and `CHARCON `The type of Token is confused, so try not to use the text when judging the current Token in the subroutine, but directly use the Token category for judgment. In this way, the results of lexical analysis can also be fully utilized, not just the token segmentation text obtained by lexical analysis.

> `parseCharacter()` cannot analyze operators with non-character analysis subroutines



**Q: Do you still need to check the `FIRST` array after the pre-reading mechanism?**

A: Yes.

The inspection of the `FIRST` array is intuitively to avoid backtracking, but the deeper reason is: divide and conquer. After entering a subroutine, a grammatical component may be successfully analyzed, but the analysis may also be interrupted due to grammatical errors. If the subroutine's update of characters is irreversible, it may cause the source text that could match another grammatical component to fail.

At the same time, if the subprogram’s update of characters is reversible, that is, when a subprogram’s matching failure will not affect the subsequent matching, there may still be inaccurate positioning of the error message: for example, the source text that can be matched with B is in There will be traces of errors in A before B.

Therefore, the best way is to check the `FIRST` array and analyze the grammatical components independently to achieve the effect of "a source text Token combination can only match one grammatical component", then the above error conditions can be avoided.

> Note: Not all calls to sub-functions need to check `FIRST`. Only when there are multiple parallel sub-function branches, a judgment is made to ensure divide and conquer.



**Q: How to deal with the BNF notation of `()/[]/{}`**

A:

* `()`

  Indicates that the element will appear, just choose one. Therefore, just use `||` to judge.

* `[]`

  Indicates that the element either appears or does not appear, just use `if(xxx==elem)` to deal with the situation that appears.

* `{}`

  It means that the number of occurrences of the element is arbitrary, use the `while` loop to solve it, and jump out when the `FIRST` judges illegal.

  > For a single `{}`, such as `{\<Statement\>}`, it can be rewritten as `\<Statement\>{\<Statement\>}|\<Empty\>` before processing.
  >
  > It is worth noting that this `\<empty\>` is not the same as a compound statement because the statement column is empty. Because the compound statement must call the sub-functions of the statement column anyway, but the statement column does not need to call the statement sub-functions.
  >
  > ```c++
  > {
  >
  >}
  > // \<statement list\>
  > // \<compound statement\>
  >
  > {
  >;
  >}
  > // \<statement\>
  > // \<statement list\>
  > // \<compound statement\>
  > ```



**Q: How to achieve the requirement in the title: "Before the analysis of the grammatical analysis component highlighted in the grammar, start a new line to output the name of the current grammatical component"**

A:

This question can be equivalently described as: when to output all the tokens used in the analysis of the current grammatical components?

Analyzing from the equivalence problem, it is not difficult for us to get the following conclusions:

* Before a subroutine actually starts to analyze, it is necessary to output the tokens that have been analyzed by other subroutines before entering and do not belong to any grammatical components, because they do not belong to the current grammatical components.
* After the analysis of the subroutine is over, and before the highlight component is output, it is necessary to output the used tokens analyzed by the subroutine.

Through the above two analysis, it can be known that a subroutine has two places where Token is output. Similar to the case of pre-reading characters, if the last step of analysis before outputting the highlighted components is realized by calling other subroutines, then all the tokens used by this subroutine have been output, and the tokens have also been updated, so no Need to be output manually. But if the last step is completed by the Token judgment, it needs to be output manually, and the output needs to be before the Token is updated, otherwise it will cause the Token that does not belong to the subroutine to be output.

> Note: When the program header outputs Token, it is correct in most cases, because the `FIRST` array and pre-reading ensure that the entry into this sub-function must be analyzed. However, **if there are situations that may be empty**, such as statement lists, parameter lists, etc., it cannot be output as soon as the function is entered. It is necessary to determine whether it is empty, that is, whether the current character is in the `FOLLOW` array. When it is not an element in `FOLLOW`, it means that the component is not empty and can be analyzed, so Token can be output.

### 3.1.1 Special circumstances

* If it is the "\<component\> output" after the subroutine, there is no need for `outputAnalyzedTokenBuffer()`. Because the next character has been output at the end of the subroutine and the next character is pre-read, if you return to the calling function at this time If you output it again later, there will be a problem.

* It is not necessary to call the subroutine before `updateToken()`, such as the unsigned integer resolution in the step size analysis, only when the current module **real** uses the `currentToken` and then calls the subroutine, `update` is required .

  > Real use: **Promoted the parsing of grammatical rules**, if it is only for the judgment of the `FIRST` array, etc., there is no need for `update`

## 3.2 Implementation

Further analysis of grammatical requirements, we can summarize the following properties and methods as the basis for implementation.

* `realCurrentToken`: grammatically analyze the current real Token. As for why `real` is added, it is because irreversible lexical analysis cannot well support the realization of the pre-reading mechanism. Therefore, a buffering mechanism is introduced. The pre-read Token is put into the buffer. When the Token is updated, the buffer is fetched first, and the lexical analysis is notified to read the next Token when the buffer is empty.
* `analyzedTokenBuffer`: In order to achieve the output method required by the title, the Token cannot be output immediately during the update. Therefore, the pre-read Token needs to be temporarily stored and can be output only after the confirmation has been used.
* `updateCurrentToken()`: Get the next `Token`
* `previewTokenCategory()`: Pre-reading Token as an auxiliary tool for the judgment of the `FIRST` array

There are many key points of grammatical analysis, the most important of which can be attributed to the following points:

* Correctly divide the analysis components so that the token and grammatical components are output in the correct order.
* The use of each recursive subroutine needs to be able to record as many matching paths as possible to prepare for later error handling.

For the first point, it has already been analyzed in the design idea part, just follow the narrative to realize it.

For the second point, the current method is a combination of `FIRST` and pre-reading to ensure that as long as a Token group enters a certain sub-function, it must be impossible to enter another parallel sub-function. In this way, the result of grammatical analysis is more pure: correct or wrong processing work is assigned to each specific function, so that there will be no confusion when synthesizing.

## 3.3 Summary

Through the design and implementation of the grammatical analysis program, a few thoughts and experiences can be summarized:

* When designing a stage, you can't just consider one stage. This usually results in low scalability of the architecture and brings unnecessary workload to the subsequent stages. Therefore, before you start, you must first think about the requirements of this stage, and link it with other stages for analysis, so that you can elegantly carry out incremental development.
* Compared with grammatical analysis and lexical analysis, one big difference is complexity. Although the grammar is analyzed, the lexical analysis does not need to consider the conflicts between various tokens and various grammatical components too much. Its complexity basically appears at the character level. But for grammatical analysis, it is at the Token group level. Therefore, the realization of grammatical analysis needs to be bold and careful: not only the arrangement of the various grammatical components must be considered at the macro level, but also the detailed analysis of each grammar at the micro level.

# 4 Error handling

## 4.1 Design Ideas

When designing the architecture, there is no doubt that we should always keep in mind the requirements of the problem and the related functions of error handling. Therefore, in this part, I plan to use a problem-oriented approach to narrate: the problems faced in the design process and the path of thinking are displayed through Q&A, so as to show the context of error handling more clearly.

**Q: The function will only be defined in the `GLOBAL` scope**

A: correct



**Q: Where may the new identifier appear**

A: The global defined by `GLOBAL`, the formal parameters of the function, and the local identifier in the function, so the symbol table can use the function name and `GLOBAL` to distinguish the scope.



**Q: In error handling, which line should be the line number of "function with return value missing return statement" and "missing default statement" when reporting an error? **

A: In both cases, it is reported on the line of **right brace** at the end

```cpp
6 int foo() {
7 int a = 1;
8 a = a + 1;
9 }

15 switch(a) {
16 case 1: ...
17 case 2: ...
18}
```



**Q: Is the expression of `a['a'+1]=0` legal?**

A: legal



**Q: Is the type of the expression `-'a'` an integer? **

A: Yes



**Q: If an illegal symbol appears in the identifier, should the identifier be stored in the symbol table, that is, whether subsequent references to the identifier report an error of quoting an undefined name, or an error of using an illegal symbol? Are errors reported when quoted multiple times? **

A: Wrongly defined variables, constants or functions will not be quoted. Only need to report illegal symbol errors in the definition.



**Q: If there is a global variable a, if a function a is defined after it, this line will report the error of repeated naming. Do you still need to check whether there are errors in the contents of this function? **

A: This "function definition that has been judged to be renamed" should also be checked for other errors, including functions that are repeatedly defined, and should also be checked in the function body defined for the second time.



**Q: Excuse me, if you define a variable or function with the same name as a reserved word, is it a "name redefinition" error, or is it not within the scope of our work**

A: Do not examine this situation



**Q: What is malicious line break**

A:

* No line breaks appear in the function call statement
* Line breaks that may cause ambiguity in the number of error lines, such as: line breaks in function calls will lead to ambiguities in the number of error lines, whether it is the number of lines in the call name or the number of lines with the wrong parameter type.



**Q: If a return statement exists in a function with a return value and only has an error, do you still need to report an error of no return statement when the closing brace of the function is analyzed? **

A: No need



**Q: Character expression judgment**

A: **If and only if ** are the three cases in the regulations, the expression type is char type, and the other cases are int type.



**Q: Is it legal to have single quotes in a string**

A: legal



**Q: Whether the variable initialization type does not match is an error, for example, the initialization element type of the array is different from the declaration type. **

A: Need



**Q: Whether the function name and its formal parameter name are the same as an error report**

```cpp
void a(int a, int aa, int aaa) {}
```

A: No, the variables are on the second level.



**Q: Does the wrongly defined identifier need to be stored?**

A: Yes, although this variable will not be used later, it may be redefined in the same scope.

```cpp
int a = 1;
int a ='c';

int a ='c';
char a ='c';
```

> Setting an `isProper` domain to restrict variables with the same name in the scope is illegal, the default is `true`.



**Q: The variable `a` in the scope A is correct, but the variable in the scope B is incorrect, so whether the part of A that does not contain B can refer to `a`.**

A: Yes



**Q: How to judge the legality of `Symbol`**

A: To judge the legality of a symbol, you can't just look at your own `isProper`, you also need to recursively check whether its level is `proper`.



**Q: Is `b` legal?**

```cpp
char a;
int a, b;
```

A: legal



**Q: How to determine if the empty statement lacks a semicolon**

A: The absence of a semicolon in an empty statement means that it will not appear



**Q: Referencing an undefined function will cause the program to stop directly**

A: Special judgment is required when parsing function call statements

## 4.2 Misclassification

| Category Code | Error Type | Details |
| :----: | ------------------------------------------ -------------- | ----------------------------------- ------------------------- |
| a | Illegal symbols or not lexical | For example, illegal symbols appear in characters and strings, and there are no symbols in the symbol string. |
| b | Name redefinition | The same name appears in the same scope (not case sensitive) |
| c | Undefined name | Reference to undefined name |
| d | The number of function parameters does not match | The number of actual parameters when the function is called is greater than or less than the number of formal parameters |
| e | Function parameter types do not match | When the function is called, the formal parameter is of integer type, and the actual parameter is of character type; or the formal parameter is of character type, and the actual parameter is of integer type. |
| f | An illegal type appears in the conditional judgment | The left and right expressions of the conditional judgment can only be integers, and if any expression is a character type, an error will be reported, such as `’a’==1`. |
| g | A function with no return value has a mismatched `return` statement | A function without a return value can have no `return` statement, or a statement like `return;`, if there is a statement like `return( expression Type);` or `return();` statements are all reporting this error. |
| h | A function with a return value lacks a `return` statement or a mismatched `return` statement | For example, a function with a return value does not have any return statement; or has a statement like `return;`; or has a shape like `return( );` statement; or the expression type in the `return` statement is inconsistent with the return value type. |
| i | The subscript of an array element can only be an integer expression | The subscript of an array element cannot be a character type |
| j | The value of a constant cannot be changed | The constant here refers to an identifier declared as `const`. For example, `const int a=1;` If there is a code to modify the value of `a` in the subsequent code, such as assigning a value to `a` or using `scanf` to get the value of `a`, an error will be reported. |
| k | Should be a semicolon | There should be no semicolon where a semicolon should appear, for example, `int x=1` is missing a semicolon (at the end of 7 kinds of statements, in the `for` statement, at the end of the constant definition, at the end of the variable definition) |
| l | Should be the right parenthesis `')'` | There should be no right parenthesis where the right parenthesis should appear, such as `fun(a,b;`, missing right parenthesis (with/without parameter function definition, main function) , Expressions with parentheses, `if`, `while`, `for`, `switch`, function call with/without parameters, read, write, `return`). |
| m | Should be the right square bracket `']'` | There should be no right square bracket where the right square bracket should appear, for example, `int arr[2;` is missing the right square bracket (one-dimensional/two-dimensional array variable definition yes/no Initialization, one-dimensional/two-dimensional array elements in factors, array elements in assignment statements). |
| n | The initial number of arrays does not match | The number of elements in any dimension does not match, or an error is reported if the number of elements in a certain dimension is missing. For example, `int a[2][2]={{1,2,3},{1,2}}`. |
| o | The type of the \<constant\> is inconsistent | The variable definition and initialization and the \<constant\> in the `switch` statement must be consistent with the declared type. `int x=’c’;int y;switch(y){case('1')...}` |
| p | Missing default statement | In the `switch` statement, the \<default\> statement is missing. |

### 4.2.1 Convention

* Line numbers start counting from `1`

* Including allowing variable names in **different scopes**

* At most one error will appear in each line**

* **Malicious line breaks will not occur in all errors, including characters, line breaks in strings, function calls, etc.

* For other types of errors, the line number of the error is subject to the line number of the symbol where the error can be determined**.

  > For example, a function with a return value lacks a return statement error. Only when the} at the end of the function is recognized and the return statement does not appear, the error can be determined. The error line number is the line number of `}`.

* For the lack of circumstances, it is necessary to take the Token of `-1` bit to determine the line number

* There will be no `ungetToken` during the correct grammatical analysis. Therefore, when the file is correct, there will be no problem that multiple `getToken` in the same position causes the `Token` to be output multiple times; when the file is wrong, no Will output `Token`, and it has no effect.

* New variables will only appear in the constant description, variable description and parameter list at the beginning of the program. Therefore, the symbol table only needs to be filled in at these times. Mark the function `GLOBAL` that each variable belongs to, and do not need to delete it.

## 4.3 Processing Strategy

### 4.3.1 List of situations

* `a`

  * Illegal symbols refer to visible ascii symbols outside of the grammatical requirements in **characters** and **strings** (** does not include **single quotes and double quotes, that is, although double quotes are not in the range, but Still think it is **legitimate**)

    > The value range of the character** is not the value range of the elements in the string. For example, `'!'` is illegal.

  * Null character means that the contents of **character** and **string** are empty

* `b`

  * It is not case sensitive, and the same name appears in the same scope.

    > Same as global/in one function

  * After redefining, the upper-level element with the same name will be ignored

  * Will not define the same name as the reserved word

  * Wrong identifiers will not be quoted, but may be redefined.

    ```cpp
    void main() {
        char c ='?';
        int c = 1;
    }
    ```

* `c`

  * All names are identifiers, that is, the identifier is undefined.

* `d`

  * The number of actual parameters and formal parameters is different

    > Consider the number of formal parameters and their names in the symbol table of the function

* `e`

  * The types of actual parameters and formal parameters are different

* `f`

  * The left and right expressions of the condition must be integer

    > The expression is `char` and there are only three types. Just consider judging whether there is a `char` type on the left and right.

* `g`

  * The `return` statement of a function without return value cannot return a specific value, including `return();` is also illegal.

* `h`

  * Including `return();` is also illegal.

* `i`

  * Determine whether the subscript is `char` type

* `j`

  * Assign constants
  * It is also possible to change the value of a constant through `scanf`

* `k`

  * The end of 7 kinds of sentences
  * Two semicolons in `for`
  * The end of constant definition and variable definition

* `l`

  * Function definition (with/without parameters)
  * Main function
  * Bracketed expression
  * `if`
  * `while`
  * `for`
  * `switch`
  * Function call with/without parameters
  * read
  * Write
  * `return`

  > Specifically refers to the right parenthesis, excluding the left parenthesis.

* `m`

  * One/two-dimensional array variable definition with/without initialization
  * One-dimensional/two-dimensional array elements in factors
  * Array elements in assignment statements

* `n`

  * When the array is initialized, the number of elements in a certain dimension does not match or **missing** elements in a certain dimension

* `o`

  * **Only** the \<constant\> in \<variable definition and initialization\> and \<condition substatement\> need to be checked for the same type

* `p`

  * Missing default statement in `switch`

### 4.3.2 Implementation

* The `Error` class is used to store all errors in the source code, and output them when they are found.
* `a-j`/`n-o`: Just record the error and let the parser **execute normally**.
* `k`, `l`, `m`, `p`: **Skip **corresponding missing elements and let the parser **execute normally**
* Need symbol table: `b-f`, `h-j`, `n-o`
* No symbol table: `g`, `k-m`, `p`
* `a`: Lexical analysis
* `b`: Check the symbol table of the current scope (the symbol table class encapsulates a current domain search function, **not** recursively upwards)
* `c`: Recursively look up the symbol table
* `d`: Check when parsing and calling the actual parameter list
* `e`: When parsing an expression, you need to return the expression type/incoming reference
* `f`: same as `e`
* `g`: Pass in the function name for checking when parsing the `return` statement
* `h`: same as `g`
* `i`: same as `e`
* `j`: Check if it is a constant when assigning and `scanf`
* `k`: Make necessary additions where the semicolon is checked
* `l`: Add necessary additions where the right parenthesis is checked
* `m`: Make necessary additions where the right bracket is checked
* `n`: Check the number of elements when the array is initialized
* `o`: Pass the variable type to check when parsing `case`
* `p`: directly use the return value of the original `parseSituationDefaultStatement` function

## 4.4 Summary

Through the design and implementation of error handling, a few thoughts and experiences can be summarized:

* When designing a stage, you can't just consider one stage. This usually results in low scalability of the architecture and brings unnecessary workload to the subsequent stages. Therefore, before you start, you must first think about the requirements of this stage, and link it with other stages for analysis, so that you can elegantly carry out incremental development.
* The characteristic of error handling is the unpredictability of the document. Therefore, it is necessary to be targeted when analyzing error types, and make full use of the grammatical structure that will not cause problems to simplify problem analysis, so that the realization of error handling is not so bloated and complicated. This also proves from another aspect that a good architecture involves making development work more effective.

# 5 Code Generation

## 5.1 Design Ideas

### 5.1.1 Overview

Before completing the code generation job, I first reviewed the entire compilation process: five stages and symbol table management and error handling throughout. The reason for this is simple: the code generation phase is a real leap from the front end of the compiler to the back end, so it is particularly important to grasp the front-end and back-end boundaries.

\<img src="https://media.geeksforgeeks.org/wp-content/uploads/compilerDesign.jpg" alt="img" style="zoom:50%;" /\>

In class, the teacher said that the dividing line between the front and back ends is the dividing line between the intermediate code and the target code. It sounds like this. After all, no matter what the intermediate code looks like, as long as there is corresponding logic, the intermediate code can be translated into the machine on the specified target machine. Code, then the front end and back end of the compiler are decoupled. If the story ends here, then the code generation phase seems to be nothing more than that compared to other phases.

But in fact, if we think further, is the "corresponding logic" mentioned above really so sure? No matter what kind of intermediate code, is the logic of converting it into machine code the same simple or complex?

The answer is self-explanatory: the quality of the intermediate code directly determines the complexity of the front-end and back-end interfaces of the compiler and the quality of the generated target code, so high-quality conversion logic is equally important.

### 5.1.2 Process

After carefully thinking about the above issues, I decided to design the intermediate code first. After the standard of the intermediate code was determined, the relevant logic realization of semantic analysis was carried out, and finally the conversion to the target code, which can be represented by a flowchart as follows:

```mermaid
graph TD

B[Semantic Analysis Logic]
A[Intermediate code]
C[Object Code Generation]

B--\>|Impact|A
A[Intermediate Code]--\>|OK|B
A--\>|Conversion|C
C--\>|Predefined|A
```

### 5.1.3 Analysis

It is worth mentioning that when designing the intermediate code, it is not possible to isolate the intermediate code generation stage. Why do you say that? First, the logic of semantic analysis will determine the type of intermediate code. For example, our `C0` language grammar supports order, condition, branch, and selection structures. Among them, there are two types of loops: `while` and `for`. Therefore, when designing the intermediate code, we must fully consider the common points of the two, use As few intermediate codes as possible represent two different structures. Furthermore, the type of target code also has a great influence on the intermediate code. For example, we chose the `MIPS` assembly under the `RISC` architecture. This is an assembly language with a very standardized and brief instruction format. It can even be said that the format of most machine codes is a common quaternion. Therefore, when designing the intermediate code, the format characteristics of the instruction set should also be fully considered, and a suitable point should be found between the `C0` language and the `MIPS` assembly, and the intermediate code can be constructed from this scale.

After comprehensively considering all possible assembly instructions and intermediate code semantics, the following possible "five-element" intermediate code structure can be obtained. When generating the target code, just take it directly at the specified location.

* type
* op1
* op2
* Number of targets
* label

Combined with the structure of the intermediate code, the types of intermediate code items can also be summarized as follows:

```cpp
enum IntermediateCodeItemType
{
    UndefItem, // initial type
    // immediate number
    ImmItem, // including immediate int and immediate char
    ImmIntItem, // immInt field stores immediate number
    ImmCharItem, // immInt field stores immediate number
    // register
    RegItem, // reg field stores index of register
    // symbol
    StrItem, // index field stores index of corresponding symbol
    SymItem, // index field stores index of corresponding symbol
    // label
    LabelItem, // label field stores label name
};
```

The types and semantic actions can be listed as follows:

```cpp
enum IntermediateCodeType
{
    UndefCode,
    // I/O
    Read, // scanf(t0)
    Write, // printf(t0)
    WriteOver, // printf('\n')
    // calculate
    Assign, // t2 = t0
    Add, // t2 = t0 + t1
    Sub, // t2 = t0-t1
    Mult, // t2 = t0 * t1
    Div, // t2 = t0 / t1
    LoadArr, // t2 = t0[t1]
    SaveArr, // t0[t1] = t2
    // function
    PushArg, // push t0 to t3(..., t1, ...)
    Call, // call t3
    Ret, // return t0(nullable)
    Label, // generate label t3
    // branch
    BGT, // branch to t3 if t0\> t1
    BGE, // branch to t3 if t0 \>= t1
    BLT, // branch to t3 if t0 \<t1
    BLE, // branch to t3 if t0 \<= t1
    BEQ, // branch to t3 if t0 == t1
    BNE, // branch to t3 if t0 != t1
    GOTO // goto t3
};
```

After the intermediate code design is completed, it is the insertion of the corresponding semantic action. According to the relevant knowledge of the attribute translation grammar learned in the theoretical class, we can use related ideas to convert the source code to the intermediate code. The specific logic is roughly the same as that described in the textbook. The specific details will be expanded in the next part. I won't repeat it.

Finally, we finally come to the target code generation stage. A large part of the meticulous design of the intermediate code is to reduce the complexity of this part-compared to the assembly code, most people may still prefer to look at the intermediate code or the source code. If the design of the intermediate code has fully considered the characteristics of the instruction set, then the work to be done next is to translate step by step. When translating, there are many different ways of thinking to choose, such as building classes according to the type of instruction (`J` type, `I` type, `R` type), and implementing the structure of different instructions through the inheritance relationship between them; also You can simulate instructions through functions, and call encapsulated functions according to the relevant logic generated by the intermediate code. After repeated trade-offs, I chose the latter because the "five-element formula" itself is very close to the assembly code. When the instruction set involved is not huge, it may be better to directly use the encapsulated function to represent the target instruction. It is indirect and flexible.

Therefore, the steps to add program structure can be summarized as follows:

* Add intermediate code
  * type
  * Analysis (assign a value to the intermediate code item)
* Syntax analysis inserts intermediate code
* Generate target code
  * `transXXX` function
  * Target instruction function package

Through the relevant thinking of the above design, the idea of ​​connecting the front and back ends of the compiler has been very clear, and the exciting implementation links will begin below.

## 5.2 Implementation

### 5.2.1 Overview

This part will be driven by examples, through the analysis of the target code generation process of the program segment with the specified structure of the source code, to explain the work and steps completed by the compiler during the entire code generation phase.

First of all, through the analysis of the `C0` grammar, we can get the following program control flow and data structure that need to be implemented in the code generation stage.

* order
  * Constant description
  * Variable description
  * Read sentences
  * Write sentences
  * Assignment statement
* Branch
  * `if-else`
* choose
  * `switch-case`
* Loop
  * `while`
  * `for`
* Array
  * One-dimensional array
  * Two-dimensional array
  * Appearance position
    * Variable definitions
      * Initialization
      * No initialization
    * Factor
    * Left side of assignment statement
* Function
  * Definition
  * transfer

The situations listed above are classified according to whether they need to fill in the symbol table. We can classify arrays and functions into one category, and the remaining four program structures fall into one category. Furthermore, according to whether a jump instruction is involved, we can divide loops, selections, branches, and function calls into one category. The schematic diagram is as follows:

```mermaid
graph LR

A[array]
B[function]
C[Order]
D[Select]
E[branch]
F[loop]

Program_flow--\>fill_symbol_able
Program_flow--\>Use_label
Program_flow--\>other

Fill_in_the_symbol_table--\>A
Fill_in_the_symbol_table--\>B

Use_label--\>B
Use_label--\>D
Use_label--\>E
Use_label--\>F

Other--\>C

```

After the classification, the idea of ​​our realization is also clear: first realize the basic sequence structure, then the arrays and functions that need to be filled in, and finally the label part related to the jump.

### 5.2.2 Sequence structure

The five components of the sequential structure seem to be unrelated. For example, writing sentences and assignment sentences, it seems that only the word "sentence" is comparable to the name. But in fact, these five components are all related to identifiers, and identifiers are usually strongly related to expressions. Then the key points of this part are self-explanatory: the processing of identifiers and the parsing of expressions.

The first is the identifier, because the `C0` grammar stipulates that identifiers are not case sensitive, so in the lexical analysis stage, all identifiers are converted to lowercase for storage, and the lowercase form is also used for comparison when equality is judged in the symbol table. . At the same time, for the consistency of the target code, the original identifier form is still retained. For example, if the function name is changed to lowercase, it may not be convenient to quickly correspond to the function in the source code. Furthermore, because identifiers and ordinary characters are treated as `Token` in the compiler, the lowercase conversion may also affect the string characters that were originally uppercase, so this part of the situation needs to be dealt with.

Therefore, the lowercase form of ** is only used when the symbol table has the same name, undefined name, or common variable index. In all other cases, the original form of `Token` is used. **

### 5.3.3 Branch structure

The feature of the tags in the branch structure is "not necessarily in pairs", for example, there can be no `else` after the `if`. And note: the branch structure can also be nested, so how to make the `if` structure pair when generating the intermediate code Matching is particularly important.

In order to clearly indicate each pair of tags, the compiler has numbered the tags when generating the `if` structure. The following is an example of the source code.

```cpp
void main()
{
    if (1 \<2) {
        printf(1);
    } else {
        printf(2);
    }
}
```

The intermediate code generated by the compiler is as follows:

```assembly
BGE 1 2 "" else_$0
Write 1 "" "" ""
WriteOver "" "" "" ""
GOTO "" "" "" if_end_$0
Label "" "" "" else_$0
Write 2 "" "" ""
WriteOver "" "" "" ""
Label "" "" "" if_end_$0
```

From the structure of the intermediate code, we can get the following generation steps:

* Each `if` gets a unique number as a tag when it starts parsing (in order not to conflict with the variable name, `$` is added to the tag).

* Invert the condition, if the original condition is not met, jump directly to `else`.

* If it is satisfied, jump to the end of the entire branch structure after executing the `if` block.

* There is no need to jump at the end of `else`

* If there is no `else`, the compiler will get the following intermediate code:

  ```assembly
  Call "" "" "" main
  Label "" "" "" main
  BGE 1 2 "" else_$0
  Write 1 "" "" ""
  WriteOver "" "" "" ""
  GOTO "" "" "" if_end_$0
  Label "" "" "" else_$0
  Label "" "" "" if_end_$0
  Ret "" "" "" ""
  ```

  > As you can see, an empty label is still generated for `else`, which is an artificial pairwise construction operation. Because the empty label will not increase the running cost, this operation is a viable option.

### 5.3.4 Select structure

The selection structure can be understood as a combination of multiple branch structures, but the difference is that the `C0` grammar stipulates that a `default` must appear, which is equivalent to an `else` at the end, which simplifies the operation of artificial pair construction. An example is also shown as follows:

```cpp
void main() {
    int i = 1;
    switch(i)
    {
        case 10:
            printf(1);
        default:
            printf(2);
    }
}
```

The generated intermediate code is as follows:

```assembly
Assign 1 "" sym_2 ""
Label "" "" "" switch_$0_case_$0
BNE sym_2 10 "" switch_$0_case_$1
Write 1 "" "" ""
WriteOver "" "" "" ""
GOTO "" "" "" switch_end_$0
Label "" "" "" switch_$0_case_$1
Write 2 "" "" ""
WriteOver "" "" "" ""
Label "" "" "" switch_end_$0
```

As you can see, the compiler treats `default` as a special case after the normal `case`, and the actual logic and branch structure are not very different.

### 5.3.5 Loop structure

`while` and `for` are still branch structures in essence, but the current branch becomes two before and after the statement block: one jumps back and one jumps forward. Same as the branch structure, it is still necessary to generate a unique logo for each loop body. In order to avoid the possible impact of nesting, we must also pay attention to the protection of the logo, that is, the inner loop can not wash out the outer logo .

Furthermore, the `for` loop actually assigns a value to the variable before the `while`, so the core of the loop is still on the two branch jumps. It is worth mentioning that every time the loop condition is judged again at the end of the loop, the expressions on both sides of the condition need to be recalculated. This also means that it is necessary to "memorize" the judgment conditions at the head of the loop body. In `Leopard`, the expression index recording strategy during head parsing is adopted, and the intermediate code for calculating the expression can be generated repeatedly at the head of the loop.

Let's take `while` as an example for illustration. The source code is as follows:

```cpp
void main()
{
    while(2 \<1)
    {
        printf(1);
    }
}
```

The generated intermediate code is as follows:

```assembly
BGE 2 1 "" while_end_$0
Label "" "" "" while_head_$0
Write 1 "" "" ""
WriteOver "" "" "" ""
BLT 2 1 "" while_head_$0
Label "" "" "" while_end_$0
```

### 5.3.6 Functions

The declaration of the function has been implemented in the symbol table management part, and the focus of the code generation phase is how to resolve the function call. Before implementing this part, you may wish to review the memory structure of `MIPS`.

\<img src="http://www.it.uu.se/education/course/homepage/os/vt18/images/mips/MIPS_detailed_memory_layout.png" alt="img" style="zoom:50%;" / \>

The running stack of the function is `Stack segment`, which is a data area that grows downwards, operated by the `$sp` pointer. After understanding the basic overview of the function stack, we can begin to design the function stack. Because the course group did not give a fixed runtime stack standard, we can set the most appropriate memory allocation strategy according to our compiler architecture. For `Leopard`, because the symbol table stores the stack of local variables relative to the scope Address and heap address of global variables, so choose to store `$ra` at the bottom of the function stack, so that fixed access can be achieved through `0($sp)`. For function parameters, because relevant information is also stored in the symbol table, because we can treat it as a local variable, in addition to `$a0-$a3`, the stack space is also used to store them. In summary, the stack space can be shown as follows:

```mermaid
graph TD

Local_variables--\>parameters
parameters--\>return_address
```

The following is also explained through an example, the source code is as follows:

```cpp
int f(int a)
{
    return (a);
}

void main()
{
    f(1);
}
```

The generated intermediate code is as follows:

```assembly
Label "" "" "" f
Ret sym_2 "" "" ""
Label "" "" "" main
PushArg 1 0 "" f
Call "" "" "" f
Ret "" "" "" ""
```

It is worth mentioning that the stack pointer `$sp` has not changed when the actual parameters are passed, so the stack frame size of the corresponding function needs to be subtracted and then stored on the stack. At the same time, when translating the calling statement of `Call`, you need to save `$ra`, change the stack pointer, and restore `$ra` after the function returns to decouple the caller and the callee and minimize the complexity of the target code. Spend. If the return value of the function will be used later, you need to assign `$v0` to the outer variable.

* `PushArg` translation example

  ```assembly
  # PushArg 1 0 "" f
  li $25, 1
  sw $25, -4($29)
  ```

* `Call` translation example

  ```assembly
  # Call "" "" "" main
  sw $31, 0($29)
  add $29, $29, -4
  jal main
  add $29, $29, 4
  lw $31, 0($29)
  li $2, 10
  syscall
  ```

It cannot be ignored that when a function is called as a parameter of another function, the stack of the inner function (parameter function) must be maintained first, and after all the parameters are calculated, the parameters of the outer function can be pushed into the stack. Otherwise, parameter coverage may occur, resulting in unpredictable call results.

### 5.3.7 Array

Array is a composite data structure, and the focus of translation is mainly on the conversion from index to address. This part can be carried out according to the formula of the textbook. In order to facilitate the generation of intermediate codes, `Leopard` specifically encapsulates two types of intermediate codes, `LoadArr` and `SaveArr`. Although these two types of intermediate codes can be split into multiple other codes, they will lose good object-oriented features and cause unnecessary redundancy.

Similarly, take an example to illustrate the processing process of the array, the source code is as follows:

```cpp
int a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

void main()
{
    printf(a[1][2]);
}
```

The translated intermediate code is as follows (due to space limitations, part of the assignment operation during array initialization is omitted):

```assembly
SaveArr sym_1 0 1 ""
SaveArr sym_1 1 2 ""
# ...
SaveArr sym_1 8 9 ""
Call "" "" "" main
Label "" "" "" main
Mult 1 3 sym_4 ""
Add sym_4 2 sym_4 ""
LoadArr sym_1 sym_4 sym_3 ""
Write sym_3 "" "" ""
WriteOver "" "" "" ""
Ret "" "" "" ""
```

Note: Whether it is a one-dimensional or two-dimensional array, it is stored linearly in memory, so we can calculate the index subscript and add it directly to the starting address of the array to get the address corresponding to the array element.

* `LoadArr` translation example

  ```assembly
  # LoadArr sym_1 sym_4 sym_3 ""
  lw $24, 8($sp)
  sll $24, $24, 2
  add $24, $24, 4
  add $24, $24, $28
  lw $25, 0($24)
  ```

* `SaveArr` translation example

  ```assembly
  # SaveArr sym_1 sym_5 0 ""
  lw $15, 12($sp)
  li $25, 0
  sll $15, $15, 2
  add $15, $15, 4
  add $15, $15, $28
  sw $25, 0($15)
  ```

It is not difficult to find that the `LoadArr` and `SaveArr` operations are completely equivalent in the array position acquisition, and the difference is only in the access operation.

### 5.3.8 Expression

Among the various components of the program flow mentioned earlier, there is also a role that runs through: expressions. There are many kinds of expressions, which is one of the main reasons why the examples in the theory class always start from the expression grammar.

There are many ways of analyzing expressions, the more common ones are inverse Polish and recursive descent analysis. The main idea of ​​the reverse Polish notation is to scan the strings one by one from left to right, and then perform calculations based on the obtained symbol stack and operand stack. This kind of thinking is very concise and clear, but because the reverse Polish expression requires calculation in the parsing process, when the expression is too long, stack overflow may occur, such as $1+(2+(3+(4 +(...))))$.

For the above considerations, `Leopard` finally adopted the recursive descent analysis method, which is essentially the top-down "attribute translation grammar" mentioned by the teacher in the theory class. In the analysis idea of $Expression \rightarrow Term \rightarrow Factor$, the upper layer passes a variable reference to the lower layer, and the lower layer modifies the reference according to the parsed result to achieve the purpose of returning a calculation result to the upper layer. The process is shown in the following figure.

```mermaid
graph TD

A[Expression];
B[Term];
C[Factor];

A--\>|ref|B;
B--\>|ref|C;
B--\>|val|A;
C--\>|val|B;
```

Because the process of generating the intermediate code and the register are decoupled, there is no need to consider the allocation of the register at this time, and only need to generate a temporary variable for the result of each operation for storage. Note that all operations in the `C0` grammar can be converted to binary calculations in the form of infixes, so when register allocation, each expression-related instruction only needs three registers. Furthermore, if multiple intermediate codes of an expression are considered to be independent, then the final generated target code will also only require three registers. Speaking of this, I don't know if the reader feels a little bit. This is actually the workflow of a stack processor-each time two operands and operators are loaded onto the top of the stack for calculation, and then the result is stored back to memory. Although such an implementation is simple, it does not make full use of the `MIPS` register file, so the efficiency is not high.

This approach is actually preparing for the code optimization link: more temporary variables can store more operating information, making optimization more independent, and after creating the `DAG` graph, repeated temporary variables can be Direct merging will not have a fundamental impact on the performance of the program. At the same time, new ideas can be used to replace the execution logic of the stack processor when allocating registers, which can also improve the execution efficiency of the program.

### 5.3.9 Matters needing attention

* `C0` grammar **no** constant array

* Single quote characters in `MARS` can replace numbers

* The relationship between the four (five) yuan formula and the intermediate code

  * The quaternion is a representation of the intermediate code.
  * When the output is the evaluation quaternion, some sentences need to be translated in the infix form, but the quaternion is used for compilation.

* `I/O` rules

  * number

    * Input: 5
    * Output: 1

  * Character

    * Input: 12

      > If there is a carriage return after a character input sentence, it will be affected in the `GUI` interface, but when the command line is called, it will read an extra carriage return by default, which is the same as the number input.

    * Output: 11

* Processing of strings: only appear in the writing statement and will not be modified, so it can be regarded as a **global constant**.

  > A new symbol type is added to represent string constants.

* All characters and integers are allocated in memory according to **4 bytes**

* Variable reference

  * Look up the table when compiling, and then generate the intermediate code according to the **relative address** of the variable.

    > The relative address is relative to the stack pointer `$sp`

* Jump to `main` first when generating target code (`main` has a separate label)

  ```assembly
  .text
  jal main
  li $v0, 10
  syscall
  ```

* Memory management

  * Global variables are stored in the section from `$gp` to `.data` (`0x10008000-0x10010000`), a total of 32KB, which can store 32976 variables of `int` type.

    > `.data(0x10010000-0x10040000)`: used to store strings, a total of 192KB space, up to 48K variables/constants can be stored.

* The size of the function stack frame is determined by the number of variables, the number of parameters, and the return address.

## 5.3 FAQ

**Q: Does C0 involve dynamic storage allocation?**

A: No, the case where the array index is an expression only appears in the factor.



**Q: Why does `$sp` not point to the bottom of the stack (0x7FFFFFFC) at the beginning, but 0x7FFFEFFC.**

\<img src="https://i.loli.net/2020/11/13/qVUABWZNzTuQ6fg.png" alt="image-20201113115219439" style="zoom: 67%;" /\>

A: This is specified by the operating system, so the 4KB space above is reserved.

## 5.4 Summary

If the compilation course is to teach you how to cook a dish, then code generation is the final step of cooking. Some people may choose to focus on the fire; some people will tend to cook slowly; some people will find another way. At the same time, thanks to the development freedom given to each student by the course group, each student can design his own compiler in a personalized way. Such a treatment method is not suitable for everyone-whether it is computer composition or operating system, the course group has set up unified standards and implementation methods. But if you can settle down to design, then this arrangement also has its own advantages.

Take the maintenance of the running stack when a function is called. Different `MIPS` standards may have different requirements. Therefore, we can make the most suitable design according to the requirements of the course, and not necessarily to comply with the so-called "standards." In different scenarios, the specification may also change, such as the `display` area. People design the `display` area to satisfy the inner logic to call the outer variables, such as the pointer in the `C` language. But because there are only cross-scope calls of functions to global variables in the compiler we designed, and global variables are not stored in the stack area, there is no need for the `display` area for search operations.

In the author's opinion, the design work in the code generation stage is very important, which not only determines the quality of the target code, but also directly affects the architecture of the front and back end interfaces of the entire compiler. So before you get started, it's better to pick up a pen and plan the project structure. This often brings twice the result with half the effort.

# 6 Code Optimization

## 6.1 Machine Independent Optimization

### 6.1.1 Basic block and flow graph

#### 6.1.1.1 Basic block division

Before starting optimization, the intermediate code needs to be divided into basic blocks. When dividing basic blocks, the algorithm mentioned in the book is used:

* Determine the entry sentence
  * The start statement of the program
  * The `label` statement that can be reached by the jump statement
  * The statement immediately following the jump statement
* The statement between two adjacent statements of the entry, the entry statement to the end of the program is a basic block

In terms of implementation, a basic block can be represented by a class, which may be named `BasicBlock`.

#### 6.1.1.2 Data flow analysis

After determining each basic block, the analysis of reaching definitions and active variables can be carried out.

* Arrival definition

  The calculation is done according to the formula $out=gen\cup (in-kill)$, and the finally obtained `out` is stored as an attribute of the basic block object.

* Active variables

  Calculate according to the formula $in=use\cup (out-def)$, and the finally obtained `in` is stored as an attribute of the basic block object.

After the `in` and `out` sets of each basic block are determined by calculation, the compilation and optimization can be officially started.

### 6.1.2 Optimization within the basic block

The optimization in the basic block is roughly divided into three types, and this part will be introduced one by one.

* Eliminate **local** common subexpressions

  * `DAG` graph creation

    The `DAG` graph can be established according to the algorithm in the book. Note that the selected nodes must be in the same basic block. Therefore, in the implementation, you can encapsulate all the APIs required for the establishment of the DAG graph into the BasicBlock class

  * `DAG` graph export intermediate code

    have to be aware of is. Because the deletion of common expressions is an optimization within a basic block, the corresponding duplicate nodes cannot be deleted when the operation of merging variables is performed during map creation, and can only be “temporarily” ignored in the current basic block. Because once the variable is used again by the following basic block, and the variable has been deleted, then there will be a problem.

* Constant merging and spreading

  Similarly, constant merging and dissemination also play a role in the basic block. The implementation ideas are as follows:

  For the variable `a` of the form `a=1+3`, all `a` can be replaced with the immediate number `4` before it is defined next time. Because the search range is limited to the basic block, there will be no unreachable sentences with the definition of `a=1+3`, thus ensuring the correctness of constant merging and propagation.

* Peephole optimization

  Peephole optimization is more conservative and independent than the optimization mentioned earlier, but it can also play a huge role in certain specific scenarios.

  The following peephole optimization strategies are mainly used in `Leopard`:

  * For unconditional jump instructions, if it is to jump to the next `label`, the jump can be omitted.
  * For addition and multiplication instructions, when the first operand is a constant or an immediate value and the second operand is not, the two operands can be swapped. In this way, more `MARS` package instructions can be reused when generating the target code.

### 6.1.3 Global optimization

The basis of global optimization is the division of basic blocks and data flow graphs mentioned in the first part, so the first part plays a vital role in the robustness of global optimization.

* Data flow analysis

  After the arrival definition and active variable analysis, we can establish a conflict graph between variables through the basic blocks and the relationships between them. There are many algorithms for building conflict graphs. According to the knowledge of theoretical courses: if one variable is active at the definition point of another variable, the two variables conflict.

  For non-conflicting variables, we can assign them the same global register. When allocating registers, you can choose the improved coloring method of `Briggs`, which solves the limitation of the two-coloring method of the `Chaitin` coloring method in the case of four nodes, and can obtain a more efficient register allocation strategy.

  \<img src="https://img-blog.csdnimg.cn/20201017205223798.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmzNzFFNT_color_70FxNzFFNT_size=70FxNzFFNT_size Principle Notes_Shu Yi Jiangnan's IT Blog-CSDN Blog" style="zoom: 33%;" /\>

* Copy propagation

  Copy propagation can be compared with the constant propagation in the basic block, but at this time it is the register that is propagated instead of the immediate data. According to the register allocation situation, propagation is feasible before the register corresponding to the variable is invalid and the left variable is not defined again.

* Dead code removal

  The impact of dead code on the performance of the program may not be as obvious as other parts, but it occupies a considerable part of the memory space, which has a great impact on the quality of the compiled target code. Therefore, for the integrity and standardization of the project, it is equally important to optimize related dead code removal.

  In the implementation, the basic block whose predecessor block is an invalid branch can be directly deleted. The following is an example for description.

  ```cpp
  if 1\> 2 goto invalid_block
      ...
  invalid_block:
   ...
  ```

  Because `invalid_block` has only the only predecessor and the branch cannot jump to the basic block corresponding to `invalid_block`, all codes in this basic block are unreachable. Therefore, the basic block can be ignored.

* Function inlining

  Function inlining changes to the code structure can be said to be quite large in many optimization strategies, but the benefits it brings are also quite significant. This is like "Navigators always take greater risks than spectators". It is a compromise between reliability and performance.

  In the implementation, there are two key points of concern, one is whether the function can be inlined, and the other is the renaming of the label after the function is inlined.

  Regarding whether a function can be inlined, you can use `BFS` to determine the existence of a ring in a directed graph of the function call relationship. Once a ring appears in the relationship graph, it means that the function cannot be expanded inline. Correspondingly, although many high-level languages ​​now specify whether the function should be expanded or not, for performance reasons, if there is no loop, it can be expanded by default.

  The renaming of the label after the function is inlined can be achieved by maintaining a variable `inlineCnt`. After generating a new label, it is self-incremented to ensure that all the labels will not have the same name, so that the functions of each inline expansion are different. There will be conflicts.

### 6.1.4 Loop optimization

* Loop unrolling

  The contribution of this part to performance is obvious, but the increase in the size of the memory occupied by the code file is also significant, which is a typical space-for-time strategy.

  Since MARS has a limit on the number of lines of code, it is difficult to determine the expansion threshold of the optimization (under what circumstances), so in the end, only individual loops with a small amount of statements and a small number of loops can be expanded.

* Code outsourcing and weakened loop strength

  Specifically, you can scan the statements inside the loop first to determine which variables have not been modified, then they are loop invariants. The definitions of these variables are moved outside the loop, which can reduce repeated calculations within the loop.

## 6.2 Machine related optimization

Since our compiler ultimately runs on the `MIPS` simulator, this part is equivalent to the optimization strategy for `MARS`.

When writing the compiler backend, a large number of instructions that have been encapsulated by `MARS` are usually used. They do not belong to the instruction set of the `MIPS` architecture, such as `mul`, `li`, `div`, etc. Note that their translation method is predefined by `MARS`, so there may be redundant translation. The redundant translation here does not mean that there is a problem with the translation of `MARS`, but that in the environment we face, certain steps can be omitted.

Take `addu` as an example. This is a `MIPS` native `R` type instruction, but it can be used as an `I` type instruction in `MARS`. The example is as follows:

* Object code generated by the compiler

  ```assembly
  addu $t1, $t1, 1001
  ```

* `MARS` translated target code

  ```assembly
  lui $1, 0x00000000
  ori $1, $1, 0x000003e9
  addu $t1, $t1, $1
  ```

It is not difficult to see that the original one instruction has been expanded to three, but if we change the target code generated by the compiler to:

* Modified compiler target code

  ```assembly
  li $1, 1001
  addu $t1, $t1, $1
  ```

At this time, `addu` is the native `R` type instruction of `MIPS`, and `MARS` will not be expanded, so the number of operation instructions can be reduced. Similarly, similar optimizations can be done for the `subu` instruction.

The following table lists some of the target instruction optimizations supported in `Leopard` for readers' reference.

| Original instruction | Equivalent instruction |
| ------------------- | ----------------------------- -------- |
| `div $t1, $t1, 2` | `li $1, 2`, `div $t1, $1`, `mflo $t1` |
| `mul $t1, $t1, 2^n` | `sll $t1, $t1, n` |
| `addu $t1, $t1, 1` | `li $1, 1`, `addu $t1, $t1, 1` |
| `subu $t1, $t1, 1` | `li $1, 1`, `subu $t1, $t1, 1` |

The following gives a set of comparative statistics on the number of calculation instructions before and after optimization. It can be seen that the role of machine-related optimization is also not to be underestimated.

* Original instructions

  ```assembly
  DIV: 605662
  MULT: 3638018
  JUMP/BRANCH: 3441232
  MEM: 47817479
  OTHER: 51217347
  FinalCycle: 168984827.0
  ```

* Optimize multiplication and division

  ```assembly
  DIV: 605662
  MULT: 526256
  JUMP/BRANCH: 3217708
  MEM: 47817477
  OTHER: 47711601
  FinalCycle: 155808505.0
  ```

* Optimize addition and subtraction

  ```assembly
  DIV: 605662
  MULT: 526256
  JUMP/BRANCH: 3217708
  MEM: 47817477
  OTHER: 43609601
  FinalCycle: 151706505.0
  ```

# Reference

* BUAA Compiler Lecture, Autumn of 2020.