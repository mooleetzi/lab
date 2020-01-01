package exception;

public class NotLoginException extends Exception {
    @Override
    public String toString() {
        return "Please login first.";
    }
}
