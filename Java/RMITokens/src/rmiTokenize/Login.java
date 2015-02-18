/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package rmiTokenize;

import com.thoughtworks.xstream.*;
import com.thoughtworks.xstream.io.xml.StaxDriver;
import java.io.EOFException;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author nikolay
 */
public class Login extends UnicastRemoteObject implements LoginInterface {

    private HashSet<Account> accounts;
    private final XStream xstream = new XStream(new StaxDriver());

    public Login() throws RemoteException {
        super();
        accounts = new HashSet();
    }

    public Login(String filename) throws RemoteException {
        super();
        accounts = new HashSet();
        load(filename);
    }

    public Login(int port) throws RemoteException {
        super(port);
    }

    private void load(String filename) {
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
            Logger.getLogger(Login.class.getName()).log(Level.SEVERE, null, io);

        } finally {
            try {
                in.close();
            } catch (IOException ex) {
                Logger.getLogger(Login.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

    }

    private void save(String filename) {
        ObjectOutputStream out = null;
        try {
            out = xstream.createObjectOutputStream(new FileOutputStream(filename));
            Iterator<Account> iter = accounts.iterator();
            while (iter.hasNext()) {
                out.writeObject(iter.next());
            }
        } catch (IOException io) {
        } finally {
            try {
                out.close();
            } catch (IOException ex) {
                Logger.getLogger(Login.class.getName()).log(Level.SEVERE, null, ex);
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

    @Override
    public Boolean logout() throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    public static void main(String[] args) throws RemoteException {
        System.out.println("ffs");
        Login login = new Login("test");
        //login.addAccount("admin", "admin", 3);
        //login.addAccount("nikolay", "pass", 2);
        login.save("test");
        System.out.println(login.login("admin", "admin"));
        System.out.println(login.login("", ""));
    }

}
