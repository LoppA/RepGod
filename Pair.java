import java.util.*;
import java.io.*;


public class a {
	static Scanner in;

	public static void main(String[] args) {
		TreeSet <Pair<Integer, Double> > s = new TreeSet<Pair<Integer, Double> >();
		in = new Scanner(System.in);
		while (in.hasNext()) {
			int a = in.nextInt();
			double b = in.nextDouble();
			s.add(new Pair<Integer,Double>(a, b));
		}
		Iterator <Pair<Integer, Double> > it = s.iterator();
		while (it.hasNext()) {
			Pair <Integer, Double> p = it.next();
			System.out.println(p.fi +  " " + p.se);
		}
		System.out.println();
	}

}

class Pair<A extends Comparable<A>,B extends Comparable<B>> implements Comparable<Pair<A,B>> {
	public A fi;
	public B se;

	Pair () {}

	Pair (A a, B b) {
		fi = a;	se = b;
	}

	@Override
	public int compareTo (Pair<A,B> p2) {
		int r = this.fi.compareTo(p2.fi);
		if (r != 0) return r;
		return this.se.compareTo(p2.se);
	}

}
