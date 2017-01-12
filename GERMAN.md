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

<table align="center">
<tr>
<td>
	prog1.hpp
</td>
<td>
	prog1.cpp
</td>
</tr>
<tr>
<td valign="top">
	<pre lang = "C++">
	#ifndef __prog1__hpp__
	#define __prog1__hpp__

	int add(short a, short b);


	#endif	
	</pre>
</td>
<td valign="top">
<pre lang = "C++">
	#include "include/prog1.hpp"	
	#include < iostream >

	int add(short a, short b){
	    return static_cast< int >(a+b);
	}
</pre>
</td>
</tr>
</table>

Das Programm macht nichts anderes, als zwei shorts zu addieren und die Summe als Integer zurückzuliefern.
Für das Programm, dass unsere Addition testet müssen wir noch eine statische Bibliothek erzeugen. Zuerst
erstellen wir dafür eine Objektdation *.o*:

```bash
g++ -isystem ${GTEST_DIR}/include -pthread -c prog1.cpp
```

Auch wer schon mal mit g++ ein Programm kompiliert hat, kennt nicht umbedingt das Flag `-isystem`. Mit diesem
Flag können Pfade für Systemheader angegeben werden. Und in unserem Fall möchten wir die Google Test Header 
nutzen.
Außerdem nutzen wir das Flag `-pthread`, da Google Test gebrauch von threads macht.

Nun haben wir eine Objektdatei. Jetzt möchten wir eine statische Bibliothek haben. Diese können wir mit `ar` erzeugen:

```bash
ar -rv libgtest.a prog1.o
```

Für weitere Informationen über `ar` führe `man ar` der Konsole aus.

Kommen wir nun zu unserem ersten Testprogram (*prog1_test1.cpp*):
```cpp
#include "include/prog1.hpp"
#include "gtest/gtest.h"

TEST(Addition, boring){
	
	ASSERT_EQ(2, add(1,1));
	
}

int main(int argc,char **argv){
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
```

Zuerst müssen wir den Header einbinden, der die zu testenden Funktionen enthält:

```cpp
	#include "include/prog1.hpp"
```

Außerdem muss in jedem Fall der Google Test-Header eingebunden werden:

```cpp
	#include "include/prog1.hpp"
```

Nun definieren wir unseren ersten Test. Ein Test hat immer folgende Struktur
	
```cpp
TEST(NameDesTestCases, NameDiesesSpeziellenTest){

	//Hier steht der Testcode

}
```

Mit `NameDesTestCases` registriert man sozusagen den Test bei einem Test case. Danach gibt man den Namen des Tests an.
Erst dann kommt der eigentliche Code zu testen. In unserem einfachen Fall hatten wir:

```cpp
	ASSERT_EQ(2, add(1,1));
```

Der Befehl `ASSERT_EQ( ... , ... )` prüft, ob das erste Argument mit dem zweiten übereinstimmt. Dabei ist die Reihenfolge
egal.


```bash
g++ -isystem ${GTEST_DIR}/include -pthread prog1_test1.cpp libgtest.a -o prog1_test1 -lgtest
```


**prog1_test2.cpp**:
```cpp
#include "include/prog1.hpp"
#include "gtest/gtest.h"

TEST(Addition, fail){
	
	ASSERT_EQ(120000, add(60000,60000));
	
}

int main(int argc,char **argv){
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
```

```bash
g++ -isystem ${GTEST_DIR}/include -pthread prog1_test2.cpp libgtest.a -o prog1_test2 -lgtest
```

## Google Mock ##



