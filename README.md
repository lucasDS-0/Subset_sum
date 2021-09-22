# Subset sum problem
A team project done in an advanced algorithms and data structures about the [subset sum problem](https://en.wikipedia.org/wiki/Subset_sum_problem).


## Usage
The source code to solves the problem at hand it's located in the `distanciamiento_social.cpp` archive.

To compile it, the following fragment of code is needed to be executed in the command line:
```
g++ -o distanciamiento_social distanciamiento_social.cpp -O2 -std=c++14
```

The script should use one of the following arguments to work with the desired algorithm:
- `FB`: Brute Force
- `BT`: Backtracking
- `BT-F`: Backtracking with only the feasibility constraint.
- `BT-O`: Backtracking with only the optimality constraint.
- `DP`: Dynamic programming.

Lastly, an instance is needed to be processed. For example, to execute backtracking with only optimality constraints over instance `INST1.TXT`, the next command is needed:
```
cat INST1.txt | ./distanciamiento_social BT-O
```

The solution itself it's shown through the standard output, and the execution time is shown through the stderr.

The instance generation and run of experiments is handled in Python using [Jupyter Lab](https://jupyter.org/) (to see these notebooks, a Jupyter Labs installation is needed).

Once the required software is installed, open a terminal in the `Python` folder and run:
```
jupyter lab
```

There are 3 files to be found:
- `generar-instancias.ipynb`: generates the instances described in the article y places them in the `python/instancias` folder.
- `experimentos.ipynb`: runs the experiments and stores the results of every execution in a CSV en the `python/resultados` folder.
- `analysis.ipynb`: takes the results and renders the corresponding graphics.
