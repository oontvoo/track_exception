public class TestNPE {
    public static void main(String[] args) {
        int n = 0;
        String st = null;

        System.out.println("about to throw NPE");
        if (n >= 0 && st.isEmpty()){
            System.out.println("empty");
        }
        else {
            System.out.println("othereise");
        }
    }
    
}
