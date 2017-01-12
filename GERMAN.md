# Das deutsche Tutorial #

Damit wir uns Tipparbeit sparen, wird die Variable `${GTEST_DIR}` mit dem Pfad zum googletest-Ordner gesetzt. Dazu füge in der `~/.bashrc` folgende Zeile hinzu.

	export GTEST_DIR = Pfad/zum/Ordner

Danach muss du in der Kommandozeile einmal `source ~/.bashrc` ausführen, damit der Befehl geladen wird.

Da Google Test auf Google Test aufbaut, werden wir uns zuerst mit Google Test beschäftigen.
 
## Google Test ##

Google Test ist eine Modultest(Unittest)-Bibliothek für C++. Die Grundlegende Struktur basiert auf der xUnit-Architektur.
Für Google Test ist die Struktur in der folgenden Tabelle aufgeführt.

| Komponente   | Erklärung                                                                                      |
|--------------|------------------------------------------------------------------------------------------------|
| Assertion    | Prüft, ob eine eine Bedingung wahr ist.                                                        |
| Test         | Nutzt Assertions, um das Verhalten des Codes  zu prüfen.                                       |
| Test case    | Bestehen aus mindestens einem Test. Es soll die Struktur des zu testenden Codes widerspiegeln. |
| Test fixture | Setzt die Umgebung(svariablen), so dass Tests dies nicht immer selbst machen müssen.           |
| Test program | Besteht aus mindestens einem Testcase. Lässt diese durchlaufen.                                | 

Wie man der Tabelle entnehmen kann, sieht die Struktur eines Minimalbeispiels wie folgt aus.
	
	Test program( Test case ( Test ( Assertion ( ... ) ) ) )

Wir arbeiten uns nun von der kleinsten Einheiten, den Assertions, zu dem großen ganzen, dem Test program, vor.

### Assertions ###

Allgemein gesprochen eine Assertion eine vorn drei Zuständen zurückmelden: **success**, **nonfatal failure** und **fatal failure**.

Es ist zwar einfach einen Erfolg festzustellen, aber Google Test hat keine Möglichkeit abzuleiten, ob ein Fehler fatal ist oder nicht.
Dies muss der Benutzer selbst festlegen. Deshalb gibt es **2** Typen von Assertions:

|Typ     |Erfolg|Fehler          |
|:-------|:-----|:---------------|
| ASSERT |succes|fatal failure   |
| EXPECT |succes|nonfatal failure|

Mehr Informationen brauchen wir nicht für unseren ersten Test. Hierzu nutzen wir ein erstes Beispielprogramm:

## Google Mock ##



