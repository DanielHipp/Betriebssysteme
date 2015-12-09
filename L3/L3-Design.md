# L3-Design 
---
---

## Einführung 
---

* In dieser Aufgabe war vorgegeben, dass eine vorgegebene Anzahl von zu erzeugenden Threads die Worte "Hallo Welt" ausgeben mussten. 
* Anschließend sollte jeder Thread für eine angegebene Mindestanzahl und/oder Maximalanzahl bzw. eine zufällige Anzahl an Sekunden warten. 
* Alle Threads müssen ihren Job beenden und es muss eine Textausgabe zur Hilfe des Users geben.

---


## Übersicht 
---

* In meinem Entwurf werden in einer Schleife zuerst alle Threads mit einer Methode für die Ausgabe und die Wartezeit erzeugt. 
* Anschließend wird eine zweite Schleife durchlaufen die dafür sorgt das jeder Thread gejoined wird und so alle Threads durchlaufen werden können. 
* Die Ausgabemethode selbst gibt lediglich eine Textzeile aus und lässt den Thread für eine gegebene oder zufällige Zeit an Sekunden schlafen.
* Die Hilfsmethode gibt an, welche Parameter möglich sind. 
* Globale Variablen:
	* verbose: 
		* Sofern der Parameter -v angegeben wird, bekommt der User weitere Informationen
	* timeval: 
		* Sofern der Parameter -c angegeben wird, wird die Zeit an Mikrosekunden angezeigt, die der Gesamtprozess und die einzelnen Threads brauchen
	* randomMin bzw. randomMax:
		* Speichert die jeweilige Mindest- und/oder Maximalzufallszahl. Angegeben wird das jeweils mit -r(min) und -R (max)
	* auf diese Daten musste auch die Funktion PrintHello(...) zugreifen, weshalb diese vier Variablen außerhalb der main(...) initialisiert wurden. Sie der PrintHello(...) - Funktion direkt zu übergeben, wäre zu umständlich für dieses relativ kleine Programm gewesen.

---


## Funktionen 
---

### int main(int argc, char *argv[]) 
* Die wichtigste Funktion. Sie erzeugt alle Threads, joined alle und beendet auch das Programm wieder.
* Die einzelnen Schritte die die main(...) dabei durchläuft:
	* Zuerst wird ausgelesen was übergeben wird:
		* Dazu wird die Funktion getopt(...) genutzt. Diese liest aus einer Reihe von char* Werten. Sofern Werte nach einem Parameter vorkommen, werden diese vorrübergehend in "optarg" gespeichert
		* Unterschieden wird dabei nach:
			* h: 
				* ruft die "Helper" - Methode auf, die angibt welche Parameter benutzt werden dürfen
			* v: 
				* aktiviert die "verbose" - Variable die dafür sorgt das der User mehr Ausgabetext erhält.
			* r: 
				* Die anschließende Zahl ist die untere Grenze der zufälligen Wartezeit der einzelnen Threads
			* R:
				* Die anschließende Zahl ist die obere Grenze der zufälligen Wartezeit der einzelnen Threads.
			* t:
				* Die anschließende Zahl gibt die Anzahl an Threads die erstellt werden und die PrintHello(...) Methode durchlaufen sollen an
			* c:
				* aktiviert die "timeval" - Variable wodurch der User erfährt wie lange ein einzelner Thread an Ausführungszeit braucht und wie lange das Gesamtprogramm benötigt um zu beenden
			* j:
				* ist dieser Parameter gegeben, wird das joinen in die Threads nicht ausgeführt
	* Nachdem gegebene Parameter analysiert wurden, wird die erste Schleife durchlaufen, welche die Threads erzeugt:
		* Die Schleife läuft solange wie Threads angegeben wurden oder die Standart-Anzahl von 4 Threads.
		* Jeder Thread wird mit der Funktion "PrintHello" sowie der Nummer des Threads erzeugt.
	* Sofern die "verbose" - Variable gesetzt wurde wird anschließend ausgegeben ob alle Threads erzeugt wurden
	* Sofern die "timeval" - variable gesetzt wurde bekommt der User angegeben wie lange das erzeugen der Threads gedauert hat
	* Anschließend wird die zweite Schleife durchlaufen die die Threads joined:
		* Die Schleife läuft ebenfalls solange, wie Threads angegeben und erzeugt wurden oder die Standard-Anzahl von 4
		* Jeder Thread wird gejoined und gibt seinen Speicherort an die Variable "status"
	* je nach Aktivierung der "verbose" - und der "timeval" - Variablen wird wieder die Zeit die benötigt wurde um die Threads zu joinen angegeben und/oder mehr Text ausgegeben

### void *PrintHello (void *threadarg) 
* Es wird der Satz "Thread with Number x says 'Hello World'" ausgegeben 
* Anschließend wird der Thread für eine zufällige Zeit schlafen gelegt. Sofern die beiden Variablen "randomMin" und/oder "randomMax" festgelegt wurden geben diese die Ober- und Untergrenze der Zufallszahl an
* Sofern die "timeval"- und/oder "verbose"- Variable gesetzt sind wird zusätzlich die Ausführungszeit des Threads in Mikrosekunden und/oder weitere Zeilen Text ausgegeben
* Nach dem "Schlaf" wird der Thread beendet und sein Zustand in die Variable "status" geschrieben

### void printHelper() 
* eine einfache Methode die den Hilfstext ausgibt, wenn der User eine falsche Eingabe eingegeben hat oder gewollt den Parameter -h angefügt hat. 
* Sollte der User weitere Parameter zu -h genutzt haben, so "verfallen" diese, da diese Methode das Programm beendet, mit der Annahme, dass der User nur -h aufruft, wenn er nicht weiß was das Programm für Eingaben erwartet

### void checkBorder() 
* diese einfache Methode überprüft ob die untere Grenze der Zufallszahl für die Threads wirklich kleiner ist als die Obere.

---


## Weitere Probleme / Themen 
---

### Fehlerbehandlung
* In der Main wird am Anfang bei getopt(...) geprüft ob Argumente vorhanden sind und ob diese korrekt sind.
Wenn nicht, wird der "Helper" aufgerufen und das Programm beendet.
* Bei der Erzeugung eines Threads und beim joinen eines Threads wird überprüft ob das jeweils erfolgreich war.
	* Sofern der Rückgabewert 0 ist, ist es ein Erfolg
	* Bei Misserfolg wird ein fehler ausgegeben

---



### -j: ohne join 
* Sofern dieser Parameter angegeben wird, entfällt das join, wodurch die Wartezeit sehr stark sinkt, da die Threads nun nicht mehr schlafen, da sie davor beenden. Allerdings besteht dadurch die Möglichkeit das nicht alle Threads beendet werden, da der Hauptthread beendet ohne auf die wartenden Threads zu warten.

---


## Kritik 
---

* Bei sehr großer Anzahl an Threads kapituliert das Programm da nicht mehr Threads erzeugt werden können.

---


## Milestones 
---

* Sämtliche Aufgaben werden von Daniel Hipp übernommen:
	* Zuerst wird nur ein Thread erzeugt um die Methoden "PrintHelper", "testBorder" und "PrintHello" zuerst an nur einem Thread zu testen
	* Anschließend werden zwei Schleifen implementiert die mehrere Threads erzeugen und joinen.

---