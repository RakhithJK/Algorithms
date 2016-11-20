import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;

import java.util.*;

/**
 * Created by Gabrijel Boduljak on 11/20/2016.
 */

public class FastCollinearPoints {

    public FastCollinearPoints(Point[] points) {

        if(points == null)
            throw new NullPointerException();

        ensureAllPointsAreNotNull(points);
        ensureAllPointsAreDifferent(points);

        Point[] pointsCopy = Arrays.copyOf(points, points.length);
        Arrays.sort(pointsCopy);

        for (Point startPoint : points) {
            Arrays.sort(pointsCopy, startPoint.slopeOrder());

            double      currentSlope             = 0;
            SortedSet<Point> currentSlopePoints  = new TreeSet<>();
            double      previousSlope = Double.NEGATIVE_INFINITY;

            for (int i = 0; i < pointsCopy.length; i++) {
                currentSlope = startPoint.slopeTo(pointsCopy[i]);

                if (currentSlope == previousSlope) {
                    currentSlopePoints.add(pointsCopy[i]);
                } else {
                    if (currentSlopePoints.size() >= 3) {
                        currentSlopePoints.add(startPoint);
                        saveCollinearPointsIfNew(previousSlope, currentSlopePoints);
                    }
                    currentSlopePoints.clear();
                    currentSlopePoints.add(pointsCopy[i]);
                }
                previousSlope = currentSlope;
            }

            if (currentSlopePoints.size() >= 3) {
                currentSlopePoints.add(startPoint);
                saveCollinearPointsIfNew(currentSlope, currentSlopePoints);
            }
        }
    }

    private HashMap<Double, SortedSet<Point>> foundCollinearPoints = new HashMap<>();
    private List<LineSegment>            foundSegments        = new ArrayList<>();

    public int           numberOfSegments()   { return foundSegments.size(); }
    public LineSegment[] segments()           { return foundSegments.toArray(new LineSegment[foundSegments.size()]); }

    private void saveCollinearPointsIfNew(double slope, SortedSet<Point> collinearPoints) {
        SortedSet<Point> previouslyFoundCollinearPoints = foundCollinearPoints.get(slope);

        Point startPoint = collinearPoints.first();
        Point endPoint   = collinearPoints.last();

        if (previouslyFoundCollinearPoints == null) {
            previouslyFoundCollinearPoints = new TreeSet<>();
            previouslyFoundCollinearPoints.add(endPoint);
            foundCollinearPoints.put(slope, previouslyFoundCollinearPoints);
            foundSegments.add(new LineSegment(startPoint, endPoint));
        } else {
            for (Point currentEndPoint : previouslyFoundCollinearPoints) {
                if (currentEndPoint.compareTo(endPoint) == 0) {
                    return;
                }
            }
            previouslyFoundCollinearPoints.add(endPoint);
            foundSegments.add(new LineSegment(startPoint, endPoint));
        }
    }

    private void ensureAllPointsAreNotNull(Point[] points) {
        for (int i = 0; i < points.length; i++) {
            if(points[i] == null)
                throw new NullPointerException();
        }
    }
    private void ensureAllPointsAreDifferent(Point[] points) {
        for (int i = 0; i < points.length; i++)
            for (int j = i + 1; j < points.length; j++)
                if (points[i].slopeTo(points[j]) == Double.NEGATIVE_INFINITY)
                    throw new IllegalArgumentException();
    }

    public static void main(String[] args) {
        In in = new In(args[0]);
        int n = in.readInt();
        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            int x = in.readInt();
            int y = in.readInt();
            points[i] = new Point(x, y);
        }
        StdDraw.enableDoubleBuffering();
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);
        for (Point p : points) {
            p.draw();
        }
        StdDraw.show();

        FastCollinearPoints collinear = new FastCollinearPoints(points);
        for (LineSegment segment : collinear.segments()) {
            StdOut.println(segment);
            segment.draw();
        }
        StdDraw.show();
    }
}