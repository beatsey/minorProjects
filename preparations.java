/*
Подготовка

Харитон расспросил однокурсников, уже сдавших экзамен, какие дополнительные вопросы задавал им преподаватель.

Всего Харитон расспросил n однокурсников, и каждый из них перечислил Харитону заданные ему дополнительные вопросы.
Для каждого дополнительного вопроса Харитон записывал тему, к которой этот вопрос относится.

Требуется выяснить, по каким темам было задано больше всего дополнительных вопросов.

ВХОДНЫЕ ДАННЫЕ
В первой строке содержится целое число n (1<=n<=1000) - количество однокурсников, которых расспросил Харитон.

В каждой из следующих n строк содержится число m_i (0<=m_i<=1000) - количество дополнительных вопросов, на которые пришлось отвечать i-му однокурснику.
Через пробел далее записаны m_i чисел t_1,t_2,...,t_m_i (1<=t_i<=1000000) - номера тем, к которым относились эти вопросы.

Выходные данные
В первой строке выведите целые числа p и q - количество тем, по которым было задано максимальное количество дополнительных вопросов, и количество этих вопросов.

Пример.
6
3 10 5 14
2 14 12
5 8 13 5 12 3
4 10 13 1 4
0
3 2 2 8


7 2

*/
import java.util.HashMap;
import java.util.Scanner;
import java.util.Iterator;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
		// (тема, количество)
        HashMap<String, Integer> tasks_counter = new HashMap<String, Integer>();
		
        int n = s.nextInt();
        s.nextLine();
		for(int i=0;i<n;i++){
            String[] str = s.nextLine().split(" ");
            for(int j=1;j<str.length;j++){
                if(tasks_counter.containsKey(str[j])){
					Integer val = tasks_counter.get(str[j]);
                    tasks_counter.put(str[j],val+1);
                }else{
                    tasks_counter.put(str[j],1);
                }
			}
		}
		
		Integer max = 0,
		        counter = 0;
		
		Iterator iter = tasks_counter.entrySet().iterator();
		while (iter.hasNext()){
			Map.Entry mEntry = (Map.Entry) iter.next();
			
			Object obj = mEntry.getValue();
			if((Integer)obj>max){
			    max = (Integer)mEntry.getValue();
			    counter = 1;
			}else if((Integer)obj==max){
			    counter++;
			}
		}
		
		System.out.println(counter+" "+max);
    }
}

/*
6
3 10 5 14
2 14 12
5 8 13 5 12 3
4 10 13 1 4
0
3 2 2 8
*/