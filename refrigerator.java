/*
Мороженое и холодильник

Харитон любит мороженое.
В своём любимом магазине мороженого Харитон каждому сорту мороженого присвоил рейтинг.
Чем больше этот рейтинг, тем вкуснее мороженое с точки зрения Харитона.
Каждый день в киоске некоторое мороженое назначаются мороженым дня и продают со скидкой.
Харитон любит экономить, поэтому он покупает только мороженое дня или не покупает мороженого вообще.
Если рейтинг мороженого дня не меньше, чем рейтинг самого вкусного мороженого, хранящегося в холодильнике Харитона, то он купит две порции этого мороженого.
Одну съест сразу, а вторую положит в холодильник.
Иначе Харитон не будет ничего покупать и съест самое вкусное мороженое из своего холодильника.

Требуется по заданной информации о мороженых дня за n дней определить, какое максимальное количество порций мороженого одновременно оказывалось в холодильнике Харитона на протяжении этих n дней.
А также какое мороженое Харитон покупал чаще всего.

ВХОДНЫЕ ДАННЫЕ
В первой строке содержится целое число (1<=n<=300000) - количество дней, для которых имеется информация о мороженом.

В каждой из следующих n строк содержится информация о мороженом дня в соответствующий день: наименование сорта мороженного s_j и через пробел его рейтинг r_j (0<=r_j<=1000000).

Наименование сорта мороженого s_j - непустая строка из строчных латинских букв, цифр и нижнего подчёркивания, начинающаяся с буквы и имеющая длину не более 30 символов.

Гарантируется, что для фиксированного наименования мороженого рейтинг сорта мороженого постоянный.

ВЫХОДНЫЕ ДАННЫЕ
В первой строке выведите целое число m - максимальное число одновременно лежавших в холодильнике порций мороженого.

Во второй строке вывести целые числа v и k - максимальное количество раз, которое Харитон покупал мороженое одного и того же сорта, и количество сортов мороженого, которые Харитон покупал чаще всего.

Далее выведите k строк, в каждой строке укажите по одному наименованию сорта мороженого, которое Харитон покупал чаще всего.
Наимеинования сортов выводите в лексикографическом (алфавитном) порядке.

Пример.
Входные данные
14
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

Выходные данные
5
2 3
strawberry
vanilla
vanilla2
*/

import java.util.Scanner;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
public class Main {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		int n = s.nextInt(), mc = -1, m = -1;
		int[] f = new int[n];
		HashMap<String, Integer> icecream_counter = new HashMap<String, Integer>();
		for (int j = 0; j < n; j++)
		{
			f[j] = -1;
		}
		
		for (int j = 0; j < n; j++)
		{
			String name = s.next();
			int r = s.nextInt();
			if (mc==-1 || r >= f[mc])
			{
				mc++;
				f[mc]=r;
				
				if(icecream_counter.containsKey(name)){
					icecream_counter.put(name,icecream_counter.get(name)+1);
				}else{
					icecream_counter.put(name,1);
				}
				
				if(mc > m)
				{
					m = mc;
				}
			}
			else
			{
			// mc указывает на максимальный индекс	
				f[mc] = -1;
				mc--;
			}
		}
		
		System.out.println(m+1);
		
		Integer v = 0;
		
		// в v получили максимальное количество мороженных для какого-то сорта
		Iterator iter = icecream_counter.entrySet().iterator();
		while (iter.hasNext()){
			Map.Entry mEntry = (Map.Entry) iter.next();
			
			if((Integer)mEntry.getValue()>v){
				v = (Integer) mEntry.getValue();
			}
		}
		
		ArrayList<String> names = new ArrayList<String>();
		
		iter = icecream_counter.entrySet().iterator();
		while (iter.hasNext()){
			Map.Entry mEntry = (Map.Entry) iter.next();
			// mEntry (сорт, количество)
			
			// mEntry.getValue() -> количество
			// mEntry.getKey() -> сорт
			if(mEntry.getValue()==v){
				names.add((String)mEntry.getKey());
			}
		}
		
		
		System.out.println(v + " " + names.size());
		
		Collections.sort(names);
		
		for (int i = 0; i < names.size(); i++)
		{
			System.out.println(names.get(i));
		}
	}
}
