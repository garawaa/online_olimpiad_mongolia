import static java.util.Arrays.deepToString;

import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class D {
	static final Random rand = new Random(14123123L);
	static final long PRIME = BigInteger.probablePrime(20, rand).longValue();
	static final int MINLEN = 7;
	static final int MAXLEN = 100000;

	static List<Tag> getTags(String s) {
		List<Tag> ret = new ArrayList<Tag>();
		while (!s.isEmpty()) {
			if (s.charAt(0) != '<') {
				return null;
			}
			int p = s.indexOf('>');
			if (p < 0) {
				return null;
			}
			String d = s.substring(1, p);
			if (d.isEmpty()) {
				return null;
			}
			s = s.substring(p + 1);
			ret.add(new Tag(d));
		}
		return ret;
	}

	static boolean canParse(String s) {
		while (!s.isEmpty()) {
			if (s.charAt(0) != '<') {
				return false;
			}
			int p = s.indexOf('>');
			if (p < 0) {
				return false;
			}
			String d = s.substring(1, p);
			if (d.isEmpty()) {
				return false;
			}
			s = s.substring(p + 1);
			if (d.charAt(0) == '/') {
				d = d.substring(1);
				if (!isAlmostWord(d)) {
					return false;
				}
			} else {
				if (!isAlmostWord(d)) {
					return false;
				}
			}
		}
		return true;
	}

	static boolean isWord(String s) {
		for (int i = 0; i < s.length(); i++) {
			if (!isAlpha(s.charAt(i))) {
				return false;
			}
		}
		return true;
	}

	static boolean isAlmostWord(String s) {
		for (int i = 0; i < s.length(); i++) {
			if (!isAlpha(s.charAt(i)) && s.charAt(i) != '/') {
				return false;
			}
		}
		return true;
	}

	static boolean isAlpha(char c) {
		return c >= 'a' && c <= 'z';
	}

	static int getBalance(List<Tag> tags) {
		int balance = 0;
		for (Tag e : tags) {
			if (!e.open) {
				balance--;
			} else {
				balance++;
			}
		}
		return balance;
	}

	static class Tag {
		boolean open;
		String name;

		public Tag(String s) {
			if (s.charAt(0) == '/') {
				open = false;
				name = s.substring(1);
			} else {
				open = true;
				name = s;
			}
		}

		boolean isPair(Tag tag) {
			return tag.open != open && tag.name.equals(name);
		}

		@Override
		public String toString() {
			return "<" + (open ? "" : "/") + name + ">";
		}
	}

	final static char[] ALPHABET;
	static {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < 26; i++) {
			sb.appendCodePoint('a' + i);
		}
		sb.append('/').append('<').append('>');
		ALPHABET = sb.toString().toCharArray();
	}

	static boolean checkInput(String line) {
		if (line.length() < MINLEN || line.length() > MAXLEN) {
			throw new AssertionError("length of input is not in range ["
					+ MINLEN + " .. " + MAXLEN + "]");
		}
		String a = new String(ALPHABET);
		for (int i = 0; i < line.length(); i++) {
			char c = line.charAt(i);
			if (a.indexOf(c) < 0) {
				throw new AssertionError("invalid character in input: " + c);
			}
		}
		return true;
	}

	static void solve() throws Exception {
		String s = br.readLine();
		checkInput(s);
		out.println(solve(s));
	}

	static String solve(String s) {
		if (canParse(s)) {
			return solveOnlyLettersAndSlash(s);
		} else {
			int open = 0;
			int clos = 0;
			int slash = 0;
			for (int i = 0; i < s.length(); i++) {
				if (s.charAt(i) == '<') {
					open++;
				}
				if (s.charAt(i) == '>') {
					clos++;
				}
				if (s.charAt(i) == '/') {
					slash++;
				}
			}
			if (s.charAt(0) != '<') {
				return replaceChar(s, 0, '<');
			}
			if (s.charAt(s.length() - 1) != '>') {
				return replaceChar(s, s.length() - 1, '>');
			}
			// '<' => '>'
			int badFirst = s.indexOf(">>");
			if (open + 2 == clos && badFirst >= 0 && badFirst + 2 < s.length()) {
				return replaceChar(s, badFirst + 1, '<');
			}
			// '>' => '<'
			int badSecond = s.indexOf("<<");
			if (clos + 2 == open && badSecond > 0) {
				return replaceChar(s, badSecond, '>');
			}
			// '<' => 'a'-'z'|'/'
			if (open + 1 == clos && (open & 1) == 1) {
				int last = -1;
				for (int i = 0; i < s.length(); i++) {
					if (s.charAt(i) == '>' && last != Integer.MIN_VALUE) {
						return replaceChar(s, last + 1, '<');
					} else if (s.charAt(i) == '>') {
						last = i;
					} else if (s.charAt(i) == '<') {
						last = Integer.MIN_VALUE;
					}
				}
			}
			// '>' => 'a'-'z'|'/'
			if (clos + 1 == open && (clos & 1) == 1) {
				boolean was = false;
				for (int i = 0; i < s.length(); i++) {
					if (s.charAt(i) == '<' && was) {
						return replaceChar(s, i - 1, '>');
					} else if (s.charAt(i) == '<') {
						was = true;
					} else if (s.charAt(i) == '>') {
						was = false;
					}
				}
				if (was) {
					return replaceChar(s, s.length() - 1, '>');
				}
			}
			// '/'|'a'-'z' => '<'
			if (open - 1 == clos && (open & 1) == 1) {
				boolean was = false;
				for (int i = 0; i < s.length(); i++) {
					if (s.charAt(i) == '<' && was) {
						if (slash < clos / 2) {
							return replaceChar(s, i, '/');
						} else {
							return trySolveOnlyLettersAndSlash(
									replaceChar(s, i, 'a'), s);
						}
					} else if (s.charAt(i) == '<') {
						was = true;
					} else if (s.charAt(i) == '>') {
						was = false;
					}
				}
			}
			// '/'|'a'-'z' => '>'
			if (clos - 1 == open && (clos & 1) == 1) {
				int last = -1;
				for (int i = 0; i < s.length(); i++) {
					if (s.charAt(i) == '>' && last != Integer.MIN_VALUE) {
						if (slash < open / 2) {
							return replaceChar(s, last, '/');
						} else {
							return trySolveOnlyLettersAndSlash(
									replaceChar(s, last, 'a'), s);
						}
					} else if (s.charAt(i) == '>') {
						last = i;
					} else if (s.charAt(i) == '<') {
						last = Integer.MIN_VALUE;
					}
				}
			}
			throw new AssertionError();
		}
	}

	static String trySolveOnlyLettersAndSlash(String s, String init) {
		{
			List<Tag> tags = getTags(s);
			Stack<Tag> stack = new Stack<Tag>();
			for (Tag e : tags) {
				if (!e.open) {
					if (stack.isEmpty()) {
						throw new AssertionError();
					}
					e.name = stack.pop().name;
				} else {
					stack.add(e);
				}
			}
			String s1 = printToString(tags);
			if (s1.length() == init.length()) {
				int changes = 0;
				for (int i = 0; i < s1.length(); i++) {
					if (s1.charAt(i) != init.charAt(i)) {
						changes++;
					}
				}
				if (changes == 1) {
					return s1;
				}
			}
		}
		{
			List<Tag> tags = getTags(s);
			Collections.reverse(tags);
			Stack<Tag> stack = new Stack<Tag>();
			for (Tag e : tags) {
				if (e.open) {
					if (stack.isEmpty()) {
						throw new AssertionError();
					}
					e.name = stack.pop().name;
				} else {
					stack.add(e);
				}
			}
			Collections.reverse(tags);
			String s1 = printToString(tags);
			if (s1.length() == init.length()) {
				int changes = 0;
				for (int i = 0; i < s1.length(); i++) {
					if (s1.charAt(i) != init.charAt(i)) {
						changes++;
					}
				}
				if (changes == 1) {
					return s1;
				}
			}
		}
		throw new AssertionError();
	}

	static String replaceChar(String s, int i, char c) {
		char[] ans = s.toCharArray();
		ans[i] = c;
		return new String(ans);
	}

	static String solveOnlyLettersAndSlash(String s) {
		List<Tag> tags = getTags(s);
		int balance = getBalance(tags);
		Tag badTag = null;
		for (Tag e : tags) {
			if (e.name.indexOf('/') >= 0) {
				if (badTag != null) {
					throw new AssertionError();
				}
				badTag = e;
			}
		}
		if (balance == 0 && badTag == null) {
			return solveOnlyLetterToLetter(tags);
		} else if (badTag != null) {
			return solveWhenLetterToSlash(tags, badTag);
		} else {
			return solveWhenFirstLetterToSlashOrSlashToLetter(tags, balance);
		}
	}

	static String solveWhenFirstLetterToSlashOrSlashToLetter(List<Tag> tags,
			int balance) {
		if (balance == 2) {
			return solveSlashToLetter(tags);
		}
		if (balance == -2) {
			return solveFirstLetterToSlash(tags);
		}
		throw new AssertionError();
	}

	static String solveFirstLetterToSlash(List<Tag> tags) {
		Set<String> set = new HashSet<String>();
		for (Tag e : tags) {
			if (set.contains(e.name)) {
				set.remove(e.name);
			} else {
				set.add(e.name);
			}
		}
		if (set.size() != 2) {
			throw new AssertionError();
		}
		String[] z = set.toArray(new String[2]);
		if (z[0].length() < z[1].length()) {
			String t = z[0];
			z[0] = z[1];
			z[1] = t;
		}

		long[] hash = new long[tags.size()];
		boolean[] ok = new boolean[tags.size()];
		long curHash = 0;
		Stack<String> stack = new Stack<String>();
		Stack<Long> stackHash = new Stack<Long>();
		for (int i = 0; i < tags.size(); i++) {
			Tag e = tags.get(i);
			if (!e.open) {
				if (stack.isEmpty() || !stack.pop().equals(e.name)) {
					break;
				}
				stackHash.pop();
				curHash = stack.isEmpty() ? 0 : stackHash.peek();
			} else {
				stack.add(e.name);
				curHash = curHash * PRIME + e.name.hashCode();
				stackHash.add(curHash);
			}
			ok[i] = true;
			hash[i] = curHash;
		}
		stack.clear();
		stackHash.clear();
		curHash = 0;
		int change = -1;
		for (int i = tags.size() - 1; i >= 0; i--) {
			Tag e = tags.get(i);
			if (!e.open) {
				if (e.name.equals(z[1]) && !stack.isEmpty()
						&& stack.peek().equals(z[0]) && (i == 0 || ok[i - 1])) {
					long newHash = i == 0 ? 0 : hash[i - 1];
					newHash = newHash * PRIME + z[0].hashCode();
					if (newHash == curHash) {
						change = i;
						break;
					}
				}
				stack.add(e.name);
				curHash = curHash * PRIME + e.name.hashCode();
				stackHash.add(curHash);
			} else {
				if (stack.isEmpty() || !stack.pop().equals(e.name)) {
					throw new AssertionError();
				}
				stackHash.pop();
				curHash = stack.isEmpty() ? 0 : stackHash.peek();
			}
		}
		if (change < 0) {
			throw new AssertionError();
		}
		tags.get(change).name = z[0];
		tags.get(change).open = !tags.get(change).open;
		return printToString(tags);

	}

	static String solveSlashToLetter(List<Tag> tags) {
		Set<String> set = new HashSet<String>();
		for (Tag e : tags) {
			if (set.contains(e.name)) {
				set.remove(e.name);
			} else {
				set.add(e.name);
			}
		}
		if (set.size() != 2) {
			throw new AssertionError();
		}
		String[] z = set.toArray(new String[2]);
		if (z[0].length() > z[1].length()) {
			String t = z[0];
			z[0] = z[1];
			z[1] = t;
		}
		long[] hash = new long[tags.size()];
		boolean[] ok = new boolean[tags.size()];
		long curHash = 0;
		Stack<String> stack = new Stack<String>();
		Stack<Long> stackHash = new Stack<Long>();
		for (int i = tags.size() - 1; i >= 0; i--) {
			Tag e = tags.get(i);
			if (e.open) {
				if (stack.isEmpty() || !stack.pop().equals(e.name)) {
					break;
				}
				stackHash.pop();
				curHash = stack.isEmpty() ? 0 : stackHash.peek();
			} else {
				stack.add(e.name);
				curHash = curHash * PRIME + e.name.hashCode();
				stackHash.add(curHash);
			}
			ok[i] = true;
			hash[i] = curHash;
		}
		stack.clear();
		stackHash.clear();
		curHash = 0;
		int change = -1;
		for (int i = 0; i < tags.size(); i++) {
			Tag e = tags.get(i);
			if (e.open) {
				if (e.name.equals(z[1]) && !stack.isEmpty()
						&& stack.peek().equals(z[0])
						&& (i + 1 >= tags.size() || ok[i + 1])) {
					long newHash = i + 1 >= tags.size() ? 0 : hash[i + 1];
					newHash = newHash * PRIME + z[0].hashCode();
					if (newHash == curHash) {
						change = i;
						break;
					}
				}
				stack.add(e.name);
				curHash = curHash * PRIME + e.name.hashCode();
				stackHash.add(curHash);
			} else {
				if (stack.isEmpty() || !stack.pop().equals(e.name)) {
					throw new AssertionError();
				}
				stackHash.pop();
				curHash = stack.isEmpty() ? 0 : stackHash.peek();
			}
		}
		if (change < 0) {
			throw new AssertionError();
		}
		tags.get(change).name = tags.get(change).name.substring(1);
		tags.get(change).open = !tags.get(change).open;
		return printToString(tags);
	}

	static String solveWhenLetterToSlash(List<Tag> tags, Tag badTag) {
		Stack<Tag> stack = new Stack<Tag>();
		for (Tag e : tags) {
			if (e.open) {
				stack.add(e);
			} else {
				if (e == badTag) {
					e.name = stack.pop().name;
				} else {
					Tag got = stack.pop();
					if (got == badTag) {
						got.name = e.name;
					}
				}
			}
		}
		return printToString(tags);
	}

	static String solveOnlyLetterToLetter(List<Tag> tags) throws AssertionError {
		Stack<Tag> stack = new Stack<Tag>();
		for (Tag e : tags) {
			if (!e.open) {
				if (stack.isEmpty()) {
					throw new AssertionError();
				}
				e.name = stack.pop().name;
			} else {
				stack.add(e);
			}
		}
		return printToString(tags);
	}

	static String printToString(List<Tag> tags) {
		StringBuilder sb = new StringBuilder();
		for (Tag e : tags) {
			sb.append(e);
		}
		return sb.toString();
	}

	static BufferedReader br;
	static StringTokenizer st;
	static PrintWriter out;

	static void debug(Object... a) {
		System.err.println(deepToString(a));
	}

	public static void main(String[] args) {
		try {
			File file = new File("input.txt");
			InputStream input = System.in;
			OutputStream output = System.out;
			if (file.canRead()) {
				input = (new FileInputStream(file));
				output = (new PrintStream("output.txt"));
			}
			br = new BufferedReader(new InputStreamReader(input));
			out = new PrintWriter(output);
			solve();
			out.close();
			br.close();
		} catch (Throwable e) {
			e.printStackTrace();
			System.exit(1);
		}
	}
}