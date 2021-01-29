/*
Мороженое и холодильник 2

Харитон решил изменить стратегию.
Он не станет покупать мороженое в двух случаях:
* Если в холодильнике имеется мороженое, которое лежит там уже d дней.
В этом случае Харитон съест в этот день именно это мороженое.
* Если никакое мороженок не лежит в холодильнике d дней, но рейтинг мороженого дня меньше, чем рейтинг самого вкусного мороженого, которое есть у Харитона в холодильнике.
В этом случае Харитон съест в этот день самое вкусное мороженое из своего холодильника.
Если в холодильнике несколько порций мороженого с одинаковым рейтингом, то он съест то, которое купил последним.

Если рейтинг мороженого дня не меньше, чем рейтинг самого вкусного мороженого, хранящегося в холодильнике Харитона, и, кроме того, никакое мороженое в холодильнике не лежит уже d дней, Харитон купит две порции мороженого дня.
Одну съест, а вторую положит в холодильник.

Требуется по заданной информации о мороженых дня за n дней определить:
* Сколько раз Харитон отказывался от покупки мороженого, рейтинг которого был выше, чем хотя бы у одного мороженого, имевшегося в тот момент в холодильнике.
* Максимальное количество дней, которое порция мороженого провела в холодильнике Харитона, и количество таких порций.
* Количество сортов мороженого, порции которого пробыли в холодильнике максимальное количество дней, и вывести список этих сортов в лексикографическом (алфавитном) порядке.

ВХОДНЫЕ ДАННЫЕ
В первой строке содержатся целые числа n,d
(1<=n<=300000, 1<=d<=100000) - количество дней, для которых имеется информация о мороженом дня, количество дней, в течение которого Харитон считает нахождение мороженого в холодильнике допустимым.

В каждой из следующих n строке содержится информация о мороженом дня в соответствующий день: наименование сорта мороженого s_j и через пробел его рейтинг r_j с точки зрения Харитона (j=1,2,...,n), (0<=r_j<=1000000)

Наименование сорта мороженого s_j - непустая строка из строчных латинских букв, цифр и нижнего подчёркивания, начинающаяся с буквы и имеющая длину не более 30 символов.

Гарантируется, что для фиксированного наименования мороженого рейтинг сорта мороженого постоянный.

ВЫХОДНЫЕ ДАННЫЕ
В первой строке выведите целое число z - количество раз, которое Харитон отказывался от покупки мороженого, рейтинг которого был выше, чем хотя бы у одного мороженого, имевшегося в тот момент в холодильнике.

Во второй строке выведите целые числа p и q - максимальное количество дней, которое порция мороженого провела в холодильнике Харитона, и количество таких порций.

В третьей строке выведите целое число w - количество сортов, порции которых провели в холодильнике Харитона максимальное количество дней.

Далее выведите w строк - названия этих сортов в лексикографическом (алфавитном) порядке.

Примеры
Вход
14 3
strawberry 3
vanilla 5
blackberry 4
banana 3
strawberry 3
watermelon 2
lemon 6
vanilla 5
blackberry 4
vanilla2 4
strawberry 3
vanilla2 4
vanilla 5
strawberry 3

1
3 2
2
blackberry
strawberry


Вход
8 4
blackberry 4
strawberry 3
vanilla 5
watermelon 2
banana 3
lemon 6
strawberry 3
vanilla 5

0
3 1
1
banana


Вход
1 1
blackberry 4

0
0 1
1
blackberry
*/


import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.Scanner;

class Item {
    int days;
    String name;
    int rating;
	
    Item(String str, int val){ // vanilla 5
        name = str;
        rating = val;
		days = 0;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        int d = s.nextInt();
        
        int denies = 0; // Сколько раз Харитон отказался ...
        int dmax = 0; // максимальное количество дней в холодильнике
        int dmax_counter = 1; // количество такого мороженого        
        HashSet<String> dmax_names_set = new HashSet<String>();
        
        ArrayDeque<Item> refrigerator = new ArrayDeque<Item>();
		
		Item item = new Item(s.next(),s.nextInt()); // "vanilla 5"
		
        refrigerator.addFirst(item);
        dmax_names_set.add(refrigerator.peekFirst().name);
        
        for (int j = 1; j < n; j++)
        {
            item = new Item(s.next(),s.nextInt());
            
            if(refrigerator.isEmpty())
            {   // Холодильник пустой. Покупаем два мороженого. Одно едим, второе в холодильник.
                refrigerator.addLast(item);
            }
            else
            {
				// Увеличили счётчик дней каждого мороженого на 1
				ArrayDeque<Item> newRefrigerator = new ArrayDeque<Item>();
				Item itm;
				
				while((itm = refrigerator.pollFirst())!=null){
					itm.days++;
					newRefrigerator.addLast(itm);
				}
				refrigerator = newRefrigerator;
                
                // Обновили список самого долгохранящегося мороженого 
                if(refrigerator.peekFirst().days>dmax){
                    dmax = refrigerator.peekFirst().days;
					
                    dmax_counter=1;
                    dmax_names_set.clear();
                    dmax_names_set.add(refrigerator.peekFirst().name);
                }else if(refrigerator.peekFirst().days==dmax){
                    dmax_counter++;
                    dmax_names_set.add(refrigerator.peekFirst().name);
                }
			
                if(refrigerator.peekFirst().days==d)
                {   // Едим нулевое мороженое из холодильника
                    
                    if(item.rating>refrigerator.peekFirst().rating)
                        denies++;
					
                    refrigerator.removeFirst();
                }
                else if(refrigerator.peekLast().rating>item.rating)
                {   // Едим из холодильника
                    
                    if(item.rating>refrigerator.peekFirst().rating)
                        denies++;
                    
                    refrigerator.removeLast();
                }
                else
                {   // Покупаем два мороженого. Одно едим, второе в холодильник.
                    refrigerator.addLast(item);
                }
            }
        }
        
        System.out.println(denies);        
        System.out.println(dmax+" "+dmax_counter);
        System.out.println(dmax_names_set.size());
        
        ArrayList<String> dmax_names_list = new ArrayList<String>(dmax_names_set);
        Collections.sort(dmax_names_list);
        
        for (int i = 0,len=dmax_names_list.size(); i < len;i++)
        {
            System.out.println(dmax_names_list.get(i));          
        }
    }
}
/*
14 3
strawberry 3
vanilla 5
blackberry 4
banana 3
strawberry 3
watermelon 2
lemon 6
vanilla 5
blackberry 4
vanilla2 4
strawberry 3
vanilla2 4
vanilla 5
strawberry 3

Выход
1
3 2
2
blackberry
strawberry


8 4
blackberry 4
strawberry 3
vanilla 5
watermelon 2
banana 3
lemon 6
strawberry 3
vanilla 5

Выход
0
3 1
1
banana


1 1
blackberry 4

0
0 1
1
blackberry


*/
