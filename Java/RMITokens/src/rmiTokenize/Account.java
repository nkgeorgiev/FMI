/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package rmiTokenize;

/**
 *
 * @author nikolay
 */
public class Account {
    String username;
    String password;
    int rights;

    public Account(String username, String password, int rights) {
        this.username = username;
        this.password = password;
        this.rights = rights;
    }
    
    public Account(){
        this("admin","admin",2);
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }

    public int getRights() {
        return rights;
    }
    
    
}
