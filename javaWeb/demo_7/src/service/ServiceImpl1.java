package service;

public class ServiceImpl implements Service {
    @Override
    public double plus(double a, double b) {
        return a+b;
    }

    @Override
    public double sub(double a, double b) {
        return a-b;
    }
}
