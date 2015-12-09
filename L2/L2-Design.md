# 1.Aufgabenstellung #
---

Der Stack aus Aufgabe 1 soll nun in einen generischen Stack umgewandelt werden, sodass nicht eine jeweils eigene Stack-API für unterschiedliche Typen erstellt werden muss.

## 1.1 Vorraussetzungen ##
* Die vorhandene API sollte nicht geändert werden. Falls doch mit  
ausführlicher Begründung.
* Die Bibliothek soll eine ausführliche Fehlermeldung beinhalten.
* Speicherleaks sofern vorhanden entfernen.
* Die Bibliothek wird unabhängig von den Tests kompiliert.
* in genstacklib.c und in allen Tests soll lediglich genstacklib.h includiert werden.
* Sofern für die Tests ebenfalls Headerdateien angelegt werden, so werden diese der Bibliothek nicht bekannt gegeben.

# 2. Lösung #
---

## 2.1 Einleitung ##
* Es werden erneut die Funktionen aus dem Stack aus L1 verwendet
* Die Funktionen haben in diesem Fall keine Ahnung vom Typen der gespeicherten Objekte, weshalb jetzt die Größe mitangegeben werden muss.
* Daher werden sie mithilfe von size_t und void pointern generisch gemacht.
* Die API die dafür verwendet wird, sieht wie folgt aus:
  * Ein void - Zeiger namens elems, der auf den Anfang des Stacks zeigt.
  * Ein int - Wert namens elemSize der die Größe eines übergebenen Objekts angibt.
  * Ein int - Wert namens logLength der die Anzahl der Elemente auf dem Stack angibt.
  * Ein int - Wert namens allogLength der die Gesamtgröße des Stacks angibt.
  * Ein void - Zeiger namens freefn der auf eine erweiterte free - Methode zeigt die zum Löschen komplexer Datentypen benötigt wird.

## 2.2 Funktionen##

### 2.2.1 void GenStackNew(genStack *s,int elemSize, void (*freefn)(void*))###
* Erstellt einen neuen Stack an der übergebenen Adresse. 
* Dieser Stack wird direkt initialisiert und bekommt eine Größe von 4 mal der mitgegeben Element - Größe.
* Die übergebene freefn - Adresse wird dem internen void - Zeiger freefn übergeben.

### 2.2.2 void GenStackDispose(genStack *s) ###
* Sofern der Zeiger 'elems' nicht NULL ist, wird überprüft ob die Funktion freefn() von Nöten ist, indem der interne Zeiger 'freefn' auf NULL getestet wird. 
  * Ist der Zeiger vorhanden so wird die externe Funktion aufgerufen um den Speicher komplett zu reinigen und anschließend den eigentlichen Stack zu löschen. (Für komplexe Typen)
  * Ist der Zeiger nicht vorhanden so wird lediglich der Stack gelöscht ohne eine externe Funktion zu verwenden. (Für einfache Typen)

### 2.2.3 void GenStackEmpty(const genStack *s) ###
* Diese Funktion testet ob der Stack leer ist oder nicht.
* Dazu benutzt sie eine einfach Abfrage der Variablen 'logLength'. Ist diese größer null liefert GenStackEmpty false, ansonsten true zurück.

### 2.2.4 void GenStackPush(genStack *s, const void *elemAddr) ##
* In der Funktion wird zuerst ein void - Zeiger angelegt der später auf die Adresse im Stack zeigt auf die gespeichert werden soll. 
* Es wird abgefragt ob die Werte 'logLength' und 'allocLength' gleichwertig sind, da dann der Speicher vergrößert werden muss.
  * Sofern sie gleichgroß sind, wird ein neuer Stack durch realloc() erzeugt. Dazu wird realloc der Zeiger 'elems' übergeben sowie die (in diesem Fall) doppelte allogLength.
  Anschließend wird per assert() überprüft ob realloc erfolgreich verlief.
    * Wenn ja wird der Wert 'allocLength' verdoppelt und der void - Zeiger zeigt auf die oberste Stelle des Stacks, die mithilfe der Datengröße sowie der 'logLength' berechnet wird. 
    * Danach wird die Funktion memcpy() aufgerufen die einen neuen Zeiger auf ein neues Objekt erstellt. 
      * Es gibt nach dem Aufruf von memcpy() also sowohl das Urspungsobjekt, wie auch die Kopie. 
      * Dabei gilt zu beachten, das memcpy() nur den ersten Zeiger kopiert und mit doppelten Zeigern wie z.B. bei structs seine Schwierigkeiten hat.
    * Anschließend wird 'logLength' um eins erhöht.
  * Sofern der Speicher noch groß genug für ein weiteres Objekt ist und die beiden Werte ungleich sind, wird direkt der Zielpunkt des void - Zeigers ermittelt und memcpy() aufgerufen. 
  * Anschließend wird auch hier 'loglength' um eins erhöht.

### 2.2.5 void GenStackPop(genStack *s, void *elemAddr) ###
* GenStackPop liefert das erste Element des Stacks zurück. Dazu wird zuerst 'logLength' um eins erniedrigt. 
* Anschließend wird ein void - Zeiger erzeugt dem danach die Adresse mit dem obersten Element zugewiesen wird. Diese wird wieder wie in Push mithilfe der Datengröße und der 'logLength' berechnet. 
* Ebenfalls wie in Push wird die memcpy() - Funktion aufgerufen. Diesmal wird aber an der Stelle einer, der GenStackPop() - Methode übergebenen Adresse eine Kopie des obersten Elements des Stacks erzeugt.

## 2.3 Weiteres ##
* Es wäre auch möglich gewesen einen Stack mithilfe einer verketteten Liste zu erzeugen.

# 3. Weitere Probleme / Themen #
---

# 4. Kritik #
---

* Der Typ der Elemente muss im Client zuerst festgelegt werden. 
  * Die Möglichkeit beliebige Elemente die nicht oder nur in geringen Maße definiert werden müssen auf einen 'Einheitsstack' zu pushen, ist nicht möglich.
* Der Speicher wird unnötig groß. 
  * Wenn man beispielsweiße 17 Elemente darauf pusht wird Platz für 32 erzeugt. 
  * Da der Speicher jedes Mal verdoppelt wird, wird zwar die Funktion realloc() selten aufgerufen, dafür wird wie in obigem Beispiel gerade bei etwas größeren Mengen an Objekten teilweise zu viel Speicher allociert.
  * Würde man aber die realloc() - Funktion bei jedem gepushten Objekt nutzen, würde die Performance deutlich daran leiden, da die diese Funktion sehr langsam ist.
* Die memcpy() - Funktion in der GenStackPush() bzw. GenStackPop() kopiert keine doppelten Zeiger.
  * Will heißen einfache Zeiger wie ein beliebiger Char - Zeiger wwerden korrekt kopiert. 
  * Allerdings ist dies bei z.B. einem Struct das einen oder mehrere weitere Zeiger beinhaltet nicht der Fall. Stattdessen wird das Struct kopiert aber die Zeiger in diesem Struct nicht. Stattdessen existiert eine Kopie des Structs die ebenfalls auf die gleichen Dateien Zeiger besitzt wie sein Original.
  * Um trotzdem korrekte Ergebnisse zu erhalten, dürfen Structs mit internen Zeigern nicht gelöscht werden, bevor nicht der Client beendet wird. Das kann sich allerdings als problematisch herausstellen.
* Keine bedienerfreundliche Möglichkeit um zu überprüfen ob bereits ein Stack vorhanden ist. 
  * Der Stack hat keine Möglichkeit das zu überprüfen, solange er keine Variable vom Client übergeben bekommt, die nur für diesen Zweck gedacht ist.
  * Natürlich könnte man das kreieren, in dem der Client diese Variable manuell setzt und übergibt, aber das wäre nicht besonders benutzerfreundlich.
