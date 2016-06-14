//Code for Rationals used from: http://introcs.cs.princeton.edu/java/92symbolic/BigRational.java.html

import java.math.BigInteger;
import java.util.Arrays;
import java.util.Scanner;
import java.util.Vector;

public class BigRational {
    private BigInteger num;   // the numerator
    private BigInteger den;   // the denominator

    // create and initialize a new Rational object
    public BigRational(BigInteger numerator, BigInteger denominator) {
        BigInteger g = numerator.gcd(denominator);
        num = numerator.divide(g);
        den = denominator.divide(g);
    }

    // return string representation of (this)
    public String toString() { 
        return num + "/" + den;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for (int ti=1; ti<=t; ti++) {
        	//Read n
        	int n = sc.nextInt();
        	//Read dice string
        	String s = sc.next();
        	//Split dice string into "adb" string
        	String[] dice = s.split("\\+");
        	//Vector will contain all dice represented as their side count
        	Vector<Integer> sides = new Vector<Integer>();
        	//total number of dice
        	int diceCount = 0;
        	for (int i=0; i<dice.length; i++) {
        		//split into "a" and "b"
        		String[] d = dice[i].split("d");
        		int count = Integer.parseInt(d[0]);
        		diceCount += count;
        		//add dice to vector
        		for (int j=0; j<count; ++j) {
        			sides.addElement(Integer.parseInt(d[1]));
        		}
        	}

        	//if n == 0 there's no chance of 
        	if (n == 0) {
        		System.out.println("Case #" + ti + ": 1/1");
        		continue;
        	}
            BigInteger den = BigInteger.ONE;
            for (int i=0; i<sides.size(); i++) {
            	den = den.multiply(new BigInteger(""+sides.get(i)));
            }
            
            BigInteger[][] dp = new BigInteger[diceCount+1][n];
            
            for (int i=0; i<diceCount+1; i++) {
            	Arrays.fill(dp[i], BigInteger.ZERO);
            }
            dp[0][0] = new BigInteger("1");
            for (int i=1; i<diceCount+1; i++) {
            	for (int j=1;j<n; j++) {
            		for (int k=1; k<=sides.get(i-1); k++) {
            			if (j-k < 0) continue;
            			dp[i][j] = dp[i][j].add(dp[i-1][j-k]);
            		}
            	}
            }
            
            BigInteger nom = BigInteger.ZERO;
            for (int i=0; i<n; i++) {
            	nom = nom.add(dp[diceCount][i]);
            }
            BigRational r = new BigRational(den.subtract(nom), den);
            
            System.out.println("Case #" + ti + ": " + r.toString());
            
        } 
    }
}

/*
3
3 1d6
15 1d6+2d20
75 25d6
*/

/*
 10
212 8d12+17d18
234 6d14+15d6+6d14
427 13d17+3d10+16d17
54 5d15+8d4
310 43d8
74 9d17
77 31d5
132 15d16
494 6d18+28d14
196 43d5
 */