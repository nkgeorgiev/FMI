/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package rmiTokenize;

import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.StaxDriver;
import java.io.EOFException;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Formatter;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Random;
import java.util.Set;
import java.util.SortedMap;
import java.util.TreeMap;

/**
 *
 * @author nikolay
 */
public class RMIServer extends UnicastRemoteObject implements ServerInterface {

    private static final String accFileName = "accounts.xml";
    private static final String tokenFileName = "tokens.xml";
    private static final Random random = new Random();
    private final XStream xstream = new XStream(new StaxDriver());

    private final HashSet<Account> accounts;
    //k : token v: card number
    private final SortedMap<String, String> tokens;

    public RMIServer() throws RemoteException {
        super();
        tokens = new TreeMap<>();
        accounts = new HashSet<>();
        loadAccounts(accFileName);
        loadTokens(tokenFileName);

    }

    public RMIServer(int port) throws RemoteException {
        super(port);
        tokens = new TreeMap<>();
        accounts = new HashSet<>();
        loadAccounts(accFileName);
        loadTokens(tokenFileName);

    }

    @Override
    public String tokenize(String number) throws RemoteException, InvallidTokenException {
        //remove all whitespaces
        number = number.replaceAll("[\\s]", "");
        if (!isCorrect(number) || tokens.containsKey(number)) {
            throw new InvallidTokenException();
        }
        //create a list with the digits 0-9
        ArrayList<Character> digits = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            digits.add((char) ('0' + i));
        }
        
        String token = "";
        int sum;
        do {
            StringBuilder sb = new StringBuilder();
            sum = 0;
            //get the first digit of the token
            // remove 3,4,5,6 from digits and get a random digit from the others 
            digits.removeIf(ch -> ch == '3' || ch == '4' || ch == '5' || ch == '6');
            int i = random.nextInt(digits.size());
            sb.append(digits.get(i) - '0');
            sum += (char) digits.get(i) - '0';
            //add 3,4,5,6 to digits to make the list whole 
            digits.add('3');
            digits.add('4');
            digits.add('5');
            digits.add('6');
            //get 2nd to 12th digits of the token
            for (int idx = 1; idx < 12; idx++) {
                //remove from digits the digit at place idx in the card number
                digits.remove((Character) number.charAt(idx));
                //get a random digit from the remaining digits
                i = random.nextInt(digits.size());
                sb.append((char) digits.get(i) - '0');
                sum += digits.get(i) - '0';
                //add the missing digit
                digits.add(number.charAt(idx));
            }
            //get the last 4 digits of the token
            for (int idx = 12; idx < 16; idx++) {
                sb.append(number.charAt(idx));
            }
            token = sb.toString();
        } while (tokens.keySet().contains(token) && sum % 10 != 0);
        tokens.put(token, number);
        saveTokens(tokenFileName);

        return token;
    }

    @Override
    public String detokenize(String token) throws RemoteException, InvallidTokenException {
        token = token.replace("[\\s]", "");
        if(tokens.keySet().contains(token))
            return tokens.get(token);
        throw new InvallidTokenException();
    }

    public static Boolean isCorrect(String creditCard) {
        if (creditCard.length() != 16) {
            return false;
        }
        //convert the string to char[int] with the digits of the number
        char[] d = creditCard.toCharArray();
        int[] digits = new int[d.length];
        for (int i = 0; i < digits.length; i++) {
            digits[i] = d[i] - '0';
        }

        if (digits[0] != 3 && digits[0] != 4 && digits[0] != 5 && digits[0] != 6) {
            return false;
        }
        
        //calculate the Luhn formula 
        int j = 1;
        int sum = 0;
        for (int i = digits.length - 1; i >= 0; i--) {
            int digit = digits[i];
            if (j % 2 == 0) {
                digit *= 2;
            }
            if (digit > 9) {
                sum += digit % 10 + 1;
            } else {
                sum += digit;
            }
            j++;
        }
        return sum % 10 == 0;
    }

    private void loadAccounts(String filename) {
        //read every object from the xml file and add it to the accounts set
        ObjectInputStream in = null;
        try {
            in = xstream.createObjectInputStream(new FileInputStream(filename));
            while (true) {
                try {
                    Account acc = (Account) in.readObject();
                    accounts.add(acc);
                } catch (ClassNotFoundException ex) {
                    System.out.println("ClassNotFoundException: " + ex);
                }
            }

        } catch (EOFException eof) {

        } catch (IOException io) {
            System.out.println("IOException" + io);
        } finally {
            try {
                in.close();
            } catch (IOException ex) {
                System.out.println("IOException" + ex);
            }
        }

    }

    private void saveAccounts(String filename) {
        //iterate through every account in accounts and write it to the xml file
        
        ObjectOutputStream out = null;
        try {
            out = xstream.createObjectOutputStream(new FileOutputStream(filename));
            Iterator<Account> iter = accounts.iterator();
            while (iter.hasNext()) {
                out.writeObject(iter.next());
            }
        } catch (IOException io) {
            System.out.println("IOException" + io);

        } finally {
            try {
                out.close();
            } catch (IOException ex) {
                System.out.println("IOException" + ex);
            }
        }
    }

    private void loadTokens(String filename) {
        //read every object from the xml file and add it to tokens map
        ObjectInputStream in = null;
        try {
            in = xstream.createObjectInputStream(new FileInputStream(filename));
            while (true) {
                try {
                    Token token = (Token) in.readObject();
                    tokens.put(token.getToken(), token.getNumber());
                } catch (ClassNotFoundException ex) {
                    System.out.println("ClassNotFoundException");
                }
            }
        } catch (EOFException eof) {

        } catch (IOException io) {
            System.out.println("IOException" + io);
        } finally {
            try {
                in.close();
            } catch (IOException ex) {
                System.out.println("IOException" + ex);
            }
        }
    }

    private void saveTokens(String filename) {
        //iterate through every entry of tokens and write them to the xml file

        ObjectOutputStream out = null;
        try {
            out = xstream.createObjectOutputStream(new FileOutputStream(filename));
            Iterator<Map.Entry<String, String>> iter = tokens.entrySet().iterator();
            while (iter.hasNext()) {
                Map.Entry<String, String> entry = iter.next();
                Token token = new Token(entry.getValue(), entry.getKey());
                out.writeObject(token);
            }
        } catch (IOException io) {
            System.out.println("IOException");

        } finally {
            try {
                out.close();
            } catch (IOException ex) {
                System.out.println("IOException");
            }
        }
    }

    @Override
    public Boolean addAccount(String username, String password, int rights) throws RemoteException {
        final Account acc = new Account(username, password, rights);
        //if there exists an account with the same username return false
        if (!accounts.stream().noneMatch((a) -> (a.getUsername().equals(acc.getUsername())))) {
            return false;
        }
        accounts.add(new Account(username, password, rights));
        saveAccounts(accFileName);
        return true;

    }

    @Override

    public int login(String username, String password) throws RemoteException {
        Iterator<Account> iter = accounts.iterator();
        while (iter.hasNext()) {
            Account acc = iter.next();
            if (acc.getUsername().equals(username) && acc.getPassword().equals(password)) {
                return acc.getRights();
            }
        }
        return 0;
    }

    @Override
    public void TokensToFile(String file) throws RemoteException {
        try (Formatter out = new Formatter(file)) {
            Iterator<Map.Entry<String, String>> iter = tokens.entrySet().iterator();
            while (iter.hasNext()) {
                Map.Entry<String, String> entry = iter.next();
                out.format("%s\t%s\n", entry.getKey(), entry.getValue());
            }
        } catch (FileNotFoundException ex) {
            System.out.println("FileNotFoundException");
        }
    }

    @Override
    public void NumberstoFile(String file) throws RemoteException {
        try (final Formatter out = new Formatter(file)) {
            Set<Map.Entry<String, String>> set = tokens.entrySet();
            set.stream().sorted(Comparator.comparing(entry -> entry.getValue())).forEach(entry -> out.format("%s\t%s\n", entry.getValue(), entry.getKey()));
        } catch (FileNotFoundException ex) {
            System.out.println("FileNotFoundException");
        }

    }

    public static void main(String[] args) throws RemoteException, UnknownHostException {

        try {
            ServerInterface obj = new RMIServer(33333);
            Registry registry = LocateRegistry.createRegistry(33333);
            registry.rebind("rmiServer", obj);
            System.out.println("RMI server " + obj + " registered");
        } catch (Exception ex) {
            System.out.println("Exception: " + ex);
        }

    }

}

class Token {

    private final String number;
    private final String token;

    public Token(String number, String token) {
        this.number = number;
        this.token = token;
    }

    public String getNumber() {
        return number;
    }

    public String getToken() {
        return token;
    }

}
