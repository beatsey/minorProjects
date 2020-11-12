# minorProjects
В данном репозитории собраны небольшие учебные проекты.

<h3>Рюкзак (backpack.cpp)</h3>

Решить задачу о рюкзаке методом динамического программирования. Алгоритм должен быть инкапсулирован.

<h4>Формат входных данных</h4>
Данные подаются на стандартный поток ввода. Пустые строки игнорируются.
Первая строка содержит натуральное число - максимальную массу предметов, которую выдержит рюкзак.
Каждая последующая содержит два неотрицательных числа: массу предмета и его стоимость.

<h4>Формат результата</h4>
Первая строка содержит два числа: суммарную массу предметов и их суммарную стоимость.
В последующих строках записаны номера предметов, которые были помещены в рюкзак, в порядке возрастания номера.
Результат работы программы выводится в стандартный поток вывода.
В любой непонятной ситуации результатом работы любой команды будет "error".

<h4>Пример</h4>
<table><tbody>
  <tr>
    <td><b>Входные данные</b></td>
    <td><b>Результат работы</b></td>
  </tr>
  <tr>
    <td valign='top'>
165<br>
23 92<br>
31 57<br>
29 49<br>
44 68<br>
53 60<br>
38 43<br>
63 67<br>
85 84<br>
89 87<br>
82 72
</td>
  <td valign='top'>
165 309<br>
1<br>
2<br>
3<br>
4<br>
6
</td>
  </tr>
</tbody></table>

<h3>Сумасшедший богач (millionaire.py)</h3>
Один сумасшедший богач на старости лет впал в маразм и стал еще более сумасшедшим. Он решил отдать половину своих богатств тому, кто выиграет в математической игре.
Правила игры: изначально каждый игрок начинает с нулевой суммой. Он может либо получить у богача 1 миллион сантиков, либо отдать ему 1 миллион сантиков, либо получить от богача ту же сумму, которая есть у него сейчас.
Выигрывает тот, кто за минимальное количество действий наберет сумму, равную половине состояния богача.
На беду других игроков, нашелся человек, который что-то слышал про жадные алгоритмы и двоичную систему счисления (возможно это вы).

<h4>Формат входных данных</h4>
В стандартном потоке записано единственное натуральное число - размер половины состояния богача (в миллионах).

<h4>Формат результата</h4>
Каждая строка выхода содержит ровно одну операцию (inc, dec или dbl) из кратчайшей последовательности действий для победы.
Результат работы программы выводится в стандартный поток вывода.

<h4>Пример</h4>
<table><tbody>
  <tr>
    <td><b>Входные данные</b></td>
    <td><b>Результат работы</b></td>
  </tr>
  <tr>
    <td valign="top">23</td>
    <td valign="top">
inc<br>
dbl<br>
inc<br>
dbl<br>
dbl<br>
dbl<br>
dec
</td>
  </tr>
</tbody></table>

<h3>Автокоррекция (word_correction.py)</h3>
Реализуйте программу, которая предлагает варианты замены слова, в котором допущена одна ошибка.
Эту задачу можно решить достаточно многими способами - на это ограничений нет, но код должен быть хорошего качества и читаемым.
Регистр букв для программы коррекции не имеет значения (слова в словаре хранятся в нижнем регистре).
Варианты ошибок - как в алгоритме Дамерау-Левенштейна: вставка лишнего символа, удаление символа, замена символа или транспозиция соседних символов.

<h4>Формат входных данных</h4>
Данные подаются на стандартный поток ввода. Пустые строки игнорируются.
Первая строка содержит число N - количество слов в словаре.
Последующие N строк содержат слова из словаря, по одному в строке.
Остальные строки - слова, которые надо проверять.

<h4>Формат результата</h4>
Каждая строка выхода содержит предложение для исправления слов, в порядке их появления.
Если слово не содержит ошибок, то выводится "%слово% - ok".
Если слово содержит одну ошибку, то выводится "%слово% -> %слово_в_словаре%". Если вариантов несколько, то они разделяются запятой с пробелом.
Если слово содержит более одной ошибки, то выводится "%слово% -?"
Результат работы программы выводится в стандартный поток вывода.

<h4>Пример</h4>
<table><tbody>
  <tr>
    <td><b>Входные данные</b></td>
    <td><b>Результат работы</b></td>
  </tr>
  <tr>
    <td valign="top">
8<br>
some<br>
random<br>
words<br>
for<br>
testing<br>
your<br>
solutions<br>
far<br>
<br>
some<br>
randoms<br>
wards<br>
seeking<br>
fro<br>
solution<br>
fur
</td>
    <td valign="top">
some - ok<br>
randoms -&gt; random<br>
wards -&gt; words<br>
seeking -?<br>
fro -&gt; for<br>
solution -&gt; solutions<br>
fur -&gt; far, for
</td>
  </tr>
</tbody></table>
