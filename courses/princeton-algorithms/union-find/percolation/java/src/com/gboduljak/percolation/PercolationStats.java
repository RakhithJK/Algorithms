import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;

public class PercolationStats {

    public PercolationStats(int n, int trials) {

        if (n <= 0 || trials <= 0) {
            throw new IllegalArgumentException();
        }

        experimentsCount = trials;
        fractions        = new double[experimentsCount];

        for (int experimentId = 0; experimentId < experimentsCount; experimentId++) {
            percolation = new Percolation(n);
            int openedSites = 0;
            while (!percolation.percolates()) {
                int randomSiteRow    = StdRandom.uniform(1, n + 1);
                int randomSiteColumn = StdRandom.uniform(1, n + 1);

                if (!percolation.isOpen(randomSiteRow, randomSiteColumn)) {
                    percolation.open(randomSiteRow, randomSiteColumn);
                    openedSites++;
                }
            }
            double fraction = (double) openedSites / (n * n);
            fractions[experimentId] = fraction;
        }
    }

    public double mean() {
        return StdStats.mean(fractions);
    }

    public double stddev() {
        return StdStats.stddev(fractions);
    }

    public double confidenceLo() {
        return mean() - ((1.96 * stddev()) / Math.sqrt(experimentsCount));
    }

    public double confidenceHi() {
        return mean() + ((1.96 * stddev()) / Math.sqrt(experimentsCount));
    }

    public static void main(String[] args) {
        int n                             = Integer.parseInt(args[0]);
        int trials                        = Integer.parseInt(args[1]);
        PercolationStats percolationStats = new PercolationStats(n, trials);

        String confidence = percolationStats.confidenceLo() + ", " + percolationStats.confidenceHi();
        StdOut.println("mean                    = " + percolationStats.mean());
        StdOut.println("stddev                  = " + percolationStats.stddev());
        StdOut.println("95% confidence interval = " + confidence);
    }

    private int         experimentsCount;
    private double[]    fractions;
    private Percolation percolation;
}