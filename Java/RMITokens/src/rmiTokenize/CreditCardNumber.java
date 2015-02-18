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
public class CreditCardNumber {
    private String number;
    private int numCrypt;
    private String encryptedNumber;

    public CreditCardNumber(String number) {
        this.number = number;
        numCrypt = 0;
        encryptedNumber = "";
    }

    public String getNumber() {
        return number;
    }

    public int getNumCrypt() {
        return numCrypt;
    }

    public String getEncryptedNumber() {
        return encryptedNumber;
    }

    public void setEncryptedNumber(String encryptedNumber) {
        this.encryptedNumber = encryptedNumber;
    }
    
    public void incNumCrypt(){
        numCrypt++;
    }
    
    public void decNumCrypt(){
        numCrypt--;
    }
    
    
    
    
}
