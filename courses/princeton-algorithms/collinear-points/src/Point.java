/**
 * Created by Gabrijel Boduljak on 11/19/2016.
 */

import java.util.Comparator;
import edu.princeton.cs.algs4.StdDraw;

public class Point implements Comparable<Point> {

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    private class PointsComparator implements Comparator<Point>
    {
        @Override
        public int compare(Point point1, Point point2) {
            double slopeBetweenPoint1AndThis = slopeTo(point1);
            double slopeBetweenPoint2AndThis = slopeTo(point2);
            if(slopeBetweenPoint1AndThis == slopeBetweenPoint2AndThis)
                return 0;
            else if(slopeBetweenPoint1AndThis < slopeBetweenPoint2AndThis)
                return -1;
            else
                return 1;
        }
    }

    private final int x;
    private final int y;

    public void draw() {
        StdDraw.point(x, y);
    }

    public void drawTo(Point that) {
        StdDraw.line(this.x, this.y, that.x, that.y);
    }

    public double slopeTo(Point that) {
        if (that == null) {
            throw new NullPointerException();
        }
        if(that.x == this.x && that.y == this.y)
            return Double.NEGATIVE_INFINITY;
        if(that.x == this.x)
            return Double.POSITIVE_INFINITY;
        if(that.y == this.y)
            return +0.0;

        return (double) (that.y - this.y) / (that.x - this.x);
    }

    public int compareTo(Point that) {
        if(this.y < that.y || (this.x < that.x && this.y == that.y))
            return -1;
        else if(slopeTo(that) == Double.NEGATIVE_INFINITY)
            return 0;
        else
            return 1;
    }

    public Comparator<Point> slopeOrder() {
        return new PointsComparator();
    }

    public String toString() {
        return "(" + x + ", " + y + ")";
    }
}