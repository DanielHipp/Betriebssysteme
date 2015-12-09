# L3-Timing

## Race-Condition

### Messergebnisse

| Threads, Loops | Mutex  | Peterson |
|----------------|--------|----------|
| 5, 10          | 0.099s | 2.114s   |
| 5, 100         | 0.594s | 34.536s  |
| 10, 10         | 0.155s | 14.785s  |

### Interpretation

Es ist zu erkennen, dass der Peterson-Algorithmus sehr langsam ist.
Dies hängt u. a. damit zusammen, dass dieser Algorithmus aktiv wartet.
Ein Mutex hingegen ist deutlich schneller, da nur ein Lock gesetzt bzw.
aufgehoben wird und die Threads nicht aktiv warten.

## C in Python

### Messergebnisse

Für jede Messung wurde 100000 mal die Wurzel aus 5 berechnet.

    ===== cyforksqrt.sqrtm(5) =====
    Result: 2.23606797749979
    Execution Time: 0.026903095000307076 sec
    
    ===== cyforksqrt.sqrt2(5) =====
    Result: 2.23606797749979
    Execution Time: 0.034482742004911415 sec
    
    ===== forksqrt.sqrt2(5) =====
    Result: 2.23606797749979
    Execution Time: 5.625927301996853 sec
    
    ===== math.sqrt(5) =====
    Result: 2.23606797749979
    Execution Time: 0.03002017100516241 sec

### Interpretation

Die Funktion forksqrt.sqrt2() ist mit großem Abstand am langsamsten.
Das war auch zu erwarten, da diese Funktion in reinem Python geschrieben ist
und zudem nicht mit normalem Float-Datentyp rechnet, sondern Decimal verwendet.
Deutlich schneller hingegen sind die 3 anderern Implementierungen. 
Die Funktion cyforksqrt.sqrtm() ist am schnellsten, gefolgt von math.sqrt()
und danach cyforksqrt.sqrt2(). Alle sind mit Hilfe von C optimiert worden. Dabei
verwenden cyforksqrt.sqrtm() und math.sqrt() die sqrt Funktion aus der
C-Bibliothek und cyforksqrt.sqrt2() ist die in Cython umgeschriebene Funktion
forksqrt.sqrt2().

## mthread

### Maximale Threads

Die maximale Anzahl an Threads ist bei Linux abhängig davon, wieviele Prozesse maximal ausgeführt werden dürfen. Da in Linux ein Thread als Prozess behandelt wird, können natürlich nur soviele Threads laufen bis diese Zahl erreicht ist. Und diese Zahl richtet sich nach dem gesamten virtuellen Speicher. Ist dieser voll, können auch keine Prozesse mehr kreiert und dementsprechend auch keine Threads mehr erzeugt werden.

### Zeitverhalten

Das Zeitverhalten ist größtenteils abhängig von der Wartezeit der einzelnen Threads. Je länger die einzelnen Wartezeit, desto größer die gesamte Wartezeit. Die Threads selber brauchen nur Bearbeitungszeit im Mikrosekundenbereich. Lässt man das join weg, ist das Programm so schnell beendet wie der Hauptthread benötigt um einmal durch das gesamte Programm zu laufen und alle Threads zu erstellen. (Das ist mit time nicht mehr zu messen, da diese Zeit kürzer als eine Millisekunde ist).

### pthread_join weglassen

Sofern pthread_join weggelassen wird besteht zuerst einmal folgende Gefahr: Der Prozess der die Threads erzeugt hat wartet nicht auf die Threads, sodass diese unter Umständen einfach beendet werden, sobald der Prozess endet. 
In unserem speziellen Fall kann man Glück haben und es werden alle Threads bis zu dem Punkt ausgeführt, an dem sie die Ausgabe 'Hallo Welt' ausgeben. Aber die Wartezeit die jeder Thread hat wird nicht gewartet, da der Prozess keine eigene Wartezeit hat und dementsprechend einfach beendet. So kommt es dem Nutzer vor als hätten die Threads keine Wartezeit. 
 
# matrix.c

### Messergebnisse

Sämtliche Matrizen haben als Zahlen Zufallszahlen zwischen 1 und 10 (inkl. drei Kommastellen).
Gemessen wurde mit time.

|Anzahl Spalten/Zeilen | ohne Threads | mit wenig Threads (10)| mit vielen Threads (1000)|
|----------------------|--------------|-----------------------|--------------------------|
|10                    | 0.0s         | 0.0s                  | 0.0s                     |
|100                   | 0.02s        | 0.01s                 | 0.01s                    |
|1000                  | 21.64s       | 3.57s                 | 1.79s                    |

### Interpretation

Wie zu erwarten wurde das Programm schneller je mehr Threads genutzt wurden. Das ist allerdings nur bis zu einem bestimmten Punkt so: Jeder Matrizenmultiplikation (nXn) besitzt genau n * n Multiplikationen. Benutzt man nun mehr threads als diesen Wert wird mein Programm nicht mehr schneller. Die überzähligen Threads berechnen lediglich Werte die bereits andere Threads berechnet haben/berechnen. Insofern kann das Programm nicht mehr schneller werden. Bei großen Matrizen wie etwa 1000X1000 ist es schwer 1000000 Threads zur Verfügung zu stellen, da spielt diese Warnung keine Rolle, aber bei kleineren Matrizen wie etwa 10X10 ist dieser Fall gut möglich.



