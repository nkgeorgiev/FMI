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
public class InvallidTokenException extends Exception {

    /**
     * Creates a new instance of <code>InvallidTokenException</code> without
     * detail message.
     */
    public InvallidTokenException() {
    }

    /**
     * Constructs an instance of <code>InvallidTokenException</code> with the
     * specified detail message.
     *
     * @param msg the detail message.
     */
    public InvallidTokenException(String msg) {
        super(msg);
    }

    public InvallidTokenException(String message, Throwable cause) {
        super(message, cause);
    }

    public InvallidTokenException(Throwable cause) {
        super(cause);
    }

    public InvallidTokenException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
    
}
