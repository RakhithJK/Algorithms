/**
 * Created by Gabrijel Boduljak on 11/19/2016.
 */

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class BruteCollinearPoints {
    public BruteCollinearPoints(Point[] points) {
        if(points == null)
            throw new NullPointerException();
        ensureAllPointsAreNotNull(points);
        ensureAllPointsAreDifferent(points);

        Point[] pointsCopy = Arrays.copyOf(points, points.length);
        segmentList        = new ArrayList<>();

        Arrays.sort(pointsCopy);

        for (int p = 0; p < pointsCopy.length; p++)
        {
            for (int q = p + 1; q < pointsCopy.length; q++)
            {
                for (int r = q + 1; r < pointsCopy.length; r++)
                {
                    for(int s = r + 1; s < pointsCopy.length; s++){
                        double slopeToQ = pointsCopy[p].slopeTo(pointsCopy[q]);
                        double slopeToR = pointsCopy[p].slopeTo(pointsCopy[r]);
                        double slopeToS = pointsCopy[p].slopeTo(pointsCopy[s]);

                        if(slopeToQ == slopeToR && slopeToQ == slopeToS)
                            segmentList.add(new LineSegment(pointsCopy[p], pointsCopy[s]));
                    }
                }
            }
        }
    }

    private ArrayList<LineSegment>  segmentList;

    public int           numberOfSegments() { return segmentList.size(); }
    public LineSegment[] segments()         { return segmentList.toArray(new LineSegment[segmentList.size()]); }

    private void ensureAllPointsAreNotNull(Point[] points) {
        for (int i = 0; i < points.length; i++) {
            if(points[i] == null)
                throw new NullPointerException();
        }
    }
    private void ensureAllPointsAreDifferent(Point[] points) {
        for (int i = 0; i < points.length; i++)
            for (int j = i + 1; j < points.length; j++)
                if(points[i].slopeTo(points[j]) == Double.NEGATIVE_INFINITY)
                    throw new IllegalArgumentException();
    }
}