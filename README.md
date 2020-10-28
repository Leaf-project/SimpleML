#       SimpleML
Machine learning model in c++. Main methode : Gradient descent (1st derivative).
Other methodes : Study of other levels of derivatives like 2nd or -1nd (anti-derivative).

## Structure of model in c++
T - type of data (float, double, long double ...)
Array : any dimention and any length.
  -Data : vector<type>
  -Shape : the 'dimention" of array
Var: Each variable is an Array.
  -time : vector of Array<T>
Memory: Code and vector of Var<T>
  - datas : vector of variables
  - code: 'math' code
    - code : brut text split in list of lines
    - fnlines : list of lines of functions declarations (all ':')
    - argsid : list of all args variables 'names'
    - main : with functions to execute first (the MAIN function)
Model: List of all functions (f-1, f0, f1 ...)
  - levels : from smaller n of var to bigger
  - relativ (witch is the MAIN functions (f[0]) (where -1 is anti-derivativ and 1 is first derivative)

## Code
Code is just a list of operation. Each variable is show as 'id' (position in Memory.datas)
To compute 3x+1 we store like this { {x}, {3.0}, {1} } then : 0 | 1 * 2 +  ((0|), (1*), (2+))
Operators:
  - | - set target
  - ) - call functions
  - + - add
  - - - sub
  - '*' - mul
  - / - div
  - ^ - pow
  - @ - dot product
  - a - sum of array (Σ ) *not implemented*
  - s - sub of array *not implemented*
  - d - div of array *not implemented*
  - m - mul of array
Functions declatation:
argument_id:   <- declaration
...code
return_var_id# <- end
First decladed function is named 0, second 1 ...
To call first func : 0)
