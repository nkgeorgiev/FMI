/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package rmiTokenize;

import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.StaxDriver;
/**
 *
 * @author nikolay
 */
public class zcxzczx {
//    public static void main(String[] args) {
//        XStream xstream = new XStream(new StaxDriver()); 
//        xstream.alias("person", Person.class);
//        xstream.alias("phonenumber", PhoneNumber.class);
//        Person joe = new Person("Joe", "Walnes",new PhoneNumber(123, "1234-456"), new PhoneNumber(123, "9999-999"));
//        String xml = xstream.toXML(joe);
//        System.out.println(xml);
//        Person newJoe = (Person)xstream.fromXML(xml);
//        
//    
//    }
}

class Person {
  private String firstname;
  private String lastname;
  private PhoneNumber phone;
  private PhoneNumber fax;
  // ... constructors and methods

    public Person(String firstname, String lastname, PhoneNumber phone, PhoneNumber fax) {
        this.firstname = firstname;
        this.lastname = lastname;
        this.phone = phone;
        this.fax = fax;
    }
}

class PhoneNumber {
  private int code;
  private String number;
  // ... constructors and methods

    public PhoneNumber(int code, String number) {
        this.code = code;
        this.number = number;
    }


}