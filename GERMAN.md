# Das deutsche Tutorial #

Damit wir uns Tipparbeit sparen, wird die Variable `${GTEST_DIR}` mit dem Pfad zum googletest-Ordner gesetzt. Dazu füge in der `~/.bashrc` folgende Zeile hinzu.

	export GTEST_DIR = Pfad/zum/Ordner

Danach muss du in der Kommandozeile einmal `source ~/.bashrc` ausführen, damit der Befehl geladen wird.

Da Google Test auf Google Test aufbaut, werden wir uns zuerst mit Google Test beschäftigen.
 
## googletest ##

Google Test ist eine Modultest(Unittest)-Bibliothek für C++. Die Grundlegende Struktur basiert auf der xUnit-Architektur.

| Komponente   | Erklärung                                                                                      |
|--------------|------------------------------------------------------------------------------------------------|
| Assertion    | Prüft, ob eine eine Bedingung wahr ist.                                                        |
| Test         | Nutzt Assertions, um das Verhalten des Codes  zu prüfen.                                       |
| Test case    | Bestehen aus mindestens einem Test. Es soll die Struktur des zu testenden Codes widerspiegeln. |
| Test fixture | Setzt die Umgebung(svariablen), so dass Tests dies nicht immer selbst machen müssen.           |
| Test program | Besteht aus mindestens einem Testcase. Lässt diese durchlaufen.                                | 

## googlemock ##



