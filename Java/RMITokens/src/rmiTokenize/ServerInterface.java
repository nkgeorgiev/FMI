/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package rmiTokenize;

import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 *
 * @author nikolay
 */
public interface ServerInterface extends Remote {
    public String tokenize(String number) throws RemoteException, InvallidTokenException;
    public String detokenize(String token)  throws RemoteException, InvallidTokenException;  
    public int login(String username, String password) throws RemoteException;
    public void TokensToFile(String file) throws RemoteException;
    public void NumberstoFile(String file) throws RemoteException;
    public Boolean addAccount(String username, String password, int rights) throws RemoteException;
}
