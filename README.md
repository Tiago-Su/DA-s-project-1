## Description
**This project was made for the subject "Desenho de Algoritmos" and the objective of this program is the following:**<br>
Given a set of articles with domains and a set of reviewers with expertise in certain domains, we need to find the best or one of the best distributions, knowing that reviewers can only review a maximum amount of articles and an article needs at a minimum amount of reviewers.
In case which is impossible to fill all articles with reviewers, we need to print which articles cannot be filled.
<br>

Besides the main algorithm, we need to find critical reviwers which if the person fails to do his assignment, it will cause a failure.

## How to use
1º Press 2 in the main menu to select the dataset
2º Write the relative path to the dataset
3º Press 3 to run

## Project structure
![ProjectUML](./misc/DA1.png)

## Parser
![ParserUML](./misc/parser.png)

### How does it work
The parser class...    

### Why does it need to read the file from the start for each header 
Due to some irregularities in the dataset file (e.g. An '#' between Submissions and Reviewers) and some doubts about the .csv structure (e.g. Can the topics have a different order), led us to make the decision to create the most generic parser to avoid problems in the future.

### Time Complexity
Let l be the number of lines and h be the number of headers, we can define the upper bound to be O(l * h).
So in our project, the time complexity to parse the dataset is O(4 * l) = O(l)

## Adapter
![AdapterUML](.misc/adapter.png)

### How does it work
The adapter class...    

### Time Complexity:
Because it creates the graph, the time complexity is O(V + E)
<br>V: number of vertices
<br>E: number of edges

## MaxFlow
### How does it work
The adapter class...    

### Time Complexity
Because it creates the graph, the time complexity is O(V * E)
<br>V: number of vertices
<br>E: number of edges

## Tool
### How does it work
The adapter class...    


## Risk analysis
### How does it work
...

### Time complexity
The BFS takes O(V + E) and then we search for unvisited submissions and for their edges (O(V * E)). We can define our algorithm as O(V * E).
<br>But because the number of edges in this projects is smaller or equal to 2, i.e. constant, the BFS is the part which takes more time. 
<br>Overall: O(V + E)


## Credits
**This program was made by**
- Francisca Baldaia da Silveira
- Tiago Alexandre Rodrigues Botelho
- Tiago Su
