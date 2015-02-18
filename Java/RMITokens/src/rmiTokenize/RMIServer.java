/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package rmiTokenize;

import com.sun.javafx.scene.control.skin.VirtualFlow;
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
import java.util.logging.Level;
import java.util.logging.Logger;
import sun.rmi.runtime.Log;

/**
 *
 * @author nikolay
 */
public class RMIServer extends UnicastRemoteObject implements ServerInterface {

    //k: tokens v: bank number
    private final HashSet<Account> accounts;
    private final XStream xstream = new XStream(new StaxDriver());

    private final SortedMap<String, String> tokens;
    private static final Random random = new Random();

    public RMIServer() throws RemoteException {
        super();
        tokens = new TreeMap<>();
        accounts = new HashSet<>();

    }

    public RMIServer(String AccFile, String tokenFile) throws RemoteException {
        super();
        tokens = new TreeMap<>();
        accounts = new HashSet<>();
        loadAccounts(AccFile);
        loadTokens(tokenFile);


    }

    public RMIServer(String AccFile, String tokenFile, int port) throws RemoteException {
        super(port);
        tokens = new TreeMap<>();
        accounts = new HashSet<>();
        loadAccounts(AccFile);
        loadTokens(tokenFile);

    }

    @Override
    public String tokenize(String number) throws RemoteException {
        number = number.replaceAll("[\\s]", "");
        if (!isCorrect(number) || tokens.containsKey(number)) {
            System.out.println("gyz");
            return null;
        }
        String token = "";
        //tokens.put(text, text);
        System.out.println(number);
        ArrayList<Character> digits = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            digits.add((char) ('0' + i));
            //System.out.println(digits.get(i));
        }
        int sum;
        do {
            StringBuilder sb = new StringBuilder();
            sum = 0;
            digits.removeIf(ch -> ch == '3' || ch == '4' || ch == '5' || ch == '6');
            int i = random.nextInt(digits.size());
            sb.append(digits.get(i) - '0');
            sum += (char) digits.get(i) - '0';
            digits.add('3');
            digits.add('4');
            digits.add('5');
            digits.add('6');
            for (int idx = 1; idx < 12; idx++) {

                digits.remove((Character) number.charAt(idx));
                i = random.nextInt(digits.size());
                sb.append((char) digits.get(i) - '0');
                sum += digits.get(i) - '0';
                digits.add(number.charAt(idx));
            }
            for (int idx = 12; idx < 16; idx++) {
                sb.append(number.charAt(idx));
            }
            token = sb.toString();
        } while (tokens.keySet().contains(token) && sum % 10 != 0);
        tokens.put(token, number);
        System.out.println(token);
        return token;
    }

    @Override
    public String detokenize(String token) throws RemoteException {
        //todo
        return tokens.get(token);
    }

    public static Boolean isCorrect(String creditCard) {
        if (creditCard.length() != 16) {
            return false;
        }
        char[] d = creditCard.toCharArray();
        int[] digits = new int[d.length];
        for (int i = 0; i < digits.length; i++) {
            digits[i] = d[i] - '0';
        }

        if (digits[0] != 3 && digits[0] != 4 && digits[0] != 5 && digits[0] != 6) {
            return false;
        }

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
        ObjectInputStream in = null;
        try {
            in = xstream.createObjectInputStream(new FileInputStream(filename));
            while (true) {
                try {
                    Account acc = (Account) in.readObject();
                    accounts.add(acc);
                } catch (ClassNotFoundException ex) {
                    Logger.getLogger(Login.class.getName()).log(Level.SEVERE, null, ex);
                }
            }

        } catch (EOFException eof) {

        } catch (IOException io) {
            System.out.println("IOException");
        } finally {
            try {
                in.close();
            } catch (IOException ex) {
                System.out.println("IOException");
            }
        }

    }

    private void saveAccounts(String filename) {
        ObjectOutputStream out = null;
        try {
            out = xstream.createObjectOutputStream(new FileOutputStream(filename));
            Iterator<Account> iter = accounts.iterator();
            while (iter.hasNext()) {
                out.writeObject(iter.next());
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

    private void loadTokens(String filename) {
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
            System.out.println("IOException");
        } finally {
            try {
                in.close();
            } catch (IOException ex) {
                System.out.println("IOException");
            }
        }
    }

    private void saveTokens(String filename) {
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

    public void addAccount(String username, String password, int rights) {
        accounts.add(new Account(username, password, rights));

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

    public void TokensToFile(String file) {
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

    public void NumberstoFile(String file) {
        try (final Formatter out = new Formatter(file)) {
            Set<Map.Entry<String, String>> set = tokens.entrySet();
            set.stream().sorted(Comparator.comparing(entry -> entry.getValue())).forEach(entry -> out.format("%s\t%s\n", entry.getValue(), entry.getKey()));
        } catch (FileNotFoundException ex) {
            System.out.println("FileNotFoundException");
        }

    }

    public static void main(String[] args) throws RemoteException, UnknownHostException {
//        RMIServer rmi = new RMIServer("accTest.xml", "tokenTest.xml");
//        rmi.tokenize("3400 0799 2739 8713");
//        rmi.addAccount("admin", "admin", 3);
//        rmi.addAccount("nikolay", "pass", 2);
//        System.out.println(rmi.detokenize("2952562339528713"));
//        System.out.println(rmi.login("admin", "admin"));
//        System.out.println(rmi.login("", ""));
//        rmi.NumberstoFile("test.txt");
//        //rmi.saveAccounts("accTest.xml");
//        //rmi.saveTokens("tokenTest.xml");
//        try {
//      StudentServerInterface obj = new Student3TierImpl();
//      Registry registry = LocateRegistry.getRegistry();
//      registry.rebind("StudentServerInterfaceImpl", obj);
//      System.out.println("Student server " + obj + " registered");
//    } catch (Exception ex) {
//      ex.printStackTrace();
//    }
        String hostname = InetAddress.getLocalHost().getHostAddress();
        System.out.println("this host IP is " + hostname);
         //System.setProperty("java.rmi.server.hostname", hostname); 
        try {
            ServerInterface obj = new RMIServer("accTest.xml", "tokenTest.xml", 33333);
            Registry registry = LocateRegistry.createRegistry(33333);
            registry.rebind("rmiServer", obj);
            System.out.println("RMI server " + obj + " registered");
        } catch (Exception ex) {
            ex.printStackTrace();
        }

        System.out.println("asdada");

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
