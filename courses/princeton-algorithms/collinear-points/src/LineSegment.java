/**
 * Created by Gabrijel Boduljak on 11/19/2016.
 */
public class LineSegment {

    public LineSegment(Point p, Point q) {
        if (p == null || q == null) {
            throw new NullPointerException("argument is null");
        }
        this.p = p;
        this.q = q;
    }

    private final Point p;
    private final Point q;

    public void draw() {
        p.drawTo(q);
    }

    public String toString() {
        return p + " -> " + q;
    }

    public int hashCode() {
        throw new UnsupportedOperationException();
    }
}