package service;

import org.springframework.stereotype.Component;


public class CalServiceImpl implements CalService {
    @Override
    public double plus(double a, double b) {
        System.out.println("执行加法");
        return a+b;
    }

    @Override
    public double sub(double a, double b) {
        System.out.println("执行减法");
        return a-b;
    }
}
