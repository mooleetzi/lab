//package com.demo_1.action;
import com.opensymphony.xwork2.ActionSupport;

public class Helloworld extends ActionSupport {
    private String message;
    @Override
    public String execute() throws Exception {
        message="hello world";
        return SUCCESS;
    }

    public String getMessage() {
        return message;
    }
}
