import java.util.Scanner;
import java.math.BigInteger;
import java.util.ArrayList;	//vector
import java.util.Collections;
import java.io.File;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.LinkedList;	//queue
import java.io.PrintStream;
import java.util.TreeSet;	//set
import java.util.Iterator;
import java.util.TreeMap;
import java.util.Map;

public class base {
	static PrintWriter writer;
	static Scanner in;
	static PrintStream out = System.out;

	public static void main (String[] args) throws Exception{
//		writer = new PrintWriter("System.out", "UTF-8");
//		in = new Scanner (new File("file.in"));
		in = new Scanner (System.in);

		in.close();
//		writer.close();
	}
}

class set<A> {
	TreeSet <A> s;

	void imp () {
		Iterator it = s.iterator();
		while (it.hasNext()) System.out.print(it.next() + " ");
		System.out.println();
	}
}

class map<K,V> {
	public TreeMap<K,V> m = new TreeMap<K,V>();
	K key;
	V value;

	map () {}

	void example () {
		boolean f;
		m.put(key, value);
		f = m.containsKey(key);		f = m.containsValue(value);
		value = m.get(key);
		value = m.remove(key);
	}

	public void imp () {
		for (Map.Entry<K, V> e : m.entrySet()) {
			key = e.getKey();	value = e.getValue();
			System.out.println(key + " => " + value);
		}

		for (Iterator<Map.Entry<K,V>> it = m.entrySet().iterator(); it.hasNext(); ) {
			Map.Entry<K,V> e = it.next();
			System.out.println(e.getKey() + " => " + e.getValue());
		}
	}

}
