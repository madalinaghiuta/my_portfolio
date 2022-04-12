    -FUNCTII FOLOSITE-
* "number" - transforma un char intr-un numar 
* "adauga_matrice" - adauga un cuvant in matricea de joc in functie de de coordonatele acestuia si directie
* "coordonate_cuvant" - extrage din sirul de caractere coordonatele cuvantului astfel:
        - primul cuvant reprezinta coordonata "y"
        - al doilea cuvant reprezinta coordonata "x"
        - al treilea cuvant reprezinta coordonata "d"
        - al patrulea cuvant reprezinta cuvantul ce trebuie adaugat in matrice
        - primele 3 cuvinte sunt transformate in numere
* "calculare_scor" - verifica fiecare carater din cuvant si adauga la scor numarul corespunzator literei respective
* "scor_bonusuri_2_3" - se verifica in matricea de bonus daca vreo una din litere se suprapune cu 1 sau cu 2
        - daca se suprapune cu 1, scorul se inmulteste cu 2
        - daca se suprapune cu 2, scorul se inmulteste cu 3
* "scor_bonusuri_2" - se verifica in matricea de bonusuri daca vreo una din litere se suprapune cu 1
        - daca da, scorul se inmulteste cu 2
* "scor_bonusuri_3" - se verifica in matricea de bonusuri daca vreo una din litere se suprapune cu 2
        - daca da, scorul se inmulteste cu 3
* "verificare_orizontala" - verifica daca primul cuvant din words care nu a fost pus de niciunul dintre jucatori, poate fi pus pe orizontala
        - daca acel cuvant nu iese din marginile matricei de joc
        - daca de la pozitia x+1 pana la x+strlen(cuvant) nu se gaseste nicio litera, atunci s-a gasit string-ul potrivit
*  "verificare_verticala" - verifica daca primul cuvant din words care nu a fost pus de niciunul dintre jucatori, poate fi pus pe verticala
        - daca acel cuvant nu iese din marginile matricei de joc
        - daca de la pozitia y+1 pana la y+strlen(cuvant) nu se gaseste nicio litera, atunci s-a gasit string-ul potrivit
    
    -TASK-
* "task0" - se parcurge matricea de joc si se adauga caracterul '.' pe toate pozitiile
* "task1" - se citeste numarul "n" si apoi sirurile corespunzatoare celor n cuvinte cu ajutorul functiei coordonate_cuvant
        - se adauga in matrice cu ajutorul functiei adauga_matrice
* "task2" - se citeste numarul "n" si apoi sirurile corespunzatoare celor n cuvinte
        - daca pozitia pe care se citeste cuvantul este una impara, cuvantul corespunde primului jucator 
        - se calculeaza scorul acestuia cu ajutorul functiei calculare_scor
        - in mod identic se procedeaza pentru al doilea jucator
* "task3" - se citesc cele 2 siruri de doua caractere dupa care se face conditionarea bonusurilor
        - se citeste numarul "n" si apoi sirurile corespunzatoare celor n cuvinte
        - se verifica conditiile de acordare de bonus
        - daca un cuvant contine "XX", se verifica cu ajutorul functiei scor_bonusuri_2
        - daca un cuvant se termina cu "YY", se verifica cu ajutorul functiei scor_bonusuri_3
        - daca un cunvant contine "XX" si se si termina cu "YY", se verifica cu ajutorul functiei scor_bonusuri_2_3
        - se afiseaza scorurile corespunzatoare celor 2 jucatori cu mesajele corespunzatoare
* "task4" - se citesc cele 2 siruri de doua caractere dupa care se face conditionarea bonusurilor
        - se citeste numarul "n" si apoi sirurile corespunzatoare celor n cuvinte 
        - se citesc cuvintele si coordonatele lor cu ajutorul functiei coordonate_cuvant
        - fiecare cuvant nou citit se adauga la un sir de cuvinte
        - se verifica fiecare cuvant din word daca face parte din sirul format 
        - daca nu, se parcurge matricea de joc din coltul din stanga sus, linie cu linie
        - daca se gaseste prima litera in matrice, se verifica conditiile pentru adaugarea pe orizonatala
        - daca nu se poate adauga pe orizontala, se incearca adaugarea pe vericala a cuvantului
* "task5" - se calculeaza scorul pentru fiecare dintre jucatori la fel ca la task-ul 3
        - se verifica conditiile in mod asemanator task-ului 4
        - se calculeaza un maxim al scorurilor posibilelor cuvinte
        - daca acesta insumat cu scorul celui de-al doilea jucator da un punctaj mai mare sau egal cu scorul primului, se adauga cuvantul in matricea de joc
        - in caz contrat, se afiseazamesajul "FAIL!" 