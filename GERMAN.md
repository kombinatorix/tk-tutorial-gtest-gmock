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
erstellen wir dafür eine Objektdatei *.o*:

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

Nun definieren wir unseren ersten Test. Ein Test hat immer folgende Struktur:
	
```cpp
TEST(NameDesTestCases, NameDiesesSpeziellenTest){

	//Hier steht der Testcode

}
```

Mit `NameDesTestCases` registriert man sozusagen den Test bei einem Test case. Danach gibt man den Namen des Tests an.
Man sollte am besten auf Unterstriche `_` verzichten. Da Google Test vielfach Makros nutzt kann es durch ungeschickte 
Benennungen zu Uneindeutigkeiten und damit Fehlern beim kompilieren kommen.
Erst dann kommt der eigentliche Code zu testen. In unserem einfachen Fall hatten wir:

```cpp
	ASSERT_EQ(2, add(1,1));
```

Der Befehl `ASSERT_EQ( ... , ... )` prüft, ob das erste Argument mit dem zweiten übereinstimmt. Dabei ist die Reihenfolge
egal.

Der Code, der in der main-Funktion steht ist ziemlich selbsterklärend. Bis aufs weitere ist er immer der selbe. Erst später
wird noch einmal darauf eingegangen.

Als nächstes muss das Testprogramm kompiliert werden. Dies geschieht mit:

```bash
g++ -isystem ${GTEST_DIR}/include -pthread prog1_test1.cpp libgtest.a -o prog1_test1 -lgtest
```

Hier ist wichtig, dass man das Flag `-lgtest` nicht vergisst. In der offiziellen README des Google Test Projekts fehlt dies.
Ohne das Flag gibt es jedoch einige Linkerfehler. Ansonsten muss man nur die Namen jeweils anpassen. Das betrifft die .cpp und die .a Datei, sowie
den Namen der Binary.

Gab es keine Probleme beim Kompilieren, kann das Testprogramm mit `./prog1_test1` ausgeführt werden. Es sollte dann folgenden Output geben:

```
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from Addition
[ RUN      ] Addition.boring
[       OK ] Addition.boring (0 ms)
[----------] 1 test from Addition (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 1 test.
```

Damit lief unser Test ohne Probleme durch. Das ist schön, aber wir haben noch nicht alle Fälle abgedeckt. So haben wir in unserem ursprünglichen unseren
Input nicht überprüft. Dies kann zu überläufen führen. Dies wird in *prog1_test2.cpp* überprüft:

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

Jetzt müssen wir das Programm wieder kompilieren:

```bash
g++ -isystem ${GTEST_DIR}/include -pthread prog1_test2.cpp libgtest.a -o prog1_test2 -lgtest
```

Ausgeführt sollte es dann diesen Output geben:

```
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from Addition
[ RUN      ] Addition.fail
prog1_test2.cpp:6: Failure
      Expected: 120000
To be equal to: add(60000,60000)
      Which is: -11072
[  FAILED  ] Addition.fail (0 ms)
[----------] 1 test from Addition (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 0 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] Addition.fail

 1 FAILED TEST
```

Unser Test schlägt hier fehl. Aber Google Test versorgt uns mit mehr Informationen. So sehen an welcher Stelle (`prog1_test2.cpp:6: Failure`) das Programm fehlschlug. Außerdem wird uns gezeigt, welche Wert erwartet wurde und welchen Wert wir tatsächlich bekommen.

Ein weiteres nützliches Feature ist, dass man bei einer Assertion eine eigene Fehlermeldung mit dem Streamoperator anhängen kann. Siehe dazu das Testprogramm *prog1_test3.cpp*:

```cpp
// ...

TEST(Addition, fail){
	
	ASSERT_EQ(120000, add(60000,60000)) << "Hier gab es einen Bufferüberlauf und damit ein falsches Ergebnis von: " << add(60000,60000);
	
}

// ...
```

Oben haben wir schon davon gesprochen, dass es `ASSERT` und `EXPECT` gibt. Der Unterschied besteht darin, dass `ASSERT` sofort den Test beendet.
Bei einem Fehler in `EXPECT` können noch weitere Fehler zurückgemeldet werden. Um das zu demonstrieren, kann *prog1_test4.cpp* genutzt werden.


```cpp
#include "include/prog1.hpp"
#include "gtest/gtest.h"

TEST(Addition, failOne){
	ASSERT_EQ(120000, add(60000,60000));
	ASSERT_EQ(120000, add(60000,60000));
}
TEST(Addition, failTwo){
	EXPECT_EQ(120000, add(60000,60000));
	EXPECT_EQ(120000, add(60000,60000));
}
TEST(Addition, failThree){
	ASSERT_EQ(120000, add(60000,60000));
	EXPECT_EQ(120000, add(60000,60000));
}
TEST(Addition, failFour){
	EXPECT_EQ(120000, add(60000,60000));
	ASSERT_EQ(120000, add(60000,60000));
}

int main(int argc,char **argv){
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
```

Nach Kompilierung und Ausführung sehen wir, dass failOne und failThree nur einen Fehler zurückmelden, wobei failTwo und failFour 2 Fehler zurückmelden.

Da wir jetzt ein Gefühl dafür bekommen haben, was eine Assertion ist und wie sie benutzt wird, sollen im Folgenden die möglichen Ausprägungen vorgestellt werden.

#### Wahrheitswertige Assertions ####

Hier wird nur darauf geprüft, ob die Bedingung den richtigen Wahrheitswert hat.

| **Fatal assertion** | **Nonfatal assertion** | **Prüft** |
|:--------------------|:-----------------------|:----------|
| `ASSERT_TRUE(`_Bedingung_`)`;  | `EXPECT_TRUE(`_Bedingung_`)`;   | _Bedingung_ is wahr |
| `ASSERT_FALSE(`_Bedingung_`)`; | `EXPECT_FALSE(`_Bedingung_`)`;  | _Bedingung_ is falsch |

#### Binäre Vergleiche ####

Hier geht es um den binären Vergleich von zwei Werten.

| **Fatal assertion** | **Nonfatal assertion** | **Prüft** |
|:--------------------|:-----------------------|:----------|
|`ASSERT_EQ(`_Wert1_`, `_Wert2_`);`|`EXPECT_EQ(`_Wert1_`, `_Wert2_`);`| _Wert1_ `==` _Wert2_ |
|`ASSERT_NE(`_Wert1_`, `_Wert2_`);`|`EXPECT_NE(`_Wert1_`, `_Wert2_`);`| _Wert1_ `!=` _Wert2_ |
|`ASSERT_LT(`_Wert1_`, `_Wert2_`);`|`EXPECT_LT(`_Wert1_`, `_Wert2_`);`| _Wert1_ `<` _Wert2_ |
|`ASSERT_LE(`_Wert1_`, `_Wert2_`);`|`EXPECT_LE(`_Wert1_`, `_Wert2_`);`| _Wert1_ `<=` _Wert2_ |
|`ASSERT_GT(`_Wert1_`, `_Wert2_`);`|`EXPECT_GT(`_Wert1_`, `_Wert2_`);`| _Wert1_ `>` _Wert2_ |
|`ASSERT_GE(`_Wert1_`, `_Wert2_`);`|`EXPECT_GE(`_Wert1_`, `_Wert2_`);`| _Wert1_ `>=` _Wert2_ |

#### C-String Vergleiche ####

Hier geht es explizit um C-Strings, da normale Strings mit den binären Vergleichen abgedeckt werden.

| **Fatal assertion** | **Nonfatal assertion** | **Prüft** |
|:--------------------|:-----------------------|:----------|
| `ASSERT_STREQ(`_str1_`, `_str2_`);`    | `EXPECT_STREQ(`_str1_`, `_str_2`);`     | Beide C-Strings haben den gleichen Inhalt |
| `ASSERT_STRNE(`_str1_`, `_str2_`);`    | `EXPECT_STRNE(`_str1_`, `_str2_`);`     | Beide C-Strings haben unterschiedliche Inhalte |
| `ASSERT_STRCASEEQ(`_str1_`, `_str2_`);`| `EXPECT_STRCASEEQ(`_str1_`, `_str2_`);` | Beide C-Strings haben den gleichen Inhalte bei ignorierter Groß- und Kleinschreibung  |
| `ASSERT_STRCASENE(`_str1_`, `_str2_`);`| `EXPECT_STRCASENE(`_str1_`, `_str2_`);` | Beide C-Strings unterschiedliche Inhalte bei ignorierter Groß- und Kleinschreibung |

#### Explizite Rückgaben ####

|Assertion|Ergebnis|
|:--------|:-------|
|SUCCEED();|success|
|FAIL();|fatal failure|
|ADD_FAILURE();|nonfatal failure|
|ADD_FAILURE_AT(" Pfad_zur_Datei ", Zeilennummer );| nonfatal failure|

#### Exception Assertions ####

| **Fatal assertion** | **Nonfatal assertion** | **Verifies** |
|:--------------------|:-----------------------|:-------------|
| `ASSERT_THROW(`_Anweisung_, _exception\_type_`);`  | `EXPECT_THROW(`_Anweisung_, _exception\_type_`);`  | _Anweisung_ wirft eine Exception des gegebenen Typs  |
| `ASSERT_ANY_THROW(`_Anweisung_`);`                | `EXPECT_ANY_THROW(`_Anweisung_`);`                | _Anweisung_ wirft eine Exception irgendeines Typs        |
| `ASSERT_NO_THROW(`_Anweisung_`);`                 | `EXPECT_NO_THROW(`_Anweisung_`);`                 | _Anweisung_ wirft keine Exception            |

Für weitere Assertions gucke [hier](https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md#using-an-existing-boolean-function).



## Google Mock ##



