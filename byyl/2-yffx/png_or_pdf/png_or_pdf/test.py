import graphviz
import os

data = []

with open("syntax.output", "r") as f:
    lines = f.readlines()
    # print(lines)
    for line in lines:
        line = line.strip("\n")
        if line != "":
            data.append(line.strip("\t"))

idx = 0
id = 0

while idx < len(data) and data[idx].find("State") == -1:
    idx += 1

with open("graphviz-git_basics-syntax.txt", "w") as of:
    of.write("""digraph git_basics {
	graph [
		label = "Basic git concepts and operations"
		labelloc = t
		fontname = "Helvetica,Arial,sans-serif"
		fontsize = 20
		layout = dot
		rankdir = LR
		newrank = true
	]
	node [
		style=filled
		shape=rect
		pencolor="#00000044" // frames color
		fontname="Helvetica,Arial,sans-serif"
		shape=plaintext
	]
	edge [
		arrowsize=0.5
		fontname="Helvetica,Arial,sans-serif"
		labeldistance=3
		labelfontcolor="#00000080"
		penwidth=2
		style=dotted // dotted style symbolizes data transfer
	]""")
    while idx < len(data):
        thisline = "\n"+str(id) + "[label=<<table><tr> <td> <b> " + data[idx] + " </b>"
        idx += 1
        while idx < len(data) and data[idx][4].isnumeric():
            thisline += " <br/>"+ data[idx]
            idx += 1
        thisline +=  "</td> </tr></table>>]"
        of.write(thisline)
        while idx < len(data) and data[idx].find("State") == -1:
            if data[idx].find("reduce") == -1:
                tmp = data[idx].split()
                of.write("\n"+str(id)+"->"+tmp[-1]+"[label=\""+tmp[0]+"\"]")
            idx+=1
        id += 1
    of.write("\n}")

os.system("dot -Tpng graphviz-git_basics-syntax.txt -o graphviz-git_basics-syntax.png")
