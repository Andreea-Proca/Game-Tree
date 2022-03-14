# Game-Tree
 
Pentru task 1 si 2 am folosit aceeasi citire si am utilizat acceasi structura struct tree_node pentru a defini un nod din arbore.
Functia "creare" creeaza in mod recursiv noduri in arbore care contin tabla de joc in formatul unei matrici de 3x3 la un moment dat al jocului, 
pornind de la o tabla data si jucatorul care urmeaza la rand, cu alte cuvinte arborele de joc.
Fiecare nod reprezinta stadiul jocului la un miment dat. Aceasta foloseste si functia "verificare" care verifica daca exista un castigator pentru un nod dat.
Pentru task 1 am creat o functie recursiva care salveaza arborele intr-un fisier de iesire dat ca argument,  "save_task1".
Pentru task 1 si 2 am creat o functie recursiva care elibereaza memoria alocata fiecarui nod.

Pentru task 2 am folosit task 1 si functiile sale. Dupa citirea tablei initiale, am creat arborele de joc folosind functia "creare". 
In structura tree_node se afla atributul de tip char "sisau" care retine valoarea nodului in arborele SI/SAU.
Functia recursiva "task2" construieste arborele SI/SAU. Pentru nodurile de tip frunza se verifica folosind functia "verifica" daca contin o tabla castigatoare, daca da, atunci atributul sisau este "T', iar daca nu, "F". 
Daca nodul dat are un singur fiu, atributul sisau devine acelasi cu al fiului.
Daca are mai multi fii, daca nodul este de tip "sau"(jucatorul care urmeaza sa mute este cel care trebuie sa castige), atributul sisau este "T" daca cel putin un fiu are "T",
iar daca nodul este de tip "si"(jucatorul care urmeaza sa mute este adversarul), atributul sisau este "T" daca toti fiii au "T".
Se autoapleleza functia pentru fiecare fiu al nodului. Arborele sisau creat este salvat intr-un fisier dat cu ajutorul functiei recursive "save_task2".

Pentru task 3 am folosit o structura putin diferita struct tree_node_3 si o citire diferita. Am citit inaltimea arborelui ca sir de caractere pe care l-am transformat in numar intreg.
Mai departe am folosit o bucla "for" in care am parcurs fieare nivel si am citit caracter cu caracter valorile din fisierul de intrare. 
Totodata, daca nivelul este impar, toate nodurile de pe acel nivel vor avea atibutul jucator din structura cu valoarea "max", iar daca nu, "min".
Am folosit doi vectori de pointeri la noduri. In primul am retinut toate nodurile de pe nivelu anterior, iar in al doilea am retinut noduile de pe nivelul curent pe care le am creat si retinut ca copii ai nodurilor de pe nivelul anterior.
Inainte de a trece la urmatorul nivel, am retinut nodurile din al doilea vector in primul si am eliberat memoria alocata celui de al doilea.
In fucntie de tipul de paranteza, am retinut valoarea citita ca numar de fii sau valoare in structura nodului.
Functia recursiva "calc" calculeaza valoarea fiecarui nod, realizand algoritmul Minimax. Daca atributul jucator este "min", se apeleaza functia min, daca este "max" se apeleaza functia max.
Functia min returneaza valoarea minima dintre toti copiii unui nod dat, iar functia max, valoare maxima. Astfel valoarea nodului dat devine minimul sau maximul dintre valorile fiilor.
Functia "save_task3" valveaza valorile sub forma de arboreintr-un fisier dat, iar "free_node_task3" elibereaza memoria alocata nodurilor.
