# Command line parsing

To effectively interact with command-line input, our algorithm must be able to interpret it. This requires translating the command line input, a process known as parsing. Among the various parsing methods available, we have selected a Recursive Descent parser. This choice is motivated by the parser's simplicity and flexibility, making it well-suited for Minishell.

Here is a link to the best video I found regarding Recursive Descent parsing :

	https://youtu.be/SToUyjAsaFk?si=7EHUhZQaDTpUa-Sv&t=1

## Lexing

In order to translate it we first need to change our command line from a string to a list of tokens. This is a process known as the lexing, short for "lexical analysis". A token is a meaningful element of a language, in shell they are words, pipes, redirections, etc...

Each token will have their content associated with a specific type, in our case:

* T_PIPE
* T_WORD
* T\_RET_FROM
* T\_RET_TO
* T_DLESS
* T_DGREAT

The lexing is separated into three steps:

1. Expanding environment variables
2. Tokenisation
3. Formating quoted text

**Expanding environment variables**

The first step is to expand environment variables (such as \$PATH). To do so, we will simply replace the \$VAR with its corresponding value. However, environment variables can only be expanded when they are located outside simple quotes ('), or inside double quotes (").

**Tokenisation**

The second step is simply to split on whitespaces unless the whitespace is situated between quotes (more on the quote formatting later).
If the word contains only '|' it becomes a T\_PIPE If the word contains only '>' it becomes a T\_RET_TO, etc... The rest usually become T\_WORDs.


**Formating quoted text**

The third and final step is to format the quoted text according to the simple and double quotes rules.

The way quotes are handled in bash can be quite confusing. So I'll try my best to explain it clearly.

First, let's distinguish between syntactic and literal quotes. Literal quotes are the characters themselves, like " and '. Syntactic quotes, on the other hand, function as formatting indicators.

When entering a cmd line, what differenciate syntactic and literal quotes is simply the order by which they come. Syntactic quotes come by pair, we will talk about opening and closing quotes.

	Example :
		In "'ls -l'", the first " before 'ls, is the opening quote, so everything before the next " (closing quote)
	will be interpreted according to the double quotes rules.
		In '"ls -l"', the first ' before "ls, is the opening quote, so everything before the next ' (closing quote)
	will be interpreted according to the simple quotes rules.

There are two types of formatting:

* Simple quotes :
 Every character between an opening and a closing simple quote will be interpreted literally. It means that any double quote will be interpreted as the literal ". It will also interpret environment variables literally, '\$VAR' will still be '$VAR'.
* Double quotes :
Similarly, everything between two syntactic double quotes will be interpreted literally, and escape characters will be interpreted literally. However, environment variables are expanded.

Now, the confusing part comes when quotes appear in the cmd line and in variables.

	Entering : "ls -l" will be interpreted as a single token |ls -l| because of the syntactic quotes.
	Entering : 'ls' "-"'l' will be interpreted as two token |ls||-l| because the syntactic quotes will be removed in the third step of the lexer.
	Entering : "'ls'" -l will be interpreted as |'ls'||-l| and will result in an error because the inner ' will be literal, and then won't be removed in the third step.

	With VAR="-l -a"
	Entering : ls $VAR will be interpreted as |ls||"-l -a"| because any quotes contained inside a variable value is a literal quote. Therefore ls "$VAR" will still result in |ls||"-l -a"|

**Examples of the three steps together:**

> Entering : **ls -la**
> 
> 1. Variable expansion:	**| ls -la |** (no var here)
> 2. Split into tokens:		**| ls | | -la |**
> 3. Quote formatting:		**| ls | | -la |** (no quotes here)
>  
> With **VAR=-l -a**
> 
> Entering : **ls \$VAR**
> 
> 1. Variable expansion:	**| ls -l -a |**
> 2. Split into tokens:	**| ls | | -l | | -a |** (gets splitted on whitespaces)
> 3. Quote formatting:		**| ls | | -l | | -a |** (no quotes here)
> 
> Entering : **ls "\$VAR"**
> 
> 1. Variable expansion:	**| ls "-l -a" |**
> 2. Split into tokens:		**| ls | | "-ls -a" |** (does not get splitted in between quote)
> 3. Quote formatting:		**| ls | | -ls -a |** (syntactic quotes are removed)
> 
> Entering : **ls '\$VAR'**
> 
> 1. Variable expansion:	**| ls '$VAR' |** (does not expand when between simple quotes)
> 2. Split into tokens:		**| ls | | '$VAR' |**
> 3. Quote formatting:		**| ls | | $VAR |** (syntactic quotes are removed)
> 
> With **VAR="-l -a"**
> 
> Entering : **ls \$VAR**
> 
> 1. Variable expansion:	**| ls "-l -a" |**
> 2. Split into tokens:		**| ls | | "-ls | | -a" |** (gets splitted because the quotes are literal)
> 3. Quote formatting:		**| ls | | "-ls | | -a" |** (literal quotes are not removed)

We talked about quotes being interpreted literally when contained in a variable value, however, they are not the exception. Every character contained in a variable value should be interpreted literally, therefore, any special characters ('>', '<', '|', etc...) should be interpreted as T_WORD, and not as any other type of token.

## Parsing

Now that we have converted our command line into its meaningful elements, we now need to arrange them following the rules of our grammar. To do so, we will apply the Recursive Descent Parsing algorithm (watch the video for more details) to build an AST (Abstract Syntax Tree). Basically, we will convert each tokens into node, and arrange in a manner that will allow us to interpret these commands more easily while respecting the order of the command line.

## Builtins

### export

**export VAR=VALUE**

	Adds VAR or modify VAR if it already exist in the environment variables.
	Modify the env variables of every subshells accordingly.

**export VAR=**

	Same behaviour but with empty string, added as VAR=

**export VAR**

	If VAR exist in the environment variables, does nothing.
	Else, the variable VAR is added to the shell variables in the format **VAR=**

**export**

	Prints all environment variables as well as the subshells shell variables.
	All variables are printed in the order they are stored.
	They are formatted as : **declare -x VAR="VALUE"**
	If the value is empty, it is formatted as :
		when exported as export VAR : declare -x VAR
		when exported as export VAR="" : declare -x VAR=""

**export "" || export ''**

	Outputs error : bash: export: '': not a valid identifier

Any variable and quotes in the argument will first be expanded and handled following the rules specified earlier.

###env

	Displays all environment variables and not the shell variables.

The order in bash appears to be in ASCII order but it has not been strictly defined by the POSIX standards, so balec en gros.
